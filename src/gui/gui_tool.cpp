#ifndef GUI_TOOL_CPP

#	define GUI_TOOL_CPP

#	include "gui_tool.hpp"
#	include "gui_engine.hpp"

#	include "../app/app_engine.hpp"
#	include "../sys/sys_engine.hpp"
#	include "../gfx/gfx_engine.hpp"
#	include "../fsx/fsx_engine.hpp"
#	include "../ecs/ecs_engine.hpp"

#	include "../../lib/imgui/src/imgui.h"

#	define TREE_FLAGS (						\
		ImGuiTreeNodeFlags_Selected |		\
		ImGuiTreeNodeFlags_Framed |			\
		ImGuiTreeNodeFlags_OpenOnArrow |	\
		ImGuiTreeNodeFlags_OpenOnDoubleClick\
) /* TREE_FLAGS */
#	define TEXT_INPUT_FLAGS					\
	ImGuiInputTextFlags_AutoSelectAll |		\
	ImGuiInputTextFlags_EnterReturnsTrue	\
/* TEXT_INPUT_FLAGS */
#	define PIVOT_TEXT "pivot"
#	define PIVOT_FROM -1.0f
#	define PIVOT_UPTO +1.0f

#	define COORD_TEXT "coord"
#	define COORD_FROM -100.0f
#	define COORD_UPTO +100.0f

#	define SCALE_TEXT "scale"
#	define SCALE_FROM 0.001f
#	define SCALE_UPTO 100.0f

#	define COLOR_TEXT "color"
#	define COLOR_FROM 0.0f
#	define COLOR_UPTO 1.0f

#	define ROTAT_TEXT "rotat"
#	define ROTAT_FROM 0.000f
#	define ROTAT_UPTO 360.0f

#	define INDEX_TEXT "index"
#	define INDEX_FROM 0
#	define INDEX_UPTO GT_GFX_TEXTURE_COUNT_USE

namespace gt {

	namespace gui {

		inline bool
			input_slide_v1f(const char* text, v1f_t* data, v1f_t from, v1f_t upto)
		{
			if (ImGui::SliderFloat(text, data, from, upto, "%.2f")) { return true;  }
			/*
			ImGui::PushID(data);
			if (ImGui::InputFloat(text, data, 1.0f, 0.0f, "%.2f")) {
				data[0] = data[0] <= from ? from : data[0] >= upto ? upto : data[0];
				return true;
			}
			ImGui::PopID();
			*/
			return false;
		}
		inline bool
			input_slide_v2f(const char* text, v1f_t* data, v1f_t from, v1f_t upto)
		{
			if (ImGui::SliderFloat2(text, data, from, upto, "%.2f")) { return true; }
			/*
			ImGui::PushID(data);
			if (ImGui::InputFloat2(text, data, "%.2f")) {
				data[0] = data[0] <= from ? from : data[0] >= upto ? upto : data[0];
				data[1] = data[1] <= from ? from : data[1] >= upto ? upto : data[1];
				return true;
			}
			ImGui::PopID();
			*/
			return false;
		}
		inline bool
			input_slide_v3f(const char* text, v1f_t* data, v1f_t from, v1f_t upto)
		{
			if (ImGui::SliderFloat3(text, data, from, upto, "%.2f")) { return true; }
			/*
			ImGui::PushID(data);
			if (ImGui::InputFloat3(text, data, "%d")) {
				data[0] = data[0] <= from ? from : data[0] >= upto ? upto : data[0];
				data[1] = data[1] <= from ? from : data[1] >= upto ? upto : data[1];
				data[2] = data[2] <= from ? from : data[2] >= upto ? upto : data[2];
				return true;
			}
			ImGui::PopID();
			*/
			return false;
		}
		inline bool
			input_slide_v4f(const char* text, v1f_t* data, v1f_t from, v1f_t upto)
		{
			if (ImGui::SliderFloat4(text, data, from, upto, "%.2f")) { return true; }
			/*
			ImGui::PushID(data);
			if (ImGui::InputFloat4(text, data, "%d")) {
				data[0] = data[0] <= from ? from : data[0] >= upto ? upto : data[0];
				data[1] = data[1] <= from ? from : data[1] >= upto ? upto : data[1];
				data[2] = data[2] <= from ? from : data[2] >= upto ? upto : data[2];
				data[3] = data[3] <= from ? from : data[3] >= upto ? upto : data[3];
				return true;
			}
			ImGui::PopID();
			*/
			return false;
		}

