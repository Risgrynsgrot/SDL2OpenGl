set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")

set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/libSDL2.a;${CMAKE_CURRENT_LIST_DIR}/lib/x86/libSDL2main.lib")

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
