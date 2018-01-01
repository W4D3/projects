// jtar.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "jrb.h"
#include "dllist.h"

void processFile(char* file, JRB tree); 
void writeData(JRB); 
void readData(); 
