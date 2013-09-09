//
//  main.c
//  BinToC
//
//  Created by liwei on 7/13/13.
//  Copyright (c) 2013 liwei. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bin2c(FILE * in, FILE * out);
void c2bin(const char ptr[], long len);

int main(int argc, const char * argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s filepath\n", argv[0]);
        exit(1);
    }
    
    FILE *in, *out;
    if ((in = fopen(argv[1], "rb")) == NULL)
    {
        fprintf(stderr, "Couldn't open the file \"%s\"\n", argv[1]);
        exit(2);
    }
    
    char filePath[400];
    char fileName[40];
    
    strcpy(filePath, argv[1]);
    char * ptr;
    
    while ((ptr = strchr(filePath, '.')))
        filePath[ptr-filePath] = '_';
    if ((ptr = strrchr(filePath, '/')))
        strcpy(fileName, filePath+(ptr-filePath+1));
    strcat(filePath, ".c");
    
    if ((out = fopen(filePath, "wb")) == NULL)
    {
        fprintf(stderr, "Can't create output file.\n");
        exit(3);
    }
    
    fprintf(out, "const static char %s[] = {", fileName);
    bin2c(in, out);
    fprintf(out, "};");
    
//    c2bin(MCNode_pkg_txt, sizeof(MCNode_pkg_txt)/sizeof(MCNode_pkg_txt[0]));
    
    if (fclose(in) != 0 || fclose(out) != 0)
        fprintf(stderr, "Error in closing files\n");
    return 0;
}

void bin2c(FILE * in, FILE * out)
{
    unsigned char digit;
    unsigned long filesize;
    unsigned long index = 0;
    char word[6];
    
    fseek(in, 0L, SEEK_END);
    filesize = ftell(in);
    fseek(in, 0L, SEEK_SET);
    
    while (index < filesize)
    {
        fread(&digit, 1, 1, in);
        index++;
        sprintf(word, "0X%02X,", digit);
        fwrite(word, 5, 1, out);
    }
}

void c2bin(const char ptr[], long len)
{
    unsigned long  index = 0;
    
    while (index < len)
        printf("%c",ptr[index++]);
}

