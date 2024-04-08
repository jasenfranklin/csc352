#include <stdio.h>
#include "bcd.h"
int audit_digits(Digit *d){
	if((d <=9 &&c>=0)&&(d->next_higher_digit==NULL||audit_digits(d->next_higher_digit))){
		return 1;
	}else{
		return 0;
	}
}
char *bcd_to_string(BCD *bcd){
	
}
BCD* read_bcd(){
	
}
BCD* zero(){
	
}
BCD* add_bcd(BCD* a, BCD* b){
	
}
BCD* scale_bcd(BCD* a, int scale){
	
}

int main(){

	return 0;
}
