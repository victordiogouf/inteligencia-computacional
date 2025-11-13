/**
* * Job.h - Arquivo da classe Job onde sera o padrao para todos os jobs utilizados
* 
* * Autor(es): Quezia Emanuelly e Victor Araujo
* * Projeto: Trabalho Pratico 1 - Inteligencia Computacional
* * Organizacao: Universidade Federal de Juiz de Fora
* * Departamento: Dep. Ciencia da Computacao 
*/

#ifndef JOB_H
#define JOB_H

class Job
{
    private:
        int id;
        int processingTime;
        int initTime;
        int initTimeAux;
        int endTime;
    public:
        Job(int time);
        ~Job();
        int getProcessingTime();
        void setProcessingTime(int time);
        int getId();
        void setId(int id);
        int getInitTime();
        void setInitTime(int time);
        int getInitTimeAux();
        void setInitTimeAux(int time);
        int getEndTime();
        void setEndTime(int time);
};

#endif