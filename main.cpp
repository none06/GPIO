#include "gpio.h"
#include <iostream>

int main(int argc, char *argv[]) {

	int number = atoi(argv[1]);
	int value = atoi(argv[3]);
	
	gpio *g = new gpio(number);
	
	g->setVerbose(true);
	g->setLog(true);
	g->setOutput(argv[2]);
	g->setValue(value);

	delete(g);

	return 0;
}
