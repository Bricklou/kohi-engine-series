#include "application.h"
#include "game_types.h"

#include "logger.h"

#include "core/event.h"
#include "core/kmemory.h"
#include "platform/platform.h"

typedef struct application_state {
  game *game_inst;
  b8 is_running;
  b8 is_suspended;
  platform_state platform;
  i16 width;
  i16 height;
  f64 last_time;
} application_state;

static b8 initialize = FALSE;
static application_state app_state;

b8 application_create(game *game_inst) {
  if (initialize) {
    KERROR("application_crate called more than once");
    return FALSE;
  }

  app_state.game_inst = game_inst;

  // Initialize subsystems.
  initialize_logging();

  // TODO: remove this
  KFATAL("A test message: %f", 3.14f);
  KERROR("A test message: %f", 3.14f);
  KWARN("A test message: %f", 3.14f);
  KINFO("A test message: %f", 3.14f);
  KDEBUG("A test message: %f", 3.14f);
  KTRACE("A test message: %f", 3.14f);

  app_state.is_running = TRUE;
  app_state.is_suspended = FALSE;

  if (!event_initialize()) {
    KERROR("Event system failed initialization. Application cannot continue.");
    return FALSE;
  }

  if (!platform_startup(
          &app_state.platform, game_inst->config.name,
          game_inst->config.start_pos_x, game_inst->config.start_pos_y,
          game_inst->config.start_width, game_inst->config.start_height)) {
    return FALSE;
  }

  // Initialize the game
  if (!app_state.game_inst->initialize(app_state.game_inst)) {
    KFATAL("Game failed to intialize");
    return FALSE;
  }

  app_state.game_inst->on_resize(app_state.game_inst, app_state.width,
                                 app_state.height);

  initialize = FALSE;

  return TRUE;
}

b8 application_run() {
  KINFO(get_memory_usage_str());

  while (app_state.is_running) {
    if (!platform_pump_message(&app_state.platform)) {
      app_state.is_running = FALSE;
    }

    if (!app_state.is_suspended) {
      if (!app_state.game_inst->update(app_state.game_inst, (f32)0)) {
        KFATAL("Game update failed, shutting down.");
        app_state.is_running = FALSE;
        break;
      }

      // Call the game's render routine
      if (!app_state.game_inst->render(app_state.game_inst, (f32)0)) {
        KFATAL("Game render failed, shutting down.");
        app_state.is_running = FALSE;
        break;
      }
    }
  }

  app_state.is_running = FALSE;

  event_shutdown();

  platform_shutdown(&app_state.platform);

  return TRUE;
}