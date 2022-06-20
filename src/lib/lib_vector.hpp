#ifndef LIB_VECTOR_HPP

#	define LIB_VECTOR_HPP

#	include "../../lib/glm/src/vec2.hpp"
#	include "../../lib/glm/src/vec3.hpp"
#	include "../../lib/glm/src/vec4.hpp"

namespace gt {

	/* signed 08bit integer */
	using v1s08_t = signed char;
	using v2s08_t = glm::i8vec2;
	using v3s08_t = glm::i8vec3;
	using v4s08_t = glm::i8vec4;
	/* signed 16bit integer */
	using v1s16_t = unsigned short;
	using v2s16_t = glm::i16vec2;
	using v3s16_t = glm::i16vec3;
	using v4s16_t = glm::i16vec4;
	/* signed 32bit integer */
	using v1s32_t = signed int;
	using v2s32_t = glm::i32vec2;
	using v3s32_t = glm::i32vec3;
	using v4s32_t = glm::i32vec4;
	/* default signed int */
	using v1s_t = signed int;
	using v2s_t = glm::ivec2;
	using v3s_t = glm::ivec3;
	using v4s_t = glm::ivec4;

	/* unsigned 08bit integer */
	using v1u08_t = signed char;
	using v2u08_t = glm::u8vec2;
	using v3u08_t = glm::u8vec3;
	using v4u08_t = glm::u8vec4;
	/* unsigned 16bit integer */
	using v1u16_t = unsigned short;
	using v2u16_t = glm::u16vec2;
	using v3u16_t = glm::u16vec3;
	using v4u16_t = glm::u16vec4;
	/* unsigned 32bit integer */
	using v1u32_t = unsigned int;
	using v2u32_t = glm::u32vec2;
	using v3u32_t = glm::u32vec3;
	using v4u32_t = glm::u32vec4;
	/* default unsigned int */
	using v1u_t = unsigned int;
	using v2u_t = glm::uvec2;
	using v3u_t = glm::uvec3;
	using v4u_t = glm::uvec4;

	/* 32-bit float */
	using v1f32_t = float;
	using v2f32_t = glm::vec2;
	using v3f32_t = glm::vec3;
	using v4f32_t = glm::vec4;
	/* 64-bit float */
	using v1f64_t = double;
	using v2f64_t = glm::dvec2;
	using v3f64_t = glm::dvec3;
	using v4f64_t = glm::dvec4;
	/* default float */
	using v1f_t = v1f32_t;
	using v2f_t = v2f32_t;
	using v3f_t = v3f32_t;
	using v4f_t = v4f32_t;

}

#endif /* LIB_VECTOR_HPP */