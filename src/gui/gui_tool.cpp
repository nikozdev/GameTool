#ifndef GUI_TOOL_CPP

#	define GUI_TOOL_CPP

#	include "gui_tool.hpp"
#	include "gui_engine.hpp"

#	include "../app.hpp"
#	include "../sys.hpp"
#	include "../gfx.hpp"
#	include "../ecs.hpp"

#	include "../../lib/imgui/src/imgui.h"
#	include "../../lib/imgui/src/imgui_internal.h"

#	define TREE_FLAGS (						\
		ImGuiTreeNodeFlags_Selected |		\
		ImGuiTreeNodeFlags_Framed |			\
		ImGuiTreeNodeFlags_OpenOnArrow |	\
		ImGuiTreeNodeFlags_OpenOnDoubleClick\
) /* TREE_FLAGS */
#	define INPUT_FLAGS						\
	ImGuiInputTextFlags_AutoSelectAll |		\
	ImGuiInputTextFlags_EnterReturnsTrue	\
/* INPUT_FLAGS */
#	define POPUP_FLAGS						\
	ImGuiPopupFlags_MouseButtonRight		\
/* POPUP_FLAGS */

#	define PIVOT_TEXT "pivot"
#	define PIVOT_FROM -1.0f
#	define PIVOT_UPTO +1.0f

#	define COORD_TEXT "coord"
#	define COORD_FROM -GT_MAP_SIZES_USE
#	define COORD_UPTO +GT_MAP_SIZES_USE

#	define SCALE_TEXT "scale"
#	define SCALE_FROM 0.01f
#	define SCALE_UPTO 10.0f

#	define SIZES_TEXT "sizes"
#	define SIZES_FROM 0.01f
#	define SIZES_UPTO 10.0f

#	define COLOR_TEXT "color"
#	define COLOR_FROM 0.0f
#	define COLOR_UPTO 1.0f

#	define INDEX_TEXT "index"
#	define INDEX_FROM 0
#	define INDEX_UPTO GT_GFX_TEXTURE_COUNT_USE

#	define WIDTH_TEXT "width"
#	define WIDTH_FROM 0.01f
#	define WIDTH_UPTO 1.00f

#	define IMAGE_SIZE 128.0f

namespace gt {

	namespace gui {

		inline v2f_t
			get_myvec2(const v2u_t& vec)
		{
			return v2f_t{ static_cast<float>(vec[0]), static_cast<float>(vec[1]) };
		}
		inline v2f_t
			get_myvec2(const ImVec2& imvec)
		{
			return v2f_t { imvec.x, imvec.y };
		}
		inline ImVec2
			get_imvec2(const v2f_t& myvec)
		{
			return ImVec2 { myvec[0], myvec[1] };
		}
		inline ImVec4
			get_imvec4(const v4f_t& myvec)
		{
			return ImVec4{ myvec[0], myvec[1], myvec[2], myvec[3] };
		}

	}

	namespace gui {

		bool
			tool_gfx_t::init()
		{
			this->gfx = gfx::engine_t::get();
			
			this->grid.flag = true;
			
			this->grid.width = 0.05f;

			this->grid.tiles.count = { static_cast<count_t>(GT_MAP_SIZES_USE*2) };
			this->grid.tiles.sizes = { 1.0f, 1.0f };

			return this->show();;
		}

