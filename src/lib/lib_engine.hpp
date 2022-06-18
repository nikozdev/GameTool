#ifndef LIB_ENGINE_HPP

#	define LIB_ENGINE_HPP

#   include "../cfg.hpp"

#   include "lib_event.hpp"

#   include "lib_single.hpp"

namespace gt {

    namespace lib {

        class engine_a_t {

        public:

            using this_t = engine_a_t;

            using flag_t = bool;

        protected:

            inline flag_t
                set_flag(flag_t flag)
            {
                this->flag = flag;
                return this->flag;
            }

        public:

            inline flag_t
                get_flag() const
            {
                return this->flag;
            }

        public:

            inline bool
                exec()
            {
                this->flag = true;

                GT_CHECK(this->init(), "engine init error!", return false);
                while (this->flag) { GT_CHECK(this->work(), "engine work error!", break); }
                GT_CHECK(this->quit(), "engine quit error!", return false);

                return true;
            }
            inline bool
                stop()
            {
                GT_CHECK(this->flag == true, "engine cannot stop!", return false);

                this->flag = false;

                return true;
            }

        public:

            virtual bool
                init() = 0;
            virtual bool
                work() = 0;
            virtual bool
                quit() = 0;

            virtual bool
                proc(event_a_t* event) = 0;

        private:

            flag_t flag;

        };

        template<typename type_t>
        class engine_t_t : public single_t_t<type_t>, public engine_a_t {};

    }

}

#endif /* LIB_ENGINE_HPP */