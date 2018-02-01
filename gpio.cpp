#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
using namespace std;

gpio::gpio(int i)
{
	if (i < 10) {
		id[0] = i + 48;
		id[1] = '\0';
	}
	else {
		int *tmp = new int;
		*tmp = i / 10;

		id[0] = *tmp+48;
		id[1] = (i % 10) + 48;

		delete(tmp);
		
	}

	if (i <= 0) {
		system("echo Numero de GPIO invalide !");
	}
	else {
		if(this->verbose) system("echo GPIO valide.");
		this->isValide = true;
	}
	

	this->exportGPIO();
}

gpio::~gpio()
{
	//this->unexport();
}

void gpio::exportGPIO() {
	if (this->isValide) {
		strcpy(cmd, "echo \"");
		strcat(cmd, id);
		strcat(cmd, "\" > /sys/class/gpio/export");
		
		system(cmd);
	}
}

void gpio::setOutput(const char *mode) {

	if (strcmp(mode, "in") || strcmp(mode, "out") ) {

	}else{
		strcpy(cmd, "echo mode invalide !");
		system(cmd);
		this->isValide = false;
	}

	if (this->isValide) {

		strcpy(cmd, "echo \"");
		strcat(cmd, mode);
		strcat(cmd, "\" > /sys/class/gpio/gpio");
		strcat(cmd, id);
		strcat(cmd, "/direction");
		system(cmd);
		
	}
}

void gpio::setValue(int value) {

	if (value != 0 && value != 1) {
		strcpy(cmd, "echo valeur invalide !");
		system(cmd);
		this->isValide = false;
	}

	if (this->isValide) {
		
		char *c = new char[2];
		*c = (value + 48);
		c[1] = '\0';
	
		strcpy(cmd, "echo \"");
		strcat(cmd, c);

		

		strcat(cmd, "\" > /sys/class/gpio/gpio");
		strcat(cmd, id);
		strcat(cmd, "/value");

		char *msg = new char[255];
		strcpy(msg, "\tChangement de valeur du GPIO n° ");
		strcat(msg, id);
		strcat(msg, " -> ");
		strcat(msg, c);
		strcat(msg, ".\n");
		if (this->verbose) this->putInLog(msg);

		delete(msg);
		delete(c);

		system(cmd);	

	}
}

void gpio::unexport() {
	if (this->isValide) {
		strcpy(cmd, "echo \"");
		strcat(cmd, id);
		strcat(cmd, "\" > /sys/class/gpio/unexport");
		system(cmd);
	}
}

void gpio::setVerbose(bool b){
	this->verbose = b;
}

void gpio::setLog(bool b) {
	this->log = b;
}

bool gpio::createLogFile(const char *name) {
	ofstream logFile(name, ios::app);
	if (logFile) {
		return true;
	}
	else {
		return false;
	}
}

void gpio::putInLog(const char *str) {
	ofstream logFile("log.txt", ios::app);
	system("echo -n $(date +%A) $(date +%T) >> log.txt");
	logFile << str;
}