		bool
			tool_gfx_t::work()
		{
			if (ImGui::TreeNodeEx("state", TREE_FLAGS)) {

				auto state = gfx->get_state();
				
				auto viewport = state->viewport;
				ImGui::Text("viewport=([x]%d[y]%d[w]%d[h]%d)", viewport[0], viewport[1], viewport[2], viewport[3]);
				auto clearcol = state->clearcol;
				ImGui::Text("clearcol=([r]%.3f[g]%.3f[b]%.3f[a]%.3f)", clearcol[0], clearcol[1], clearcol[2], clearcol[3]);

				if (ImGui::SliderFloat("point size", &this->state.point_size, 0.1f, 10.0f, "%.2f")) { gfx->set_point_size(this->state.point_size); }
				if (ImGui::SliderFloat("lines size", &this->state.lines_size, 0.1f, 10.0f, "%.2f")) { gfx->set_lines_size(this->state.lines_size); }

				ImGui::Text("facemode");
				if (ImGui::Button("fill")) { gfx->set_facemode(gfx::FACEMODE_FILL); }
				if (ImGui::Button("line")) { gfx->set_facemode(gfx::FACEMODE_LINE); }

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("camera", TREE_FLAGS)) {

				auto camera = &gfx->camera;

				ImGui::SliderFloat2(COORD_TEXT, &camera->coord[0], COORD_FROM, COORD_UPTO);
				ImGui::SliderFloat(SCALE_TEXT, &camera->scale, SCALE_FROM, SCALE_UPTO, "%.2f");

				ImGui::InputFloat("ratio", &camera->ratio, 0.0f, 0.0f, "%.2f", ImGuiInputTextFlags_ReadOnly);
				
				ImGui::SliderFloat("speed", &camera->speed, 0.0f, 10.0f, "%.2f");
				ImGui::InputFloat3("velocity", &camera->veloc[0], "%.2f", ImGuiInputTextFlags_ReadOnly);
				
				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("drawtool", TREE_FLAGS)) {

				auto drawtool = &gfx->drawtool;

				if (ImGui::TreeNodeEx("input layout", TREE_FLAGS)) {

					auto ilayout = &drawtool->ilayout;

					if (ImGui::TreeNodeEx("input layout mapping", TREE_FLAGS)) {

						auto mapping = &ilayout->mapping;
						ImGui::Text("memory size=%d", mapping->msize);
						ImGui::Text("count of elements=%d", mapping->count);

						for (index_t index = 0; index < mapping->count; index++) {

							auto element = &mapping->mdata[index];
							if (ImGui::TreeNodeEx(element->sname.sdata, TREE_FLAGS) == false) { continue; }
							
							int iname = element->iname;
							ImGui::InputInt("index", &iname, 0, 0, ImGuiInputTextFlags_ReadOnly);
							auto sname = &element->sname;
							ImGui::InputText("label", &sname->sdata[0], sname->msize, ImGuiInputTextFlags_ReadOnly);
							
							int count = element->count;
							ImGui::InputInt("count", &count, 0, 0, ImGuiInputTextFlags_ReadOnly);
							
							int msize = element->msize;
							ImGui::InputInt("memory size", &msize, 0, 0, ImGuiInputTextFlags_ReadOnly);
							int start = element->start;
							ImGui::InputInt("memory offset", &start, 0, 0, ImGuiInputTextFlags_ReadOnly);
							int malig = element->malig;
							ImGui::InputInt("memory alignment", &malig, 0, 0, ImGuiInputTextFlags_ReadOnly);
							
							ImGui::TreePop();
						}

						ImGui::TreePop();
					}

					ImGui::TreePop();
				}
				if (ImGui::TreeNodeEx("graphics material", TREE_FLAGS)) {

					auto materia = &drawtool->materia;
					auto binding = &materia->binding;

					if (ImGui::TreeNodeEx("material mapping", TREE_FLAGS)) {

						auto mapping = &materia->mapping;
						ImGui::Text("memory size=%d", mapping->msize);
						ImGui::Text("count of elements=%d", mapping->count);

						for (index_t index = 0; index < mapping->count; index++) {

							auto element = &mapping->mdata[index];
							if (ImGui::TreeNodeEx(element->sname.sdata, TREE_FLAGS) == false) { continue; }
							ImGui::Text("index name=%d", element->iname);
							ImGui::Text("string name=%s", element->sname.sdata);
							ImGui::Text("count=%d", element->count);
							ImGui::Text("msize=%zu", element->msize);
							ImGui::Text("memory offset=%d", element->start);
							ImGui::Text("memory alignment=%d", element->malig);

							ImGui::TreePop();
						}

						ImGui::TreePop();
					}

					if (ImGui::TreeNodeEx("textures", TREE_FLAGS)) {

						for (index_t iter = 0; iter < GT_GFX_TEXTURE_COUNT_LAST; iter++) {
							
							char buffer[GT_GFX_TEXTURE_COUNT_MAX] = { '\0' };
							::itoa(iter + 1, buffer, 10);

							auto texture = &binding->texture_array[iter];
							if (ImGui::TreeNodeEx(buffer, TREE_FLAGS) == false) { continue; }
							ImGui::Text("index=(%d)", texture->index);
							ImGui::Text("sizes=(%dx%dy)", texture->sizes[0], texture->sizes[1]);
							ImGui::Text("pixel bytes=(%zu)", texture->pixel_bytes);
							ImGui::Text("memory size=(%zu)", texture->mbufr.msize);
						
							auto index = reinterpret_cast<ImTextureID>(texture->index);
							auto ratio = static_cast<float>(texture->sizes[0]) / static_cast<float>(texture->sizes[1]);
							ImVec2 sizes = { IMAGE_SIZE * ratio, IMAGE_SIZE * 1.0f };
							if (ImGui::ImageButton(index, sizes)) {
								
								

							}

							ImGui::TreePop();
						}

						ImGui::TreePop();
					}

					ImGui::TreePop();
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("framebuffer", TREE_FLAGS)) {

				auto fmbuffer = gfx->get_fmbuffer();
				
				int index = fmbuffer->index;
				ImGui::InputInt("index", &index, 0, 0, ImGuiInputTextFlags_ReadOnly);
				
				auto viewport = fmbuffer->viewport;
				ImGui::InputInt4("viewport", &viewport[0], ImGuiInputTextFlags_ReadOnly);

				if (ImGui::TreeNodeEx("color attachment", TREE_FLAGS)) {
					
					auto colorbuf = &fmbuffer->colorbuf;
					
					int index = colorbuf->index;
					ImGui::InputInt("index", &index, 0, 0, ImGuiInputTextFlags_ReadOnly);

					v2s_t sizes = { colorbuf->sizes[0], colorbuf->sizes[1] };
					ImGui::InputInt2("sizes", &sizes[0], ImGuiInputTextFlags_ReadOnly);
					ImGui::Text("pixel bytes=(%zu)", colorbuf->pixel_bytes);
					ImGui::Text("memory size=(%zu)", colorbuf->mbufr.msize);

					float ratio = static_cast<float>(colorbuf->sizes[0]) / static_cast<float>(colorbuf->sizes[1]);
					auto imindex = reinterpret_cast<ImTextureID>(colorbuf->index);
					ImVec2 imsizes = { IMAGE_SIZE * ratio, IMAGE_SIZE * 1.0f };
					ImGui::Image(imindex, imsizes);
					
					ImGui::TreePop();
				}

				ImGui::TreePop();
			}

			auto ginfo = gfx->get_ginfo();
			if (ImGui::TreeNodeEx("performance", TREE_FLAGS)) {

				ImGui::Text("draw call count=(%d)", ginfo->drawcall.count);
				ImGui::Text("rectangle count=(%d/%d)", ginfo->drawable.drawn_count, ginfo->drawable.store_count);
				ImGui::Text("vertex memory size=(%zu)", ginfo->vbuffer.vsize);
				ImGui::Text("vertex data memory=(%zu/%zu)", ginfo->vbuffer.drawn_bytes, ginfo->vbuffer.store_bytes);
				ImGui::Text("texture count=(%d)", ginfo->texture.count);
				
				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("grid", TREE_FLAGS)) {

				ImGui::Checkbox("visible", &this->grid.flag);
				
				ImGui::SliderFloat(WIDTH_TEXT, &this->grid.width, WIDTH_FROM, WIDTH_UPTO, "%.2f");
				ImGui::SliderFloat2(SCALE_TEXT, &this->grid.tiles.sizes[0], SCALE_FROM, SCALE_UPTO);

				ImGui::TreePop();
			}
			if (this->grid.flag) {

				gfx::rect_t tile;
				tile.pivot = { 0.0f, 0.0f };
				tile.color = { 0.0f, 0.0f, 0.0f, 1.0f };
				tile.texuv = { 0.0f, 0.0f, 1.0f, 1.0f };
				tile.texid = { GT_GFX_TEXTURE_COUNT_LAST };

				v2f_t grid_sizes = {
					this->grid.tiles.sizes.y * static_cast<float>(this->grid.tiles.count),
					this->grid.tiles.sizes.y * static_cast<float>(this->grid.tiles.count)
				};

				auto iter = 0.0f;
				auto step = 1.0f;
				auto tiles_count = static_cast<float>(this->grid.tiles.count);
				auto tiles_count_side = tiles_count / 2.0f;

				tile.scale = { this->grid.width, this->grid.tiles.sizes.y * tiles_count };
				for (iter = -tiles_count_side; iter <= +tiles_count_side; iter += step) {

					tile.coord = { iter * this->grid.tiles.sizes.x - this->grid.tiles.sizes.x / 2.0f, 0.0f };

					this->gfx->add_for_draw(tile);
				}
				tile.scale = { this->grid.tiles.sizes.x * tiles_count, this->grid.width };
				for (iter = -tiles_count_side; iter <= +tiles_count_side; iter += step) {

					tile.coord = { 0.0f, iter * this->grid.tiles.sizes.y - this->grid.tiles.sizes.y / 2.0f };

					this->gfx->add_for_draw(tile);
				}

			}
			
			gfx::rect_t frame;
			frame.color = { 0.0f, 0.0f, 0.0f, 1.0f };
			frame.scale = { 1000.0f, 1000.0f };
			
			frame.texid = { GT_GFX_TEXTURE_COUNT_LAST };
			frame.texuv = { 0.0f, 0.0f, 1.0f, 1.0f };
			
			frame.pivot = { +0.5f, 0.0f };
			frame.coord = { -GT_MAP_SIZES_USE, 0.0f };
			gfx->add_for_draw(frame);
			frame.pivot = { -0.5f, 0.0f };
			frame.coord = { +GT_MAP_SIZES_USE, 0.0f };
			gfx->add_for_draw(frame);
			frame.pivot = { 0.0f, +0.5f };
			frame.coord = { 0.0f, -GT_MAP_SIZES_USE };
			gfx->add_for_draw(frame);
			frame.pivot = { 0.0f, -0.5f };
			frame.coord = { 0.0f, +GT_MAP_SIZES_USE };
			gfx->add_for_draw(frame);

			return true;
		}

		bool
			tool_gfx_t::quit()
		{
			this->gfx = nullptr;

			return true;
		}

	}

