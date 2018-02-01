#pragma once
class gpio
{
public:

	gpio(int i);
	~gpio();

	void setOutput(const char *mode);
	void setValue(int value);
	void setVerbose(bool b);
	void setLog(bool b);
	

private:
	void exportGPIO();
	void unexport();
	void putInLog(const char *str);
	bool createLogFile(const char *name);

	char id[2] = { '0', '0' };
	char *cmd = new char[255];
	bool isValide = false;
	bool verbose = false;
	bool log = true;

};

