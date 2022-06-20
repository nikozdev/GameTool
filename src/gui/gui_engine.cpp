#ifndef GUI_ENGINE_CPP

#	define GUI_ENGINE_CPP

#	include "gui_engine.hpp"

#	include "../app/app_engine.hpp"

#	include "../gfx/gfx_engine.hpp"
#	include "../sys/sys_engine.hpp"
#	include "../sys/sys_window.hpp"

#	include "../ecs/ecs_engine.hpp"
#	include "../ecs/ecs_compon.hpp"

#	include "../../lib/glfw/src/glfw3.h"

#	include "../../lib/imgui/src/imgui.h"
#	include "../../lib/imgui/src/imgui_impl_glfw.h"
#	include "../../lib/imgui/src/imgui_impl_opengl3.h"

#	define IMGUI_TREE_FLAGS (				\
		ImGuiTreeNodeFlags_Selected |		\
		ImGuiTreeNodeFlags_OpenOnArrow |	\
		ImGuiTreeNodeFlags_OpenOnDoubleClick\
) /* IMGUI_TREE_FLAGS */

namespace gt {

	namespace gui {

		bool
			engine_t::init()
		{

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			auto imgui_style = &ImGui::GetStyle();
			auto imgui_iodata = &ImGui::GetIO();
			auto imgui_contex = ImGui::GetCurrentContext();

			imgui_iodata->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			imgui_iodata->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			imgui_iodata->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

			ImGui::StyleColorsDark();

			if (imgui_iodata->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				
				imgui_style->WindowRounding = 0.0f;
				imgui_style->Colors[ImGuiCol_WindowBg].w = 1.0f;
			
			}

			GT_CHECK(::ImGui_ImplOpenGL3_Init("#version 430"), "failed imgui opengl backend init!", return false);
			
			this->window = sys::engine_t::get()->get_window()->get_handle();
			GT_CHECK(this->window != nullptr, "cannot get system window handle!", return false);
			auto glfw_window = reinterpret_cast<GLFWwindow*>(this->window);
			
			GT_CHECK(::ImGui_ImplGlfw_InitForOpenGL(glfw_window, true), "failed imgui opengl backend init!", return false);

			return this->play();
		}
		bool
			engine_t::work()
		{
			GT_CHECK(this->open_frame(), "cannot open the frame!", return false);

			if (ImGui::BeginMenuBar()) {

				if (ImGui::BeginMenu("File")) {

					if (ImGui::MenuItem("init...", "Ctrl+N")) {
					}
					if (ImGui::MenuItem("save...", "Ctrl+S")) {
					}
					if (ImGui::MenuItem("load...", "Ctrl+L")) {
					}
					ImGui::EndMenu();
				}
				else if (ImGui::BeginMenu("view")) {

					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			if (ImGui::Begin("frame")) {
				
				auto fmbuffer = gfx::engine_t::get()->get_fmbuffer();
				ImVec2 viewport_size = ImGui::GetContentRegionAvail();

				ImGui::Image(reinterpret_cast<ImTextureID>(fmbuffer->colorbuf.index), viewport_size, {0.0f,1.0f}, {1.0f,0.0f});
				if (fmbuffer->viewport[2] != viewport_size[0] || fmbuffer->viewport[3] != viewport_size[1]) {
					gfx::engine_t::get()->set_viewport(0, 0, static_cast<int>(viewport_size[0]), static_cast<int>(viewport_size[1]));
				}
			
			}
			ImGui::End();

			if (ImGui::Begin("app")) {

			}
			ImGui::End();
			if (ImGui::Begin("sys")) {

			}
			ImGui::End();
			if (ImGui::Begin("gfx")) {

				auto gfx = gfx::engine_t::get();
				
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
				ImGui::Separator();
				
				static gfx::rect_t srect;
				gfx::rect_t drect = srect;

				ImGui::Text("rectangle");
				if (ImGui::SliderFloat2("vtx_coord", &drect.vtx_coord[0], -1.0f, +1.0f, "%.3f")) { srect.vtx_coord = drect.vtx_coord; }
				if (ImGui::SliderFloat2("vtx_pivot", &drect.vtx_pivot[0], -1.0f, +1.0f, "%.3f")) { srect.vtx_pivot = drect.vtx_pivot; }
				if (ImGui::SliderFloat2("vtx_scale", &drect.vtx_scale[0], 0.1f, 1.0f, "%.3f")) { srect.vtx_scale = drect.vtx_scale; }
				if (ImGui::SliderFloat4("tex_color", &drect.tex_color[0], 0.0f, 1.0f, "%.3f")) { srect.tex_color = drect.tex_color; }
				if (ImGui::SliderFloat4("tex_coord", &drect.tex_coord[0], 0.0f, 1.0f, "%.3f")) { srect.tex_coord = drect.tex_coord; }

				gfx->add_for_draw(srect);
				
				ImGui::Separator();

			}
			ImGui::End();
			if (ImGui::Begin("ecs")) {

				auto ecs = ecs::engine_t::get();
				auto reg = &ecs->reg;

				if (ImGui::BeginPopupContextWindow("actions", ImGuiMouseButton_Right, false)) {

					if (ImGui::MenuItem("create entity")) {

						entt::entity entity_to_create = { };
						GT_CHECK(ecs->create_entity(&entity_to_create), "failed entity creation from gui!", return false);

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
						if (ImGui::MenuItem("create component")) { }
						if (ImGui::MenuItem("remove component")) { }

						ImGui::EndPopup();
					}

					if (reg->valid(entity_to_remove)) {
						ecs->remove_entity(&entity_to_remove);
					}

				}

			}
			ImGui::End();

			GT_CHECK(this->shut_frame(), "cannot shut the frame!", return false);

			return true;
		}
		bool
			engine_t::quit()
		{

			::ImGui_ImplOpenGL3_Shutdown();
			::ImGui_ImplGlfw_Shutdown();
			::ImGui::DestroyContext();

			return true;
		}

		bool
			engine_t::proc(lib::event_a_t* event)
		{
			return true;
		}

		bool
			engine_t::open_frame()
		{
			GT_CHECK(frame_flag == false, "cannot open the frame!", return false);
			this->frame_flag = true;

			auto imgui_contex = ImGui::GetCurrentContext();
			auto imgui_iodata = &ImGui::GetIO();
			auto imgui_style = &ImGui::GetStyle();

			::ImGui_ImplOpenGL3_NewFrame();
			::ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// Note: Switch this to true to enable dockspace
			static bool dockspace_shown = true;
			static bool full_screen_keep = true;

			bool full_screen = full_screen_keep;

			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

			if (full_screen) {
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

				window_flags |= ImGuiWindowFlags_NoTitleBar;
				window_flags |= ImGuiWindowFlags_NoCollapse;
				window_flags |= ImGuiWindowFlags_NoResize;
				window_flags |= ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

			ImGui::Begin("dockspace", &dockspace_shown, window_flags);
			auto dockspace_index = ImGui::GetID("dockspace");

			ImGui::PopStyleVar();

			if (full_screen) { ImGui::PopStyleVar(2); }

			/* dockspace setup */

			float min_size_w = imgui_style->WindowMinSize.x;

			imgui_style->WindowMinSize.x = 100.0f;
			imgui_style->Alpha = 1.0f;

			if (imgui_iodata->ConfigFlags & ImGuiConfigFlags_DockingEnable) {

				ImGui::DockSpace(dockspace_index, ImVec2(0.0f, 0.0f), dockspace_flags);

			}

			imgui_style->WindowMinSize.x = min_size_w;

			return true;
		}
		bool
			engine_t::shut_frame()
		{
			GT_CHECK(frame_flag == true, "cannot shut the frame!", return false);
			this->frame_flag = false;

			auto imgui_style = &ImGui::GetStyle();
			auto imgui_iodata = &ImGui::GetIO();
			auto imgui_contex = ImGui::GetCurrentContext();

			ImGui::End();

			ImGui::Render();
			::ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			ImGui::EndFrame();

			if (imgui_iodata->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {

				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();

				::glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(this->window));

			}

			return true;
		}

	}

}

#endif /* GUI_ENGINE_CPP */