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

std::vector<Job*> Management::constructive()
{
    std::vector<Job*> solution;
    std::vector<Job*> listCandidates = getCandidatesList(solution);

    int index = prng::get_int(0,static_cast<int>(listCandidates.size()-1));

    solution.push_back(listCandidates[index]);

    std::cout << "lista de candidatos antes de tirar: " << std::endl;
    for(Job* job : listCandidates) {
        std::cout << job->getId() << " ";
    }
    std::cout << std::endl;

    listCandidates.erase(listCandidates.begin() + index);

    std::cout << "job selecionado: " << solution[0]->getId() << std::endl;
    std::cout << "lista de candidatos depois de tirar: " << std::endl;
    for(Job* job : listCandidates) {
        std::cout << job->getId() << " ";
    }

    std::cout << std::endl;

    listCandidates = getCandidatesList(solution);

    std::cout << "lista de candidatos depois de atualizar: " << std::endl;
    for(Job* job : listCandidates) {
        std::cout << job->getId() << " ";
    }

    std::cout << std::endl;




    return solution;

}

std::vector<Job*> Management::localSearch(std::vector<Job*> solutionInit)
{
    std::vector<Job*> nada;
    return nada;
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
            if(isCandidate) candidates.push_back(this->instance->getJobs()[i]);
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

