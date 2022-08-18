#include <core/asserts.h>
#include <core/logger.h>

// TODO: test
#include <platform/platform.h>

int main(void) {
  KFATAL("A test message: %f", 3.14f);
  KERROR("A test message: %f", 3.14f);
  KWARN("A test message: %f", 3.14f);
  KINFO("A test message: %f", 3.14f);
  KDEBUG("A test message: %f", 3.14f);
  KTRACE("A test message: %f", 3.14f);

  KASSERT(1 == 0);

  platform_state state;
  if (platform_startup(&state, "Kohi Engine Testbed", 100, 100, 1280, 720)) {
    while (TRUE) {
      platform_pump_message(&state);
    }
  }

  platform_shutdown(&state);

  return 0;
}