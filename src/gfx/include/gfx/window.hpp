#pragma once

#include <variant>
#include "utils/unique_value.hpp"
#include "utils/vec2.hpp"

namespace gfx {
    class Renderer;

    enum class WindowOption { Resizeable = 0 };

    class Window final {
        friend class Renderer;

    private:
        struct Deleter {
            void operator()(std::monostate) const;
        };

        // This member variable must come first so that its
        // destructor is called last to prevent segfaults
        UniqueValue<std::monostate, Deleter> m_handle;
        std::size_t m_renderers{0};

    public:
        Window(int width, int height, char const* const title);
        Window(Window const&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window const&) = delete;
        Window& operator=(Window&&) = delete;

        void set_option(WindowOption const option, bool enabled);

        void set_target_fps(int fps);

        [[nodiscard]] bool should_close() const;

        [[nodiscard]] Vec2i size() const;

        [[nodiscard]] Renderer renderer();
    };
}  // namespace gfx
