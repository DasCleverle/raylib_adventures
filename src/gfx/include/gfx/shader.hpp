#pragma once

#include <memory>
#include "utils/vec2.hpp"

struct Shader;

namespace gfx {

    class RendererBase;
    class Renderer;
    class RenderBuffer;
    class Font;

    class Shader final {
        friend class RendererBase;
        friend class Renderer;

    private:
        struct Deleter {
            void operator()(::Shader* shader);
        };

        std::unique_ptr<::Shader, Deleter> m_handle;
        Shader(::Shader&& shader);

        void set_value_impl(std::string&& uniform_name, void const* value, int type);
        void set_array_impl(std::string&& uniform_name, void const* value, int size, int type);

    public:
        int id() const;

        Shader(Shader const&) = delete;
        Shader& operator=(Shader const&) = delete;

        Shader(Shader&& other);
        Shader& operator=(Shader&& other);

        void set_value(std::string&& uniform_name, float value);
        void set_value(std::string&& uniform_name, int value);
        void set_value(std::string&& uniform_name, Vec2f value);
        void set_value(std::string&& uniform_name, Vec2i value);
        void set_value(std::string&& uniform_name, RenderBuffer const& value);

        static Shader from_memory(char const* vertex_shader_code, char const* fragment_shader_code);
        static Shader from_files(
            std::string const& vertex_shader_path,
            std::string const& fragment_shader_path
        );
    };

}  // namespace gfx
