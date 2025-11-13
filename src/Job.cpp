/**
* * Instance.cpp - Arquivo referente a implementacao da classe Job.h
* 
* * Autor(es): Quezia Emanuelly e Victor Araujo
* * Projeto: Trabalho Pratico 1 - Inteligencia Computacional
* * Organizacao: Universidade Federal de Juiz de Fora
* * Departamento: Dep. Ciencia da Computacao 
*/

#include "Job.h"

Job::Job(int time)
{
    this->processingTime = time;
    this->initTime = 0;
    this->endTime = this->processingTime;
}
Job::~Job(){}

int Job::getProcessingTime()
{
    return this->processingTime;
}

int Job::getId()
{
    return this->id;
}

void Job::setProcessingTime(int time)
{
    this->processingTime = time;
}

void Job::setId(int id)
{
    this->id = id;
}

int Job::getInitTime()
{
    return this->initTime;
}

void Job::setInitTime(int time)
{
    this->initTime = time;
}

int Job::getInitTimeAux()
{
    return this->initTimeAux;
}

void Job::setInitTimeAux(int time)
{
    this->initTimeAux = time;
}

int Job::getEndTime()
{
    return this->initTimeAux + this->processingTime;
}

void Job::setEndTime(int time)
{
    this->endTime = time;
}