	namespace gui {

		bool
			tool_ecs_t::init()
		{
			this->ecs = ecs::engine_t::get();
			this->reg = &ecs->reg;

			this->entity_to_remove = {};

			return this->show();
		}

		bool
			tool_ecs_t::work()
		{
			bool fsx_playing = ecs->fsx != nullptr;
			if (ImGui::Checkbox("physics simulation", &fsx_playing)) {
				if (!fsx_playing) { this->ecs->fsx_stop(); }
				else { this->ecs->fsx_play(); }
			}

			if (ImGui::BeginPopupContextWindow("actions", POPUP_FLAGS, false)) {

				if (ImGui::MenuItem("create entity")) {

					ecs->ecreate();

				}
				static int count = 0;
				if (ImGui::InputInt("create entity n-times", &count, 1, 100, INPUT_FLAGS)) {
					
					for (int index = 0; index < count; index++) {

						ecs->ecreate();
					
					}

				}

				ImGui::EndPopup();
			}

			ImGui::Separator();

			auto view = this->reg->view<ecs::ebase_t>();
			for (auto [entity, ebase] : view.each()) {

				if (ImGui::TreeNodeEx(&ebase.sname[0], TREE_FLAGS)) {
					
					GT_CHECK(this->draw(entity, &ebase), "failed entity draw!", return false);

					ImGui::TreePop();
				}

			}

			if (reg->valid(entity_to_remove)) { return ecs->eremove(entity_to_remove); }

			return true;
		}

