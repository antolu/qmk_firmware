/* Copyright 2015-2017 Jack Humbert
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
#include "keymap_nordic.h"
#include "keymap_swedish.h"
#include "muse.h"
#include "quantum.h"
#include "song_list.h"

#undef TAP_DANCE_ENABLE
#define TAP_DANCE_ENABLE yes

#ifdef AUDIO_ENABLE
float qwerty_song[][2] = SONG(QWERTY_SOUND);
float colemak_song[][2] = SONG(COLEMAK_SOUND);
float plover_song[][2] = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
float numpad_song[][2] = SONG(NUM_LOCK_ON_SOUND);
float rickroll[][2] = SONG(RICK_ROLL);
#endif

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _NUMBER,
  _NAVIGATE,
  _SYMBOL,
  _NUMPAD,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  PLOVER,
  EXT_PLV,
  NAVICATE,
  SYMBOL,
  NUMBER,
  NUMPAD,
  RICKRL,
  BACKLIT
};

#define CTRL_ESC LCTL_T(KC_ESC)
#define MACOS_LCK LCTL(LSFT(KC_SYSTEM_POWER))
#define CL_LEFT LCTL(KC_LEFT)
#define CL_RGHT LCTL(KC_RIGHT)
#define CL_UP LCTL(KC_UP)
#define CL_DOWN LCTL(KC_DOWN)
#define NUMBER MO(_NUMBER)
#define SYMBOL MO(_SYMBOL)
#define NAVIGATE MO(_NAVIGATE)

enum { TD_QUOTE = 0, TD_LCTL, TD_LSFT, TD_RCTL };

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

int cur_dance(tap_dance_state_t *state);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /* Qwerty International
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | ' / "|
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Enter|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  (/[ |  Del | Win  | Alt  |  Num |    Space    | Sym  | Nav  | Del |  Alt  |  )/] |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_planck_grid(
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTRL_ESC, KC_A,   KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        TD(TD_LSFT),  KC_Z,   KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, SC_SENT,
        TD(TD_LCTL),  KC_LGUI,KC_LALT, NAVIGATE,NUMBER,KC_SPC, KC_SPC, SYMBOL,NAVIGATE,KC_DEL , KC_RALT, TD(TD_RCTL)
        ),

    /* Colemak
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |     |
     * `-----------------------------------------------------------------------------------'
     */
    [_COLEMAK] = LAYOUT_planck_grid(
        _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______,
        _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______,
        _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        ),

    /* Symbol
     * ,-----------------------------------------------------------------------------------------------------------.
     * |        |   F11  |   F12  |   F13  |   F14  |   F15  |   F16  |   F17  |   F18  |   F19  |   F20  |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |    !   |    @   |    #   |    $   |    %   |    ^   |    &   |    *   |    (   |    )   |    =   |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |    _   |    +   |    ~   |    |   |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |  Held  |        |        |        |        |
     * `-----------------------------------------------------------------------------------------------------------'
     */
    [_SYMBOL] = LAYOUT_planck_grid(
        _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
        _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0),  KC_EQL,
        _______, KC_UNDS, KC_PLUS, KC_TILDE,KC_PIPE, _______, _______, _______, _______, KC_LCBR, KC_RCBR, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        ),

    /* Navigate
     * ,-----------------------------------------------------------------------------------------------------------.
     * |        |   <<   |  Mute  |   >|   |   >>   |        |        |  Home  |  PgDn  |  PgDn  |  End   |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |  Ctrl← | Ctrl ↓ | Ctrl ↑ | Ctrl → |        |    ←   |    ↓   |    ↑   |    →   |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |  Sup1  |  Sup2  |  Sup3  |  Sup4  |  Sup5  |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |
     * `-----------------------------------------------------------------------------------------------------------'
     */
    [_NAVIGATE] = LAYOUT_planck_grid(
        _______, KC_MPRV, KC_MUTE, KC_MPLY, KC_MNXT, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
        _______, CL_LEFT, CL_DOWN, CL_UP,   CL_RGHT, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
        _______, G(KC_1), G(KC_2), G(KC_3), G(KC_4), G(KC_5), _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        ),

    /* Number
     * ,-----------------------------------------------------------------------------------------------------------.
     * |    `   |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |   F10  |   Del|
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |    1   |    2   |    3   |    4   |    5   |    6   |    7   |    8   |    9   |     0  |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | CW Togg|    -   |    =   |    `   |    \   |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |
     * `-----------------------------------------------------------------------------------------------------------'
     */
    [_NUMBER] = LAYOUT_planck_grid(
        KC_GRAVE,KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        CW_TOGG, KC_MINUS,KC_EQUAL,KC_GRAVE,KC_BSLS, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        ),

    /* Numpad
     * ,-----------------------------------------------------------------------------------.
     * |  TAB |   7  |   8  |   9  |   *  |      |      |      |      |      |      |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |  Esc |   4  |   5  |   6  |   -  |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |  Bspc|   1  |   2  |   3  |   +  |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  Ent |   0  |   ,  |   /  |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_NUMPAD] = LAYOUT_planck_grid(
        KC_TAB,  KC_P7, KC_P8,   KC_P9,   KC_MPLY, _______, _______, _______, _______, _______, _______, _______,
        KC_ESC,  KC_P4, KC_P5,   KC_P6,   KC_PMNS, _______, _______, _______, _______, _______, _______, _______,
        KC_BSPC, KC_P1, KC_P2,   KC_P3,   KC_PPLS, _______, _______, _______, _______, _______, _______, _______,
        KC_PENT, KC_P0, KC_PDOT, KC_PSLS, _______, _______, _______, _______, _______, _______, _______, _______),

    /* Plover layer (http://opensteno.org)
     * ,-----------------------------------------------------------------------------------.
     * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_PLOVER] = LAYOUT_planck_grid(
        KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1,
        XXXXXXX, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC,
        XXXXXXX, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        EXT_PLV, XXXXXXX, XXXXXXX, KC_C, KC_V, XXXXXXX, XXXXXXX, KC_N, KC_M, XXXXXXX, XXXXXXX, XXXXXXX
        ),

    /* Number
     * ,-----------------------------------------------------------------------------------------------------------.
     * |        |        |        |        |        |        |        |        |        |        |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | QMK RST| RickRL |        |  MusOn | Aud On | MIDIOn |        | Colemak| QWERTY | NUMPAD | PLOVER |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |  MusOff| Aud Off| MIDIOff|        |        |        | NumLck | CpsLck |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |
     * `-----------------------------------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_planck_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        QK_BOOT,  RICKRL, _______, MU_ON,   AU_ON,   MI_ON,   _______, COLEMAK, QWERTY,  NUMPAD, PLOVER,  _______,
        _______, _______, _______, MU_OFF,  AU_OFF,  MI_OFF,  _______, _______, _______, KC_NUM, KC_CAPS, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)
    // clang-format on
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUMBER, _SYMBOL, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case QWERTY:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
#ifdef AUDIO_ENABLE
      PLAY_SONG(qwerty_song);
#endif
    }
    return false;
  case COLEMAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_COLEMAK);
#ifdef AUDIO_ENABLE
      PLAY_SONG(colemak_song);
#endif
    }
    return false;
  case NUMPAD:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_NUMPAD);
#ifdef AUDIO_ENABLE
      PLAY_SONG(numpad_song);
#endif
    }
  case PLOVER:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      stop_all_notes();
      PLAY_SONG(plover_song);
#endif
      layer_off(_ADJUST);
      layer_on(_PLOVER);
      if (!eeconfig_is_enabled()) {
        eeconfig_init();
      }
      keymap_config.raw = eeconfig_read_keymap();
      keymap_config.nkro = 1;
      eeconfig_update_keymap(keymap_config.raw);
    }
    return false;
  case EXT_PLV:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(plover_gb_song);
#endif
      layer_off(_PLOVER);
      layer_on(_QWERTY);
    }
    return false;
  case BACKLIT:
    if (record->event.pressed) {
      register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
      backlight_step();
#endif
#ifdef KEYBOARD_planck_rev5
      PORTE &= ~(1 << 6);
#endif
    } else {
      unregister_code(KC_RSFT);
#ifdef KEYBOARD_planck_rev5
      PORTE |= (1 << 6);
#endif
    }
    return false;
  case RICKRL:
    if (record->event.pressed) {
      PLAY_SONG(rickroll);
    }
    return false;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (clockwise) {
      muse_tempo += 1;
    } else {
      muse_tempo -= 1;
    }
  } else {
    if (clockwise) {
#ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_DOWN);
#else
      tap_code(KC_PGDN);
#endif
    } else {
#ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_UP);
#else
      tap_code(KC_PGUP);
#endif
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
  case 0:
    if (active) {
#ifdef AUDIO_ENABLE
      // PLAY_SONG(plover_song);
#endif
      layer_on(_ADJUST);
    } else {
#ifdef AUDIO_ENABLE
      // PLAY_SONG(plover_gb_song);
#endif
      layer_off(_ADJUST);
    }
    break;
  case 1:
    if (active) {
      muse_mode = true;
    } else {
      muse_mode = false;
#ifdef AUDIO_ENABLE
      stop_all_notes();
#endif
    }
  }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
  if (muse_mode) {
    if (muse_counter == 0) {
      uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
      if (muse_note != last_muse_note) {
        stop_note(compute_freq_for_midi_note(last_muse_note));
        play_note(compute_freq_for_midi_note(muse_note), 0xF);
        last_muse_note = muse_note;
      }
    }
    muse_counter = (muse_counter + 1) % muse_tempo;
  }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
  default:
    return true;
  }
}

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
    register_code16(KC_LPRN);
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
    unregister_code16(KC_LPRN);
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
    register_code16(KC_RPRN);
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
    unregister_code16(KC_RPRN);
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
    register_code(KC_LSFT);
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
    unregister_code(KC_LSFT);
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

tap_dance_action_t tap_dance_actions[] = {
    [TD_LCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lctrl_finished, lctrl_reset),
    [TD_LSFT] =
        ACTION_TAP_DANCE_FN_ADVANCED(NULL, lshift_finished, lshift_reset),
    [TD_RCTL] =
        ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctrl_finished, rctrl_reset)};