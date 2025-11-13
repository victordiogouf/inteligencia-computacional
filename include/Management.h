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

class Management 
{
    private:
        Instance* instance;
    
    public:

        /**
        * * Metodo construtor da classe Management
        * @param fileInstance - nome do arquivo onde esta a instancia
        * @exception invalid_argument - excecao lancada caso o nome do arquivo seja invalido
        * ! a variavel nao pode conter a path inteira, somente o nome do arquivo
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
        */
        void initInstance(std::string file);

        std::vector<Job*> constructive();
        std::vector<Job*> localSearch(std::vector<Job*> solutionInit);

        std::vector<Job*> getCandidatesList(std::vector<Job*> solution);
        bool findJob(std::vector<Job*> list, int idJob);
};

#endif