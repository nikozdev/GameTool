#ifndef GAMETOOL_CPP

#   define GAMETOOL_CPP

#   include "gametool.hpp"

#   ifdef GT_BUILD_EXE

int
main(int argc, const char** argv)
{
    gt::lib::fpath_t fpath(argv[0]);
    fpath = fpath.parent_path();
    std::filesystem::current_path(fpath);

    gt::app::engine_t* engine = gt::app::engine_t::get();
    engine->exec();
    
    return GT_ERROR_NONE;
}

#   endif /* GT_BUILD_EXE */

#endif /* GAMETOOL_CPP */