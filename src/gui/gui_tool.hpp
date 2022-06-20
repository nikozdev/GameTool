#ifndef GUI_TOOL_HPP

#	define GUI_TOOL_HPP

#	include "../cfg.hpp"

#	include "../lib/lib_vector.hpp"

namespace gt {

	namespace app { class engine_t; }
	namespace sys { class engine_t; }
	namespace gfx { class engine_t; typedef struct fmbuffer_t fmbuffer_t; }
	namespace fsx { class engine_t; }
	namespace ecs { class engine_t; }

	namespace gui {

		class tool_a_t {
		
		public:

			using this_t = tool_a_t;

			friend class engine_t;

		public:

			tool_a_t(const char* name) :
				name(name), flag(false)
			{
			}

			virtual bool
				init() = 0;
			virtual bool
				work() = 0;
			virtual bool
				quit() = 0;

			inline bool
				show()
			{
				this->flag = true;
				return true;
			}
			inline bool
				hide()
			{
				this->flag = false;
				return true;
			}

		private:

			bool flag;
			const char* name;

		};

		template<typename type_t>
		class tool_t_t : public tool_a_t {
		
		public:

			using this_t = tool_t_t<type_t>;
			using base_t = tool_a_t;

		public:

			tool_t_t(const char* name) : tool_a_t(name) {}
		
			virtual bool
				init() = 0;
			virtual bool
				work() = 0;
			virtual bool
				quit() = 0;

		};

	}

	namespace gui {

		class tool_app_t : public tool_t_t<tool_app_t> {
		
		public:

			using this_t = tool_app_t;
			using base_t = tool_t_t<this_t>;

		public:

			tool_app_t() : base_t("app"), app(nullptr) {}

			virtual bool
				init() override;
			virtual bool
				work() override;
			virtual bool
				quit() override;

		private:

			app::engine_t* app;

		};

		class tool_sys_t : public tool_t_t<tool_sys_t> {

		public:

			using this_t = tool_sys_t;
			using base_t = tool_t_t<this_t>;

		public:

			tool_sys_t() : base_t("sys"), sys(nullptr) {}

			virtual bool
				init() override;
			virtual bool
				work() override;
			virtual bool
				quit() override;

		private:

			sys::engine_t* sys;

		};

		class tool_gfx_t : public tool_t_t<tool_gfx_t> {

		public:

			using this_t = tool_gfx_t;
			using base_t = tool_t_t<this_t>;

		public:

			tool_gfx_t() : base_t("gfx") {}

			virtual bool
				init() override;
			virtual bool
				work() override;
			virtual bool
				quit() override;

		private:

			gfx::engine_t* gfx;

		};

		class tool_fsx_t : public tool_t_t<tool_fsx_t> {

		public:

			using this_t = tool_fsx_t;
			using base_t = tool_t_t<this_t>;

		public:

			tool_fsx_t() : base_t("fsx") {}

			virtual bool
				init() override;
			virtual bool
				work() override;
			virtual bool
				quit() override;

		private:

			fsx::engine_t* fsx;

		};

		class tool_ecs_t : public tool_t_t<tool_ecs_t> {

		public:

			using this_t = tool_ecs_t;
			using base_t = tool_t_t<this_t>;

		public:

			tool_ecs_t() : base_t("ecs") {}

			virtual bool
				init() override;
			virtual bool
				work() override;
			virtual bool
				quit() override;

		private:
			/*
			inline bool
				draw(const ecs::entity_t& entity);
			template<typename type_t> inline bool
				draw(const ecs::entity_t& entity);
			*/
		private:

			ecs::engine_t* ecs;

		};

	}

	namespace gui {

		class tool_frame_t : public tool_t_t<tool_frame_t> {

		public:

			using this_t = tool_frame_t;
			using base_t = tool_t_t<this_t>;

		public:

			tool_frame_t() : base_t("frame") {}

			virtual bool
				init() override;
			virtual bool
				work() override;
			virtual bool
				quit() override;

		private:

			gfx::fmbuffer_t* frame;

			v2f_t frame_rtop;
			v2f_t frame_lbot;

		};

	}

}

#endif /* GUI_TOOL_HPP */