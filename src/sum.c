#include <stdio.h>

#include "bcd.h"

int main() {
    BCD *x;
    BCD *sum = zero();
    while ((x = read_bcd()) != NULL) {
        char *str = bcd_to_string(x);
        int audit = audit_digits(x->least_significant_digit);
        printf("%s (audit=%d)\n", str, audit);
        sum = add_bcd(sum, x);
        str = bcd_to_string(sum);
        audit = audit_digits(sum->least_significant_digit);
        printf("sum: %s (audit=%d)\n", str, audit);
    }
}