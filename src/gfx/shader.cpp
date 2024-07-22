#include "gfx/shader.hpp"

#include <raylib.h>

#include "gfx/render_buffer.hpp"

using RaylibShader = ::Shader;

namespace gfx {

    void Shader::Deleter::operator()(RaylibShader* shader) {
        UnloadShader(*shader);
        delete shader;
    }

    Shader::Shader(RaylibShader&& shader)
        : m_handle{std::unique_ptr<RaylibShader, Deleter>{new RaylibShader{std::move(shader)}}} {}

    Shader::Shader(Shader&& other) {
        using std::swap;
        swap(m_handle, other.m_handle);
    }

    Shader& Shader::operator=(Shader&& other) {
        if (this == &other) {
            return *this;
        }

        using std::swap;
        swap(m_handle, other.m_handle);

        return *this;
    }

    Shader Shader::from_memory(char const* vertex_shader_code, char const* fragment_shader_code) {
        return Shader{
            LoadShaderFromMemory(vertex_shader_code, fragment_shader_code),
        };
    }

    Shader Shader::from_files(
        std::string const& vertex_shader_path,
        std::string const& fragment_shader_path
    ) {
        return Shader{
            LoadShader(vertex_shader_path.c_str(), fragment_shader_path.c_str()),
        };
    }

    int Shader::id() const {
        return m_handle->id;
    }

    void Shader::set_value_impl(std::string&& uniform_name, void const* value, int type) {
        SetShaderValue(*m_handle, GetShaderLocation(*m_handle, uniform_name.c_str()), value, type);
    }

    void Shader::set_value(std::string&& uniform_name, float value) {
        set_value_impl(std::move(uniform_name), &value, SHADER_UNIFORM_FLOAT);
    }

    void Shader::set_value(std::string&& uniform_name, int value) {
        set_value_impl(std::move(uniform_name), &value, SHADER_UNIFORM_INT);
    }

    void Shader::set_value(std::string&& uniform_name, Vec2f value) {
        auto const vector = Vector2{value.x, value.y};
        set_value_impl(std::move(uniform_name), &vector, SHADER_UNIFORM_VEC2);
    }

    void Shader::set_value(std::string&& uniform_name, Vec2i value) {
        auto const vector = Vector2{static_cast<float>(value.x), static_cast<float>(value.y)};

        set_value_impl(std::move(uniform_name), &vector, SHADER_UNIFORM_IVEC2);
    }

    void Shader::set_value(std::string&& uniform_name, RenderBuffer const& value) {
        SetShaderValueTexture(
            *m_handle,
            GetShaderLocation(*m_handle, uniform_name.c_str()),
            value.m_handle->texture
        );
    }

}  // namespace gfx
