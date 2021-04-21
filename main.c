#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <time.h>


void save()
{
    FILE* datainfile = fopen("data.txt","a");
    char* out = calloc(256,sizeof(char));
    char vnev[129];
    char knev[64];
    char nev[129];
    printf("kerjuk irja be a nevet:");
    scanf("%s %s",vnev,knev);
    strcat(vnev," ");
    strcat(vnev,knev);
    strcpy(nev,vnev);
    char szuletes[64];
    printf("szuletett:");
    scanf("%s",szuletes);
    char telefonszam[64];
    printf("telefonszama:");
    scanf("%s",telefonszam);
    char fizetosfelar[64];
    printf("fizetos felarat szeretne:");
    scanf("%s",fizetosfelar);
    strcat(out,nev);
    strcat(out,",");
    strcat(out,szuletes);
    strcat(out,",");
    strcat(out,telefonszam);
    strcat(out,",");
    strcat(out,fizetosfelar);
    strcat(out,"\n");
    fwrite(out, sizeof(char), strlen(out), datainfile);
    fclose(datainfile);
}

void delete(char* deletable)
{
    char searchable[128];
    FILE* datainfile=fopen("data.txt","r+");
    FILE* outputfile= fopen("dataout.txt","w");
    int startindex = 0;
    if(!datainfile)
    {
        perror("File opening failed!");
        return;
    }
	char delim[] = ",";

    char lines[256][256];
    int idx=0;
    while(fgets(lines[idx],sizeof lines[idx],datainfile)!=NULL)
    {
        char old[256];
        strcpy(old,lines[idx]);
        char* ptr2 = strtok(lines[idx],delim);
        if(!strcmp(ptr2,deletable)==0)
        {
            fputs(old,outputfile);
        }
        while(ptr2!=NULL)
            {                
                ptr2 = strtok(NULL,delim);
            }
    }
    fclose(datainfile);
    fclose(outputfile);
    remove("data.txt");
    rename("dataout.txt","data.txt");

}

void modify(char* modifyable)
{
    FILE* datainfile=fopen("data.txt","r+");
    FILE* outputfile= fopen("dataout.txt","w");
    int megvan = 0;
    if(!datainfile)
    {
        perror("File opening failed!");
        return;
    }
	char delim[] = ",";

    char lines[256][256];
    int idx=0;
    while(fgets(lines[idx],sizeof lines[idx],datainfile)!=NULL)
    {
        char old[256];
        strcpy(old,lines[idx]);
        char* ptr2 = strtok(lines[idx],delim);
        if(!strcmp(ptr2,modifyable)==0)
        {
        fputs(old,outputfile);
        }
        else
        {
            megvan = 1;
            char insertme[256];
            char vnev[129];
            char knev[64];
            char nev[129];
            char szuletes[64];
            printf("megvan a modositando adat,kerjuk irja be az uj nevet:");
            scanf("%s %s",vnev,knev);
            strcat(vnev," ");
            strcat(vnev,knev);
            strcpy(nev,vnev);
            printf("szuletett:");
            scanf("%s",szuletes);
            char telefonszam[64];
            printf("telefonszama:");
            scanf("%s",telefonszam);
            char fizetosfelar[64];
            printf("fizetos felarat szeretne:");
            scanf("%s",fizetosfelar);
            char* out = calloc(256,sizeof(char));
            strcat(out,nev);
            strcat(out,",");
            strcat(out,szuletes);
            strcat(out,",");
            strcat(out,telefonszam);
            strcat(out,",");
            strcat(out,fizetosfelar);
            strcat(out,"\n");
            fputs(out,outputfile);

        }    
        while(ptr2!=NULL)
        {                
            ptr2 = strtok(NULL,delim);
        }
        
    }
    if(megvan ==0)
    {
        printf("nem talaltuk meg ezt a szemelyt az adatbazisban. %s", modifyable);
    }
    fclose(datainfile);
    fclose(outputfile);
    remove("data.txt");
    rename("dataout.txt","data.txt");
}

int isvaccinated(char* haveugotvaccine)
{
    FILE* datainfile=fopen("data.txt","r+");
    FILE* outputfile=fopen("dataout.txt","w");
    int megvan = 0;
    if(!datainfile)
    {
        perror("File opening failed!");
        return -1;
    }
	char delim[] = ",";

    char lines[256][256];
    int idx=0;
    while(fgets(lines[idx],sizeof lines[idx],datainfile)!=NULL)
    {
        char old[264];
        strcpy(old,lines[idx]);
        char* ptr2 = strtok(lines[idx],delim);
        if(!strcmp(ptr2,haveugotvaccine)==0)
        {
        fputs(old,outputfile);
        }
        else
        {
            megvan = 1;
            fputs(old,outputfile);
        }    
        while(ptr2!=NULL)
        {                
            ptr2 = strtok(NULL,delim);
        }
        
    }
    if(megvan ==0)
    {
        printf("nem talaltuk meg ezt a szemelyt az adatbazisban. %s", haveugotvaccine);
    }
    fclose(datainfile);
    fclose(outputfile);
    remove("data.txt");
    rename("dataout.txt","data.txt");
    return megvan;
}

