#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "bcd.h"
#include "expr.h"
int audit_digits(Digit *d) {
	if ((d->digit <= 9 && d->digit >= 0)
			&& (d->next_higher_digit == NULL
					|| audit_digits(d->next_higher_digit))) {
		return 1;
	} else {
		return 0;
	}
}

char* bcd_to_string(BCD *bcd) {
	int off = 0;
	Digit *p = bcd->least_significant_digit;
	while (p != NULL) {
		off++;
		p = p->next_higher_digit;
	}
	char *retstr = malloc((off + 1) * sizeof(char*));
	Digit *d = bcd->least_significant_digit;
	for (int i = off - 1; i >= 0; i--) {
		char insert = ((d->digit) % 10) + '0';
		retstr[i] = insert;
		d = d->next_higher_digit;
	}
	retstr[off] = '\0';
	return retstr;
}
BCD* string_to_bcd(char *s) {
	int len = strlen(s);
	BCD *bcdhead = malloc(sizeof(BCD));
	Digit *head = malloc(sizeof(Digit));
	Digit pho;
	pho.next_higher_digit = head;
	Digit *p = head;
	for (len--; len >= 0; len--) {
		p->digit = (s[len] - '0');
		p->next_higher_digit = malloc(sizeof(Digit));
		p = p->next_higher_digit;	
	}
	p->next_higher_digit=NULL;
	bcdhead->least_significant_digit = pho.next_higher_digit;
	return bcdhead;
}
BCD* read_from_input(char *buf) {
	int i = 0;
	BCD *readin = malloc(sizeof(BCD));
	Digit *head = malloc(sizeof(Digit));
	Digit phony;
	phony.next_higher_digit = head;
	Digit *d = &phony;
	if (buf != 0) {
		int len = strlen(buf);
		for (int i = len - 1; i >= 0; i--) {
			d->next_higher_digit = malloc(sizeof(Digit));
			d->next_higher_digit->digit = buf[i] - '0';
			d->next_higher_digit->next_higher_digit = NULL;
			d = d->next_higher_digit;

		}
		readin->least_significant_digit = phony.next_higher_digit;
		return readin;
	}
	return NULL;
}
BCD* read_bcd() {
	char buf[100];
	int i = 0;
	BCD *readin = malloc(sizeof(BCD));
	Digit *head = malloc(sizeof(Digit));
	Digit phony;
	phony.next_higher_digit = head;
	Digit *d = &phony;
	if (scanf("%s", buf) != EOF) {
		int len = strlen(buf);
		for (int i = len - 1; i >= 0; i--) {
			d->next_higher_digit = malloc(sizeof(Digit));
			d->next_higher_digit->digit = buf[i] - '0';
			d->next_higher_digit->next_higher_digit = NULL;
			d = d->next_higher_digit;

		}
		readin->least_significant_digit = phony.next_higher_digit;
		return readin;
	}
	return NULL;
}
BCD* zero() {
	BCD *zeroBCD = malloc(sizeof(BCD));
	Digit *dzero = malloc(sizeof(Digit));
	dzero->digit = 0;
	zeroBCD->least_significant_digit = dzero;
	return zeroBCD;
}

BCD* add_bcd(BCD *a, BCD *b) {
	Digit *apoint = a->least_significant_digit;
	Digit *bpoint = b->least_significant_digit;
	BCD *ret = malloc(sizeof(BCD));
	Digit *head = malloc(sizeof(Digit));
	Digit phony;
	phony.next_higher_digit = head;
	Digit *p = &phony;
	int carry = 0;
	while (apoint != NULL || bpoint != NULL) {
		int temp = carry;
		if (apoint != NULL) {
			temp += apoint->digit;
			apoint = apoint->next_higher_digit;
		}
		if (bpoint != NULL) {
			temp += bpoint->digit;
			bpoint = bpoint->next_higher_digit;
		}
		p->next_higher_digit = malloc(sizeof(Digit));
		p = p->next_higher_digit;
		p->digit = temp % 10;
		carry = temp / 10;
	}
	if (carry) {
		p->next_higher_digit = malloc(sizeof(Digit));
		p = p->next_higher_digit;
		p->digit = carry;
	}
	p->next_higher_digit = NULL;
	ret->least_significant_digit = phony.next_higher_digit;
	return ret;
}

BCD* scale_bcd(BCD *a, int scale) {
	BCD *scaled = malloc(sizeof(BCD));
	Digit *temp = a->least_significant_digit;
	int carry = 0;
	Digit **curpointer = &scaled->least_significant_digit;
	while (temp != NULL) {
		int snum = temp->digit * scale + carry;
		carry = snum / 10;
		snum %= 10;
		Digit *newdigit = malloc(sizeof(Digit));
		newdigit->digit = snum;
		newdigit->next_higher_digit = NULL;
		*curpointer = newdigit;
		curpointer = &newdigit->next_higher_digit;
		temp = temp->next_higher_digit;
	}
	if (carry > 0) {
		Digit *carryplus = malloc(sizeof(Digit));
		carryplus->digit = carry;
		carryplus->next_higher_digit = NULL;
		*curpointer = carryplus;
	}
	return scaled;
}
BCD* multiply_bcd(BCD *a, BCD *b) {
	BCD *mult = malloc(sizeof(BCD));
	mult->least_significant_digit = NULL;
	int zadd = 1;
	Digit **curpointer = &mult->least_significant_digit;
	Digit *tempa = a->least_significant_digit;
	Digit *tempb;

	while (tempa != NULL) {
		int carry = 0;
		tempb = b->least_significant_digit;
		while (tempb != NULL) {
			int prod = (tempa->digit * tempb->digit) + carry;
			carry = prod / 10;
			prod %= 10;
			if (*curpointer == NULL) {
				*curpointer = malloc(sizeof(Digit));
				(*curpointer)->digit = prod;
				(*curpointer)->next_higher_digit = NULL;
			} else {
				(*curpointer)->next_higher_digit = malloc(sizeof(Digit));
				(*curpointer)->next_higher_digit->digit = prod;
				*curpointer = (*curpointer)->next_higher_digit;
			}

			tempb = tempb->next_higher_digit;
		}
		while (carry > 0) {
			*curpointer = malloc(sizeof(Digit));
			(*curpointer)->digit = carry % 10;
			(*curpointer)->next_higher_digit = NULL;
			carry /= 10;
			*curpointer = (*curpointer)->next_higher_digit;
		}
		for (int i = 0; i < zadd - 1; i++) {
			Digit *zdig = malloc(sizeof(Digit));
			zdig->digit = 0;
			zdig->next_higher_digit = NULL;
			(*curpointer) = zdig;
			curpointer = &(*curpointer)->next_higher_digit;
		}

		zadd++;
		tempa = tempa->next_higher_digit;
	}

	return mult;
}
