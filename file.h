#include <stdio.h>
#include <stdlib.h>

#include "RBT.h"
#include "string.h"

String** leArquivo(String* path, int maxCount, int *count);
int verificaArquivo(FILE* arquivo);