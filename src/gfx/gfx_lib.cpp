#ifndef GFX_LIB_CPP

#	define GFX_LIB_CPP

#	include "gfx_lib.hpp"

#   include "../lib/lib_file.hpp"

#	include "../../lib/glad/src/glad.h"

#	define STB_IMAGE_IMPLEMENTATION
#	include "../../lib/stb/src/stb_image.h"

namespace gt {

	namespace gfx {
		/**/
		msize_t
			get_dtype_msize(dtype_t dtype)
		{
			switch (dtype)
			{
			case GL_BYTE:				{ return sizeof(GLbyte) * 1u; }
			case GL_SHORT:				{ return sizeof(GLshort) * 1u; }
			case GL_INT:				{ return sizeof(GLint) * 1u; }
			case GL_INT_VEC2:			{ return sizeof(GLint) * 2u; }
			case GL_INT_VEC3:			{ return sizeof(GLint) * 3u; }
			case GL_INT_VEC4:			{ return sizeof(GLint) * 4u; }
			case GL_UNSIGNED_BYTE:		{ return sizeof(GLubyte) * 1u; }
			case GL_UNSIGNED_SHORT:		{ return sizeof(GLushort) * 1u; }
			case GL_UNSIGNED_INT:		{ return sizeof(GLuint) * 1u; }
			case GL_UNSIGNED_INT_VEC2:	{ return sizeof(GLuint) * 2u; }
			case GL_UNSIGNED_INT_VEC3:	{ return sizeof(GLuint) * 3u; }
			case GL_UNSIGNED_INT_VEC4:	{ return sizeof(GLuint) * 4u; }
			case GL_FLOAT:				{ return sizeof(GLfloat) * 1u; }
			case GL_FLOAT_VEC2:			{ return sizeof(GLfloat) * 2u; }
			case GL_FLOAT_VEC3:			{ return sizeof(GLfloat) * 3u; }
			case GL_FLOAT_VEC4:			{ return sizeof(GLfloat) * 4u; }
			case GL_FLOAT_MAT2:			{ return sizeof(GLfloat) * 2u * 2u; }
			case GL_FLOAT_MAT3:			{ return sizeof(GLfloat) * 3u * 3u; }
			case GL_FLOAT_MAT4:			{ return sizeof(GLfloat) * 4u * 4u; }
			case GL_SAMPLER_1D:			{ return sizeof(GLint) * 1u; }
			case GL_SAMPLER_2D:			{ return sizeof(GLint) * 1u; }
			case GL_SAMPLER_3D:			{ return sizeof(GLint) * 1u; }
			default:					{ GT_ERROR("unknown dtype!", return 0ul); }
			}
			return 0ul;
		}
		msize_t
			get_dtype_msize_align(dtype_t dtype)
		{
			switch (dtype)
			{
			case GL_BYTE: { return sizeof(GLint) * 1u; }
			case GL_SHORT: { return sizeof(GLint) * 1u; }
			case GL_INT: { return sizeof(GLint) * 1u; }
			case GL_INT_VEC2: { return sizeof(GLint) * 2u; }
			case GL_INT_VEC3: { return sizeof(GLint) * 4u; }
			case GL_INT_VEC4: { return sizeof(GLint) * 4u; }
			case GL_UNSIGNED_BYTE: { return sizeof(GLuint) * 1u; }
			case GL_UNSIGNED_SHORT: { return sizeof(GLuint) * 1u; }
			case GL_UNSIGNED_INT: { return sizeof(GLuint) * 1u; }
			case GL_UNSIGNED_INT_VEC2: { return sizeof(GLuint) * 2u; }
			case GL_UNSIGNED_INT_VEC3: { return sizeof(GLuint) * 4u; }
			case GL_UNSIGNED_INT_VEC4: { return sizeof(GLuint) * 4u; }
			case GL_FLOAT: { return sizeof(GLfloat) * 1u; }
			case GL_FLOAT_VEC2: { return sizeof(GLfloat) * 2u; }
			case GL_FLOAT_VEC3: { return sizeof(GLfloat) * 3u; }
			case GL_FLOAT_VEC4: { return sizeof(GLfloat) * 4u; }
			case GL_FLOAT_MAT2: { return sizeof(GLfloat) * 2u * 2u; }
			case GL_FLOAT_MAT3: { return sizeof(GLfloat) * 4u * 4u; }
			case GL_FLOAT_MAT4: { return sizeof(GLfloat) * 4u * 4u; }
			case GL_SAMPLER_1D: { return sizeof(GLint) * 1u; }
			case GL_SAMPLER_2D: { return sizeof(GLint) * 1u; }
			case GL_SAMPLER_3D: { return sizeof(GLint) * 1u; }
			default: { GT_ERROR("unknown dtype!", return 0ul); }
			}
			return 0ul;
		}
		msize_t
			get_dtype_malig(dtype_t dtype)
		{
			switch (dtype)
			{
			case GL_BYTE: { return sizeof(GLint) * 1u; }
			case GL_SHORT: { return sizeof(GLint) * 1u; }
			case GL_INT: { return sizeof(GLint) * 1u; }
			case GL_INT_VEC2: { return sizeof(GLint) * 2u; }
			case GL_INT_VEC3: { return sizeof(GLint) * 4u; }
			case GL_INT_VEC4: { return sizeof(GLint) * 4u; }
			case GL_UNSIGNED_BYTE: { return sizeof(GLuint) * 1u; }
			case GL_UNSIGNED_SHORT: { return sizeof(GLuint) * 1u; }
			case GL_UNSIGNED_INT: { return sizeof(GLuint) * 1u; }
			case GL_UNSIGNED_INT_VEC2: { return sizeof(GLuint) * 2u; }
			case GL_UNSIGNED_INT_VEC3: { return sizeof(GLuint) * 4u; }
			case GL_UNSIGNED_INT_VEC4: { return sizeof(GLuint) * 4u; }
			case GL_FLOAT: { return sizeof(GLfloat) * 1u; }
			case GL_FLOAT_VEC2: { return sizeof(GLfloat) * 2u; }
			case GL_FLOAT_VEC3: { return sizeof(GLfloat) * 4u; }
			case GL_FLOAT_VEC4: { return sizeof(GLfloat) * 4u; }
			case GL_FLOAT_MAT2: { return sizeof(GLfloat) * 2u * 2u; }
			case GL_FLOAT_MAT3: { return sizeof(GLfloat) * 4u * 4u; }
			case GL_FLOAT_MAT4: { return sizeof(GLfloat) * 4u * 4u; }
			case GL_SAMPLER_1D: { return sizeof(GLint) * 1u; }
			case GL_SAMPLER_2D: { return sizeof(GLint) * 1u; }
			case GL_SAMPLER_3D: { return sizeof(GLint) * 1u; }
			default: { GT_ERROR("unknown dtype!", return 0ul); }
			}
			return 0ul;
		}
		/**/
		dtype_t
			get_dtype_item(dtype_t dtype)
		{
			switch (dtype)
			{
			case GL_BYTE:				{ return GL_BYTE; }
			case GL_SHORT:				{ return GL_SHORT; }
			case GL_INT:				{ return GL_INT; }
			case GL_INT_VEC2:			{ return GL_INT_VEC2; }
			case GL_INT_VEC3:			{ return GL_INT_VEC3; }
			case GL_INT_VEC4:			{ return GL_INT_VEC4; }
			case GL_UNSIGNED_BYTE:		{ return GL_UNSIGNED_BYTE; }
			case GL_UNSIGNED_SHORT:		{ return GL_UNSIGNED_SHORT; }
			case GL_UNSIGNED_INT:		{ return GL_UNSIGNED_INT; }
			case GL_UNSIGNED_INT_VEC2:	{ return GL_UNSIGNED_INT_VEC2; }
			case GL_UNSIGNED_INT_VEC3:	{ return GL_UNSIGNED_INT_VEC3; }
			case GL_UNSIGNED_INT_VEC4:	{ return GL_UNSIGNED_INT_VEC4; }
			case GL_FLOAT:				{ return GL_FLOAT; }
			case GL_FLOAT_VEC2:			{ return GL_FLOAT; }
			case GL_FLOAT_VEC3:			{ return GL_FLOAT; }
			case GL_FLOAT_VEC4:			{ return GL_FLOAT; }
			case GL_FLOAT_MAT2:			{ return GL_FLOAT; }
			case GL_FLOAT_MAT3:			{ return GL_FLOAT; }
			case GL_FLOAT_MAT4:			{ return GL_FLOAT; }
			case GL_SAMPLER_1D:			{ return GL_INT; }
			case GL_SAMPLER_2D:			{ return GL_INT; }
			case GL_SAMPLER_3D:			{ return GL_INT; }
			default: { GT_ERROR("unknown dtype!", return 0ul); }
			}
			return 0ul;
		}
		/**/
		count_t
			get_dtype_count_item(dtype_t dtype)
		{
			switch (dtype)
			{
			case GL_BYTE:				{ return 1u; }
			case GL_SHORT:				{ return 1u; }
			case GL_INT:				{ return 1u; }
			case GL_INT_VEC2:			{ return 2u; }
			case GL_INT_VEC3:			{ return 3u; }
			case GL_INT_VEC4:			{ return 4u; }
			case GL_UNSIGNED_BYTE:		{ return 1u; }
			case GL_UNSIGNED_SHORT:		{ return 1u; }
			case GL_UNSIGNED_INT:		{ return 1u; }
			case GL_UNSIGNED_INT_VEC2:	{ return 2u; }
			case GL_UNSIGNED_INT_VEC3:	{ return 3u; }
			case GL_UNSIGNED_INT_VEC4:	{ return 4u; }
			case GL_FLOAT:				{ return 1u; }
			case GL_FLOAT_VEC2:			{ return 2u; }
			case GL_FLOAT_VEC3:			{ return 3u; }
			case GL_FLOAT_VEC4:			{ return 4u; }
			case GL_FLOAT_MAT2:			{ return 2u*2u; }
			case GL_FLOAT_MAT3:			{ return 3u*3u; }
			case GL_FLOAT_MAT4:			{ return 4u*4u; }
			case GL_SAMPLER_1D:			{ return 1u; }
			case GL_SAMPLER_2D:			{ return 1u; }
			case GL_SAMPLER_3D:			{ return 1u; }
			default: { GT_ERROR("unknown dtype!", return 0ul); }
			}
			return 0ul;
		}
		/**/
		msize_t
			get_dtype_msize_item(dtype_t dtype)
		{
			switch (dtype)
			{
			case GL_BYTE:				{ return sizeof(GLbyte); }
			case GL_SHORT:				{ return sizeof(GLshort); }
			case GL_INT:				{ return sizeof(GLint); }
			case GL_INT_VEC2:			{ return sizeof(GLint); }
			case GL_INT_VEC3:			{ return sizeof(GLint); }
			case GL_INT_VEC4:			{ return sizeof(GLint); }
			case GL_UNSIGNED_BYTE:		{ return sizeof(GLubyte); }
			case GL_UNSIGNED_SHORT:		{ return sizeof(GLushort); }
			case GL_UNSIGNED_INT:		{ return sizeof(GLuint); }
			case GL_UNSIGNED_INT_VEC2:	{ return sizeof(GLuint); }
			case GL_UNSIGNED_INT_VEC3:	{ return sizeof(GLuint); }
			case GL_UNSIGNED_INT_VEC4:	{ return sizeof(GLuint); }
			case GL_FLOAT:				{ return sizeof(GLfloat); }
			case GL_FLOAT_VEC2:			{ return sizeof(GLfloat); }
			case GL_FLOAT_VEC3:			{ return sizeof(GLfloat); }
			case GL_FLOAT_VEC4:			{ return sizeof(GLfloat); }
			case GL_FLOAT_MAT2:			{ return sizeof(GLfloat); }
			case GL_FLOAT_MAT3:			{ return sizeof(GLfloat); }
			case GL_FLOAT_MAT4:			{ return sizeof(GLfloat); }
			case GL_SAMPLER_1D:			{ return sizeof(GLint); }
			case GL_SAMPLER_2D:			{ return sizeof(GLint); }
			case GL_SAMPLER_3D:			{ return sizeof(GLint); }
			default: { GT_ERROR("unknown dtype!", return 0ul); }
			}
			return 0ul;
		}
	}

