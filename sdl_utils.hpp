#pragma once

#include <expected>
#include <optional>
#include <stdexcept>
#include <variant>

#include <SDL3/SDL.h>

namespace sdl_utils {

class WindowHandles {
  public:
    struct WaylandHandles {
        Sint64 window_id;
        void* display_handle;
    };

    struct XHandles {
        Sint64 window_id;
        void* display_handle;
    };

    struct Win32Handles {
        void* instance;
        void* hWnd;
    };

    using Handles = std::variant<XHandles, WaylandHandles, Win32Handles>;

  protected:
    static std::optional<Sint64> get_num(SDL_PropertiesID props,
                                         const char* key);

    static std::optional<void*> get_ptr(SDL_PropertiesID props,
                                        const char* key);

  public:
    static std::expected<Handles, std::runtime_error> get_handles(
        SDL_Window* window);
};

}  // namespace sdl_utils
