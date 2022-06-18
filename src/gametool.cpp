#ifndef GAMETOOL_CPP

#   define GAMETOOL_CPP

#   include "gametool.hpp"

#   ifdef GT_BUILD_EXE

int
main(int argc, const char** argv)
{
    gt::engine_t* engine = gt::engine_t::get();
    engine->exec();
    
    return GT_ERROR_NONE;
}

#   endif /* GT_BUILD_EXE */

namespace gt {
    
    bool
    engine_t::init()
    {
        auto sys = sys::engine_t::get();
        auto gfx = gfx::engine_t::get();

        GT_CHECK(sys->init(), "sys engine init error!", return false);
        GT_CHECK(gfx->init(), "gfx engine init error!", return false);

        return true;
    }
    bool
    engine_t::work()
    {
        auto sys = sys::engine_t::get();
        auto gfx = gfx::engine_t::get();

        GT_CHECK(sys->work(), "sys engine work error!", return false);
        GT_CHECK(gfx->work(), "gfx engine work error!", return false);
        
        if (sys::engine_t::get()->get_keybod()->vet_button_press(GT_KEYBOD_BUTTON_ESCAPE)) {
            return this->stop();
        }

        this->set_flag(this->get_flag() && sys->get_flag() && gfx->get_flag());

        return true;
    }
    bool
    engine_t::quit()
    {
        auto sys = sys::engine_t::get();
        auto gfx = gfx::engine_t::get();

        GT_CHECK(gfx->quit(), "gfx engine quit error!", return false);
        GT_CHECK(sys->quit(), "sys engine quit error!", return false);

        return true;
    }

    bool
	engine_t::proc(lib::event_t* event)
    {
        return true;
    }

}

#endif /* GAMETOOL_CPP */