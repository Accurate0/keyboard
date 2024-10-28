#include "accurate0.h"
#include "os_detection.h"

#define KEEPALIVE_TIME_BETWEEN (1 * 60)

globals_t _globals = {.is_mac_os = false, .keepalive = {.enabled = false}};

void keepalive_toggle(void) {
    _globals.keepalive.enabled = !_globals.keepalive.enabled;
}

void keyboard_post_init_user(void) {
    /* debug_enable = true; */
    _globals.keepalive.last_keepalive = timer_read32();
}

void matrix_scan_user(void) {
    if (_globals.keepalive.enabled && timer_elapsed32(_globals.keepalive.last_keepalive) > KEEPALIVE_TIME_BETWEEN) {
        // send a f13 every minute when this is enabled
        _globals.keepalive.last_keepalive = timer_read32();
        // gnome has a keybind for F13...
        if(_globals.is_mac_os) {
            tap_code(KC_F13);
        } else {
            tap_code(KC_F24);
        }
    }
}

bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            _globals.is_mac_os = true;
            break;
        default:
            break;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_KAL:
            if (record->event.pressed) {
                keepalive_toggle();
                return false;
            }
            break;
    }

    return true;
}
