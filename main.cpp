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

int main(int argc, char* argv[]) 
{
  try {
    if(argc == 2) {
      std::string file(argv[1]);
      Management* management = new Management(file);
      management->initInstance(file);
      auto solutionInit = management->constructive();

      std::cout << "makespan: " << solutionInit.second << std::endl;
      std::cout << "makespan2: " << solutionInit.first[solutionInit.first.size()-1]->getEndTime() << std::endl;
      std::cout << "a solucao encontrada foi: " << std::endl;
      for(Job* job : solutionInit.first) {
        std::cout << job->getId() << " ";
      }

      std::cout << std::endl;

    } else {
      throw std::invalid_argument("Informe o arquivo");
    }

  } catch(std::ios_base::failure& e) {
    std::cout << "ERROR: " << e.what() << std::endl;
  } catch(const std::invalid_argument& e) {
    std::cout << "ERROR: " << e.what() << std::endl;
  }
}