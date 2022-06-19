#ifndef GFX_ENGINE_CPP

#   define GFX_ENGINE_CPP

#   include "gfx_engine.hpp"

#   include "../app/app_engine.hpp"
#   include "../sys/sys_engine.hpp"

#   include "../lib/lib_file.hpp"

#   include "../../lib/glad/src/glad.h"

#   define GLFW_EXPOSE_NATIVE_WIN32
#   include "../../lib/glfw/src/glfw3.h"
#   include "../../lib/glfw/src/glfw3native.h"

namespace gt {

    namespace gfx {

        bool
            engine_t::set_point_size(float scale)
        {
            ::glPointSize(scale);

            return true;
        }
        bool
            engine_t::set_lines_size(float scale)
        {
            ::glLineWidth(scale);

            return true;
        }

        bool
            engine_t::set_facemode(facemode_t facemode)
        {
            this->state.facemode = facemode;

            if (facemode == FACEMODE_FILL) {
                ::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                return true;
            }
            if (facemode == FACEMODE_LINE) {
                ::glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                return true;
            }

            return false;
        }

        bool
            engine_t::set_viewport(int x, int y, int w, int h)
        {
            this->state.viewport = { x, y, w, h };
            
            ::glViewport(x, y, w, h);

            if (this->fmbuffer.viewport[2] != w || this->fmbuffer.viewport[3] != h) {
                
                this->fmbuffer.viewport = { x, y, w, h };
                
                if (this->fmbuffer.index > 0) {
                    GT_CHECK(this->quit_fmbuffer(&this->fmbuffer), "failed fmbuffer quit!", return false);
                }
                GT_CHECK(this->init_fmbuffer(&this->fmbuffer), "failed fmbuffer init!", return false);
            
            }

            return true;
        }

        bool
            engine_t::set_clearcol(float r, float g, float b, float a)
        {
            this->state.clearcol = { r, g, b, a };

            ::glClearColor(r, g, b, a);

            return true;
        }

        bool
            engine_t::add_for_draw(const rect_t& rect)
        {
            auto vbuffer = &this->drawtool.ilayout.vbuffer;

            msize_t msize_next;
            
            msize_next = (vbuffer->mtail - vbuffer->mhead) + sizeof(rect_t);
            if (vbuffer->mbufr.msize <= msize_next) {
                
                GT_CHECK(this->draw(), "failed to draw the current content!", return false);
            
            }

            msize_next = vbuffer->mtail - vbuffer->mhead;
            GT_CHECK(vbuffer->mbufr.msize >= msize_next, "cannot render anything!", return false);

            memcpy(vbuffer->mtail, &rect, sizeof(rect_t));
            vbuffer->mtail += sizeof(rect_t);

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
                ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                ::glDisable(GL_DEPTH_TEST);
                ::glDisable(GL_CULL_FACE);
            
                this->set_point_size(10.0f);
            }

            GT_CHECK(this->init_drawtool(&this->drawtool), "failed sprites init!", return false);
            
            this->fmbuffer.viewport = this->state.viewport;
            GT_CHECK(this->init_fmbuffer(&this->fmbuffer), "failed fmbuffer init!", return false);

            this->set_facemode(FACEMODE_FILL);

            this->set_clearcol(0.125,0.250,0.500,1.000);
            this->set_viewport(this->state.viewport[0], this->state.viewport[1], this->state.viewport[2], this->state.viewport[3]);

