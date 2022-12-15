#define XXX &none
#define ___ &trans

#define BASE 0
#define NAV 1
#define SYM 2
#define NUM 3
#define MEDIA 4
#define FUN 5
#define MOUSE 6

#define SK(KEY) &nk KEY KEY
#define MO(LAYER, TAP) &mo_tap LAYER TAP

#define U_MT(MOD, TAP) &u_mt MOD TAP
#define U_LT(LAYER, TAP) &u_lt LAYER TAP
#define U_TD(ONE, TWO) &u_td ONE TWO

#define _BT_SEL_KEYS_ &bt BT_SEL 0 &bt BT_SEL 1 &bt BT_SEL 2 &bt BT_SEL 3 &bt BT_SEL 4
#define _BT_CFG_KEYS_ &bt BT_CLR &trans &out OUT_TOG

// Keep sticky keys active for a long time so they effectively do not time out
#define STICKY_KEY_TIMEOUT 60000

#define COMBO_TIMEOUT 100
#define U_TAPPING_TERM 200
#define QUICK_TAP_MS 175

// Apple "Globe" key
// https://github.com/zmkfirmware/zmk/issues/947
#define GLOBE CAPSLOCK

