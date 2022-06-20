#ifndef GFX_ENGINE_CPP

#   define GFX_ENGINE_CPP

#   include "gfx_engine.hpp"
#   include "gfx_data.hpp"

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
            engine_t::set_facemode(facemode_e facemode)
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
            
            this->ginfo.drawable.drawn_count += 1;

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
            ::memset(&this->ginfo, 0, sizeof(ginfo_t));
            
            GT_CHECK(this->draw(), "failed graphics engine drawing!", return false);

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
            this->ginfo.texture.taken_count = 1u;
            this->ginfo.vbuffer.taken_bytes += static_cast<msize_t>(this->drawtool.ilayout.vbuffer.mtail - this->drawtool.ilayout.vbuffer.mhead);
            this->ginfo.drawcall.count += 1;

            ::glBindFramebuffer(GL_FRAMEBUFFER, fmbuffer.index);
            ::glClear(GL_COLOR_BUFFER_BIT);

            auto materia = &this->drawtool.materia;
            ::glUseProgram(materia->index);
            
            auto binding = &materia->binding;
            GLint index_array[GT_GFX_TEXTURE_COUNT_USE];
            for (index_t index = 0; index < binding->count; index++) {
                
                auto texture = &binding->texture_array[index];

                ::glActiveTexture(GL_TEXTURE0 + index);
                ::glBindTexture(GL_TEXTURE_2D, texture->index);
                
                index_array[index] = texture->index;

            }
            auto mapping = &materia->mapping;
            for (index_t index = 0; index < mapping->count; index++) {
                auto element = &mapping->mdata[index];
                if (strcmp(element->sname.sdata, "uni_tex_array[0]") == 0) {
                    ::glUniform1iv(element->iname, element->count, index_array);
                    break;
                }
            }

            auto ilayout = &this->drawtool.ilayout;
            ::glBindVertexArray(ilayout->index);
            
            auto vbuffer = &ilayout->vbuffer;
            ::glBufferSubData(GL_ARRAY_BUFFER, 0, vbuffer->mbufr.msize, vbuffer->mbufr.mdata);
            vbuffer->mtail = vbuffer->mhead = vbuffer->mbufr.mdata;

            ::glDrawArrays(GL_POINTS, 0, vbuffer->mbufr.msize / ilayout->mapping.msize);

            ::glBindFramebuffer(GL_FRAMEBUFFER, 0u);

            return true;
        }

        bool
            engine_t::load_texture(lib::fpath_t fpath, index_t index)
        {
            auto materia = &this->drawtool.materia;
            auto binding = &materia->binding;
            
            GT_CHECK(index < binding->count, "the index is too high!", return false);
            
            auto texture = &binding->texture_array[index];
            GT_CHECK(lib::load(fpath, texture), "failed texture load!", return false);

            if (texture->index > 0) { ::glDeleteTextures(1, &texture->index); texture->index = 0;  }
            
            return this->init_texture(texture);
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

                ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fmbuffer->viewport[2], fmbuffer->viewport[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

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

            GT_CHECK(this->init_materia(&drawtool->materia), "failed materia construction!", return false);
            GT_CHECK(this->init_ilayout(&drawtool->ilayout), "failed ilayout construction!", return false);

            return true;
        }

        bool
            engine_t::init_ilayout(ilayout_t* ilayout)
        {
            GT_CHECK(ilayout->index == 0, "cannot create ilayout!", return false);

            GT_CHECK(this->init_buffer(&ilayout->vbuffer), "cannot create ilayout!", return false);

            ::glGenVertexArrays(1u, &ilayout->index);
            ::glBindVertexArray(ilayout->index);

            auto mapping = &ilayout->mapping;
            GLint count = 0;
            ::glGetProgramiv(this->drawtool.materia.index, GL_ACTIVE_ATTRIBUTES, &count);

            if (count > 0) {
                mapping->count = static_cast<count_t>(count);
                mapping->mdata = new element_t[mapping->count];
                memset(mapping->mdata, 0, mapping->count * sizeof(element_t));
            }

            for (index_t index = 0; index < mapping->count; index += 1) {

                auto element = &mapping->mdata[index];

                GLenum  dtype;
                GLint   count;

                GLchar* name_data;
                GLsizei name_size_max;
                GLsizei name_size_use;

                ::glGetProgramiv(this->drawtool.materia.index, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &name_size_max);
                name_data = new GLchar[name_size_max];

                ::glGetActiveAttrib(this->drawtool.materia.index, index, name_size_max, &name_size_use, &count, &dtype, name_data);

                element->sname.msize = ++name_size_use;
                element->sname.sdata = new char[element->sname.msize];
                ::strcpy_s(element->sname.sdata, element->sname.msize, name_data);
                delete[] name_data;

                element->iname = ::glGetAttribLocation(this->drawtool.materia.index, element->sname.sdata);
                element->count = get_dtype_count_item(dtype) * count;
                element->msize = get_dtype_msize(dtype);
                element->dtype = get_dtype_item(dtype);

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

            return true;
        }
        bool
            engine_t::init_buffer(buffer_t* buffer)
        {
            GT_CHECK(buffer->index == 0, "cannot create the buffer!", return false);
            
            ::glGenBuffers(1u, &buffer->index);
            ::glBindBuffer(GL_ARRAY_BUFFER, buffer->index);

            buffer->mbufr.msize = sizeof(rect_t) * GT_GTX_RECT_COUNT_USE;
            buffer->mbufr.mdata = new mbyte_t[buffer->mbufr.msize];
            memset(buffer->mbufr.mdata, 0, buffer->mbufr.msize);
            ::glBufferData(GL_ARRAY_BUFFER, buffer->mbufr.msize, buffer->mbufr.mdata, GL_DYNAMIC_DRAW);

            buffer->mhead = buffer->mtail = buffer->mbufr.mdata;

            this->ginfo.vbuffer.store_bytes = this->drawtool.ilayout.vbuffer.mbufr.msize;
            this->ginfo.vbuffer.vsize = sizeof(rect_t);
            this->ginfo.drawable.drawn_count = this->ginfo.vbuffer.store_bytes / this->ginfo.vbuffer.vsize;

            return true;
        }

        bool
            engine_t::init_materia(materia_t* materia)
        {
            materia->index = ::glCreateProgram();

            GT_CHECK(this->init_shader(&materia->vshader, SHTYPE_VERTEX), "failed vertex shader construction!", return false);
            GT_CHECK(this->init_shader(&materia->gshader, SHTYPE_GEOMETRY), "failed geometry shader construction!", return false);
            GT_CHECK(this->init_shader(&materia->pshader, SHTYPE_PIXEL), "failed pixel shader construction!", return false);

            ::glLinkProgram(materia->index);
            GT_CHECK(check_shader(materia->index), "default materia is not linked!", return false);
            ::glUseProgram(materia->index);

            auto mapping = &materia->mapping;
            GLint count = 0;
            ::glGetProgramiv(materia->index, GL_ACTIVE_UNIFORMS, &count);
            if (count > 0) {
                mapping->count = static_cast<count_t>(count);
                mapping->mdata = new element_t[mapping->count];
                memset(mapping->mdata, 0, mapping->count * sizeof(element_t));
            }
            for (index_t index = 0; index < mapping->count; index += 1) {

                auto element = &mapping->mdata[index];

                GLenum  dtype;
                GLint   count;

                GLchar* name_data;
                GLsizei name_size_max;
                GLsizei name_size_use;

                ::glGetProgramiv(materia->index, GL_ACTIVE_UNIFORM_MAX_LENGTH, &name_size_max);
                name_data = new GLchar[name_size_max];

                ::glGetActiveUniform(materia->index, index, name_size_max, &name_size_use, &count, &dtype, name_data);

                element->sname.msize = ++name_size_use;
                element->sname.sdata = new char[element->sname.msize];
                ::strcpy_s(element->sname.sdata, element->sname.msize, name_data);
                delete[] name_data;

                element->iname = ::glGetUniformLocation(this->drawtool.materia.index, element->sname.sdata);
                element->count = get_dtype_count_item(dtype) * count;
                element->msize = get_dtype_msize(dtype);
                element->dtype = get_dtype_item(dtype);

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

            auto binding = &materia->binding;

            binding->count = GT_GFX_TEXTURE_COUNT_USE;

            binding->texture_array = new texture_t[binding->count];
            ::memset(binding->texture_array, 0, sizeof(texture_t) * binding->count);
                
            binding->sampler_array = new sampler_t[binding->count];
            ::memset(binding->texture_array, 0, sizeof(sampler_t) * binding->count);
            
            for (index_t index = 0; index < binding->count; index++) {
                
                GT_CHECK(this->init_texture(&binding->texture_array[index]), "failed texture creation!", return false);
                /*
                GT_CHECK(this->init_sampler(&binding->sampler_array[index]), "failed sampler creation!", return false);
                */
            
            }

            this->ginfo.texture.store_count = materia->binding.count;

            return true;
        }
        bool
            engine_t::init_texture(texture_t* texture)
        {
            GT_CHECK(texture->index == 0, "cannot create a texture!", return false);

            ::glGenTextures(1u, &texture->index);

            ::glBindTexture(GL_TEXTURE_2D, texture->index);

            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

            ::glGenerateMipmap(GL_TEXTURE_2D);

            if (texture->mbufr.msize == 0) {

                unsigned char pixel_data[] = {
                    0x00,   0x00,   0x77,   0xff,
                    0x00,   0x77,   0x00,   0xff,
                    0x77,   0x00,   0x77,   0xff,
                    0x77,   0x77,   0x00,   0xff,
                };

                texture->mbufr.msize = sizeof(pixel_data);
                texture->mbufr.mdata = new mbyte_t[texture->mbufr.msize];
                texture->sizes = { 2u, 2u };
                memcpy(texture->mbufr.mdata, pixel_data, texture->mbufr.msize);
            
            }
            
            ::glTexImage2D(
                GL_TEXTURE_2D, 0,
                texture->pixel_bytes == 3 ? GL_RGB : GL_RGBA,
                texture->sizes[0], texture->sizes[1], 0,
                texture->pixel_bytes == 3 ? GL_RGB : GL_RGBA,
                GL_UNSIGNED_BYTE,
                texture->mbufr.mdata
            );

            return true;
        }
        bool
            engine_t::init_shader(shader_t* shader, shtype_e shtype)
        {
            GT_CHECK(shader->index == 0, "cannot create the shader!", return false);

            const char* source = nullptr;

            if (shtype == SHTYPE_VERTEX) {

                shader->index = ::glCreateShader(GL_VERTEX_SHADER);
                /*
                GT_CHECK(lib::load("../rsc/glsl/sprites_vtx.glsl", shader), "failed vertex shader load!", return false);
                */
                source = vshader_source;
            }
            if (shtype == SHTYPE_GEOMETRY) {

                shader->index = ::glCreateShader(GL_GEOMETRY_SHADER);
                /*
                GT_CHECK(lib::load("../rsc/glsl/sprites_gmt.glsl", shader), "failed vertex shader load!", return false);
                */
                source = gshader_source;
            }
            if (shtype == SHTYPE_PIXEL) {

                shader->index = ::glCreateShader(GL_FRAGMENT_SHADER);
                /*
                GT_CHECK(lib::load("../rsc/glsl/sprites_pxl.glsl", shader), "failed vertex shader load!", return false);
                */
                source = pshader_source;
            }
            GT_CHECK(source != nullptr, "could not load shader source! check the type");
            shader->sbufr.msize = strlen(source) + 1u;
            shader->sbufr.sdata = new char[shader->sbufr.msize];
            strcpy_s(shader->sbufr.sdata, shader->sbufr.msize, source);

            const GLchar* shader_sdata = shader->sbufr.sdata;
            ::glShaderSource(shader->index, 1u, &shader_sdata, nullptr);

            ::glCompileShader(shader->index);
            GT_CHECK(check_shader(shader->index), "default shader is not compiled!", return false);
            ::glAttachShader(this->drawtool.materia.index, shader->index);

            return true;
        }
        
        bool
            engine_t::quit_drawtool(drawtool_t* drawtool)
        {
            GT_CHECK(this->quit_materia(&drawtool->materia), "failed materia destruction!", return false);
            GT_CHECK(this->quit_ilayout(&drawtool->ilayout), "failed ilayout destruction!", return false);
            
            return true;
        }

        bool
            engine_t::quit_ilayout(ilayout_t* ilayout)
        {
            GT_CHECK(ilayout->index > 0, "cannot delete input layout!", return false);
            ::glDeleteVertexArrays(1u, &ilayout->index);
            ilayout->index = 0;

            GT_CHECK(this->quit_buffer(&ilayout->vbuffer), "failed vertex buffer destruction!", return false);
            
            auto mapping = &ilayout->mapping;
            if (mapping->msize > 0ul) { delete[] ilayout->mapping.mdata; }
            mapping->mdata = nullptr;
            mapping->count = 0ul;
            mapping->msize = 0ul;

            return true;
        }
        bool
            engine_t::quit_buffer(buffer_t* buffer)
        {
            GT_CHECK(buffer->index != 0, "cannot delete the buffer!", return false);
            
            GT_CHECK(buffer->index > 0, "cannot delete vertex buffer!", return false);
            ::glDeleteBuffers(1u, &buffer->index);
            buffer->index = 0;
            if (buffer->mbufr.msize > 0ul) { delete[] buffer->mbufr.mdata; }
            buffer->mbufr.mdata = nullptr;
            buffer->mbufr.msize = 0ul;

            this->ginfo.vbuffer.taken_bytes = 0ul;
            this->ginfo.vbuffer.store_bytes = 0ul;

            return true;
        }

        bool
            engine_t::quit_materia(materia_t* materia)
        {
            GT_CHECK(materia->index > 0, "cannot delete material!", return false);
            ::glDeleteProgram(materia->index);
            materia->index = 0;

            GT_CHECK(this->quit_shader(&materia->vshader, SHTYPE_VERTEX), "failed vertex shader destruction", return false);
            GT_CHECK(this->quit_shader(&materia->pshader, SHTYPE_PIXEL), "failed pixel shader destruction", return false);
            GT_CHECK(this->quit_shader(&materia->gshader, SHTYPE_GEOMETRY), "failed geometry shader destruction", return false);

            auto mapping = &materia->mapping;
            if (mapping->count > 0ul) { delete[] mapping->mdata; }
            mapping->mdata = nullptr;
            mapping->count = 0ul;
            mapping->msize = 0ul;

            auto binding = &materia->binding;

            for (index_t index = 0; index < binding->count; index++) {

                GT_CHECK(this->quit_texture(&binding->texture_array[index]), "failed texture destruction!", return false);
                /*
                GT_CHECK(this->quit_sampler(&binding->sampler_array[index]), "failed sampler destruction!", return false);
                */

            }

            if (binding->count > 0) { delete[] binding->texture_array; delete[] binding->sampler_array; }
            binding->texture_array = nullptr;
            binding->sampler_array = nullptr;
            binding->count = 0ul;

            return true;
        }
        bool
            engine_t::quit_texture(texture_t* texture)
        {
            GT_CHECK(texture->index != 0, "cannot destroy the texture!", return false);

            ::glDeleteTextures(1u, &texture->index);
            texture->index = 0u;

            if (texture->mbufr.msize > 0ul) { delete[] texture->mbufr.mdata;  }
            texture->mbufr.mdata = nullptr;
            texture->mbufr.msize = 0ul;
            
            texture->sizes = { 0, 0 };

            texture->pixel_bytes = 0ul;

            return true;
        }
        bool
            engine_t::quit_shader(shader_t* shader, shtype_e shtype)
        {
            GT_CHECK(shader->index != 0, "cannot delete the shader!", return false);

            ::glDeleteShader(shader->index);
            shader->index = 0;
            if (shader->sbufr.msize > 0ul) { delete[] shader->sbufr.sdata; }
            shader->sbufr.sdata = nullptr;
            shader->sbufr.msize = 0ul;

            return true;
        }

    }

}

#endif /* GFX_ENGINE_CPP */