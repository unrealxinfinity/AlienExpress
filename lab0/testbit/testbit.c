#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BIT(n) (1<<(n))

char *byte2bin(uint8_t n, char *binstr) 
{
    // one element per bit (0/1)
    uint8_t binary[8];

    int i = 0;
    for(i = 0; i < 8; i++) {
        binary[i] = n % 2;
        n = n / 2;
    }

    // printing binary array in reverse order
    for (int j = 7, k= 0; j >= 0; j--, k++)
        sprintf(binstr + k, "%d", binary[j]);
        
    return binstr;
}

void print_usage(char *name) {
    printf("Usage: %s <action> <byte> <bit no>\n", name);
    printf("\tWhere: <action> one of 'h'|'l'|'r'|'s'|'t'\n"
        "\t\t <byte> 8-bit integer in hexadecimal\n"
        "\t\t <bit no> of bit to operate on\n");
}
int main(int argc, char *argv[]){
    unsigned long value = strtoul(argv[2],NULL,16);
    int bit=atoi(argv[3]);
    char *flag=argv[1];

    if(argc != 4){
        print_usage(argv[0]);
        printf("Missing arguments \n");
        return EXIT_FAILURE;
    }
    if(!(argv[1][0]=='h' || argv[1][0]=='l' || argv[1][0]=='r' || argv[1][0]=='s' || argv[1][0]=='t')){
        print_usage(argv[0]);
        printf("Flag doesn't exist\n");
        return EXIT_FAILURE;
    }

    if(value>256){
        print_usage(argv[0]);
        printf("Decimal value of the Hex input has to be under 256\n");
        return EXIT_FAILURE;
    }
    if(bit>7 || bit <0){
        print_usage(argv[0]);
        printf("Bit position has to be between 0 and 7\n");
        return  EXIT_FAILURE;
    }

    char bits[9];
    char* print;
    uint8_t valueToProcess=value;
    uint8_t mask=1;
    uint8_t res;
    uint8_t checkbit;
    if(flag[0]=='h'){

        res=mask<<bit;
        checkbit=res & valueToProcess;
        print=byte2bin(valueToProcess,bits);
        for(unsigned int i=0;i<strlen(print);i++){
            printf("%c",bits[i]);
            
        }
        printf("\n");
        if(checkbit != 0){
            printf("The selected bit %d is high\n",bit);
            return EXIT_SUCCESS;
        }
        printf("The selected bit %d is not high\n",bit);
        return EXIT_SUCCESS;
    }

    if(flag[0]=='l'){

        res=mask<<bit;
        checkbit=res & valueToProcess;
        print=byte2bin(valueToProcess,bits);
        for(unsigned int i=0;i<strlen(print);i++){
            printf("%c",bits[i]);
        }
        printf("\n");
        if(checkbit == 0){
            printf("The selected bit %d is low\n",bit);
            return EXIT_SUCCESS;
        }
        printf("The selected bit %d is not low\n",bit);
            return EXIT_SUCCESS;
    }

    if(flag[0]=='r'){

        res=~(mask<<bit);
        checkbit=res&valueToProcess;

        print = byte2bin(checkbit,bits);
        for(unsigned int i=0;i<strlen(print);i++){
            printf("%c",bits[i]);
            
        }
        printf("\n");
        printf("The selected bit %d was reset",bit);
        printf("\n");

    }
    
    if(flag[0]=='s'){

        res=mask<<bit;
        checkbit=res|valueToProcess;

        print = byte2bin(checkbit,bits);
        for(unsigned int i=0;i<strlen(print);i++){
            printf("%c",bits[i]);
            
        }
        printf("\n");
        printf("The selected bit %d was set",bit);
        printf("\n");

    }
    if(flag[0]=='t'){

        res=mask<<bit;
        checkbit=res^valueToProcess;

        print = byte2bin(checkbit,bits);
        for(unsigned int i=0;i<strlen(print);i++){
            printf("%c",bits[i]);
            
        }
        printf("\n");
        printf("The selected bit %d was toggled",bit);
        printf("\n");

    }
    return EXIT_SUCCESS;
    
}