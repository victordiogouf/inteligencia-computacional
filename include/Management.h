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
        * ! a variavel nao pode conter a path inteira, somente o nome do arquivo
        */
        Management(std::string fileInstance);

        /**
        * * Metodo destrutor da classe
        */
        ~Management();

        /**
        * * Metodo responsavel por inicializar a instancia
        * @exception failure - erro na leitura do arquivo
        */
        void initInstance();

        void calcSolution();

        std::pair<std::vector<Job*>, int> constructive(double alfa);
        std::pair<std::vector<Job*>, std::vector<double>> localSearch(std::vector<Job*> solutionInit);
        int objectiveFunction(std::vector<Job*>& jobs);

        std::vector<Job*> getCandidatesList(std::vector<Job*>& solution);
        bool findJob(std::vector<Job*>& list, int idJob);
        bool compare(Job* job1, Job* job2);

        /**
        * * Metodo responsavel por realizar o movimento de swap para a busca local
        * @param solution - conjunto de jobs
        * @param indexJob1 - indice do job 1 para ser utilizado no swap
        * @param indexJob2 - indice do job 2 para ser utilizado no swap 
        * @return vector de jobs
        */
        std::vector<Job*> swap(std::vector<Job*> solution, int indexJob1, int indexJob2);

        /**
        * * Metodo responsavel por verificar se o job no indexInit possui algum job
        * * até indexEnd que tenha uma constante de precedencia com ele
        * @param solution - conjunto de jobs da solucao atual
        * @param indexInit - indice do job inicial a ser verificado
        * @param indexEnd - indice limite da solucao a ser verificada
        * @return (verdadeiro caso possua uma regra de precedencia, false caso contrario)
        */
        bool verifySucessor(std::vector<Job*>& solution, int indexInit, int indexEnd);
        
        /**
        * * Metodo responsavel por verificar se o job no indexEnd possui algum job
        * * até indexInit que tenha uma constante de precedencia com ele
        * @param solution - conjunto de jobs da solucao atual
        * @param indexInit - indice limite da solucao a ser verificada
        * @param indexEnd - indice do job inicial a ser verificado
        * @return (verdadeiro caso possua uma regra de precedencia, false caso contrario)
        */
        bool verifyPredecessor(std::vector<Job*>& solution, int indexInit, int indexEnd);
};

#endif