// ObliviousGmn // Dokuu // October 2020 // Big Brain

#include "bongo.c"
#include "oleds.h"

extern keymap_config_t keymap_config;

// Has RGB?
#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif

int RGB_current_mode;
uint16_t oled_timer;
bool oled_awake;

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef OLED_ENABLE

// OLED Rotations
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
      return OLED_ROTATION_270;
  } else {
      return OLED_ROTATION_180;
  }
}

// Master OLED
void render_master(void) {
  render_space();
  render_layer_state();
  render_space();
  render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
  render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
  render_space();
  render_logo();
  render_space();
}

// Slave OLED
void render_slave(void) {
  switch (get_highest_layer(layer_state)){
    case _GAME:
        //render_game_r();
        testing_game();
        break;
   case _WEAPON:
        //render_weapon_r();
        break;
    default:
       render_anim();
 }
}

// OLED Sleeps
bool oled_task_user(void) {
  
  // Establishing Sides
  if (is_keyboard_master()) {
    if (!oled_awake || timer_elapsed(oled_timer) > OLED_TIMEOUT) {
      oled_awake = false;
      oled_off();
    } else {
      render_master();
    }
  } else {
    render_slave();
  }

  return false;
}

#endif

// OLED Wakes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed || get_current_wpm() != 000) {
    oled_timer = timer_read();
    oled_awake = true;
  }

  // RGB
  switch (keycode) {
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        }
      #endif
      break;
  }
  return true;
}

// RGB
void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif
