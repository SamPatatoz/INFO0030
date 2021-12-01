#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>


#include "LFSR.h"
#include "pnm.h"
#include "basic_cipher_mod.h"

int main(int argc, char *argv[])
{

    int tap = 16;
    char *seed;
    PNM *image = create_image();
    char *filename;
    char *tofile;
    char *optstring = ":i:o:s:t:";
    int val;
    char *tmp;
    printf("\n");

    while((val=getopt(argc, argv, optstring))!=EOF)
    {
        switch(val)
        {
            
        case 'i':
            printf("Input : %s\n",optarg);
            filename = optarg;
            break;
        case 'o':
            printf("Output : %s\n",optarg );
            tofile = optarg;
            break;
        case 's':
            printf("Seed : %s\n",optarg);
            seed = optarg;
            break;
        case 't':
            printf("Tap : %s\n",optarg);
            tmp = optarg;
            tap = atoi(tmp);
            break;
        case '?':
            printf("Unknown option : %c\n",optopt);
            return 0;
            break;
        case ':':
            printf("Missing argument : %c\n",optopt);
            return 0;
            break;
        default:
            break;
        }
    }

    printf("\n");

    if(return_error_load(load_pnm(&image,filename))==-1)
    {
        return 0;
    }
    
    transformation(seed, tap, get_lines(image), get_columns(image), get_matrix(image), get_perfectNbr(image));
 
    if(write_pnm(image,tofile)==-1)
    {
        printf("The name of the output file passed in argument is not valid\n");
        return 0;
    }

    printf("Input file successfully encrypted to output file !\n");
    return 0;
}

