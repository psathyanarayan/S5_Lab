#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
    char opcode[10],operand[10],label[10],code[10],mnemonic[10];
    int locctr,start,length;
    FILE *f1,*f2,*f3,*f4;
    f1 = fopen("input.txt","r");
    f2 = fopen("optab.txt","r");
    f3 = fopen("symtab.txt","w");
    f4 = fopen("out.txt","w");

    fscanf(f1,"%s\t%s\t%s",label,opcode,operand);
    // printf("%s %s %s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        start = atoi(operand); // save operand as start
        locctr = start; // initialize locctr as starting address
        fprintf(f4,"\t%s\t%s\t%s\n",label,opcode,operand); // Write line to intermideate file
        fscanf(f1,"%s\t%s\t%s",label,opcode,operand);
    // printf("%s %s %s",label,opcode,operand);
    }
    else
        locctr = 0; //else set locctr as 0
    
    while(strcmp(opcode,"END") !=0)
    {
        fprintf(f4,"%d\t",locctr);
        if(strcmp(label,"**")!=0)
        {
            fprintf(f3,"%s\t%d\n",label,locctr);
        }

        fscanf(f2,"%s\t%s",code,mnemonic);
        while(strcmp(code,"END")!=0)
        {
            if(strcmp(opcode,code)==0)
            {
                locctr+=3;
                break;
            }
            fscanf(f2,"%s\t%s",code,mnemonic);
        }

        if(strcmp(opcode,"WORD")==0){
            locctr+=3;
        }
        else if(strcmp(opcode,"RESW")==0)
        {
            locctr+=(3*(atoi(operand)));
        }
        else if(strcmp(opcode,"RESB")==0)
        {
            locctr+=(atoi(operand));
        }
        else if(strcmp(opcode,"BYTE")==0)
        {
            ++locctr;
        }
        else
        {
            printf("\n!!! INVALID OPERATION !!!\n");
        }

        fprintf(f4,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(f1,"%s\t%s\t%s",label,opcode,operand);
    }
    fprintf(f4,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    length = locctr-start;
    printf("\nThe lenghth of the code : %d\n",length);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    
}