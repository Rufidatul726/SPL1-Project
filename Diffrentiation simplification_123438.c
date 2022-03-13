#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


void simplification(char *a) {
       int i,j=1,k=0;
    int count=0;

    //parting in substring to compare
    char part[1000][1000];
    part[0][0]='+';
    for(i=0;i<strlen(a);i++){
         part[count][j++]=a[i];
        if(a[i+1]=='+' || a[i+1]=='-'  || a[i+1]=='\0'){
               //printf("%s ",part[count]);
            count++;
            j=0;
        }
    }

      //Normalizing
    char temp[5]={"1*"};
    for(i=0;i<count;i++){
        if(part[i][1]<='0' || part[i][1]>='9'){
            insert(part[i],temp,1);
        }
        //printf("Norm %s\n", part[i]);
    }

    //finding coefficient
    char coefficient[1000][100]={'0'};
    int coeff[10000];
    for(i=0;i<count;i++){
        for(j=0;j<strlen(part[i]);j++){
            coefficient[i][k++]=part[i][j];
            if((part[i][j+1]<48|| part[i][j+1]>57)){
                    k=0;
                    break;}
        }
        //printf("%s\t",coefficient[i]);
        coeff[i]=atoi(coefficient[i]);
        //printf("%d\n",coeff[i]);
    }

    //simplifying
   char nocoeff[1000][100];

    for(i=0;i<count;i++){
        k=0;
        for(j=strlen(coefficient[i]);j<strlen(part[i]);j++){
            nocoeff[i][k++]=part[i][j];
        }
        //printf("%s\n", nocoeff[i]);
    }

    //comparing
    int val=0;
    int value[1000]={0};
    for(i=0;i<count;i++){
        if(nocoeff[i][0]=='\0')continue;
        for(j=i+1;j<count;j++){
            val= strcmp(nocoeff[i], nocoeff[j]);
            //printf("%s,%s\n",nocoeff[i], nocoeff[j]);
            if(val==0){
                coeff[i]=coeff[i]+coeff[j];
                nocoeff[j][0]='\0';
            }
            sprintf(coefficient[i], "%d", coeff[i]);
            if(coeff[i]==0){
                coefficient[i][0]='\0';
                nocoeff[i][0]='\0';
            }
        }
    }


    char temparray[100][100];
    j=0;
    int countagain=0;
    for(i=0;i<count;i++){
        if(nocoeff[i][0]=='\0' ){
            countagain++;
            continue;
        }

        strcpy(temparray[j],coefficient[i]);
        strcat(temparray[j++],nocoeff[i]);
        nocoeff[i][0]='\0';
    }
    j=0;
     a[0]='\0';
    strcat(a,temparray[0]);

    for(i=0;i<count-countagain;i++){
              if(temparray[j][0]!='-')strcat(a,"+");
        strcat(a, temparray[j]);
        strcpy(nocoeff[i],temparray[j++]);
        //printf("%s ",nocoeff[i]);
    }

}


void insert(char *from, char *insert_string, int pos){
        char x[1000];
        int i, j=0;
        for(i=0;i<pos;i++){
            x[i]=from[i];
        }
        for(i=pos;i<strlen(insert_string)+pos;i++){
            x[i]=insert_string[i-pos];
        }

        for(i=pos+strlen(insert_string);i<strlen(from)+strlen(insert_string);i++){
            x[i]=from[i-strlen(insert_string)];
        }
        x[i]='\0';

        strcpy(from, x);
}
