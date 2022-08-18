SET(SOURCES
    src/core/logger.c
    src/platform/platform_linux.c
    src/platform/platform_win32.c
)

add_library(engine SHARED ${SOURCES})
target_include_directories(engine PUBLIC src)
target_link_libraries(engine xcb X11 X11-xcb xkbcommon)
target_link_directories(engine PUBLIC ${VULKAN_SDK}/lib /usr/X11R6)