		bool
			tool_ecs_t::quit()
		{
			this->ecs = nullptr;
			this->reg = nullptr;

			this->entity_to_remove = {};

			return true;
		}

		template<> inline bool
			tool_ecs_t::draw(ecs::entity_t entity, ecs::player_t* player)
		{
			ImGui::SliderFloat("speed", &player->speed, 0.0f, 5.0f, "%.2f", INPUT_FLAGS);
			ImGui::Checkbox("cammera target", &player->camera_target);
			ImGui::Checkbox("is controlled", &player->controlled);
			ImGui::Checkbox("grounded", &player->grounded);

			return true;
		}

		template<> inline bool
			tool_ecs_t::draw(ecs::entity_t entity, ecs::tform_t* tform)
		{
			ImGui::SliderFloat2(SCALE_TEXT, &tform->scale[0], SCALE_FROM, SCALE_UPTO);
			ImGui::SliderFloat2(COORD_TEXT, &tform->coord[0], COORD_FROM, COORD_UPTO);
			
			return true;
		}
		template<> inline bool
			tool_ecs_t::draw(ecs::entity_t entity, ecs::b2body_t* b2body)
		{
			if (ImGui::Checkbox("isdynamic", &b2body->isdynamic)) {
				if (this->ecs->fsx != nullptr) {
					this->ecs->fsx_stop();
					this->ecs->fsx_play();
				}
			}

			return true;
		}

