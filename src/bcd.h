typedef struct digit {
  int digit;
  struct digit* next_higher_digit;
} Digit;

typedef struct bcd {
  Digit* least_significant_digit;
} BCD;

extern int audit_digits(Digit *d);
extern char *bcd_to_string(BCD *bcd);
extern BCD* read_bcd();
extern BCD* add_bcd(BCD* a, BCD* b);
extern BCD* multiply_bcd(BCD* a, BCD* b);
extern BCD* scale_bcd(BCD* a, int scale);
extern BCD* zero();