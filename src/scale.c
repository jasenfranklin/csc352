#include <stdio.h>

#include "bcd.h"

int main() {
    BCD *x;
    while ((x = read_bcd()) != NULL) {
        char *str = bcd_to_string(x);
        int audit = audit_digits(x->least_significant_digit);
        printf("%s (audit=%d)\n", str, audit);
        for (int i = 1; i < 10; i++) {
            x = scale_bcd(x, i);
            str = bcd_to_string(x);
            audit = audit_digits(x->least_significant_digit);
            printf("scaled by %d: %s (audit=%d)\n", i, str, audit);
        }
    }
}