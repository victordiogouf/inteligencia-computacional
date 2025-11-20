/**
* * Management.h - Arquivo responsavel por gerenciar toda a aplicacao e funcionalidades
* 
* * Autor(es): Quezia Emanuelly e Victor Araujo
* * Projeto: Trabalho Pratico 1 - Inteligencia Computacional
* * Organizacao: Universidade Federal de Juiz de Fora
* * Departamento: Dep. Ciencia da Computacao 
*/

#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "Instance.h"

#include <cstring>
#include <utility>

class Management 
{
    private:
        Instance* instance;
    
    public:

        /**
        * * Metodo construtor da classe Management
        * @param fileInstance - nome do arquivo onde esta a instancia
        */
        Management(std::string fileInstance);

        /**
        * * Metodo destrutor da classe
        */
        ~Management();

        /**
        * * Metodo responsavel por inicializar a instancia
        * @param file - nome do arquivo da instancia
        * @exception failure - erro na leitura do arquivo
        * ! a variavel nao pode conter a path inteira, somente o nome do arquivo
        */
        void initInstance();

        void calcSolution();

        std::pair<std::vector<Job*>, int> constructive(double alfa);
        std::pair<std::vector<Job*>, std::vector<double>> localSearch(std::vector<Job*> solutionInit);
        int objectiveFunction(std::vector<Job*>& jobs);

        std::vector<Job*> getCandidatesList(std::vector<Job*>& solution);
        bool findJob(std::vector<Job*>& list, int idJob);
        bool compare(Job* job1, Job* job2);

        // indexJob1 < indexJob2
        std::vector<Job*> swap(std::vector<Job*> solution, int indexJob1, int indexJob2);

        // retorna true se existir sucessor do job em indexInit no intervalo dado
        bool verifySucessor(std::vector<Job*>& solution, int indexInit, int indexEnd);
        // retorna true se existir predecessor do job em indexEnd no intervalo dado
        bool verifyPredecessor(std::vector<Job*>& solution, int indexInit, int indexEnd);

        void resetFileSolution();
};

#endif