int areulucky()
{
    srand(time(0));
    int random = rand() % 101;
    if(random<90)
    {
        return 1;
    }
    else return 0;

    return -1;
}

void getvaccinated(char *igotvaccine)
{
    FILE* datainfile=fopen("data.txt","r+");
    FILE* outputfile=fopen("dataout.txt","w");
    int megvan = 0;
    if(!datainfile)
    {
        perror("File opening failed!");
        return;
    }
	char delim[] = ",";

    char lines[256][256];
    int idx=0;
    while(fgets(lines[idx],sizeof lines[idx],datainfile)!=NULL)
    {
        char old[264];
        strcpy(old,lines[idx]);
        char* ptr2 = strtok(lines[idx],delim);
        if(!strcmp(ptr2,igotvaccine)==0)
        {
        fputs(old,outputfile);
        }
        else
        {
            megvan = 1;
            strcat(old,",OLTVA");
            fputs(old,outputfile);
        }    
        while(ptr2!=NULL)
        {                
            ptr2 = strtok(NULL,delim);
        }
        
    }
    if(megvan ==0)
    {
        printf("nem talaltuk meg ezt a szemelyt az adatbazisban. %s", igotvaccine);
    }
    fclose(datainfile);
    fclose(outputfile);
    remove("data.txt");
    rename("dataout.txt","data.txt");
}

void printall()
{
    FILE* datainfile = fopen("data.txt","r");
    char* readdata = calloc(256,sizeof(char));
    if(!datainfile)
    {
        perror("File opening failed!");
    }

    int c;
    while ((c = fgetc(datainfile)) != EOF) { // standard C I/O file reading loop
       putchar(c);
    }
}

void indulamandula()
{
    pid_t oltobusz1;
    pid_t oltobusz2;
    int fd1[2];
    int fd2[2];


    oltobusz1 = fork();
    oltobusz2 = fork();
    if(pipe(fd1)==-1)
    {
        perror("pipe1 failed");
    }
    if(pipe(fd2)==-1)
    {
        perror("pipe2 failed");
    }

    if(oltobusz1<0)
    {
        perror("fork failed");
    }
    if(oltobusz1>0)
    {
        close(fd2[1]);
        wait(NULL);
        printf("%s","en vagyok a szulo");
        char message[64];
        close(fd2[1]);
        read(fd2[0],message,64);
        printf("%s",message);
        close(fd2[1]);
    }
    else if(oltobusz1==0)
    {
        close(fd2[0]);
        char message[64] = "szevasz en vagyok a joska";
        printf("%s","en vagyok a gyerek");
        write(fd2[1], message, strlen(message));
        close(fd2[1]);

    }
    



}

int main(int argc, char** argv)
{
    /*printf("Udvozlom a vakcina regisztracios C programban! \n ");
    while(1)
    {
        int choice = 0;
        printf("\nMit szeretne tenni? irja be a megfelelo szamot.\n 1. -> Uj szemely felvetele \n 2. -> Meglevo szemely modositasa \n 3. -> Meglevo szemely torlese. \n 4. -> Listazas. \n 5. -> Kilepes \n");
        scanf("%d",&choice);
        char vnev[128];
        char knev[64];
        char teljesnev[128];
        switch(choice)
        {
            case 1: save(); break;
            case 2: printf("irja be a szemely nevet, akit modositani kivan:"); 
                    scanf("%s %s",vnev,knev);
                    strcat(vnev," ");
                    strcat(vnev,knev);
                    strcpy(teljesnev,vnev);
                    modify(teljesnev);
                    break;
            case 3: printf("irja be a szemely nevet, akit torolni kivan:");
                    scanf("%s %s",vnev,knev);
                    strcat(vnev," ");
                    strcat(vnev,knev);
                    strcpy(teljesnev,vnev);
                    delete(teljesnev);
                    break;
            case 4: printall(); break;
            case 5: return 0;
            default: printf("nem ertelmezett kod, kerem a megadott szamok kozul valasszon\n");                    
        }
    }
    return 1;*/



    indulamandula();


}