#include QMK_KEYBOARD_H

enum custom_keycodes {
  KC_KAL = SAFE_RANGE,
};

typedef struct {
    struct {
        bool enabled;
        uint32_t last_keepalive;
    } keepalive;

} globals_t;

// runtime
extern globals_t _globals;