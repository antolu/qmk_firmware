/* Copyright 2022 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "quantum.h"

#undef TAP_DANCE_ENABLE
#define TAP_DANCE_ENABLE yes

// clang-format off

enum layers {
    MAC_BASE,
    WIN_BASE,
    _FN1,
    _FN2,
    _FN3
};

enum { TD_QUOTE = 0, TD_LCTL, TD_LSFT, TD_RCTL, TD_RSFT };

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5,
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

// for the x tap dance. Put it here so it can be used in any keymap
void lctrl_finished(tap_dance_state_t *state, void *user_data);
void lctrl_reset(tap_dance_state_t *state, void *user_data);
void rctrl_finished(tap_dance_state_t *state, void *user_data);
void rctrl_reset(tap_dance_state_t *state, void *user_data);
void lshift_finished(tap_dance_state_t *state, void *user_data);
void lshift_reset(tap_dance_state_t *state, void *user_data);
void rshift_finished(tap_dance_state_t *state, void *user_data);
void rshift_reset(tap_dance_state_t *state, void *user_data);

int cur_dance(tap_dance_state_t *state);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_61(
        KC_GRV,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_ESC,  KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,
        TD(TD_LSFT),       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            TD(TD_RSFT),
        TD(TD_LCTL), KC_LOPT,  KC_LCMD,                        KC_SPC,                             KC_RCMD,  MO(_FN2), MO(_FN3), TD(TD_RCTL)),

    [WIN_BASE] = LAYOUT_ansi_61(
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,           _______,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,           _______,
        _______, KC_LGUI, MO(_FN1),                            _______,                            KC_RALT, MO(_FN2) , MO(_FN3), _______),

    [_FN1] = LAYOUT_ansi_61(
        KC_GRV,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,   KC_DEL,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,
        KC_CAPS, _______,  _______, _______, _______, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT, _______,  _______,            _______,
        _______,           _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______,  _______,            CW_TOGG,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),

    [_FN2] = LAYOUT_ansi_61(
        KC_GRV,  KC_BRID,  KC_BRIU, KC_NO,   KC_NO,   RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  RGB_MOD,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, KC_APP,  KC_SCRL, KC_INS,   KC_PGUP,  KC_HOME,  _______,
        _______, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, KC_UP,   KC_PSCR, KC_PGDN,  KC_END,             _______,
        _______,           _______, _______, _______, _______, _______, NK_TOGG, KC_LEFT, KC_DOWN, KC_RIGHT, KC_DEL,             _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______),

    [_FN3] = LAYOUT_ansi_61(
        KC_TILD, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______,  _______,  _______,  _______,
        _______, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______,  _______,            _______,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______)
};

// clang-format on

int cur_dance(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)
      return SINGLE_TAP;
    // key has not been interrupted, but they key is still held. Means you want
    // to send a 'HOLD'.
    else
      return SINGLE_HOLD;
  } else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually
     * wanting a double tap action when hitting 'pp'. Suggested use case for
     * this return value is when you want to send two keystrokes of the key, and
     * not the 'double tap' action/macro.
     */
    if (state->interrupted)
      return DOUBLE_SINGLE_TAP;
    else if (state->pressed)
      return DOUBLE_HOLD;
    else
      return DOUBLE_TAP;
  }
  // Assumes no one is trying to type the same letter three times (at least not
  // quickly). If your tap dance key is 'KC_W', and you want to type "www."
  // quickly - then you will need to add an exception here to return a
  // 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)
      return TRIPLE_TAP;
    else
      return TRIPLE_HOLD;
  } else
    return 8; // magic number. At some point this method will expand to work for
              // more presses
}

static tap lctrl_state = {.is_press_action = true, .state = 0};
static tap rctrl_state = {.is_press_action = true, .state = 0};
static tap lshift_state = {.is_press_action = true, .state = 0};

void lctrl_finished(tap_dance_state_t *state, void *user_data) {
  lctrl_state.state = cur_dance(state);
  switch (lctrl_state.state) {
  case SINGLE_TAP:
    register_code(KC_LBRC);
    break;
  case SINGLE_HOLD:
    register_code(KC_LCTL);
    break;
  case DOUBLE_TAP:
    register_code(KC_LBRC);
    break;
  case TRIPLE_TAP:
    register_code16(KC_LCBR);
    break;
  case DOUBLE_SINGLE_TAP:
    register_code16(KC_LPRN);
    break;
  }
}

