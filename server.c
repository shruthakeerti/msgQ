#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

int main(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;

FILE *fp;
fp = fopen("server_log.txt","w+");

    if ((key = ftok("even.c", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }
    
    printf("spock: ready to receive equations\n");

    for(;;) { /* Spock never quits! */
        if (msgrcv(msqid, &buf, sizeof buf.mtext, 0, 0) == -1) 
        {
            perror("msgrcv");
            exit(1);
        }
printf("Result saving to file\n");
int i=0,k=0,l=0;
char op;
//converting string to decimal
while(1){
k=k*10 + ((buf.mtext[i])-48);
i++;
op=(buf.mtext[i]);
if(op=='+' | op=='*'|op=='-' | op=='/' )
break;
}

i++;
while(buf.mtext[i]!='\0'){
l=l*10 + ((buf.mtext[i])-48);
i++;
}
//writing to the file
if(op=='+')
{
fprintf(fp,"client :%ld",buf.mtype);
fprintf(fp,"\n");
fprintf(fp,"%s",buf.mtext);
fprintf(fp,"\n");
fprintf(fp,"%d",k+l);
fprintf(fp,"\n");
fflush(fp);
}
if(op=='*')
{fprintf(fp,"client :%ld",buf.mtype);
fprintf(fp,"\n");
fprintf(fp,"%s",buf.mtext);
fprintf(fp,"\n");
fprintf(fp,"%d",k*l);
fprintf(fp,"\n");
fflush(fp);
}

if(op=='/')
{
fprintf(fp,"client :%ld",buf.mtype);
fprintf(fp,"\n");
fprintf(fp,"%s",buf.mtext);
fprintf(fp,"\n");
fprintf(fp,"%d",(k/l));
fprintf(fp,"\n");
fflush(fp);
}
if(op=='-')
{fprintf(fp,"client :%ld",buf.mtype);
fprintf(fp,"\n");
fprintf(fp,"%s",buf.mtext);
fprintf(fp,"\n");
fprintf(fp,"%d",k-l);
fprintf(fp,"\n");
fflush(fp);
}

}
    if (msgctl(msqid, IPC_RMID, NULL) == -1) //deleting meag quee
    {
        perror("msgctl");
        exit(1);
    }


return 0;
}
