#ifndef ECS_ENGINE_CPP

#	define ECS_ENGINE_CPP

#	include "ecs_engine.hpp"

#	include "ecs_lib.hpp"
#	include "../sys.hpp"

#	include "../app/app_engine.hpp"
#	include "../gfx/gfx_engine.hpp"

#	include "../../lib/box2d/include/box2d/b2_world.h"
#	include "../../lib/box2d/include/box2d/b2_api.h"
#	include "../../lib/box2d/include/box2d/b2_body.h"
#	include "../../lib/box2d/include/box2d/b2_collision.h"
#	include "../../lib/box2d/include/box2d/b2_shape.h"
#	include "../../lib/box2d/include/box2d/b2_polygon_shape.h"
#	include "../../lib/box2d/include/box2d/b2_fixture.h"

namespace gt {

	namespace ecs {

		entity_t
			engine_t::ecreate()
		{
			auto entity = this->reg.create();

			auto& ebase = this->reg.emplace<ebase_t>(entity);
			ebase.iname = static_cast<entt::id_type>(entity);
			ebase.sname = "entity" + std::to_string(static_cast<entt::id_type>(entity));
			
			return entity;
		}
		bool
			engine_t::eremove(entity_t entity)
		{
			this->reg.destroy(entity);

			return true;
		}

		bool
			engine_t::fsx_play()
		{
			this->fsx = new b2World({ 0.0f, -5.0f });

			for (auto& [
				entity, tform, b2body
			] : this->reg.view<tform_t, b2body_t>().each()) {

				b2BodyDef b2body_info;
				b2body_info.type = b2body.isdynamic ? b2BodyType::b2_dynamicBody : b2BodyType::b2_staticBody;
				b2body_info.fixedRotation = true;
				b2body_info.position = { tform.coord[0], tform.coord[1]};

				b2Body* rigidbody = this->fsx->CreateBody(&b2body_info);

				b2PolygonShape shape;
				shape.SetAsBox(tform.scale[0]/2.0f, tform.scale[1]/2.0f);

				b2FixtureDef fixture_info;
				fixture_info.shape = &shape;
				fixture_info.density = 0.5f;
				fixture_info.friction = 0.5f;
				fixture_info.restitution = 0.5f;
				fixture_info.restitutionThreshold = 1.0f;
				
				rigidbody->CreateFixture(&fixture_info);

				b2body.rigidbody = rigidbody;

				/*
				if (this->reg.any_of<drawgrid_t>(entity)) {

					auto drawgrid = this->reg.get<drawgrid_t>(entity);
					std::vector<b2Vec2> points;
					for (index_t iter = 0; iter < drawgrid.tiles.size(); iter++) {
						
						auto tile = &drawgrid.tiles[iter];

						auto mapx = static_cast<float>(tile->mapid[0]);
						auto mapy = static_cast<float>(tile->mapid[1]);
						auto sizex = tform.scale[0];
						auto sizey = tform.scale[1];

						auto ltile = (mapx * sizex - 0.5f) * sizex;
						auto rtile = (mapx * sizex + 0.5f) * sizex;
						auto btile = (mapy * sizey - 0.5f) * sizey;
						auto utile = (mapy * sizey + 0.5f) * sizey;

						points.push_back({ ltile, btile });
						points.push_back({ ltile, utile });
						points.push_back({ rtile, utile });
						points.push_back({ rtile, btile });

					}

					b2PolygonShape shape;
					shape.Set(&points[0], points.size());

				}
				*/

			}

			return true;
		}
		bool
			engine_t::fsx_stop()
		{
			for (auto& [
				entity, tform, b2body
			] : this->reg.view<tform_t, b2body_t>().each()) {

				this->fsx->DestroyBody((b2Body*)b2body.rigidbody);
				b2body.rigidbody = nullptr;

			}
			delete this->fsx; this->fsx = nullptr;

			return true;
		}

