#define XXX &none
#define ___ &trans

#define BASE 0
#define NAV 1
#define NUM 2

#define SK(KEY) &nk KEY KEY
#define MO(LAYER) &mo_tap LAYER F24

#define U_MT(MOD, TAP) &u_mt MOD TAP
#define U_LT(LAYER, TAP) &u_lt LAYER TAP

// Keep sticky keys active for a long time so they effectively do not time out
#define STICKY_KEY_TIMEOUT 60000

#define U_TAPPING_TERM 200

// Apple "Globe" key
// https://github.com/zmkfirmware/zmk/issues/947
#define GLOBE CAPSLOCK
