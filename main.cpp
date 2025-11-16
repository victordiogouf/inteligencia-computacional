/**
* * main.cpp - Arquivo principal do projeto
* 
* * Autor(es): Quezia Emanuelly e Victor Araujo
* * Projeto: Trabalho Pratico 1 - Inteligencia Computacional
* * Organizacao: Universidade Federal de Juiz de Fora
* * Departamento: Dep. Ciencia da Computacao 
*/

#include "Management.h"
#include "Job.h"

#include <iostream>
#include <fstream>
#include <string>

/**
* TODO: alterar o codigo para mostrar somente a melhor solucao das calculadas no loop
* TODO: calcular o tempo que o construtivo esta sendo executado
* TODO: calcular a media dos mankespans encontrados e tambem do tempo, para saber em media se ele encontra valores bons ou se teve sorte
*/
int main(int argc, char* argv[]) 
{
  try {
    if(argc == 2) {
      std::string file(argv[1]);
      Management* management = new Management(file);
      management->initInstance(file);
      std::vector<Job*> solutionOptimum;

      for(int i = 0; i < 10; i++) {
        auto solutionInit = management->constructive();
  
        std::cout << "makespan construtivo: " << solutionInit.second << std::endl;
        // std::cout << "a solucao encontrada com construtivo foi: " << std::endl;
        // for(Job* job : solutionInit.first) {
        //   std::cout << job->getId() << " ";
        // }
  
        // std::cout << std::endl;
        std::cout << std::endl;

        solutionInit = management->localSearch(solutionInit.first);
  
        std::cout << "makespan busca local: " << solutionInit.second << std::endl;
        // std::cout << "a solucao encontrada com busca local foi: " << std::endl;
        // for(Job* job : solutionInit.first) {
        //   std::cout << job->getId() << " ";
        // }
  
        // std::cout << std::endl;
        std::cout << std::endl;
      }


    } else {
      throw std::invalid_argument("Informe o arquivo");
    }

  } catch(std::ios_base::failure& e) {
    std::cout << "ERROR: " << e.what() << std::endl;
  } catch(const std::invalid_argument& e) {
    std::cout << "ERROR: " << e.what() << std::endl;
  }
}