#include <stdio.h>
#include <stdlib.h>
#include "TST.h"
#include "RBT.h"
#include "string.h"

String** leArquivo(String* path, int maxCount, int *count);
int verificaArquivo(FILE* arquivo);
TST* leArquivoTST(String* path, int maxCount, int *count);