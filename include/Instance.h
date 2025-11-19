/**
* * Instance.h - Arquivo responsavel por gerenciar a instancia utilizada para teste do algoritmo
* 
* * Autor(es): Quezia Emanuelly e Victor Araujo
* * Projeto: Trabalho Pratico 1 - Inteligencia Computacional
* * Organizacao: Universidade Federal de Juiz de Fora
* * Departamento: Dep. Ciencia da Computacao 
*/

#ifndef INSTANCE_H
#define INSTANCE_H

#include <string>
#include <vector>

#include "Job.h"
#include "config.h"

class Instance
{
    private:
        int numJobs;
        std::vector<Job*> jobs;
        std::vector<std::vector<int>> setupTimes;
        std::vector<std::vector<int>> delayConstraints;
        
        /**
        * * Metodo privado construtor da classe instance
        */
        
    public:
        Instance();
        
        const std::string path = PROJECT_ROOT"/instances/";

        /**
        * * Metodo destrutor da classe instance
        */
        ~Instance();
        int getNumJobs();
        std::vector<Job*> getJobs();
        std::vector<std::vector<int>> getSetupTimes();
        std::vector<std::vector<int>> getDelayConstraints();
        std::string getPath();

        /**
        * * Metodo responsavel por ler o arquivo da instancia e armazenar os dados na estrutura
        * @param file - nome do arquivo da instancia
        */
        void readInstance(std::string file);

        /**
        * * Metodo responsavel por resetar os valores de initTime e EndTime de cada job da instancia
        */
        void resetInstance();
};

#endif