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
  
    int random = rand() % 101;
    if(random<90)return 1;
    else return 0;

    return -1;
}

char** filloltobuszok(int* bussize)
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
    char oltva[16] = "OLTVA\n";
    int jdx=0;
    while(fgets(lines[idx],sizeof(lines[idx]),datainfile)!=NULL && jdx<10)
    {
        bevan = 0;  
        char* ptr2 = strtok(lines[idx++],delim);
        char name[64];
        strcpy(name,ptr2);
        for(int tmp=0; tmp<4 && ptr2!=NULL; tmp++)
        {
            ptr2 = strtok(NULL,delim);
        }
        if( ptr2 != NULL && strcmp(oltva,ptr2)<2)
        {
            bevan = 1;
        }
        if(bevan==0)
        {
            //printf("Varjuk a kovetkezo szemelyt az oltobuszra: %s, vajon odaer? \n", name); 
              //  printf("odaert az oltobuszra!\n");   
                strcpy(names[jdx++],name);
                //printf("novelve lettem itt %s",name);
               // printf("%d\n",jdx++);
            
        }
    }
    *bussize = jdx;
    fflush(NULL);
    fclose(datainfile);
    //printf("szar\n");
    return names;
}

int getvaccinated(char *igotvaccine)
{
    FILE* datainfile=fopen("data.txt","r+");
    FILE* outputfile=fopen("dataout.txt","w");
    int megvan = 0;
    if(!datainfile)
    {
        perror("File opening failed!");
        return 0;
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
            old[len-1]='\0';
            strcat(old,",OLTVA\n");
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
    return megvan;
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

void oltobuszgo(char names[5][64],int pipe[2],char out[5][64])
{
    int jdx=0;
    for(int idx=0;idx<5; idx++)
    {
        if(areulucky())
        {
            strcpy(out[jdx++],names[idx]);
        }
    }
    fflush(NULL);
    int nbytes = write(pipe[1],out,5*64*sizeof(char));
    //printf("%d beleirva az oltobuszba!",nbytes);
}


void sig_handler(int signum)
{
    printf("Harcra fel!\n");
}

void indulamandula()
{
    srand(time(NULL));
    signal(SIGUSR1,sig_handler);
    int     oltobusz[2], nbytes, oltobusz2[2],torzs1[2],torzs2[2];
    pid_t   childpid;
    pid_t   childpid2;
    char    readbuffer[5][64];
    char    readbuffer2[5][64];
    char    readbuffer3[5][64];// = calloc(5,sizeof(char*));
    char    readbuffer4[5][64];
   /* for(int idx=0; idx<5; idx++)
    {
        readbuffer3[idx] = calloc(64,sizeof(char));
    }
    ;
    for(int idx=0; idx<5; idx++)
    {
        readbuffer4[idx] = calloc(64,sizeof(char));
    }
    */

    int bussize;
    char** names = filloltobuszok(&bussize);
    printf("%d regisztraltat talaltam! \n",bussize);
    //printf("a busz merete: %d",bussize);
    signal(SIGUSR1,sig_handler);
    pipe(oltobusz);
    pipe(oltobusz2);
    pipe(torzs1);
    pipe(torzs2);
    
    for(int idx=0; idx<10; idx++)
    {
        //printf("%s\n",names[idx]);
    }

    //printf("%d",bussize);
    if(bussize > 4 )
    {

        childpid = fork();
        if(childpid == -1)
        {
            perror("fork");
            exit(1);
        }
        
        if(childpid == 0) { // gyerek
            //printf("gyerek vagyok\n");

            if(bussize>4)
            {
                kill(getppid(),SIGUSR1);
                close(torzs2[0]);
                close(torzs2[1]);
                close(torzs1[1]);
                int nbytes = read(torzs1[0],readbuffer3,5*64*sizeof(char));
                //printf("%d kiolvasva torzs1bol!\n",nbytes);
                char out[5][64];
                for(int idx=0;idx<5;idx++)
                {
                    //printf("%s xd1bol \n",readbuffer3[idx]);
                }
                close(oltobusz[0]);
                //printf("oltobusz indul!");
                oltobuszgo(readbuffer3,oltobusz,out);
               // printf("%d",bussize);
                //printf("cso\n");
                exit(0);
            }

        } else {
            if(bussize>9) 
            {

                childpid2 = fork();
                
                if(childpid2==0) // gyerek2
                {
                    kill(getppid(),SIGUSR1);
                    close(torzs1[0]);
                    close(torzs1[1]);
                    close(torzs2[1]);
                   int nbytes =  read(torzs2[0],readbuffer4,5*64*sizeof(char));
                  // printf("%d kiolvasva torzs2bol!\n",nbytes);
                    char out[5][64];
                    for(int idx=0;idx<5;idx++)
                    {
                        //printf("%s xd2bol \n",readbuffer4[idx]);
                    }
                    
                    int jdx=0;
                    close(oltobusz2[0]);
                    //printf("oltobusz2 indul!");
                    oltobuszgo(readbuffer4,oltobusz2,out);
                    //printf("cso2\n");
                    exit(0);
                }
                else // szülő
                {
                    char oltandok[5][64];
                    char oltandok2[5][64];
                    int jdx=0;
                    for(int idx=5; idx<10; idx++)
                    {
                        strcpy(oltandok2[jdx++],names[idx]);
                    }
                    jdx=0;
                    for(int idx=0; idx<5; idx++)
                    {
                        strcpy(oltandok[jdx++],names[idx]);
                    }

                        printf("Oltobusz2 a kovetkezo betegeket varja: \n");
                        for(int idx=0; idx<5;idx++)
                        {
                            printf("%s ", oltandok2[idx]);
                        }
                        printf("\n");
                        printf("Oltobusz1 a kovetkezo betegeket varja: \n");
                        for(int idx=0; idx<5;idx++)
                        {
                            printf("%s ", oltandok[idx]);
                        }
                    
                    //printf("hali\n");
                    close(torzs1[0]);
                    close(torzs2[0]);
                    fflush(NULL);
                    int nbytes = 0; write(torzs1[1],oltandok,5*64);
                    close(torzs1[1]);
                    fflush(NULL);
                    //printf("%d byte beleirva szulo altal torzs1be!\n ",nbytes);
                    nbytes =  write(torzs2[1],oltandok2,5*64);
                    //printf("%d byte beleirva szulo altal torzs2be!\n ",nbytes);
                    close(torzs2[1]);
                    fflush(NULL); 
                    sleep(1);
                    close(oltobusz[1]);
                    close(oltobusz2[1]);
                    nbytes = read(oltobusz[0], readbuffer, sizeof(readbuffer));
                    //printf("Read string oltobuszbol:%d  \n",nbytes);
                    nbytes = read(oltobusz2[0], readbuffer2, sizeof(readbuffer));
                    //printf("Read string oltobusz2bol: %d  \n",nbytes);
                    close(oltobusz[1]);
                    close(oltobusz2[1]);
                    char beoltottak[10][66];
                    char* delim =",";
                    printf("\n -------------------------------OSSZEFOGLALO----------------------------- \n");
                    for(int idx=0;idx<5;idx++)
                    {   
                        if(!strcmp("",readbuffer[idx])==0)
                        {
                            if(getvaccinated(readbuffer[idx])==1)
                            {
                                printf("a kovetkezo szemely beoltasra,naplozasra kerult: %s \n",readbuffer[idx]);
                            }
                        }
                        if(!strcmp("",readbuffer2[idx])==0)
                        {
                            if(getvaccinated(readbuffer2[idx])==1)
                            {
                                printf("a kovetkezo szemely beoltasra,naplozasra kerult: %s \n",readbuffer2[idx]);
                            }
                        }

                    }
                }
            } else { // ha csak 1 oltobusz indul, szülő
                    char oltandok[5][64];
                    int jdx=0;
                    for(int idx=0; idx<5; idx++)
                    {
                        strcpy(oltandok[jdx++],names[idx]);
                    }
                        printf("\n");
                        printf("Oltobusz1 a kovetkezo betegeket varja: \n");
                        for(int idx=0; idx<5;idx++)
                        {
                            printf("%s ", oltandok[idx]);
                        } 
                    close(torzs1[0]);
                    fflush(NULL);
                    int nbytes = 0; write(torzs1[1],oltandok,5*64);
                    close(torzs1[1]);
                    fflush(NULL);
                    sleep(1);
                    close(oltobusz[1]);
                    close(oltobusz2[1]);
                    nbytes = read(oltobusz[0], readbuffer, sizeof(readbuffer));
                    //printf("Read string oltobuszbol:%d  \n",nbytes);
                    close(oltobusz[1]);
                    close(oltobusz2[1]);
                    char beoltottak[10][66];
                    char* delim =",";

                    printf("\n -------------------------------OSSZEFOGLALO----------------------------- \n");
                    for(int idx=0;idx<5;idx++)
                    {   
                        if(!strcmp("",readbuffer[idx])==0)
                        {
                        getvaccinated(readbuffer[idx]);
                        printf("a kovetkezo szemely beoltasra,naplozasra kerult: %s \n",readbuffer[idx]);
                        }
                    }
            }
        }
    }
}

int main(int argc, char** argv)
{
    printf("Udvozlom a vakcina regisztracios C programban! \n ");
    while(1)
    {
        int choice = 0;
        printf("\nMit szeretne tenni? irja be a megfelelo szamot.\n 1. -> Uj szemely felvetele \n 2. -> Meglevo szemely modositasa \n 3. -> Meglevo szemely torlese. \n 4. -> Listazas. \n 5. -> Uj nap kel fel. \n 6. -> Kilepes. \n");
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
            case 5: indulamandula(); sleep(5); break;
            case 6: return 0;
            default: printf("nem ertelmezett kod, kerem a megadott szamok kozul valasszon\n"); fflush(NULL); break;              
        }
    }
    return 1;
    

    return 0;

}