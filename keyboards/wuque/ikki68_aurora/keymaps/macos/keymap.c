#include QMK_KEYBOARD_H
#define KC_GESC QK_GESC

/* Apple 功能键（QK_KB 通道，VIA 显示名由本地定义文件 customKeycodes 提供）：
 * AP_GLOBE = CUSTOM(0)；AP_MISSION = CUSTOM(1)；AP_FOCUS = CUSTOM(2)
 * DEF_WIN = CUSTOM(3)；DEF_MAC = CUSTOM(4)（持久化默认层，替代 VIA 不识别的 PDF 键码） */
enum custom_keycodes {
    AP_GLOBE = QK_KB_0,
    AP_MISSION = QK_KB_1,
    AP_FOCUS = QK_KB_2,
    DEF_WIN = QK_KB_3,
    DEF_MAC = QK_KB_4,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AP_GLOBE:
            if (record->event.pressed) {
                register_code(KC_GLOBE);
            } else {
                unregister_code(KC_GLOBE);
            }
            return false;
        case AP_MISSION:
            if (record->event.pressed) {
                register_code(KC_MISSION_CONTROL);
            } else {
                unregister_code(KC_MISSION_CONTROL);
            }
            return false;
        case AP_FOCUS:
            if (record->event.pressed) {
                register_code(KC_DND);
            } else {
                unregister_code(KC_DND);
            }
            return false;
        case DEF_WIN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(0);
            }
            return false;
        case DEF_MAC:
            if (record->event.pressed) {
                set_single_persistent_default_layer(1);
            }
            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: 默认层 */
    [0] = LAYOUT_all(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,    KC_INS, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,             KC_DEL, KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,             KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           KC_SPC,           KC_SPC,           MO(2),   MO(3),   AP_GLOBE,            KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /* Layer 1: Mac 模式（交换左 GUI/ALT） */
    [1] = LAYOUT_all(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, _______,    KC_INS, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,             KC_DEL, KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, _______,             KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,          _______,          KC_SPC,           _______,          MO(2),   MO(3),   AP_GLOBE,            KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /* Layer 2: 功能键层 */
    [2] = LAYOUT_all(
        KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, _______,    XXXXXXX, KC_HOME,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX, KC_END,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,             XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,          _______,          XXXXXXX,          _______,          XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX, XXXXXXX
    ),
    /* Layer 3: 媒体/系统控制层 */
    [3] = LAYOUT_all(
        XXXXXXX, KC_BRID, KC_BRIU, AP_MISSION, KC_WSCH, XXXXXXX, AP_FOCUS,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, _______,    XXXXXXX, UG_NEXT,
        XXXXXXX, DEF_WIN, DEF_MAC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX, UG_PREV,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          UG_TOGG,
        XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,             UG_VALU,
        XXXXXXX, XXXXXXX, XXXXXXX,          _______,          XXXXXXX,          _______,          XXXXXXX, XXXXXXX, XXXXXXX,             UG_SPDD, UG_VALD, UG_SPDU
    ),
};
