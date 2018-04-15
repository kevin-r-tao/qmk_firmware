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

#include "preonic.h"
#include "action_layer.h"

// The regular TO() wasn't working from within a layer because the release sent us back to layer 0
#define TOR(layer) (layer | QK_TO | (ON_RELEASE << 0x4))

enum preonic_layers {
  _QWERTY,
  _LOCK,
  _SYM,
  _NAV,
  _NUM,
  _CONST,
  _MOUSE,
  _FN,
  
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOCK,
  SYM,
  NAV,
  NUM,
  CONST,
  MOUSE,
  FN,
  
  LOWER,
  RAISE,
  BACKLIT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | NAV  |A(SYM)|   S  |D(NUM)|   F  |   G  |   H  |   J  |   K  |   L  |;(SYM)|Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|Z(FN) |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | LOCK | Alt  |Lower | Space(NAV)  |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_ESC,	KC_1,			KC_2,		KC_3,			KC_4,	KC_5,			KC_6,			KC_7,	KC_8,		KC_9,	KC_0,				KC_BSPC},
  {KC_TAB,	KC_Q,			KC_W,		KC_E,			KC_R,	KC_T,			KC_Y,			KC_U,	KC_I,		KC_O,	KC_P,				KC_DEL},
  {TG(_NAV),LT(_SYM,KC_A),	KC_S,		LT(_NUM,KC_D),	KC_F,	KC_G,			KC_H,			KC_J,	KC_K,		KC_L,	LT(_SYM,KC_SCOLON),	KC_ENT},
  {KC_LSFT,	LT(_FN,KC_Z),	KC_X,		KC_C,			KC_V,	KC_B,			KC_N,			KC_M,	KC_COMM,	KC_DOT,	KC_SLSH,			KC_RSFT},
  {KC_LCTL,	KC_LGUI,		MO(_LOCK),	KC_LALT,		LOWER,	LT(_NAV,KC_SPC),LT(_NAV,KC_SPC),RAISE,	KC_LEFT,	KC_DOWN,KC_UP,				RCTL_T(KC_RIGHT)}
},

/* Layer Lock
 * ,-----------------------------------------------------------------------------------.
 * | TO(0)|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | SYM  |      | NUM  |      |      |      |      |      |      | SYM  | MOUSE|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | CONST| FN   |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    NAV      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOCK] = {
  {TO(0),		_______,	_______,	_______,	_______,	_______,	_______,	_______, _______, _______, _______, _______},
  {_______,		_______,	_______,	_______,	_______,	_______,	_______,	_______, _______, _______, _______, _______},
  {_______,		TOR(_SYM),	_______,	TOR(_NUM),	_______,	_______,	_______,	_______, _______, _______,TOR(_SYM),TOR(_MOUSE) },
  {TOR(_CONST),	TOR(_FN),	_______,	_______,	_______,	_______,	_______,	_______, _______, _______, _______, _______},
  {_______, 	_______,	_______,	_______,	_______,	TOR(_NAV),	TOR(_NAV),	_______, _______, _______, _______, _______}
},

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * | TO(0)|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F11 |  F12 |   {  |   }  |   !  |   +  |   "  |   '  |   `  |   ~  | Ins  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |   (  |   )  |  &   |   !  |   =  |   -  |   >  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Caps |      |      |   <  |   >  |  |   |   @  |   /  |   *  |   \  |   _  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |   [  |   ]  |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYM] = {
  {TO(0),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______},
  {_______, KC_F11,  KC_F12,  KC_LCBR, KC_RCBR, KC_EXLM, KC_PLUS, KC_DQT,  KC_QUOT, KC_GRV,  KC_TILD, KC_INS},
  {_______, _______, _______, KC_LPRN, KC_RPRN, KC_AMPR, KC_EXLM, KC_EQL,  KC_MINS, KC_GT,   _______, _______},
  {KC_CAPS, _______, _______, KC_LT,   KC_GT,   KC_PIPE, KC_AT,   KC_SLSH, KC_ASTR, KC_BSLS, KC_UNDS, _______},
  {_______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Nav
 * ,-----------------------------------------------------------------------------------.
 * | TO(0)|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      | PrtSc| Pause|MoWhlU| PgUp | Home |  Up  | End  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      | Ins  | Del  |MoWhlD| PgDn | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |MoBtn4|MoBtn5|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = {
  {TO(0),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, KC_PSCR, KC_PAUS, KC_WH_U, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______},
  {_______, _______, _______, KC_INS,  KC_DEL,  KC_WH_D, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______},
  {_______, _______, _______, KC_BTN4, KC_BTN5, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * | TO(0)|      |      |      |      |      | NmLk | Esc  |  /   |  *   |  -   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  7   |  8   |  9   |Sft(+)|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  1   |  2   |  3   |Enter |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |  0   |  0   |  .   |Enter |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = {
  {TO(0),   _______, _______, _______, _______, _______, KC_NLCK, KC_ESC,  KC_PSLS, KC_PAST, KC_PMNS, _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,S(KC_PPLS), _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   KC_PDOT, KC_PENT, _______}
},

/* Constants
 * ,-----------------------------------------------------------------------------------.
 * | TO(0)|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      _      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_CONST] = {
  {TO(0),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), _______},
  {_______, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), _______, _______},
  {_______, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, KC_UNDS, KC_UNDS, _______, _______, _______, _______, _______}
},

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * | TO(0)|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |MoWhlU|MoBtn4| MoUp |MoBtn5|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Accl0| Accl1| Accl2|      |MoWhlD| MoLft| MoDwn| MoLft|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    MoBtn1   |MoBtn2|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = {
  {TO(0),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, KC_WH_U, KC_BTN4, KC_MS_U, KC_BTN5, _______, _______},
  {_______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, KC_BTN1, KC_BTN1, KC_BTN2, _______, _______, _______, _______}
},

/* Function Keys
 * ,-----------------------------------------------------------------------------------.
 * | TO(0)|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F11 |  F12 |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = {
  {TO(0),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______},
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______},
  {_______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL},
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),KC_HOME, KC_END, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL},
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {_______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL},
  {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______,  _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            PORTE &= ~(1<<6);
          } else {
            unregister_code(KC_RSFT);
            PORTE |= (1<<6);
          }
          return false;
          break;
      }
    return true;
};
