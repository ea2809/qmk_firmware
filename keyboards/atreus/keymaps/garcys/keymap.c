// This is the personal keymap of Jeremy Cowgar (@jcowgar). It is written for the programmer.

#include QMK_KEYBOARD_H
#include "action_layer.h"

#include <print.h>

// clang-format off

// Each layer gets a name for readability, which is then used in the keymap matrix below.
#define ALPH 0
#define NUMS 1
#define CURS 2
#define SYMB 3
#define FKEY 4

uint16_t num_layer = ALPH;

// See the key you are pushing
#define ooooooo KC_TRNS

// Some handy macros to keep the keymaps clean and easier to maintain
#define KM_SAVE LGUI(KC_S)
#define KM_CLSE LGUI(KC_W)
#define KM_OPEN LGUI(KC_O)
#define KM_COPY LGUI(KC_C)
#define KM_CUT  LGUI(KC_X)
#define KM_PAST LGUI(KC_V)
#define KM_UNDO LGUI(KC_Z)
#define KM_REDO LGUI(LSFT(KC_Z))
#define KM_LOCK LGUI(LCTL(KC_Q))
#define KM_SCST LGUI(LSFT(KC_4))

// Bottom row
#define ALTT_BSPC LALT_T(KC_BSPC)
#define GUIT_ENT LGUI_T(KC_ENT)
#define CTLT_ESC RCTL_T(KC_ESC)
#define SFTT_ENT RSFT_T(KC_ENT)
#define GUIT_MIN RGUI_T(KC_MINUS)
#define SFTT_BSPC LSFT_T(KC_BSPC)
#define ALTT_QUOTE RALT_T(KC_QUOTE)
#define GUIT_TAB LGUI_T(KC_TAB)

// Alphas modifiers 
#define CTLT_A RCTL_T(KC_A)
#define CTLT_SC LCTL_T(KC_SCLN)
#define SFTT_Z LSFT_T(KC_Z)
#define SFTT_SL RSFT_T(KC_SLSH)


// Layer change
#define NUMS_S LT(NUMS, KC_S)
#define FKEY_D LT(FKEY, KC_D)
#define CURS_K LT(CURS, KC_K)
#define SYMB_L LT(SYMB, KC_L)

// Extra keycode
enum custom_keycodes {
  TMUX_Z = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [ALPH] = LAYOUT(
    KC_Q,    KC_W,           KC_E,     KC_R,      KC_T,                           KC_Y,   KC_U,     KC_I,     KC_O,       KC_P,
    CTLT_A,  NUMS_S,         FKEY_D,   KC_F,      KC_G,                           KC_H,   KC_J,     CURS_K,   SYMB_L,     CTLT_SC,
    SFTT_Z,  KC_X,           KC_C,     KC_V,      KC_B,                           KC_N,   KC_M,     KC_COMM,  KC_DOT,     SFTT_SL,
    KC_LCTL, LALT_T(KC_ESC), GUIT_TAB, KC_SPC,    SFTT_BSPC, ALTT_BSPC, TG(NUMS), KC_ESC, SFTT_ENT, GUIT_MIN, ALTT_QUOTE, KC_EQUAL
  ),
  [NUMS] = LAYOUT(
    _______, _______, _______, KC_ASTR, KC_SLSH,                   _______, KC_7, KC_8,   KC_9,   KC_SLSH,
    _______, ooooooo, KC_EQL,  KC_PLUS, KC_MINS,                   KC_LPRN, KC_4, KC_5,   KC_6,   KC_ASTR,
    _______, _______, KC_DOT,  KC_COMM, KC_SCLN,                   KC_RPRN, KC_1, KC_2,   KC_3,   KC_MINS,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_0, KC_DOT, KC_EQL, KC_PLUS
  ),
  [CURS] = LAYOUT(
    KM_LOCK, KC_MS_BTN4,   KC_MS_UP,     KC_MS_BTN3,    KC_MS_WH_UP,                    _______, KM_SAVE, _______, KM_OPEN, _______,
    KM_SCST, KC_MS_LEFT,   KC_MS_DOWN,   KC_MS_RIGHT,   KC_MS_WH_DOWN,                  KM_UNDO, KC_LALT, ooooooo, KC_LGUI, _______,
    TMUX_Z,  KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2,  KC_MPLY,                        KM_REDO, KM_CLSE, _______, _______, _______,
    _______, _______,      RESET,        KC_MS_BTN2,    KC_MS_BTN1,    KM_COPY, KM_CUT, KM_PAST, _______, _______, _______, _______
  ),
  [SYMB] = LAYOUT(
    KC_BSLS, KC_EXLM, KC_LABK, KC_RABK, S(KC_SCLN),                   KC_UNDS, KC_DLR,  KC_QUES, _______, KC_PERC,
    KC_AT,   KC_AMPR, KC_LPRN, KC_RPRN, KC_SCLN,                   KC_COMM, KC_DOT,  KC_QUOT, ooooooo, KC_TILD,
    KC_HASH, KC_PIPE, KC_LCBR, KC_RCBR, KC_SLSH,                   _______, KC_GRV,  KC_DQT,  _______, KC_CIRC,
    _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [FKEY] = LAYOUT(
    _______, _______, _______, _______, _______,                   _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, ooooooo, _______, _______,                   _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,
    _______, _______, _______, _______, _______,                   _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
};

void keyboard_pre_init_user(void) {
  // Set Pins
  setPinOutput(B2);
}

bool led_update_user(led_t led_state) {
  // Sets caps lock led
  writePin(B2, led_state.caps_lock || num_layer == NUMS);
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  num_layer = get_highest_layer(state);
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TMUX_Z:
      if (record->event.pressed) {
        // Tmux zoom
        SEND_STRING(SS_LCTL("a")"z");
      }
      break;
  }
  return true;
};
