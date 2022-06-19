#ifndef GUI_ENGINE_CPP

#	define GUI_ENGINE_CPP

#	include "../gfx/gfx_engine.hpp"

#	include "../sys/sys_engine.hpp"
#	include "../sys/sys_window.hpp"

#	include "gui_engine.hpp"

#	include "../../lib/glfw/src/glfw3.h"

#	include "../../lib/imgui/src/imgui.h"
#	include "../../lib/imgui/src/imgui_impl_glfw.h"
#	include "../../lib/imgui/src/imgui_impl_opengl3.h"

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

			this->set_flag(true);

			return true;
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
				
				ImVec2 viewport_size = ImGui::GetContentRegionAvail();
				ImGui::Image(reinterpret_cast<ImTextureID>(1u), viewport_size);
				gfx::engine_t::get()->set_viewport(0, 0, static_cast<int>(viewport_size[0]), static_cast<int>(viewport_size[1]));
			
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