#define XXX &none
#define ___ &trans

#define BASE 0
#define NAV 1
#define SYM 2
#define NUM 3
#define MEDIA 4

#define SK(KEY) &nk KEY KEY
#define MO(LAYER) &mo_tap LAYER F24

#define U_MT(MOD, TAP) &u_mt MOD TAP
#define U_LT(LAYER, TAP) &u_lt LAYER TAP
#define U_TD(ONE, TWO) &u_td ONE TWO

#define HYP LS(LC(LA(LGUI)))
#define HYPER(key) LS(LC(LA(LG(key))))


// Keep sticky keys active for a long time so they effectively do not time out
#define STICKY_KEY_TIMEOUT 60000

#define U_TAPPING_TERM 200

// Apple "Globe" key
// https://github.com/zmkfirmware/zmk/issues/947
#define GLOBE CAPSLOCK
