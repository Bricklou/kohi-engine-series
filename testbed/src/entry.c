#include "game.h"

#include <entry.h>

#include <core/kmemory.h>

b8 create_game(game *out_game) {
  // Application configuration
  out_game->config.start_pos_x = 100;
  out_game->config.start_pos_y = 100;
  out_game->config.start_width = 1270;
  out_game->config.start_height = 720;
  out_game->config.name = "Kohi Engine Testbed";

  out_game->update = game_update;
  out_game->render = game_render;
  out_game->initialize = game_initialize;
  out_game->on_resize = game_on_resize;

  // Create the game state
  out_game->state = kallocate(sizeof(game_state), MEMORY_TAG_GAME);

  return TRUE;
}