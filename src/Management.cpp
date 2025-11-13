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
    std::vector<Job*> solution;
    std::vector<Job*> listCandidates = getCandidatesList(solution);

    while(listCandidates.size() != 0) {
        // int index = prng::get_int(0,static_cast<int>((listCandidates.size()-1)));
        std::sort(listCandidates.begin(), listCandidates.end(), [](Job* job1, Job* job2){return job1->getInitTimeAux() < job2->getInitTimeAux();});
        solution.push_back(listCandidates[0]);
        listCandidates.erase(listCandidates.begin() + 0);
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
    int makespan = 0;
    int maior = 0;

    for(int i = 0; i < jobs.size(); i++) {
        if(i > 0) {
            if(this->instance->getSetupTimes()[jobs[i-1]->getId()][jobs[i]->getId()] >= this->instance->getDelayConstraints()[jobs[i-1]->getId()][jobs[i]->getId()]) {
                maior = this->instance->getSetupTimes()[jobs[i-1]->getId()][jobs[i]->getId()];
            } else {
                maior = this->instance->getDelayConstraints()[jobs[i-1]->getId()][jobs[i]->getId()];
            }
        }
        makespan += jobs[i]->getProcessingTime() + maior;
    }

    return makespan;
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

