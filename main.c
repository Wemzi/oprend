#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<time.h>


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

int areulucky()
{
    srand(time(NULL));  
    int random = rand() % 101;
    printf("%d   ",random);
    srand(time(NULL));
    if(random<90)return 1;
    else return 0;

    return -1;
}

char** filloltobuszok()
{
    char** names = calloc(10,sizeof(char*));
    for(int idx = 0; idx<10; idx++)
    {
        names[idx] = calloc(256,sizeof(char));
    }
    FILE* datainfile=fopen("data.txt","r");  
    int megvan = 0;
    if(!datainfile)
    {
        perror("File opening failed!");
        return NULL;
    }
	char delim[] = ",";
    char lines[256][256];
    int idx=0;
    int bevan = 0;
    char oltva[7] = "OLTVA\n";
    int jdx=0;
    while(fgets(lines[idx],sizeof lines[idx],datainfile)!=NULL && jdx<9)
    {
        bevan = 0;  
        char* ptr2 = strtok(lines[idx],delim);
        char name[64];
        strcpy(name,ptr2);
        for(int tmp=0; tmp<4 && ptr2!=NULL; tmp++)
        {
            ptr2 = strtok(NULL,delim);
        }
        if( ptr2 != NULL && strcmp(oltva,ptr2)==0)
        {
            bevan = 1;
        }
        if(bevan==0 && areulucky())
        {
            strcpy(names[jdx++],name);
            sleep(1);
        }
    }
    fclose(datainfile);
    return names;
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
        int len = strlen(old);
        
        char* ptr2 = strtok(lines[idx],delim);
        if(!strcmp(ptr2,igotvaccine)==0)
        {
        fputs(old,outputfile);
        }
        else
        {
            megvan = 1;
            //remove newline and replace with terminate symbol
            if(old[len-1]=='\n')
            {
                old[len-1]='\0';
            }
            strcat(old,",OLTVA\n");
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

void oltobuszgo(char** names,int pipe[2])
{
    char* out = calloc(5*65,sizeof(char*));
    int jdx=0;
    for(int idx=0; names[idx]!=NULL; idx++)
    {
        printf("%s be lett oltva\n ", names[idx]);
        if(jdx==0)
        {
            strcat(out,names[idx]);
            strcat(out,",");
        }
        else
        {
            strcat(out,",");
            strcat(out,names[idx]);
            strcat(out,","); 
        }
    }
    write(pipe[1],out,sizeof(out));
}

int getbussize(char **names)
{
    int idx=0;
    while(strlen(names[idx])>2)
    {
        idx++;
    }
    return idx;
}

void sig_handler(int signum)
{
    printf("Harcra fel!\n");
}

void indulamandula()
{
    int     oltobusz[2], nbytes, oltobusz2[2];
    pid_t   childpid = 50;
    pid_t   childpid2 = 50;
    char    string[] = "Kutyaszar!\n";
    char    readbuffer[80];
    printf("%s\n",string);
    char** names = filloltobuszok();
    int bussize = getbussize(names);
    //printf("a busz merete: %d",bussize);
    
    pipe(oltobusz);
    pipe(oltobusz2);
    if(childpid2 > 0 && childpid >0 )
    {
        //printf("forkolok");
        childpid = fork();
        if(childpid == -1)
        {
            perror("fork");
            exit(1);
        }
    }
    if(childpid2 > 0 && childpid >0 )
    {
        //printf("forkolok");
        childpid2 = fork();
        if(childpid2 == -1)
        {
            perror("fork2");
            exit(1);
        }
    }
    printf("%d  ",childpid);
    printf("%d a buszok merete pedig: %d \n",childpid2, bussize);
    if(childpid>0 && childpid2 > 0 )
    {
        
            struct sigaction sigact;
            sigact.sa_handler=sig_handler;
            sigemptyset(&sigact.sa_mask); 
            sigact.sa_flags=0; 
            sigaction(SIGUSR2,&sigact,NULL);
            sigaction(SIGUSR1,&sigact,NULL);
            wait(NULL);
            close(oltobusz[1]);
            close(oltobusz2[1]);
            nbytes = read(oltobusz[0], readbuffer, sizeof(readbuffer));
            printf("Read string: %s", readbuffer);
            nbytes = read(oltobusz2[0], readbuffer, sizeof(readbuffer));
            printf("Read string: %s", readbuffer);
    }
    if(childpid == 0)
    {
        printf("gyerek vagyok\n");
        if(bussize>4)
        {
            printf("Harcra fel!\n");
            //raise(SIGUSR1)
            char** oltandok = calloc (5,sizeof(char*));
            for(int idx=0; idx<5; idx++)
            {
                oltandok[idx] = calloc(64,sizeof(char));
            }
            for(int idx=0; idx<5; idx++)
            {
                strcpy(oltandok[idx],names[idx]);
            }
            
            close(oltobusz[0]);
            oltobuszgo(oltandok,oltobusz);
            
        }
        exit(0);
        
    }
    if(childpid2 == 0 && bussize > 9)
    {
        //raise(SIGUSR2);
        char** oltandok = calloc (5,sizeof(char*));
        for(int idx=0; idx<5; idx++)
        {
            oltandok[idx] = calloc(64,sizeof(char));
        }
        for(int idx=5; idx<10 && names[idx]; idx++)
        {
            strcpy(oltandok[idx],names[idx]);
        }
        int bussize = getbussize(oltandok);
        close(oltobusz2[0]);
        oltobuszgo(oltandok,oltobusz2);
        exit(0);
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
    

    return 0;

}