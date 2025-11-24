/**
* * Instance.cpp - Arquivo referente a implementacao da classe Management.h
* 
* * Autor(es): Quezia Emanuelly e Victor Araujo
* * Projeto: Trabalho Pratico 1 - Inteligencia Computacional
* * Organizacao: Universidade Federal de Juiz de Fora
* * Departamento: Dep. Ciencia da Computacao 
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

#include "random.hpp"
#include "Management.h"


Management::Management(std::string fileInstance)
{
    this->instance = new Instance(fileInstance);
}

Management::~Management()
{

}

void Management::initInstance()
{
    try {
        this->instance->readInstance();
    } catch(std::ios_base::failure& e) {
        throw std::ios_base::failure(e);
    }
}

void Management::calcSolution()
{
    std::vector<Job*> solutionOptimum;
    double bestMakespan = std::numeric_limits<double>::infinity();
    int numIteracoes = 10;
    double somaTime = 0;
    double somaMakespan = 0;

    double alfa = 0.09;

    std::ofstream ofs;
    ofs.exceptions(std::ios_base::badbit);

    try {

        ofs.open(this->instance->pathSolution+this->instance->getFileName(), std::ios_base::out | std::ios_base::trunc);
        if(!ofs.is_open()) throw std::ios_base::failure("Erro ao abrir o arquivo de saida, para escrita da solucao");

        ofs << " * Resultados Obtidos nas " << numIteracoes << " Iteracoes: " << std::endl << std::endl;

        std::cout << "Gerando Solucao..." << std::endl;
    
        for(int i = 0; i < numIteracoes; i++) {
            auto inicio = std::chrono::high_resolution_clock::now();
            
            auto solutionInit = constructive(alfa);
            auto solutionLocalSearch = localSearch(solutionInit.first);
            
            auto fim = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duracao = fim - inicio;

            solutionLocalSearch.second.push_back(alfa);
            solutionLocalSearch.second.push_back(duracao.count());
            
            this->instance->writeFileSolution(ofs,solutionLocalSearch,i);
            
            somaTime += duracao.count();
            somaMakespan += solutionLocalSearch.second[0];
        
            if(solutionLocalSearch.second[0] < bestMakespan) {
                bestMakespan = solutionLocalSearch.second[0];
                solutionOptimum = solutionLocalSearch.first;
            }
        }

        ofs << std::endl;
        ofs << " --> Melhor Makespan Obtido: " << static_cast<int>(bestMakespan) << std::endl; // escreve no arquivo
        ofs << " --> Media dos Makespans Obtidos: " << somaMakespan/numIteracoes << std::endl; // escreve no arquivo
        ofs << " --> Media da Duracao Total das Iteracoes: " << static_cast<double>(somaTime)/numIteracoes << "s" << std::endl; //escreve no arquivo
       
        ofs.close();

        std::cout << "Arquivo gerado em \\saidas com os valores da solucao!!" << std::endl;
    
    } catch(std::ios_base::failure& e) {
        throw std::ios_base::failure("Erro escrita do arquivo de saida");
    }

}

std::pair<std::vector<Job*>, int> Management::constructive(double alfa)
{
    // double alfa = 0.1;
    int quantJobs = 0;
    int index = 0;
    std::vector<Job*> solution;
    
    this->instance->resetInstance();
    
    std::vector<Job*> listCandidates = getCandidatesList(solution);

    while(listCandidates.size() != 0) {
        std::sort(listCandidates.begin(), listCandidates.end(), [](Job* job1, Job* job2){
            return job1->getInitTimeAux() < job2->getInitTimeAux();
        });
        int index = prng::get_int(0,static_cast<int>((listCandidates.size()-1)*alfa));
        listCandidates[index]->setEndTime(listCandidates[index]->getInitTimeAux()+listCandidates[index]->getProcessingTime());

        solution.push_back(listCandidates[index]);
        quantJobs++;
        listCandidates.erase(listCandidates.begin() + index);
        listCandidates = getCandidatesList(solution);
    }

    int makespan = objectiveFunction(solution);
    return std::make_pair(std::vector<Job*>(solution.begin(), solution.end()), makespan);

}

std::pair<std::vector<Job*>, std::vector<double>> Management::localSearch(std::vector<Job*> solutionInit)
{
    std::vector<Job*> solutionOptimum = solutionInit;
    std::vector<Job*> s = solutionInit;
    int optimum_obj_func = objectiveFunction(solutionOptimum);
    int obj_func = 0;
    bool better_solution = false;

    while (true) {
        better_solution = false;
        auto size = solutionOptimum.size();
        int x = prng::get_int(0,static_cast<int>((solutionInit.size()-1)));
        for (int i = x; i < size - 1; ++i) {
            for (int j = 0; j < size; ++j) {
                if( i != j) {
                    s = swap(solutionOptimum, i, j);
                    obj_func = objectiveFunction(s);
                    if (obj_func < optimum_obj_func) {
                        solutionOptimum = s;
                        optimum_obj_func = obj_func;
                        better_solution = true;
                    }
                }
            }
        }
        if (!better_solution) {
            break;
        }
    }

    std::vector<double> makespan;
    makespan.push_back(objectiveFunction(solutionOptimum));
    return std::make_pair(std::vector<Job*>(solutionOptimum.begin(), solutionOptimum.end()), makespan);
}

std::vector<Job*> Management::swap(std::vector<Job*> solution, int indexJob1, int indexJob2)
{
    if(!verifySucessor(solution,indexJob1,indexJob2) && !verifyPredecessor(solution,indexJob1,indexJob2)) {
        Job* jobAux = solution[indexJob1];
        solution[indexJob1] = solution[indexJob2];
        solution[indexJob2] = jobAux;
    }

    return solution;
}

int Management::objectiveFunction(std::vector<Job*>& jobs)
{
    auto n = jobs.size();
    if (n == 0) {
        return 0;
    }
    auto r = 0;
    auto b = 0;
    auto c = 0;
    auto es = std::vector<int>(n, 0);
    auto d = this->instance->getDelayConstraints();
    auto s = this->instance->getSetupTimes();
    while (r < n) {
        c = b + jobs[r]->getProcessingTime();
        if (r == n - 1) {
            return c;
        }
        auto i = jobs[r]->getId();
        for (auto j = 0; j < n; ++j) {
            if (d[i][j] != -1) {
                es[j] = std::max(es[j], c + d[i][j]);
            }
        }
        r += 1;
        b = std::max(c + s[i][jobs[r]->getId()], es[jobs[r]->getId()]);
    }
    return c;

}

std::vector<Job*> Management::getCandidatesList(std::vector<Job*>& solution)
{
    std::vector<Job*> candidates;
    Job* sol;
    Job* atual;
    int setup = 0;
    int delay = 0;
    int maior = 0;
    bool isCandidate;

    auto numJobs = this->instance->getNumJobs();
    auto delayConstraints = this->instance->getDelayConstraints();
    auto setupTimes = this->instance->getSetupTimes();
    auto jobs = this->instance->getJobs();

    for(int i = 0; i < numJobs; i++) {
        isCandidate = true;
        if(!findJob(solution,i)) {
            for(int j = 0; j < numJobs; j++) {
                if(delayConstraints[j][i] != -1 && !findJob(solution,j)) {
                    isCandidate = false;
                }
            }
            if(isCandidate) {
                candidates.push_back(jobs[i]);
                if(solution.size() > 0) {
                    sol = solution[solution.size()-1];
                    atual = jobs[i];
                    setup = setupTimes[sol->getId()][atual->getId()];
                    delay = delayConstraints[sol->getId()][atual->getId()];
                    maior = setup >= delay ? setup : delay;
                    if(sol->getEndTime()+maior > atual->getInitTime()) {
                        if(delay < 0) {
                            atual->setInitTime(sol->getEndTime());
                            atual->setInitTimeAux(sol->getEndTime() + setup);
                        } else {
                            atual->setInitTime(sol->getEndTime() + delay);
                            atual->setInitTimeAux(sol->getEndTime() + maior);
                        } 
                    } else {
                        atual->setInitTimeAux(atual->getInitTime());
                    }
                }
            } 
        }
    }

    return candidates;
}

bool Management::findJob(std::vector<Job*>& list, int idJob)
{
    for(Job* j : list) {
        if(j->getId() == idJob) return true;
    }

    return false;
}

bool Management::compare(Job* job1, Job* job2)
{
    return job1->getInitTimeAux() < job2->getInitTimeAux();
}

bool Management::verifySucessor(std::vector<Job*>& solution, int indexInit, int indexEnd)
{

    Job* job = solution[indexInit];

    for(int i = indexInit; i <= indexEnd; i++) {
        if(this->instance->getDelayConstraints()[job->getId()][solution[i]->getId()] != -1) {
            return true;
        }
    }
    return false;
}

bool Management::verifyPredecessor(std::vector<Job*>& solution, int indexInit, int indexEnd)
{

    Job* job = solution[indexEnd];

    for(int i = indexEnd; i >= indexInit; i--) {
        if(this->instance->getDelayConstraints()[solution[i]->getId()][job->getId()] != -1) {
            return true;
        }
    }
    return false;
}

