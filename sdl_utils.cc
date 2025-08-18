#include <format>
#include <stdexcept>

#include "sdl_utils.hpp"

namespace sdl_utils {

std::optional<Sint64> WindowHandles::get_num(SDL_PropertiesID props,
                                             const char*      key) {
	auto num = SDL_GetNumberProperty(props, key, -1);
	if (num == -1) {
		return std::nullopt;
	}
	return num;
}

std::optional<void*> WindowHandles::get_ptr(SDL_PropertiesID props,
                                            const char*      key) {
	auto ptr = SDL_GetPointerProperty(props, key, nullptr);
	if (ptr == nullptr) {
		return std::nullopt;
	}
	return ptr;
}

std::expected<WindowHandles::Handles, std::runtime_error>
WindowHandles::get_handles(SDL_Window* window) {
	SDL_PropertiesID props = SDL_GetWindowProperties(window);
	if (std::string driver = SDL_GetCurrentVideoDriver(); driver == "x11") {
		auto wid     = get_num(props, SDL_PROP_WINDOW_X11_WINDOW_NUMBER);
		auto dhandle = get_ptr(props, SDL_PROP_WINDOW_X11_DISPLAY_POINTER);

		if (wid.has_value() && dhandle.has_value()) {
			return Handles{ .window_id      = wid.value(),
				            .display_handle = dhandle.value() };
		} else {
			return std::unexpected(std::runtime_error(
			  "Unable to get X window ID or display handle"));
		}
	} else if (driver == "wayland") {
		auto wid     = get_num(props, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER);
		auto dhandle = get_ptr(props, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER);

		if (wid.has_value() && dhandle.has_value()) {
			return Handles{ .window_id      = wid.value(),
				            .display_handle = dhandle.value() };
		} else {
			return std::unexpected(std::runtime_error(
			  "Unable to get wayland window ID or display handle"));
		}
	} else {
		return std::unexpected(
		  std::runtime_error(std::format("unknown driver {}", driver)));
	}
}

} // namespace sdl_utils
