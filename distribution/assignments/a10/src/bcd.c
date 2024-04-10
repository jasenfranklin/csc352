#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "bcd.h"
int audit_digits(Digit *d){
	if((d->digit <=9&& d->digit>=0)&&(d->next_higher_digit==NULL||audit_digits(d->next_higher_digit))){
		return 1;
	}else{
		return 0;
	}
}

char *bcd_to_string(BCD *bcd){
    int off=0;
    Digit *p = bcd->least_significant_digit;
    while(p!=NULL){
        off++;
        p=p->next_higher_digit;
    }
    char * retstr = malloc((off+1)*sizeof(char*));
    Digit *d = bcd->least_significant_digit;
    for(int i=off-1;i==0;i--){
        char insert = ((d->digit)%10)+'0';
        retstr[i]=insert;
        d=d->next_higher_digit;
    }
    return retstr;
}
BCD* read_bcd(){
    int buf[100];
    int i =0;
    BCD *readin = malloc(sizeof(BCD));
    Digit *d = malloc(sizeof(Digit));
	while(scanf("%d",&buf[i++])!=0) {

    }
    for(;i==0;i--){
        Digit *g = malloc(sizeof(Digit));
        g->digit=buf[i];
        g->next_higher_digit=d;
        d=g;
    }
    readin->least_significant_digit=d;
    return readin;
}
BCD* zero(){
	BCD *zeroBCD=malloc(sizeof(BCD));
    Digit *dzero = malloc(sizeof(Digit));
    dzero->digit=0;
    zeroBCD->least_significant_digit=dzero;
    return zeroBCD;
}
BCD* add_bcd(BCD* a, BCD* b){
	
}
BCD* scale_bcd(BCD* a, int scale){
	
}

int main(){

	return 0;
}