		template<> inline bool
			tool_ecs_t::draw<ecs::drawrect_t>(ecs::entity_t entity, ecs::drawrect_t* drawrect)
		{
			auto visio = &drawrect->visio;
			
			auto binding = &gfx::engine_t::get()->get_drawtool()->materia.binding;
			auto texture = &binding->texture_array[(visio->texid + 1) % binding->count];
			
			auto imtexid = reinterpret_cast<ImTextureID>(texture->index);
			auto ratio = static_cast<float>(texture->sizes[0]) / static_cast<float>(texture->sizes[1]);
			ImVec2 sizes = { IMAGE_SIZE * ratio, IMAGE_SIZE * 1.0f };
			ImGui::Image(imtexid, sizes, {0.0f, 0.0f}, {1.0f, 1.0f}, get_imvec4(visio->color));
			
			if (ImGui::InputInt("texture " INDEX_TEXT, &visio->texid, 1, 4, INPUT_FLAGS)) {
				
				visio->texid %= binding->count;

			}
			ImGui::SliderFloat4("texture " COORD_TEXT, &visio->texuv[0], COORD_FROM, COORD_UPTO);
			ImGui::SliderFloat4("texture " COLOR_TEXT, &visio->color[0], COLOR_FROM, COLOR_UPTO);

			return true;
		}
		template<> inline bool
			tool_ecs_t::draw<ecs::drawgrid_t>(ecs::entity_t entity, ecs::drawgrid_t* drawgrid)
		{
			auto visio = &drawgrid->visio;

			auto binding = &gfx::engine_t::get()->get_drawtool()->materia.binding;
			auto texture = &binding->texture_array[(visio->texid + 1) % binding->count];

			auto imtexid = reinterpret_cast<ImTextureID>(texture->index);
			auto ratio = static_cast<float>(texture->sizes[0]) / static_cast<float>(texture->sizes[1]);
			ImVec2 sizes = { IMAGE_SIZE * ratio, IMAGE_SIZE * 1.0f };
			ImGui::Image(imtexid, sizes, { 0.0f, 0.0f }, { 1.0f, 1.0f }, { get_imvec4(visio->color) });
			if (ImGui::InputInt("texture " INDEX_TEXT, &visio->texid, 1, 4, INPUT_FLAGS)) {

				visio->texid %= binding->count;
			
			}	
			if (ImGui::InputFloat4("texture " COORD_TEXT, &visio->texuv[2], "%.3f", INPUT_FLAGS)) {
				
				visio->texuv[0] = GT_CLAMP(visio->texuv[0], 0.0f, 1.0f);
				visio->texuv[1] = GT_CLAMP(visio->texuv[1], 0.0f, 1.0f);
				visio->texuv[2] = GT_CLAMP(visio->texuv[2], 0.0f, 1.0f);
				visio->texuv[3] = GT_CLAMP(visio->texuv[3], 0.0f, 1.0f);
			}
			ImGui::SliderFloat4("texture " COLOR_TEXT, &visio->color[0], COLOR_FROM, COLOR_UPTO);

			v2s_t tex_count;
			tex_count[0] = 1.0f / static_cast<v4f_t&>(visio->texuv)[2];
			tex_count[1] = 1.0f / static_cast<v4f_t&>(visio->texuv)[3];
			ImGui::InputInt2("texture count", &tex_count[0], ImGuiInputTextFlags_ReadOnly);

			if (ImGui::TreeNodeEx("tiles", TREE_FLAGS)) {

				int count = drawgrid->tiles.size();
				ImGui::InputInt("count", &count, 0, 0, ImGuiInputTextFlags_ReadOnly);

				if (ImGui::Button("add tile")) { drawgrid->tiles.push_back(gfx::tile_t{}); }

				ImGui::Separator();

				for (index_t iter = 0; iter < drawgrid->tiles.size(); iter++) {
					
					if (ImGui::TreeNodeEx(&std::to_string(iter)[0], TREE_FLAGS) == false) { continue; }

					auto tile = &drawgrid->tiles[iter];

					if (ImGui::InputInt2("map index", &tile->mapid[0], INPUT_FLAGS)) {
						tile->mapid[0] = GT_CLAMP(tile->mapid[0], COORD_FROM, COORD_UPTO);
						tile->mapid[1] = GT_CLAMP(tile->mapid[1], COORD_FROM, COORD_UPTO);
					}
					if (ImGui::InputInt2("texture index", &tile->texid[0], INPUT_FLAGS)) {
						tile->texid[0] = GT_CLAMP(tile->texid[0], 0, tex_count[0] - 1);
						tile->texid[1] = GT_CLAMP(tile->texid[1], 0, tex_count[1] - 1);
					}

					auto ratio = static_cast<v4f_t&>(visio->texuv)[2] / static_cast<v4f_t&>(visio->texuv)[3];
					ImVec2 sizes =		{ 32.0f * ratio, 32.0f * 1.0f };
					ImVec2 coord_lb =	{
						static_cast<v4f_t&>(visio->texuv)[2] * tile->texid[0] + 0,
						static_cast<v4f_t&>(visio->texuv)[3] * tile->texid[1] + 0
					};
					ImVec2 coord_rt =	{
						static_cast<v4f_t&>(visio->texuv)[2] * tile->texid[0] + 1,
						static_cast<v4f_t&>(visio->texuv)[3] * tile->texid[1] + 1
					};
					ImGui::Image(imtexid, sizes, coord_lb, coord_rt, get_imvec4(visio->color));

					if (ImGui::Button("remove")) {
						
						drawgrid->tiles.erase(drawgrid->tiles.begin() + iter);
						ImGui::TreePop();
						
						break;
					}

					ImGui::TreePop();
				}

				ImGui::TreePop();
			}

			return true;
		}

