#ifndef LIB_VECTOR_HPP

#	define LIB_VECTOR_HPP

#	include "../../lib/glm/src/vec2.hpp"
#	include "../../lib/glm/src/vec3.hpp"
#	include "../../lib/glm/src/vec4.hpp"

namespace gt {

	/* signed */
	using v1s_t = signed int;
	using v2s_t = glm::ivec2;
	using v3s_t = glm::ivec3;
	using v4s_t = glm::ivec4;

	/* unsigned */
	using v1u_t = unsigned int;
	using v2u_t	= glm::uvec2;
	using v3u_t	= glm::uvec3;
	using v4u_t = glm::uvec4;

	/* float */
	using v1f_t = float;
	using v2f_t = glm::vec2;
	using v3f_t = glm::vec3;
	using v4f_t	= glm::vec4;

}

#endif /* LIB_VECTOR_HPP */