		inline bool
			input_slide_v1s(const char* text, v1s_t* data, v1s_t from, v1s_t upto)
		{
			if (ImGui::SliderInt(text, data, from, upto, "%d")) { return true; }
			/*
			ImGui::PushID(data);
			if (ImGui::InputInt(text, data, 0.1f, TEXT_INPUT_FLAGS)) {
				data[0] = data[0] <= from ? from : data[0] >= upto ? upto : data[0];
				return true;
			}
			ImGui::PopID();
			*/
			return false;
		}
		inline bool
			input_slide_v2s(const char* text, v1s_t* data, v1s_t from, v1s_t upto)
		{
			if (ImGui::SliderInt2(text, data, from, upto, "%d")) { return true; }
			/*
			ImGui::PushID(data);
			if (ImGui::InputInt2(text, data, TEXT_INPUT_FLAGS)) {
				data[0] = data[0] <= from ? from : data[0] >= upto ? upto : data[0];
				data[1] = data[1] <= from ? from : data[1] >= upto ? upto : data[1];
				return true;
			}
			ImGui::PopID();
			*/
			return false;
		}
		inline bool
			input_slide_v3s(const char* text, v1s_t* data, v1s_t from, v1s_t upto)
		{
			if (ImGui::SliderInt3(text, data, from, upto, "%d")) { return true; }
			/*
			ImGui::PushID(data);
			if (ImGui::InputInt3(text, data, TEXT_INPUT_FLAGS)) {
				data[0] = data[0] <= from ? from : data[0] >= upto ? upto : data[0];
				data[1] = data[1] <= from ? from : data[1] >= upto ? upto : data[1];
				data[2] = data[2] <= from ? from : data[2] >= upto ? upto : data[2];
				return true;
			}
			ImGui::PopID();
			*/
			return false;
		}
		inline bool
			input_slide_v4s(const char* text, v1s_t* data, v1s_t from, v1s_t upto)
		{
			if (ImGui::SliderInt4(text, data, from, upto, "%d")) { return true; }
			/*
			ImGui::PushID(data);
			if (ImGui::InputInt4(text, data, TEXT_INPUT_FLAGS)) {
				data[0] = data[0] <= from ? from : data[0] >= upto ? upto : data[0];
				data[1] = data[1] <= from ? from : data[1] >= upto ? upto : data[1];
				data[2] = data[2] <= from ? from : data[2] >= upto ? upto : data[2];
				data[3] = data[3] <= from ? from : data[3] >= upto ? upto : data[3];
				return true;
			}
			ImGui::PopID();
			*/
			return false;
		}


	}

	namespace gui {

		bool
			tool_app_t::init()
		{
			this->app = app::engine_t::get();

			return this->hide();
		}

		bool
			tool_app_t::work()
		{
			return true;
		}

		bool
			tool_app_t::quit()
		{
			this->app = nullptr;

			return true;
		}

	}

	namespace gui {
		
		bool
			tool_sys_t::init()
		{
			this->sys = sys::engine_t::get();

			return this->hide();
		}

		bool
			tool_sys_t::work()
		{
			return true;
		}

		bool
			tool_sys_t::quit()
		{
			this->sys = nullptr;

			return true;
		}

	}

	namespace gui {

