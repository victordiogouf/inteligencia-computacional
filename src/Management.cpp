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
    this->instance = new Instance();
}

Management::~Management()
{

}

void Management::initInstance(std::string file)
{
    try {
        this->instance->readInstance(file);
    } catch(std::ios_base::failure& e) {
        throw std::ios_base::failure(e);
    }
}

std::pair<std::vector<Job*>, int> Management::constructive()
{
    double alfa = 0.5;
    std::vector<Job*> solution;
    
    for(Job* job : this->instance->getJobs()) {
        job->setInitTime(0);
        job->setInitTimeAux(0);
        job->setEndTime(job->getProcessingTime());
    }
    
    std::vector<Job*> listCandidates = getCandidatesList(solution);

    while(listCandidates.size() != 0) {
        std::sort(listCandidates.begin(), listCandidates.end(), [](Job* job1, Job* job2){
            return job1->getInitTimeAux() < job2->getInitTimeAux();
        });
        int index = prng::get_int(0,static_cast<int>((listCandidates.size()-1)*alfa));
        listCandidates[index]->setEndTime(listCandidates[index]->getInitTimeAux()+listCandidates[index]->getProcessingTime());
        // std::cout << "endtime: " << listCandidates[index]->getEndTime() << std::endl;
        solution.push_back(listCandidates[index]);
        listCandidates.erase(listCandidates.begin() + index);
        listCandidates = getCandidatesList(solution);
    }

    int makespan = objectFunction(solution);
    return std::make_pair(std::vector<Job*>(solution.begin(), solution.end()), makespan);

}

std::vector<Job*> Management::localSearch(std::vector<Job*> solutionInit)
{
    std::vector<Job*> nada;
    return nada;
}

int Management::objectFunction(std::vector<Job*> jobs)
{
    auto n = jobs.size();
    if (n == 0) {
        return 0;
    }
    auto r = 0;
    auto b = 0;
    auto c = 0;
    auto es = std::vector<int>(n, 0);
    while (r < n) {
        c = b + jobs[r]->getProcessingTime();
        if (r == n - 1) {
            return c;
        }
        auto d = this->instance->getDelayConstraints();
        auto i = jobs[r]->getId();
        for (auto j = 0; j < n; ++j) {
            if (d[i][j] != -1) {
                es[j] = std::max(es[j], c + d[i][j]);
            }
        }
        r += 1;
        auto s = this->instance->getSetupTimes();
        b = std::max(c + s[i][jobs[r]->getId()], es[jobs[r]->getId()]);
    }
    return c;

}

std::vector<Job*> Management::getCandidatesList(std::vector<Job*> solution)
{
    std::vector<Job*> candidates;
    bool isCandidate;

    for(int i = 0; i < this->instance->getNumJobs(); i++) {
        isCandidate = true;
        if(!findJob(solution,i)) {
            for(int j = 0; j < this->instance->getNumJobs(); j++) {
                if(this->instance->getDelayConstraints()[j][i] != -1 && !findJob(solution,j)) {
                    isCandidate = false;
                }
            }
            if(isCandidate) {
                candidates.push_back(this->instance->getJobs()[i]);
                if(solution.size() > 0) {
                    Job* sol = solution[solution.size()-1];
                    Job* atual = this->instance->getJobs()[i];
                    int setup = this->instance->getSetupTimes()[sol->getId()][atual->getId()];
                    int delay = this->instance->getDelayConstraints()[sol->getId()][atual->getId()];
                    int maior = setup >= delay ? setup : delay;
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

bool Management::findJob(std::vector<Job*> list, int idJob)
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

