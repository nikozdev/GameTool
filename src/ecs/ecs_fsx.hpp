#ifndef ECS_FSX_HPP

#	define ECS_FSX_HPP

#	include "../cfg.hpp"

#	include "ecs_lib.hpp"

namespace gt {
	/* alias */
	namespace ecs {
		/* just position */
		ECS_TYPEDEF(coord_t, v2f_t);
		/* just rotation */
		ECS_TYPEDEF(angle_t, v1f_t);
		/* size multiplier */
		ECS_TYPEDEF(scale_t, v2f_t);
		/* gravity - acceleration y changing value */
		ECS_TYPEDEF(gravi_t, v1f_t);
		/* acceleration - velocity changing value */
		ECS_TYPEDEF(accel_t, v1f_t);
		/* velocity - position changing value */
		ECS_TYPEDEF(veloc_t, v1f_t);
		/* torque - angle changing value */
		ECS_TYPEDEF(torqu_t, v1f_t);

	}
	/* components */
	namespace ecs {
		/* collection of position, rotation and scale */
		typedef struct tform_t {
			coord_t coord;
			angle_t angle;
			scale_t	scale;
		} tform_t;
		/* position and angle changing values */
		typedef struct mover_t {

			veloc_t veloc;
			accel_t accel;

			torqu_t	torqu;

		} mover_t;
		/* body - transform, mover and other physical values bundle */
		typedef struct body_t {

			tform_t tform;
			mover_t mover;

		} body_t;
	}
	/* functions */
	namespace ecs {

		template<> inline void
			ecproc(entity_t& entity, gravi_t& gravi, accel_t& accel)
		{
			static_cast<v2f_t>(accel)[1] = gravi;
		}
		template<> inline void
			ecproc(entity_t& entity, accel_t& accel, veloc_t& veloc)
		{
			accel = 0.1f;
			veloc += accel;
		}
		template<> inline void
			ecproc(entity_t& entity, veloc_t& veloc, coord_t& coord)
		{
			static_cast<v2f_t>(coord) += veloc;
		}
		template<> inline void
			ecproc(entity_t& entity, torqu_t& torqu, angle_t& angle)
		{
			static_cast<v1f_t>(angle) += torqu;
		}

		template<> inline void
			ecproc(entity_t& entity, mover_t& mover)
		{
			ecproc(entity, mover.accel, mover.veloc);
		}
		template<> inline void
			ecproc(entity_t& entity, mover_t& mover, coord_t& coord)
		{
			static_cast<v2f_t>(coord) += mover.veloc;
		}
		template<> inline void
			ecproc(entity_t& entity, mover_t& mover, tform_t& tform)
		{
			static_cast<v2f_t>(tform.coord) += mover.veloc;
			static_cast<v2f_t>(tform.angle) += mover.torqu;
		}

	}

}

#endif /* ECS_FSX_HPP */