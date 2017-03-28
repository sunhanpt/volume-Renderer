#pragma once
#include <iostream>
#include <stdio.h>

using namespace std;

class BinaryFileReader
{
protected:
	FILE *fp;

public:
	BinaryFileReader(char * filename)
	{
		if(filename == NULL)
			return;
		fp = fopen(filename, "rb");
	}

	~BinaryFileReader(void)
	{
		if(fp != NULL) {
			fclose(fp);
		}
	}
protected:
	FILE * GetFile() {
		return fp;
	}
};