		inline bool
			tool_ecs_t::draw(ecs::entity_t entity, ecs::ebase_t* ebase)
		{
			int index = ebase->iname;
			ImGui::InputInt(INDEX_TEXT, &index, 0, 0, ImGuiInputTextFlags_ReadOnly);

			static char buffer[GT_NAME_SIZE_MAX];
			strcpy_s(buffer, GT_NAME_SIZE_MAX, &ebase->sname[0]);
			if (ImGui::InputText("label", buffer, GT_NAME_SIZE_MAX, INPUT_FLAGS)) { ebase->sname = buffer; }

			ImGui::Separator();

			if (ImGui::Button("remove")) { this->entity_to_remove = entity; }
			
			if (this->reg->all_of<
				ecs::player_t,
				ecs::tform_t,
				ecs::b2body_t,
				ecs::drawrect_t,
				ecs::drawgrid_t
			>(entity) == false) {
				if (ImGui::Button("create component")) { ImGui::OpenPopup("create component menu"); }
			}
			if (this->reg->any_of<
				ecs::player_t,
				ecs::tform_t,
				ecs::b2body_t,
				ecs::drawrect_t,
				ecs::drawgrid_t
			>(entity) == true) {
				if (ImGui::Button("remove component")) { ImGui::OpenPopup("remove component menu"); }
			}

#			define CREATE_COMPON_ITEM(type, label)				\
				if (reg->any_of<type>(entity) == false) {		\
					if (ImGui::MenuItem(label)) {				\
						ecs->ccreate<type>(entity);				\
					}											\
				}												\
			/* CREATE_COMPON_ITEM */
			if (ImGui::BeginPopup("create component menu")) {

				CREATE_COMPON_ITEM(ecs::player_t, "player");
				CREATE_COMPON_ITEM(ecs::tform_t, "transform");
				CREATE_COMPON_ITEM(ecs::b2body_t, "rigid body");
				CREATE_COMPON_ITEM(ecs::drawrect_t, "sprite");
				CREATE_COMPON_ITEM(ecs::drawgrid_t, "tilemap");

				ImGui::EndPopup();
			}
#			undef CREATE_COMPON

#			define REMOVE_COMPON_ITEM(type, label)				\
				if (reg->any_of<type>(entity) == true) {		\
					if (ImGui::MenuItem(label)) {				\
						GT_CHECK(								\
							ecs->cremove<type>(entity),			\
							"failed component interaction!",	\
							{ return false; }					\
						);										\
					}											\
				}												\
			/* REMOVE_COMPON_ITEM */
			if (ImGui::BeginPopup("remove component menu")) {

				REMOVE_COMPON_ITEM(ecs::player_t, "player");
				REMOVE_COMPON_ITEM(ecs::tform_t, "transform");
				REMOVE_COMPON_ITEM(ecs::b2body_t, "rigidbody");
				REMOVE_COMPON_ITEM(ecs::drawrect_t, "sprite");
				REMOVE_COMPON_ITEM(ecs::drawgrid_t, "tilemap");

				ImGui::EndPopup();
			}
#			undef REMOVE_COMPON
			
			ImGui::Separator();

#			define DRAW_COMPON(type, label)					\
			if (reg->any_of<type>(entity)) {				\
															\
				if (ImGui::TreeNodeEx(label, TREE_FLAGS)) {	\
															\
					auto& compon = reg->get<type>(entity);	\
					this->draw<type>(entity, &compon);		\
															\
					ImGui::TreePop();						\
				}											\
															\
			}												\
			/* DRAW_COMPON */

			DRAW_COMPON(ecs::player_t, "player");
			DRAW_COMPON(ecs::tform_t, "transform");
			DRAW_COMPON(ecs::b2body_t, "rigid body");
			DRAW_COMPON(ecs::drawrect_t, "sprite");
			DRAW_COMPON(ecs::drawgrid_t, "tilemap");

#			undef DRAW_COMPON

			return true;
		}

	}

