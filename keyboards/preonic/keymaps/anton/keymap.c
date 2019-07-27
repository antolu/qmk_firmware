
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
#include "muse.h"
#include "keymap_swedish.h"
#include "song_list.h"

float se_song[][2] = SONG(QWERTY_SOUND);
float us_song[][2] = SONG(COLEMAK_SOUND);

enum preonic_layers {
  _QWERTY_SE,
  _LOWER_SE,
  _RAISE_SE,
  _QWERTY_US,
  _LOWER_US,
  _RAISE_US,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY_SE = SAFE_RANGE,
  QWERTY_US,
  LOWER_SE,
  RAISE_SE,
  LOWER_US,
  RAISE_US,
  BACKLIT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty Swedish
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   Å  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      | Win  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY_SE] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,   KC_6,   KC_7,     KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,   KC_Y,   KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,     KC_G,   KC_H,   KC_J,     KC_K,    KC_L,    NO_OSLH, NO_AE, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,   KC_N,   KC_M,     KC_COMM, KC_DOT,  NO_AA,   KC_ENT, \
  KC_LCTL, KC_LALT, KC_LGUI, KC_LALT, LOWER_SE, KC_SPC, KC_SPC, RAISE_SE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Lower Swedish
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |   +  |  -   |  =   |      |      |   7  |   8  |   9  |   ,  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   !  |   *  |  /   |  %   |  ^   | Home |   4  |   5  |   6  |      |  *   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  ?   |   '  |  "   |      |      |  End |   1  |   2  |   3  |  0   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER_SE] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, NO_PLUS, NO_MINS, NO_EQL,  _______, _______, KC_7,    KC_8,    KC_9,    KC_COMM, KC_BSPC, \
  NO_ACUT, S(KC_1), NO_ASTR, NO_SLSH, S(KC_5), NO_CIRC, KC_HOME, KC_4,    KC_5,    KC_6,    KC_DOT,  KC_PIPE, \
  KC_CAPS, NO_QUES, NO_APOS, NO_QUO2, _______, _______, KC_END,  KC_1,    KC_2,    KC_3 ,   KC_0,    _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise Swedish
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  |   |   &  |  \   |  $   |  '   |  "   |   (  |   {  |   [  | PgUp |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  £   |  #   |  @   |  _   |  "   |  ~   |   )  |   }  |   ]  | PgDn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE_SE] = LAYOUT_preonic_grid( \
  _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_F1,   KC_F2,      KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL, \
  _______, NO_PIPE, NO_AMPR,    NO_BSLS, NO_DLR,  NO_LESS, NO_GRTR, NO_LPRN, NO_LCBR, NO_LBRC, KC_PGUP, _______, \
  _______, NO_GRV,  LSFT(KC_3), NO_AT,   NO_UNDS, NO_QUOT, NO_TILD, NO_RPRN, NO_RCBR, NO_RBRC, KC_PGDN, _______, \
  _______, KC_PSCR, _______,    _______, _______, KC_SPC,  KC_SPC,  _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Qwerty International
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   \  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      | Win  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY_US] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,   KC_6,   KC_7,     KC_8,    KC_9,    KC_0,      KC_DEL, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,   KC_Y,   KC_U,     KC_I,    KC_O,    KC_P,      KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,     KC_G,   KC_H,   KC_J,     KC_K,    KC_L,    KC_SCOLON, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,   KC_N,   KC_M,     KC_COMM, KC_DOT,  KC_BSLS,   KC_ENT, \
  KC_LCTL, KC_LALT, KC_LGUI, KC_LALT, LOWER_US, KC_SPC, KC_SPC, RAISE_US, KC_LEFT, KC_DOWN, KC_UP,     KC_RGHT \
),

/* Lower International
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |   +  |  -   |  =   |      |      |   7  |   8  |   9  |   ,  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   !  |   *  |  /   |  %   |  ^   | Home |   4  |   5  |   6  |      |  *   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  ?   |   '  |  "   |      |      |  End |   1  |   2  |   3  |  0   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER_US] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_PLUS, KC_MINUS, KC_EQL,  _______, _______, KC_7,    KC_8,    KC_9,    KC_COMM, _______, \
  _______, KC_EXLM, KC_ASTR, KC_SLSH,  KC_PERC, KC_CIRC, KC_HOME, KC_4,    KC_5,    KC_6,    KC_DOT,  _______, \
  KC_CAPS, KC_QUES, KC_QUOT, KC_DQT,   _______, _______, KC_END,  KC_1,    KC_2,    KC_3 ,   KC_0,    _______, \
  _______, _______, _______,  _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise International
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  |   |   &  |  \   |  $   |  <   |  >   |   (  |   {  |   [  | PgUp |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |  #   |  @   |  _   |  '   |  ~   |   )  |   }  |   ]  | PgDn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE_US] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL, \
  _______, KC_PIPE, KC_AMPR, KC_BSLS, KC_DLR,  KC_LT,   KC_GT,   KC_LPRN, KC_LCBR, KC_LBRC, KC_PGUP, _______, \
  _______, _______, S(KC_3), KC_AT,   KC_UNDS, KC_GRV,  KC_TILD, KC_RPRN, KC_RCBR, KC_RBRC, KC_PGDN, _______, \
  _______, KC_PSCR, _______, _______, _______, KC_SPC,  KC_SPC,  _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap| sv_SE| en_US|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,     KC_F10,  KC_F11,  KC_F12,  \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON,   TERM_OFF,  _______, _______, KC_DEL,  \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY_SE, QWERTY_US, _______, _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______,   _______,   _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,   _______,   _______, _______, _______  \
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY_SE:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY_SE);
	    #ifdef AUDIO_ENABLE
	    PLAY_SONG(se_song);
	    #endif
          }
          return false;
          break;
	case QWERTY_US:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY_US);
	    #ifdef AUDIO_ENABLE
	    PLAY_SONG(us_song);
	    #endif
          }
          return false;
          break;
        case LOWER_SE:
          if (record->event.pressed) {
            layer_on(_LOWER_SE);
            update_tri_layer(_LOWER_SE, _RAISE_SE, _ADJUST);
          } else {
            layer_off(_LOWER_SE);
            update_tri_layer(_LOWER_SE, _RAISE_SE, _ADJUST);
          }
          return false;
          break;
        case RAISE_SE:
          if (record->event.pressed) {
            layer_on(_RAISE_SE);
            update_tri_layer(_LOWER_SE, _RAISE_SE, _ADJUST);
          } else {
            layer_off(_RAISE_SE);
            update_tri_layer(_LOWER_SE, _RAISE_SE, _ADJUST);
          }
          return false;
          break;
        case LOWER_US:
          if (record->event.pressed) {
            layer_on(_LOWER_US);
            update_tri_layer(_LOWER_US, _RAISE_US, _ADJUST);
          } else {
            layer_off(_LOWER_US);
            update_tri_layer(_LOWER_US, _RAISE_US, _ADJUST);
          }
          return false;
          break;
        case RAISE_US:
          if (record->event.pressed) {
            layer_on(_RAISE_US);
            update_tri_layer(_LOWER_US, _RAISE_US, _ADJUST);
          } else {
            layer_off(_RAISE_US);
            update_tri_layer(_LOWER_US, _RAISE_US, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            PORTE &= ~(1<<6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            PORTE |= (1<<6);
            #endif
          }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE_SE) || IS_LAYER_ON(_RAISE_US)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(_ADJUST);
      } else {
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
    case RAISE_US:
    case LOWER_US:
      return false;
    default:
      return true;
  }
}
