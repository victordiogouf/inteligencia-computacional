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
#include <string>
#include <fstream>
#include <chrono>

int main(int argc, char* argv[]) 
{
  try {
    if(argc == 2) {
      std::string file(argv[1]);
      Management* management = new Management(file);
      management->initInstance();
      management->calcSolution();
    } else {
      throw std::invalid_argument("Informe o arquivo de instancias");
    }

  } catch(std::ios_base::failure& e) {
    std::cout << "ERROR: " << e.what() << std::endl;
  } catch(const std::invalid_argument& e) {
    std::cout << "ERROR: " << e.what() << std::endl;
  }
}