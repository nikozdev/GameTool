#ifndef CFG_GFX_CPP

#	define CFG_GFX_CPP

#   include "cfg_gfx.hpp"

#   include "../../lib/glad/src/glad.h"

namespace gt {

    namespace gfx {

        void
            clear_error()
        {
            while (glGetError() != GL_NO_ERROR);
        }

        bool
            check_error()
        {

            GLint errorc = glGetError();

            switch (errorc) {

            case GL_INVALID_ENUM:       { GT_ERROR("GL_INVALID_ENUM_____", return GL_TRUE); } break;
            case GL_INVALID_VALUE:      { GT_ERROR("GL_INVALID_VALUE____", return GL_TRUE); } break;
            case GL_INVALID_OPERATION:  { GT_ERROR("GL_INVALID_OPERATION", return GL_TRUE); } break;
            case GL_STACK_OVERFLOW:     { GT_ERROR("GL_STACK_OVERFLOW___", return GL_TRUE); } break;
            case GL_STACK_UNDERFLOW:    { GT_ERROR("GL_STACK_UNDERFLOW__", return GL_TRUE); } break;
            case GL_OUT_OF_MEMORY:      { GT_ERROR("GL_OUT_OF_MEMORY____", return GL_TRUE); } break;

            default: { return GL_FALSE; } break;
            }

        }

        bool
            check_shader(index_t itype, index_t index) {

            GT_CHECK(index > 0, "invalid shader index!", return GL_FALSE);

            int success;
            char* buffer_data = nullptr;
            GLint buffer_size = 0;

            if (itype == GL_CURRENT_PROGRAM) {

                glGetProgramiv(index, GL_LINK_STATUS, &success);
                if (success == GL_TRUE) { return GL_FALSE; }

                glGetProgramiv(index, GL_INFO_LOG_LENGTH, &buffer_size);
                buffer_data = new char[buffer_size];

                glGetProgramInfoLog(index, buffer_size, nullptr, buffer_data);
                GT_ERROR("shader program linkage error!", {
                    GT_EPUT("\n%s\n", buffer_data);
                });

                delete[] buffer_data;

                return GL_TRUE;

            }
            else {

                glGetShaderiv(index, GL_COMPILE_STATUS, &success);
                if (success == GL_TRUE) { return GL_FALSE; }

                glGetShaderiv(index, GL_INFO_LOG_LENGTH, &buffer_size);
                buffer_data = new char[buffer_size];

                glGetShaderInfoLog(index, buffer_size, nullptr, buffer_data);
                GT_ERROR("shader compile error!", {
                    GT_EPUT("\n%s\n", buffer_data);
                });

                delete[] buffer_data;

                return GL_TRUE;

            }

            return GL_FALSE;
        }
 
    }

}

#endif /* CFG_GFX_CPP */