		bool
			engine_t::init()
		{
			auto entity = this->reg.create();

			auto app = app::engine_t::get();
			auto sys = sys::engine_t::get();
			auto gfx = gfx::engine_t::get();

			auto drawtool = gfx->get_drawtool();
			auto materia = &drawtool->materia;
			auto binding = &materia->binding;

			gfx->load_texture("../rsc/imag/bit2tile16.png", 1);
			gfx->load_texture("../rsc/imag/bit2char16.png", 2);
			gfx->load_texture("../rsc/imag/bit1nikochir32.png", 3);
			gfx->load_texture("../rsc/imag/bit1bone16.png", 4);
			gfx->load_texture("../rsc/imag/bit1cursemark16.png", 5);
			gfx->load_texture("../rsc/imag/bit1necro16.png", 6);

			this->fsx = nullptr;

			v2f_t coords[] = {
				{ +0.0f, -GT_MAP_SIZES_USE - 1.0f },
				{ +0.0f, +GT_MAP_SIZES_USE + 1.0f },
				{ -GT_MAP_SIZES_USE - 1.0f, +0.0f },
				{ +GT_MAP_SIZES_USE + 1.0f, +0.0f },
			};
			v2f_t scales[] = {
				{ GT_MAP_SIZES_USE * 2.0f, 1.0f },
				{ GT_MAP_SIZES_USE * 2.0f, 1.0f },
				{ 1.0f, GT_MAP_SIZES_USE * 2.0f },
				{ 1.0f, GT_MAP_SIZES_USE * 2.0f },
			};
			for (index_t iter = 0; iter < 4; iter++) {

				entity = this->ecreate();

				auto& ebase = this->reg.get<ebase_t>(entity);

				auto& drawrect = this->ccreate<drawrect_t>(entity);

				drawrect.visio.color = { 1.0f, 1.0f, 1.0f, 0.75f };
				drawrect.visio.texid = { GT_GFX_TEXTURE_COUNT_LAST };
				drawrect.visio.texuv = { 0.125f, 0.125f, 0.250f, 0.250f };

				auto& tform = this->ccreate<ecs::tform_t>(entity);

				tform.coord = coords[iter];
				tform.scale = scales[iter];

				auto& b2body = this->ccreate<b2body_t>(entity);

				b2body.isdynamic = false;
			}
			{
				entity = this->ecreate();

				auto& ebase = this->reg.get<ebase_t>(entity);
				ebase.sname = "player";
				
				auto& player = this->ccreate<ecs::player_t>(entity);
				player.camera_target = true;
				player.controlled = true;
				player.speed = 2.0f;

				auto& mover = this->ccreate<ecs::mover_t>(entity);

				auto& drawrect = this->ccreate<ecs::drawrect_t>(entity);
				drawrect.visio.color = { 1.0f, 1.0f, 1.0f, 1.0f };
				drawrect.visio.texid = { 1 };
				drawrect.visio.texuv = { 0.0f, 0.0f, 1.0f, 1.0f };

				auto& tform = this->ccreate<ecs::tform_t>(entity);
				tform.coord = { 0.0f, 0.0f };
				tform.scale = { 1.0f, 1.0f };

				auto& b2body = this->ccreate<b2body_t>(entity);
				
				b2body.isdynamic = true;

			}

			return this->play();
		}
		bool
			engine_t::work()
		{
			auto app = app::engine_t::get();
			auto gfx = gfx::engine_t::get();
			auto sys = sys::engine_t::get();

			auto timer = app->get_timer();
			auto timer_delta = static_cast<float>(timer->get_delta());
			/* physics */
			if (this->fsx != nullptr) {

				const v1s_t iter_veloc = 6, iter_coord = 2;
				this->fsx->Step(timer_delta, iter_veloc, iter_coord);

				for (auto& [
					entity, tform, b2body
				] : this->reg.view<tform_t, b2body_t>().each()) {

					auto rigidbody = (b2Body*)(b2body.rigidbody);
					tform.coord = { rigidbody->GetPosition().x, rigidbody->GetPosition().y };

				}

			}
			/* graphics */
			for (auto&[
				entity, tform, drawrect
			] : this->reg.view<tform_t, drawrect_t>().each()) {

				gfx->add_for_draw(
					v2f_t{ 0.0f, 0.0f },
					tform.scale,
					tform.coord,
					drawrect.visio.texid,
					drawrect.visio.texuv,
					drawrect.visio.color
				);

			}
			for (auto&[
				entity, tform, drawgrid
			] : this->reg.view<tform_t, drawgrid_t>().each()) {

				gfx->add_for_draw(
					tform.scale,
					drawgrid.visio.texid,
					drawgrid.visio.texuv,
					drawgrid.visio.color,
					drawgrid.tiles
				);

			}
			/* game logic */
			for (auto& [
				entity, player, tform
			] : this->reg.view<player_t, tform_t>().each()) {
				
				auto camera = gfx::engine_t::get()->get_camera();
				if (player.camera_target) { camera->coord = tform.coord; }

				player.grounded = (tform.coord[1] - tform.scale[1] / 2.0f) < -GT_MAP_SIZES_USE;

			}
			for (auto&
				[entity, player, b2body]
				: this->reg.view<player_t, b2body_t>().each()) {

				if (player.controlled) {

					auto keybod = sys->get_keybod();

					using enum sys::keybod_t::kcode_t;
					using enum sys::keybod_t::state_t;

					b2Body* rigidbody = (b2Body*)b2body.rigidbody;
					if (rigidbody != nullptr) {

						if (keybod->vet_button_held(KCODE_A)) { rigidbody->ApplyForce({ -player.speed,0.0f }, { 0.0f, 0.0f }, true); }
						if (keybod->vet_button_held(KCODE_D)) { rigidbody->ApplyForce({ +player.speed,0.0f }, { 0.0f, 0.0f }, true); }
						if (keybod->vet_button_press(KCODE_W)) {
							if (rigidbody->GetLinearVelocity().y < 0.05f) {

								rigidbody->ApplyForce({ 0.0f, +player.speed * 50.0f }, { 0.0f, 0.0f }, true);
							}
						}
						
					}

				}

			}
			/* general */
			auto each = [this](auto entity)->void {

				if (reg.orphan(entity)) { reg.destroy(entity); }

			};
			this->reg.each(each);

			return true;
		}
		bool
			engine_t::quit()
		{

			this->reg.clear();

			return true;
		}

		bool
			engine_t::proc(lib::event_a_t* event)
		{
			
			if (event->has_kind<sys::keybod_t::event_t>()) {

				using enum sys::keybod_t::kcode_t;
				using enum sys::keybod_t::state_t;

				auto evt = static_cast<sys::keybod_t::event_t*>(event);
				
				return true;
			}

			return true;
		}

	}

}

#endif /* ECS_ENGINE_CPP */