	namespace lib {
		/* saving functions */
		template<> bool
			save(const fpath_t& fpath, const gfx::shader_t* shader)
		{
			GT_CHECK(shader->sbufr.sdata != nullptr && shader->sbufr.msize > 0ul, "there is nothing to save!", return false);
			
			GT_CHECK(save_str(fpath, shader->sbufr.sdata, shader->sbufr.msize), "failed shader file save!", return false);

			return true;
		}
		/* loading functions */
		template<> bool
			load(const fpath_t& fpath, gfx::shader_t* shader)
		{
			if (shader->sbufr.msize != 0ul) {
				delete[] shader->sbufr.sdata;
				shader->sbufr.sdata = nullptr;
				shader->sbufr.msize = 0ul;
			}

			GT_CHECK(load_str(fpath, &shader->sbufr.sdata, &shader->sbufr.msize), "failed shader file load!", return false);

			return true;
		}
		/**/
		template<> bool
			load(const fpath_t& fpath, gfx::texture_t* texture)
		{
			int x, y, comp;
			auto path = fpath.string();
			auto data = stbi_load(&path[0], &x, &y, &comp, STBI_default);
			GT_CHECK(data != nullptr, "failed stbi load!", return false);

			texture->mbufr.msize = x * y * comp;
			texture->mbufr.mdata = data;
			
			texture->pixel_bytes = comp;
			texture->sizes = { x, y };

			return true;
		}
		/**/
	}

}

#endif /* GFX_LIB_CPP */