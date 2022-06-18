#ifndef LIB_MATRIX_HPP

#	define LIB_MATRIX_HPP

#	include "../../lib/glm/src/matrix.hpp"
#	include "../../lib/glm/src/ext/matrix_transform.hpp"

namespace gt {

	/* signed */
	using v2s_t = glm::ivec2;
	using v3s_t = glm::ivec3;
	using v4s_t = glm::ivec4;

	/* unsigned */
	using v2u_t = glm::uvec2;
	using v3u_t = glm::uvec3;
	using v4u_t = glm::uvec4;

	/* float */
	using v2f_t = glm::vec2;
	using v3f_t = glm::vec3;
	using v4f_t = glm::vec4;

}

#endif /* LIB_VECTOR_HPP */