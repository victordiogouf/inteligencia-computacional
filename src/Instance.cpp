/**
* * Instance.cpp - Arquivo referente a implementacao da classe Instance.h
* 
* * Autor(es): Quezia Emanuelly e Victor Araujo
* * Projeto: Trabalho Pratico 1 - Inteligencia Computacional
* * Organizacao: Universidade Federal de Juiz de Fora
* * Departamento: Dep. Ciencia da Computacao 
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string_view>

#include "Instance.h"

Instance::Instance()
{

}

Instance::~Instance()
{

}

int Instance::getNumJobs()
{
    return this->numJobs;
}

std::vector<Job*> Instance::getJobs()
{
    return this->jobs;
}

std::vector<std::vector<int>> Instance::getSetupTimes()
{
    return this->setupTimes;
}

std::vector<std::vector<int>> Instance::getDelayConstraints()
{
    return this->delayConstraints;
}

std::string Instance::getPath()
{
    return this->path;
}

void Instance::readInstance(std::string file)
{
    std::ifstream ifs;
    std::string line;

    ifs.exceptions(std::ios_base::badbit);

    try {

        ifs.open(path+file, std::ios_base::in);
        if(!ifs.is_open()) throw std::ios_base::failure("Erro ao abrir o arquivo, informe um arquivo dentro de /instances");

        while (std::getline(ifs, line)) {
            if (line.starts_with("R=")) {
                this->numJobs = std::stoi(line.substr(2));
                for(int i = 0; i < this->numJobs; i++) {
                    std::vector<int> vazio (this->numJobs, -1);
                    this->delayConstraints.push_back(vazio);
                }
            } else if (line.starts_with("Pi=")) {
                auto ss = std::stringstream{line.substr(4)};
                auto token = std::string{};
                while (std::getline(ss, token, ',')) {
                    Job* job = new Job(std::stoi(token));
                    this->jobs.push_back(job);
                    job->setId(this->jobs.size()-1);
                }
            } else if (line.starts_with("A=")) {
                while (std::getline(ifs, line)) {
                    if (line.starts_with("Sij=")) {
                    // Rewind one line for the next section
                        ifs.seekg(-static_cast<int>(line.length()) - 1, std::ios::cur);
                        break;
                    }
                    auto ss = std::stringstream{line};
                    auto token = std::string{};
                    auto token2 = std::string{};
                    auto valor = std::string{};
                    std::getline(ss, token, ',');
                    std::getline(ss, token2, ',');
                    std::getline(ss, valor, ',');
                    this->delayConstraints[std::stoi(token)][std::stoi(token2)] = std::stoi(valor);
                }
            } else if (line.starts_with("Sij=")) {
                while (std::getline(ifs, line)) {
                    auto ss = std::stringstream{line};
                    auto token = std::string{};
                    auto row = std::vector<int>{};
                    while (std::getline(ss, token, ',')) {
                        row.push_back(std::stoi(token));
                    }
                    this->setupTimes.push_back(row);
                }
            }
        }

        // std::cout << "Numero de Jobs: " << this->numJobs << std::endl;
        // std::cout << "Tempo de processamento de cada job: " << std::endl;
        // for(Job* job : this->jobs) {
        //     std::cout << job->getProcessingTime() << " ";
        // }

        // std::cout << std::endl;
        
        // std::cout << "Matriz de Precedencia: " << std::endl;
        // for(int i = 0; i < this->numJobs; i++) {
        //     for(int j = 0; j < this->numJobs; j++) {
        //         std::cout << this->delayConstraints[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }
        
        // std::cout << std::endl;

        // std::cout << "Tempo de setup: " << std::endl;
        // for(int i = 0; i < this->numJobs; i++) {
        //     for(int j = 0; j < this->numJobs; j++) {
        //         std::cout << this->setupTimes[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }

    } catch(std::ios_base::failure& e) {
        throw std::ios_base::failure("Erro leitura do arquivo");
    }
}