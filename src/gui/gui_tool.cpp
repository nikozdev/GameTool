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

#	define IMGUI_TREE_FLAGS (				\
		ImGuiTreeNodeFlags_Selected |		\
		ImGuiTreeNodeFlags_OpenOnArrow |	\
		ImGuiTreeNodeFlags_OpenOnDoubleClick\
) /* IMGUI_TREE_FLAGS */

namespace gt {

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

			return this->show();;
		}

		bool
			tool_gfx_t::work()
		{
			auto state = gfx->get_state();

			auto viewport = state->viewport;
			ImGui::Text("[viewport]=([x]%.3f[y]%.3f[w]%.3f[h]%.3f)", viewport[0], viewport[1], viewport[2], viewport[3]);
			auto clearcol = state->clearcol;
			ImGui::Text("[clearcol]=([r]%.3f[g]%.3f[b]%.3f[a]%.3f)", clearcol[0], clearcol[1], clearcol[2], clearcol[3]);

			auto fmbuffer = gfx->get_fmbuffer();

			static v1f_t point_size = 1.0f;
			if (ImGui::SliderFloat("point_size", &point_size, 0.1f, 50.0f, "%.3f")) { gfx->set_point_size(point_size); }
			static v1f_t lines_size = 1.0f;
			if (ImGui::SliderFloat("lines_size", &lines_size, 0.1f, 50.0f, "%.3f")) { gfx->set_lines_size(lines_size); }

			ImGui::Text("facemode");
			if (ImGui::Button("fill")) { gfx->set_facemode(gfx::FACEMODE_FILL); }
			if (ImGui::Button("line")) { gfx->set_facemode(gfx::FACEMODE_LINE); }

			ImGui::Separator();

			auto ginfo = gfx->get_ginfo();
			ImGui::Text("performance");

			ImGui::Text("[draw call count]=(%u)", ginfo->drawcall.count);

			ImGui::Text("[rectangle count]=(%u/%u)", ginfo->drawable.drawn_count, ginfo->drawable.store_count);

			ImGui::Text("[texture count]=(%u/%u)", ginfo->texture.taken_count, ginfo->texture.store_count);

			ImGui::Text("[vertex memory size]=(%zu)", ginfo->vbuffer.vsize);
			ImGui::Text("[vertex data memory]=(%zu/%zu)", ginfo->vbuffer.taken_bytes, ginfo->vbuffer.store_bytes);
#if false
			ImGui::Separator();

			if (ImGui::TreeNodeEx("[drawtool]", IMGUI_TREE_FLAGS)) {

				auto drawtool = gfx->get_drawtool();

				if (ImGui::TreeNodeEx("[ilayout]", IMGUI_TREE_FLAGS)) {

					auto ilayout = &drawtool->ilayout;

					if (ImGui::TreeNodeEx("[ilayout mapping]"), IMGUI_TREE_FLAGS) {

						auto mapping = &ilayout->mapping;
						ImGui::Text("[msize]=%d", mapping->msize);
						ImGui::Text("[count of elements]=%d", mapping->count);

						for (index_t index = 0; index < mapping->count; index++) {

							auto element = &mapping->mdata[index];

							ImGui::Separator();
							ImGui::Text("[start]=%d", element->start);
							ImGui::Text("[iname]=%d", element->iname);
							ImGui::Text("[sname]=%d", element->sname);
							ImGui::Text("[count]=%d", element->count);
							ImGui::Text("[msize]=%zu", element->msize);

						}

						ImGui::TreePop();
					}

					ImGui::TreePop();
				}
				if (ImGui::TreeNodeEx("[materia]"), IMGUI_TREE_FLAGS) {

					auto materia = &drawtool->materia;

					if (ImGui::TreeNodeEx("[materia mapping]"), IMGUI_TREE_FLAGS) {

						auto mapping = &materia->mapping;
						ImGui::Text("[msize]=%d", mapping->msize);
						ImGui::Text("[count of elements]=%d", mapping->count);

						for (index_t index = 0; index < mapping->count; index++) {

							auto element = &mapping->mdata[index];

							ImGui::Separator();
							ImGui::Text("[start]=%d", element->start);
							ImGui::Text("[iname]=%d", element->iname);
							ImGui::Text("[sname]=%d", element->sname);
							ImGui::Text("[count]=%d", element->count);
							ImGui::Text("[msize]=%zu", element->msize);

						}

						ImGui::TreePop();
					}

					ImGui::TreePop();
				}

				ImGui::TreePop();
			}

#endif // false

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

			return this->show();
		}

		bool
			tool_ecs_t::work()
		{
			auto reg = &this->ecs->reg;

			if (ImGui::BeginPopupContextWindow("actions", ImGuiMouseButton_Right, false)) {

				if (ImGui::MenuItem("create entity")) {

					entt::entity entity_to_create = { };
					GT_CHECK(ecs->create_entity(&entity_to_create), "failed entity creation!", return false);

				}

				ImGui::EndPopup();
			}

			entt::entity entity_to_remove = { };
			auto view = reg->view<ecs::ebase_t>();
			for (auto [entity, ebase] : view.each()) {

				if (ImGui::TreeNodeEx(&ebase.name[0], IMGUI_TREE_FLAGS)) {

					ImGui::Text("[label]=(%s)", &ebase.name[0]);
					ImGui::Text("[index]=(%d)", entity);

					ImGui::TreePop();
				}
				if (ImGui::BeginPopupContextItem(&ebase.name[0])) {

					if (ImGui::MenuItem("remove")) { entity_to_remove = entity; }
					if (ImGui::MenuItem("create component")) {}
					if (ImGui::MenuItem("remove component")) {}

					ImGui::EndPopup();
				}

				if (reg->valid(entity_to_remove)) {
					ecs->remove_entity(&entity_to_remove);
				}

			}

			return true;
		}

		bool
			tool_ecs_t::quit()
		{
			this->ecs = nullptr;

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