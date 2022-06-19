#ifndef FSX_ENGINE_HPP

#   define FSX_ENGINE_HPP

#   include "../cfg.hpp"

#   include "fsx_lib.hpp"

#   include "../lib/lib_event.hpp"

#   include "../lib/lib_engine.hpp"

namespace gt {

    namespace fsx {

        class engine_t : public lib::engine_t_t<engine_t> {

        public:

            using this_t = engine_t;
            using base_t = lib::engine_t_t<this_t>;

        public:

            virtual bool
                init() override;
            virtual bool
                work() override;
            virtual bool
                quit() override;

            virtual bool
                proc(lib::event_a_t* event) override;
            
        private:

        };

    }

}

#endif /* FSX_ENGINE_HPP */