void lctrl_reset(tap_dance_state_t *state, void *user_data) {
  switch (lctrl_state.state) {
  case SINGLE_TAP:
    unregister_code(KC_LBRC);
    break;
  case SINGLE_HOLD:
    unregister_code(KC_LCTL);
    break;
  case DOUBLE_TAP:
    unregister_code(KC_LBRC);
    break;
  case TRIPLE_TAP:
    unregister_code16(KC_LCBR);
    break;
  /* case DOUBLE_HOLD: unregister_code(KC_LALT); */
  case DOUBLE_SINGLE_TAP:
    unregister_code16(KC_LPRN);
    break;
  }
  lctrl_state.state = 0;
}

void rctrl_finished(tap_dance_state_t *state, void *user_data) {
  rctrl_state.state = cur_dance(state);
  switch (rctrl_state.state) {
  case SINGLE_TAP:
    register_code(KC_RBRC);
    break;
  case SINGLE_HOLD:
    register_code(KC_RCTL);
    break;
  case DOUBLE_TAP:
    register_code(KC_RBRC);
    break;
  case TRIPLE_TAP:
    register_code16(KC_RCBR);
    break;
  case DOUBLE_SINGLE_TAP:
    register_code16(KC_RPRN);
    break;
  }
}

void rctrl_reset(tap_dance_state_t *state, void *user_data) {
  switch (rctrl_state.state) {
  case SINGLE_TAP:
    unregister_code(KC_RBRC);
    break;
  case SINGLE_HOLD:
    unregister_code(KC_RCTL);
    break;
  case DOUBLE_TAP:
    unregister_code(KC_RBRC);
    break;
  case TRIPLE_TAP:
    unregister_code16(KC_RCBR);
    break;
  /* case DOUBLE_HOLD: unregister_code(KC_LALT); */
  case DOUBLE_SINGLE_TAP:
    unregister_code16(KC_RPRN);
    break;
  }
  rctrl_state.state = 0;
}

void lshift_finished(tap_dance_state_t *state, void *user_data) {
  lshift_state.state = cur_dance(state);
  switch (lshift_state.state) {
  case SINGLE_TAP:
    register_code16(KC_LPRN);
    break;
  case SINGLE_HOLD:
    register_code(KC_LSFT);
    break;
  case DOUBLE_TAP:
    caps_word_on();
    break;
  case TRIPLE_TAP:
    register_code(KC_CAPS);
    break;
  }
}

void lshift_reset(tap_dance_state_t *state, void *user_data) {
  switch (lshift_state.state) {
  case SINGLE_TAP:
    unregister_code16(KC_LPRN);
    break;
  case SINGLE_HOLD:
    unregister_code(KC_LSFT);
    break;
  case DOUBLE_TAP:
    break;
  case TRIPLE_TAP:
    unregister_code(KC_CAPS);
    break;
  }
  lshift_state.state = 0;
}

void rshift_finished(tap_dance_state_t *state, void *user_data) {
  lshift_state.state = cur_dance(state);
  switch (lshift_state.state) {
  case SINGLE_TAP:
    register_code16(KC_RPRN);
    break;
  case SINGLE_HOLD:
    register_code(KC_RSFT);
    break;
  case DOUBLE_TAP:
    caps_word_on();
    break;
  case TRIPLE_TAP:
    register_code(KC_CAPS);
    break;
  }
}

void rshift_reset(tap_dance_state_t *state, void *user_data) {
  switch (lshift_state.state) {
  case SINGLE_TAP:
    unregister_code16(KC_RPRN);
    break;
  case SINGLE_HOLD:
    unregister_code(KC_RSFT);
    break;
  case DOUBLE_TAP:
    break;
  case TRIPLE_TAP:
    unregister_code(KC_CAPS);
    break;
  }
  lshift_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lctrl_finished, lctrl_reset),
    [TD_LSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lshift_finished, lshift_reset),
    [TD_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctrl_finished, rctrl_reset),
    [TD_RSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rshift_finished, rshift_reset),
};


bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
