#include <stdio.h>

#include "bcd.h"

int main() {
    BCD *x;
    BCD *y;
    BCD *sum = zero();
   x = read_bcd();
   y=read_bcd();
        char *str = bcd_to_string(x);
        int audit = audit_digits(x->least_significant_digit);
        printf("%s (audit=%d)\n", str, audit);
        sum = multiply_bcd(x, y);
        str = bcd_to_string(sum);
        audit = audit_digits(sum->least_significant_digit);
        printf("product: %s (audit=%d)\n", str, audit);
}
