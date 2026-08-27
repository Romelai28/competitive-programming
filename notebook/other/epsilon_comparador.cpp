bool epsilon_equal(ld a, ld b) {return fabs(a-b) < EPSILON;}
bool epsilon_bigger(ld a, ld b) {return a > b+EPSILON;}
bool epsilon_smaller(ld a, ld b) {return a+EPSILON < b;}
bool epsilon_smaller_equal(ld a, ld b) {return a <= b+EPSILON;}
bool epsilon_bigger_equal(ld a, ld b) {return a+EPSILON >= b;}