	namespace gui {

		bool
			tool_frame_t::init()
		{
			this->frame = &gfx::engine_t::get()->fmbuffer;

			this->frame_lbot = { 0.0f, 1.0f };
			this->frame_rtop = { 1.0f, 0.0f };

			return this->show();
		}

		bool
			tool_frame_t::work()
		{
			auto gfx = gfx::engine_t::get();

			auto fmbuffer = gfx::engine_t::get()->get_fmbuffer();
			auto colorbuf_index = reinterpret_cast<ImTextureID>(fmbuffer->colorbuf.index);

			ImVec2 viewport_size = ImGui::GetContentRegionAvail();

			ImGui::Image(
				colorbuf_index, viewport_size,
				{ this->frame_lbot[0], this->frame_lbot[1]},
				{ this->frame_rtop[0], this->frame_rtop[1] }
			);
			
			if (fmbuffer->viewport[2] != viewport_size[0] || fmbuffer->viewport[3] != viewport_size[1]) {
				gfx::engine_t::get()->set_viewport(
					0, 0,
					static_cast<int>(viewport_size[0]), static_cast<int>(viewport_size[1])
				);
			}
			/*
			ImGui::Separator();
			ImGui::Text(
				"viewport=([x]=(%d)[y]=(%d)[w]=(%d)[h]=(%d))",
				0, 0,
				static_cast<int>(viewport_size[0]), static_cast<int>(viewport_size[1])
			);

			ImGui::InputFloat2("frame left bottom uv", &this->frame_lbot[0], "%.3f");
			ImGui::InputFloat2("frame right top uv", &this->frame_rtop[0], "%.3f");
			*/

			return true;
		}

		bool
			tool_frame_t::quit()
		{
			this->frame = nullptr;

			return true;
		}

	}

}

#endif /* GUI_TOOL_CPP */