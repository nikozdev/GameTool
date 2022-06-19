#ifndef GFX_ENGINE_CPP

#   define GFX_ENGINE_CPP

#   include "gfx_engine.hpp"

#   include "../app/app_engine.hpp"
#   include "../sys/sys_engine.hpp"

#   include "../../lib/glad/src/glad.h"

#   define GLFW_EXPOSE_NATIVE_WIN32
#   include "../../lib/glfw/src/glfw3.h"
#   include "../../lib/glfw/src/glfw3native.h"

struct vtx2f4f_t {
    gt::v2f_t vtx_coord;
    gt::v4f_t vtx_color;
};
struct vtx2f4f2f_t {
    gt::v2f_t vtx_coord;
    gt::v4f_t vtx_color;
    gt::v2f_t tex_coord;
};

static constexpr const vtx2f4f2f_t vbuffer_source[] = {
    { { -0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
    { { -0.5f, +0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
    { { +0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
    { { +0.5f, +0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
};
static constexpr const GLuint ibuffer_source[] = {
    0u, 1u, 2u,
    2u, 3u, 1u,
};

static const GLchar* vshader_source = R"(
#version 330 core

layout(location=0) in vec2 vsi_vtx_coord;
layout(location=1) in vec4 vsi_vtx_color;
layout(location=2) in vec4 vsi_tex_coord;

out vec2 vso_vtx_coord;
out vec4 vso_vtx_color;
out vec4 vso_tex_coord;

uniform mat4 uni_mat_modl;
uniform mat4 uni_mat_view;
uniform mat4 uni_mat_proj;

void main() {
    
    gl_Position = vec4(vsi_vtx_coord.x, vsi_vtx_coord.y, 0.0, 1.0);
    
    vso_vtx_coord = vsi_vtx_coord;
    vso_vtx_color = vsi_vtx_color;
    vso_tex_coord = vsi_tex_coord;

}
)";
static const GLchar* pshader_source = R"(
#version 330 core

out vec4 pso_color;

in vec2 vso_vtx_coord;
in vec4 vso_vtx_color;
in vec2 vso_tex_coord;

uniform float uni_num_time;

void main() {
    
    float time_sin = sin(uni_num_time) / 2.0f + 1.0f;
    float time_cos = cos(uni_num_time) / 2.0f + 1.0f;
    
    pso_color = vec4(
        time_sin * vso_vtx_color.r,
        time_cos * vso_vtx_color.g,
        time_sin * vso_vtx_color.b,
        time_cos * vso_vtx_color.a
    );
    
}
)";

static GLuint ilayout_index = 0;
static GLuint ibuffer_index = 0;
static GLuint vbuffer_index = 0;

static GLuint materia_index = 0;
static GLuint vshader_index = 0;
static GLuint pshader_index = 0;

static GLuint materia_uni_mat_modl = 0;
static GLuint materia_uni_mat_view = 0;
static GLuint materia_uni_mat_proj = 0;
static GLuint materia_uni_num_time = 0;

static GLuint fmbuf_index = 0;
static GLuint fmbuf_color_index = 0;

namespace gt {

    namespace gfx {

        bool
            engine_t::set_facemode(facemode_t facemode)
        {
            this->state.facemode = facemode;

            ::glPolygonMode(GL_FRONT_AND_BACK, facemode);

            return true;
        }

        bool
            engine_t::set_viewport(int x, int y, int w, int h)
        {
            this->state.viewport = { x, y, w, h };
            
            ::glViewport(x, y, w, h);

            return true;
        }

        bool
            engine_t::set_clear_color(float r, float g, float b, float a)
        {
            this->state.clear_color = { r, g, b, a };

            ::glClearColor(r, g, b, a);

            return true;
        }

        bool
            engine_t::init()
        {
            this->window = sys::engine_t::get()->get_window()->get_handle();
            GT_CHECK(this->window != nullptr, "cannot get system window handle!", return false);

            ::GLFWwindow* glfw_window = reinterpret_cast<::GLFWwindow*>(this->window);
            ::glfwMakeContextCurrent(glfw_window);

            ::HWND hwnd = ::glfwGetWin32Window(glfw_window);
            GT_CHECK(hwnd != NULL, "failed to get the platform window!", return false);

            this->device = ::GetWindowDC(hwnd);
            GT_CHECK(this->device != nullptr, "failed to get the graphics device!", return false);

            this->contex = ::wglGetCurrentContext();
            GT_CHECK(this->contex != nullptr, "failed to get the graphics context!", return false);

            ::glfwSwapInterval(1u);
            ::glfwGetWindowSize(glfw_window, &this->state.viewport[2], &this->state.viewport[3]);

            GT_CHECK(::gladLoadGL(), "failed gladLoadGL!", return false);

            if constexpr(true) {

                ::glEnable(GL_BLEND);

                ::glDisable(GL_DEPTH_TEST);
                ::glDisable(GL_CULL_FACE);
            
            }
            do {

            ::glGenVertexArrays(1u, &ilayout_index);
            ::glBindVertexArray(ilayout_index);

            ::glGenBuffers(1u, &vbuffer_index);
            ::glBindBuffer(GL_ARRAY_BUFFER, vbuffer_index);

            ::glBufferData(GL_ARRAY_BUFFER, sizeof(vbuffer_source), vbuffer_source, GL_STATIC_DRAW);

            ::glVertexAttribPointer(0u, 2u, GL_FLOAT, GL_FALSE, sizeof(vtx2f4f2f_t), (const GLvoid*)(0u));
            ::glVertexAttribPointer(1u, 4u, GL_FLOAT, GL_FALSE, sizeof(vtx2f4f2f_t), (const GLvoid*)(sizeof(v2f_t)));
            ::glVertexAttribPointer(2u, 2u, GL_FLOAT, GL_FALSE, sizeof(vtx2f4f2f_t), (const GLvoid*)(sizeof(v2f_t) + sizeof(v4f_t)));

            ::glEnableVertexAttribArray(0u);
            ::glEnableVertexAttribArray(1u);
            ::glEnableVertexAttribArray(2u);

            ::glGenBuffers(1u, &ibuffer_index);
            ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer_index);

            ::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ibuffer_source), ibuffer_source, GL_STATIC_DRAW);

            } while (ilayout_index == 0);
            do {

                materia_index = ::glCreateProgram();

                vshader_index = ::glCreateShader(GL_VERTEX_SHADER);
                ::glShaderSource(vshader_index, 1u, &vshader_source, nullptr);
                ::glCompileShader(vshader_index);
                GT_CHECK(check_shader(GL_VERTEX_SHADER, vshader_index), "default vertex shader is not compiled!", return false);
                ::glAttachShader(materia_index, vshader_index);

                pshader_index = ::glCreateShader(GL_FRAGMENT_SHADER);
                ::glShaderSource(pshader_index, 1u, &pshader_source, nullptr);
                ::glCompileShader(pshader_index);
                GT_CHECK(check_shader(GL_FRAGMENT_SHADER, vshader_index), "default vertex shader is not compiled!", return false);
                ::glAttachShader(materia_index, pshader_index);

                ::glLinkProgram(materia_index);
                GT_CHECK(check_shader(GL_PROGRAM, materia_index), "default materia is not linked!", return false);
                ::glUseProgram(materia_index);

                materia_uni_mat_modl = ::glGetUniformLocation(materia_index, "uni_mat_modl");
                materia_uni_mat_view = ::glGetUniformLocation(materia_index, "uni_mat_view");
                materia_uni_mat_proj = ::glGetUniformLocation(materia_index, "uni_mat_proj");
                
                materia_uni_num_time = ::glGetUniformLocation(materia_index, "uni_num_time");

            } while (materia_index == 0);
            do {

                ::glGenFramebuffers(1u, &fmbuf_index);

                ::glBindFramebuffer(GL_FRAMEBUFFER, fmbuf_index);

                ::glCreateTextures(GL_TEXTURE_2D, 1u, &fmbuf_color_index);
                
                ::glBindTexture(GL_TEXTURE_2D, fmbuf_color_index);
                
                ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->state.viewport[2], this->state.viewport[3], 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

                ::glTextureParameteri(fmbuf_color_index, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                ::glTextureParameteri(fmbuf_color_index, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                ::glTextureParameteri(fmbuf_color_index, GL_TEXTURE_WRAP_S, GL_CLAMP);
                ::glTextureParameteri(fmbuf_color_index, GL_TEXTURE_WRAP_T, GL_CLAMP);

                ::glBindTexture(GL_TEXTURE_2D, 0u);

                ::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fmbuf_color_index, 0);

                GT_CHECK(::glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "the frame buffer is not complete!", return false);
                
                ::glBindFramebuffer(GL_FRAMEBUFFER, 0u);

            } while (fmbuf_index == 0);

            this->set_facemode(FACEMODE_LINE);

            this->set_clear_color(0.125,0.250,0.500,1.000);
            this->set_viewport(this->state.viewport[0], this->state.viewport[1], this->state.viewport[2], this->state.viewport[3]);

            this->set_flag(true);

            return true;
        }
        bool
            engine_t::work()
        {
            ::glBindFramebuffer(GL_FRAMEBUFFER, fmbuf_index);
            this->set_clear_color(this->state.clear_color[0], this->state.clear_color[1], this->state.clear_color[2], this->state.clear_color[3]);
            ::glClear(GL_COLOR_BUFFER_BIT);

            ::glUseProgram(materia_index);
            ::glBindVertexArray(ilayout_index);

            auto timer = app::engine_t::get()->get_timer();
            float senow = timer->get_senow();
            ::glUniform1f(materia_uni_num_time, senow);

            ::glDrawElements(GL_TRIANGLES, sizeof(ibuffer_source) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
            
            ::glBindFramebuffer(GL_FRAMEBUFFER, 0u);
            ::glfwSwapBuffers(reinterpret_cast<::GLFWwindow*>(this->window));
            ::glClear(GL_COLOR_BUFFER_BIT);
            
            return true;
        }
        bool
            engine_t::quit()
        {
            ::glDeleteTextures(1u, &fmbuf_color_index);

            ::glDeleteFramebuffers(1u, &fmbuf_index);

            ::glDeleteProgram(materia_index);

            ::glDeleteShader(vshader_index);
            ::glDeleteShader(pshader_index);

            ::glDeleteBuffers(1u, &vbuffer_index);
            ::glDeleteBuffers(1u, &ibuffer_index);
            
            ::glDeleteVertexArrays(1u, &ilayout_index);

            this->contex = nullptr;
            this->device = nullptr;
            this->window = nullptr;

            return true;
        }

        bool
            engine_t::proc(lib::event_a_t* event)
        {
            
            if (event->has_kind<sys::cursor_t::event_coord_t>()) {

                auto evt = static_cast<sys::cursor_t::event_coord_t*>(event);
                
                float cursor_x = static_cast<float>(evt->coord_x);
                float cursor_y = static_cast<float>(evt->coord_y);
                float window_w = static_cast<float>(this->state.viewport[2]);
                float window_h = static_cast<float>(this->state.viewport[3]);

                this->set_clear_color(this->state.clear_color[0], cursor_x / window_w, cursor_y / window_h, this->state.clear_color[3]);

                return true;
            }

            if (event->has_kind<sys::cursor_t::event_coord_t>()) {

                auto evt = static_cast<sys::cursor_t::event_coord_t*>(event);

                return true;
            }

            if (event->has_kind<sys::window_t::event_sized_t>()) {
                
                auto evt = static_cast<sys::window_t::event_sized_t*>(event);
                
                /*return this->set_viewport(0, 0, evt->sized_x, evt->sized_y); */
                return true;
            }

            return true;
        }

    }

}

#endif /* GFX_ENGINE_CPP */