		bool
			tool_gfx_t::init()
		{
			this->gfx = gfx::engine_t::get();
			
			this->grid_flag = false;

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

				input_slide_v2f(COORD_TEXT, &camera->coord[0], COORD_FROM, COORD_UPTO);
				input_slide_v1f(ROTAT_TEXT, &camera->rotat, ROTAT_FROM, ROTAT_UPTO);
				input_slide_v1f(SCALE_TEXT, &camera->scale, SCALE_FROM, SCALE_UPTO);

				ImGui::Text("ratio=(%dw/h)", &camera->ratio);
				
				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("drawtool", TREE_FLAGS)) {

				auto drawtool = gfx->get_drawtool();

				if (ImGui::TreeNodeEx("input layout", TREE_FLAGS)) {

					auto ilayout = &drawtool->ilayout;

					if (ImGui::TreeNodeEx("input layout mapping", TREE_FLAGS)) {

						auto mapping = &ilayout->mapping;
						ImGui::Text("memory size=%d", mapping->msize);
						ImGui::Text("count of elements=%d", mapping->count);

						for (index_t index = 0; index < mapping->count; index++) {

							auto element = &mapping->mdata[index];
							if (ImGui::TreeNodeEx(element->sname.sdata, TREE_FLAGS) == false) { continue; }
							ImGui::Text("index name=%d", element->iname);
							ImGui::Text("string name=%s", element->sname.sdata);
							ImGui::Text("count=%d", element->count);
							ImGui::Text("memory size=%zu", element->msize);
							ImGui::Text("memory offset=%d", element->start);
							ImGui::Text("memory alignment=%zu", element->malig);

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

						for (index_t index = 0; index < binding->count; index++) {
							
							char buffer[GT_GFX_TEXTURE_COUNT_MAX] = { '\0' };
							::itoa(index + 1, buffer, 10);

							auto texture = &binding->texture_array[index];
							if (ImGui::TreeNodeEx(buffer, TREE_FLAGS) == false) { continue; }
							ImGui::Text("index=(%d)", texture->index);
							ImGui::Text("sizes=(%dx%dy)", texture->sizes[0], texture->sizes[1]);
							ImGui::Text("pixel bytes=(%zu)", texture->pixel_bytes);
							ImGui::Text("memory size=(%zu)", texture->mbufr.msize);
							
							if (ImGui::ImageButton(
								reinterpret_cast<ImTextureID>(texture->index), {
									static_cast<float>(texture->sizes[0]),
									static_cast<float>(texture->sizes[1])
							})) {
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
				
				ImGui::Text("index=(%d)", fmbuffer->index);

				auto viewport = fmbuffer->viewport;
				ImGui::Text("viewport=([x]%d[y]%d[w]%d[h]%d)", viewport[0], viewport[1], viewport[2], viewport[3]);

				if (ImGui::TreeNodeEx("color attachment", TREE_FLAGS)) {
					
					auto colorbuf = &fmbuffer->colorbuf;
					
					auto index = reinterpret_cast<ImTextureID>(colorbuf->index);
					ImGui::Text("index=(%d)", colorbuf->index);
					ImGui::Image(index, { 128.0f, 128.0f });
					
					ImGui::Text("sizes=(%dx%dy)", colorbuf->sizes[0], colorbuf->sizes[1]);
					ImGui::Text("pixel bytes=(%zu)", colorbuf->pixel_bytes);
					ImGui::Text("memory size=(%zu)", colorbuf->mbufr.msize);

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

			if (ImGui::Checkbox("grid", &this->grid_flag)) {
				
				v1f_t grid_count = 10.0f;
				v2f_t grid_tiles_sizes = { 1.0f, 1.0f };
				v2f_t grid_sizes = { grid_tiles_sizes.x * grid_count, grid_tiles_sizes.y * grid_count };
				v1f_t grid_width = 0.025f;

				gfx::rect_t tile;
				tile.vtx_pivot = { 0.0f, 0.0f };
				tile.tex_color = { 0.0f, 0.0f, 0.0f, 1.0f };
				tile.tex_coord = { 0.0f, 0.0f, 1.0f, 1.0f };
				tile.tex_index = { 0 };

				tile.vtx_scale = { grid_width, grid_sizes.y };
				for (float iterx = -grid_count / 2.0f; iterx < +grid_count / 2.0f; iterx += 1.0f) {
					
					tile.vtx_coord = { iterx * grid_tiles_sizes.x, 0.0f };

					this->gfx->add_for_draw(tile);
				}
				tile.vtx_scale = { grid_sizes.x, grid_width };
				for (float itery = -grid_count / 2.0f; itery < +grid_count / 2.0f; itery += 1.0f) {
					
					tile.vtx_coord = { 0.0f, itery * grid_tiles_sizes.y };

					this->gfx->add_for_draw(tile);
				}

			}

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
			tool_fsx_t::init()
		{
			this->fsx = fsx::engine_t::get();

			return this->hide();
		}

		bool
			tool_fsx_t::work()
		{
			return true;
		}

		bool
			tool_fsx_t::quit()
		{
			this->fsx = nullptr;

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
			if (ImGui::BeginPopupContextWindow("actions", ImGuiMouseButton_Right, false)) {

				if (ImGui::MenuItem("create entity")) {

					ecs::entity_t entity_to_create = { };
					GT_CHECK(ecs->create_entity(&entity_to_create), "failed entity creation!", return false);

				}

				ImGui::EndPopup();
			}

			auto view = this->reg->view<ecs::ebase_t>();
			for (auto [entity, ebase] : view.each()) {

				if (ImGui::TreeNodeEx(&ebase.name[0], TREE_FLAGS)) {
					
					ImGui::Text("[label]=(%s)", &ebase.name[0]);
					ImGui::Text("[index]=(%d)", entity);

					GT_CHECK(this->draw(entity), "failed entity draw!", return false);
					
					if (ImGui::BeginPopupContextItem(&ebase.name[0])) {

						if (ImGui::MenuItem("remove")) { this->entity_to_remove = entity; }
						if (ImGui::MenuItem("create component")) {}
						if (ImGui::MenuItem("remove component")) {}

						ImGui::EndPopup();
					}

					ImGui::TreePop();
				}

			}

			if (reg->valid(entity_to_remove)) { return ecs->remove_entity(&entity_to_remove); }

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
			tool_ecs_t::draw<ecs::sprite_t>(const ecs::entity_t& entity)
		{
			if (reg->any_of<ecs::sprite_t>(entity) == false) { return false; }

			auto& sprite = reg->get<ecs::sprite_t>(entity);
			bool change = false;

			change |= input_slide_v2f(PIVOT_TEXT, &sprite.vtx_pivot[0], PIVOT_FROM, PIVOT_UPTO);
			change |= input_slide_v2f(COORD_TEXT, &sprite.vtx_coord[0], COORD_FROM, COORD_UPTO);
			change |= input_slide_v2f(SCALE_TEXT, &sprite.vtx_scale[0], SCALE_FROM, SCALE_UPTO);
			change |= input_slide_v2f("texture " COORD_TEXT, &sprite.tex_coord[0], COORD_FROM, COORD_UPTO);
			change |= input_slide_v4f("texture " COLOR_TEXT, &sprite.tex_color[0], COLOR_FROM, COLOR_UPTO);

			int tex_index = 0;
			if (input_slide_v1s("texture " INDEX_TEXT, &tex_index, INDEX_FROM, INDEX_UPTO)) {
				
				sprite.tex_index = static_cast<float>(tex_index);
				
				change = true;
			}
			
			return true;
		}

		inline bool
			tool_ecs_t::draw(const ecs::entity_t& entity)
		{
			this->draw<ecs::sprite_t>(entity);
			
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

			ImGui::Separator();

			ImGui::Text(
				"viewport=([x]=(%d)[y]=(%d)[w]=(%d)[h]=(%d))",
				0, 0,
				static_cast<int>(viewport_size[0]), static_cast<int>(viewport_size[1])
			);

			ImGui::InputFloat2("frame left bottom uv", &this->frame_lbot[0], "%.3f");
			ImGui::InputFloat2("frame right top uv", &this->frame_rtop[0], "%.3f");

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