            return this->play();;
        }
        bool
            engine_t::work()
        {
            auto senow = app::engine_t::get()->get_timer()->get_senow();
            auto sinow = sinf(senow);
            auto conow = cosf(senow);

            for (float iterx = -1.0f; iterx < +1.0f; iterx += 0.01f) {

                for (float itery = -1.0f; itery < +1.0f; itery += 0.01f) {

                    rect_t rect;
                    
                    rect.vtx_coord = { iterx * sinow, itery * conow };
                    rect.vtx_pivot = { 0.0f, 0.0f };
                    rect.vtx_scale = { 0.0025f * sinow, 0.0025f * conow };
                    rect.tex_color = { iterx * sinow, itery * conow, iterx * sinow, itery * conow };
                    rect.tex_coord = { 0.0, 0.0, 1.0, 1.0 };
                    rect.tex_index = { 0 };
                    
                    this->add_for_draw(rect);
                }

            }

            this->draw();

            ::glfwSwapBuffers(reinterpret_cast<::GLFWwindow*>(this->window));
            ::glClear(GL_COLOR_BUFFER_BIT);
            
            return true;
        }
        bool
            engine_t::quit()
        {
            GT_CHECK(this->quit_drawtool(&this->drawtool), "failed sprites quit!", return false);
            /* GT_CHECK(this->quit_drawtool(&this->tilemap), "failed sprites quit!", return false); */
            
            GT_CHECK(this->quit_fmbuffer(&this->fmbuffer), "failed framebuffer quit!", return false);
            
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

                this->set_clearcol(
                    this->state.clearcol[0],
                    cursor_x / window_w, cursor_y / window_h,
                    this->state.clearcol[3]
                );

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

        bool
            engine_t::draw()
        {
            ::glBindFramebuffer(GL_FRAMEBUFFER, fmbuffer.index);
            ::glClear(GL_COLOR_BUFFER_BIT);

            auto materia = &this->drawtool.ilayout;
            ::glUseProgram(this->drawtool.materia.index);

            /*
            if (this->drawtool.materia.mapping.count > 0) {

                auto timer = app::engine_t::get()->get_timer();
                float senow = timer->get_senow();
                ::glUniform1f(this->drawtool.materia.mapping.mdata[1].iname, senow);

            }
            */
            auto ilayout = &this->drawtool.ilayout;
            ::glBindVertexArray(this->drawtool.ilayout.index);
            
            auto vbuffer = &ilayout->vbuffer;
            ::glBufferSubData(GL_ARRAY_BUFFER, 0, vbuffer->mbufr.msize, vbuffer->mbufr.mdata);
            vbuffer->mtail = vbuffer->mhead = vbuffer->mbufr.mdata;

            ::glDrawArrays(GL_POINTS, 0, vbuffer->mbufr.msize / ilayout->mapping.msize);

            ::glBindFramebuffer(GL_FRAMEBUFFER, 0u);

            return true;
        }


        bool
            engine_t::init_fmbuffer(fmbuffer_t* fmbuffer)
        {
            ::glGenFramebuffers(1u, &fmbuffer->index);

            ::glBindFramebuffer(GL_FRAMEBUFFER, fmbuffer->index);
            
            fmbuffer->viewport[2] = max(fmbuffer->viewport[2], 0x10);
            fmbuffer->viewport[3] = max(fmbuffer->viewport[3], 0x10);

            auto colorbuf = &fmbuffer->colorbuf;
            do {
                ::glCreateTextures(GL_TEXTURE_2D, 1u, &colorbuf->index);

                ::glBindTexture(GL_TEXTURE_2D, colorbuf->index);

                ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fmbuffer->viewport[2], fmbuffer->viewport[3], 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

                ::glTextureParameteri(colorbuf->index, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                ::glTextureParameteri(colorbuf->index, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                ::glTextureParameteri(colorbuf->index, GL_TEXTURE_WRAP_S, GL_CLAMP);
                ::glTextureParameteri(colorbuf->index, GL_TEXTURE_WRAP_T, GL_CLAMP);

                ::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorbuf->index, 0);

                ::glBindTexture(GL_TEXTURE_2D, 0u);

            } while (colorbuf->index == 0);

            GT_CHECK(::glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "the frame buffer is not complete!", return false);

            ::glBindFramebuffer(GL_FRAMEBUFFER, 0u);

            return true;
        }
        bool
            engine_t::quit_fmbuffer(fmbuffer_t* fmbuffer)
        {
            GT_CHECK(fmbuffer->index > 0, "cannot delete framebuffer!", return false);
            ::glDeleteFramebuffers(1u, &fmbuffer->index);
            fmbuffer->index = 0;

            auto colorbuf = &fmbuffer->colorbuf;
            GT_CHECK(colorbuf->index > 0, "cannot delete framebuffer color texture!", return false);
            ::glDeleteTextures(1u, &colorbuf->index);
            colorbuf->index = 0;
            if (colorbuf->mbufr.msize > 0ul) { delete[] colorbuf->mbufr.mdata; }
            colorbuf->mbufr.mdata = nullptr;
            colorbuf->mbufr.msize = 0ul;

            return true;
        }

        bool
            engine_t::init_drawtool(drawtool_t* drawtool)
        {
            auto materia = &drawtool->materia;
            do {
                materia->index = ::glCreateProgram();

                auto vshader = &materia->vshader;
                vshader->index = ::glCreateShader(GL_VERTEX_SHADER);
                
                GT_CHECK(lib::load("../rsc/glsl/sprites_vtx.glsl", vshader), "failed vertex shader load!", return false);
                const GLchar* vshader_sdata = vshader->sbufr.sdata;
                ::glShaderSource(vshader->index, 1u, &vshader_sdata, nullptr);

                ::glCompileShader(vshader->index);
                GT_CHECK(check_shader(GL_VERTEX_SHADER, vshader->index), "default vertex shader is not compiled!", return false);
                ::glAttachShader(materia->index, vshader->index);

                auto gshader = &materia->gshader;
                gshader->index = ::glCreateShader(GL_GEOMETRY_SHADER);

                GT_CHECK(lib::load("../rsc/glsl/sprites_gmt.glsl", gshader), "failed geometry shader load!", return false);
                const GLchar* gshader_sdata = gshader->sbufr.sdata;
                ::glShaderSource(gshader->index, 1u, &gshader_sdata, nullptr);

                ::glCompileShader(gshader->index);
                GT_CHECK(check_shader(GL_GEOMETRY_SHADER, gshader->index), "default geometry shader is not compiled!", return false);
                ::glAttachShader(materia->index, gshader->index);

                auto pshader = &materia->pshader;
                pshader->index = ::glCreateShader(GL_FRAGMENT_SHADER);
                
                GT_CHECK(lib::load("../rsc/glsl/sprites_pxl.glsl", pshader), "failed pixel shader load!", return false);
                const GLchar* pshader_sdata = pshader->sbufr.sdata;
                ::glShaderSource(pshader->index, 1u, &pshader_sdata, nullptr);

                ::glCompileShader(pshader->index);
                GT_CHECK(check_shader(GL_FRAGMENT_SHADER, pshader->index), "default pixel shader is not compiled!", return false);
                ::glAttachShader(materia->index, pshader->index);

                ::glLinkProgram(materia->index);
                GT_CHECK(check_shader(GL_PROGRAM, materia->index), "default materia is not linked!", return false);
                ::glUseProgram(materia->index);

                auto mapping = &materia->mapping;
                do {
                    GLint count = 0;
                    ::glGetProgramiv(materia->index, GL_ACTIVE_UNIFORMS, &count);
                    if (count == 0) { break; }

                    mapping->count = static_cast<count_t>(count);
                    mapping->mdata = new element_t[mapping->count];
                    memset(mapping->mdata, 0, mapping->count * sizeof(element_t));

                    for (index_t index = 0; index < mapping->count; index += 1) {

                        auto element = &mapping->mdata[index];

                        GLint   count;
                        GLenum  dtype;
                        GLsizei name_size_max;
                        GLsizei name_size_use;
                        GLchar* name_data;

                        ::glGetProgramiv(materia->index, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &name_size_max);
                        name_data = new GLchar[name_size_max];

                        ::glGetActiveUniform(materia->index, index, name_size_max, &name_size_use, &count, &dtype, name_data);

                        element->sname.msize = ++name_size_use;
                        element->sname.sdata = new char[element->sname.msize];
                        ::strcpy_s(element->sname.sdata, element->sname.msize, name_data);
                        delete[] name_data;

                        element->iname = index;
                        element->count = get_dtype_count_item(dtype) * count;
                        element->msize = get_dtype_msize(dtype);
                        element->dtype = get_dtype_item(dtype);
                        element->start += mapping->msize;

                        mapping->msize += element->msize;
                    }

                } while (false);

            } while (materia->index == 0);

            auto ilayout = &drawtool->ilayout;
            do {
                ::glGenVertexArrays(1u, &ilayout->index);
                ::glBindVertexArray(ilayout->index);

                auto vbuffer = &ilayout->vbuffer;
                do {
                    ::glGenBuffers(1u, &vbuffer->index);
                    ::glBindBuffer(GL_ARRAY_BUFFER, vbuffer->index);

                    vbuffer->mbufr.msize = sizeof(rect_t) * GT_GTX_RECT_COUNT_USE;
                    vbuffer->mbufr.mdata = new mbyte_t[vbuffer->mbufr.msize];
                    memset(vbuffer->mbufr.mdata, 0, vbuffer->mbufr.msize);
                    ::glBufferData(GL_ARRAY_BUFFER, vbuffer->mbufr.msize, vbuffer->mbufr.mdata, GL_DYNAMIC_DRAW);

                    vbuffer->mhead = vbuffer->mtail = vbuffer->mbufr.mdata;

                } while (vbuffer->index == 0);

                auto mapping = &ilayout->mapping;
                do {
                    GLint count = 0;
                    ::glGetProgramiv(materia->index, GL_ACTIVE_ATTRIBUTES, &count);
                    if (count == 0) { break; }

                    mapping->count = static_cast<count_t>(count);
                    mapping->mdata = new element_t[mapping->count];
                    memset(mapping->mdata, 0, mapping->count * sizeof(element_t));

                    for (index_t index = 0; index < mapping->count; index += 1) {

                        auto element = &mapping->mdata[index];

                        GLenum  dtype;
                        GLint   count;

                        GLchar* name_data;
                        GLsizei name_size_max;
                        GLsizei name_size_use;

                        ::glGetProgramiv(materia->index, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &name_size_max);
                        name_data = new GLchar[name_size_max];

                        ::glGetActiveAttrib(materia->index, index, name_size_max, &name_size_use, &count, &dtype, name_data);

                        element->sname.msize = ++name_size_use;
                        element->sname.sdata = new char[element->sname.msize];
                        ::strcpy_s(element->sname.sdata, element->sname.msize, name_data);
                        delete[] name_data;

                        element->iname = ::glGetAttribLocation(materia->index, element->sname.sdata);
                        element->count = get_dtype_count_item(dtype) * count;
                        element->msize = get_dtype_msize(dtype);
                        element->dtype = get_dtype_item(dtype);
                        /*element->start += mapping->msize; */

                        /* mapping->msize += element->msize; */
                    }
                    for (index_t ihead = 0, itail = 0; ihead < mapping->count; itail += 1) {
                        
                        auto element = &mapping->mdata[itail];
                        
                        if (element->iname == ihead) {
                            
                            element_t temp = mapping->mdata[ihead];
                            mapping->mdata[ihead] = *element;
                            mapping->mdata[itail] = temp;
                            element = &mapping->mdata[ihead];

                            element->start += mapping->msize;
                            mapping->msize += element->msize;

                            itail = ihead;
                            ihead += 1;

                        }
                    
                    }
                    for (index_t index = 0; index < mapping->count; index += 1) {

                        auto element = &mapping->mdata[index];

                        ::glVertexAttribPointer(
                            element->iname,
                            element->count, element->dtype, GL_FALSE,
                            mapping->msize, (const GLvoid*)(element->start)
                        );
                        ::glEnableVertexAttribArray(element->iname);

                    }

                } while (false);

            } while (ilayout->index == 0);

            return true;
        }
        bool
            engine_t::quit_drawtool(drawtool_t* drawtool)
        {
            auto materia = &drawtool->materia;
            do {
                GT_CHECK(materia->index > 0, "cannot delete material!", return false);
                ::glDeleteProgram(materia->index);
                materia->index = 0;

                auto vshader = &materia->vshader;
                GT_CHECK(vshader->index > 0, "cannot delete vertex shader!", return false);
                ::glDeleteShader(drawtool->materia.vshader.index);
                vshader->index = 0;
                if (vshader->sbufr.msize > 0ul) { delete[] vshader->sbufr.sdata; }
                vshader->sbufr.sdata = nullptr;
                vshader->sbufr.msize = 0ul;

                auto pshader = &materia->pshader;
                GT_CHECK(pshader->index > 0, "cannot delete pixel shader!", return false);
                ::glDeleteShader(pshader->index);
                pshader->index = 0;
                if (pshader->sbufr.msize > 0ul) { delete[] pshader->sbufr.sdata; }
                pshader->sbufr.sdata = nullptr;
                pshader->sbufr.msize = 0ul;

                auto mapping = &materia->mapping;
                if (mapping->msize > 0ul) { delete[] mapping->mdata; }
                mapping->mdata = nullptr;
                mapping->count = 0ul;
                mapping->msize = 0ul;

            } while (materia->index > 0);

            auto ilayout = &drawtool->ilayout;
            do {
                GT_CHECK(ilayout->index > 0, "cannot delete input layout!", return false);
                ::glDeleteVertexArrays(1u, &ilayout->index);
                ilayout->index = 0;

                auto vbuffer = &ilayout->vbuffer;
                GT_CHECK(vbuffer->index > 0, "cannot delete vertex buffer!", return false);
                ::glDeleteBuffers(1u, &vbuffer->index);
                vbuffer->index = 0;
                if (vbuffer->mbufr.msize > 0ul) { delete[] vbuffer->mbufr.mdata; }
                vbuffer->mbufr.mdata = nullptr;
                vbuffer->mbufr.msize = 0ul;

                auto mapping = &ilayout->mapping;
                if (mapping->msize > 0ul) { delete[] ilayout->mapping.mdata; }
                mapping->mdata = nullptr;
                mapping->count = 0ul;
                mapping->msize = 0ul;

            } while (ilayout->index > 0);


            return true;
        }

    }

}

#endif /* GFX_ENGINE_CPP */