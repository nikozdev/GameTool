#ifndef ECS_SYSTEM_CPP

/* configs */

#   define NC_ECS_SYSTEM_CPP

/* modules */

#   include "ecs_system.hpp"

/* typedef */


namespace nc { namespace ecs {

    /* codetor */
    
    system_t::system_t() : masters()
    {
        this->masters.insert_value(this->get_master_index<entity_t>(), &master_t<entity_t>::get());
    }
    
    system_t::~system_t()
    {
    }

    /* setters */
    
    v1bit_t system_t::setup_master(index_t index, master_a_t* master) {

        if (this->vet_master(index) == NC_FALSE) { this->masters.set_count(index + 1); }
        
        this->masters.set_value(index, master);
        NC_CHECK(this->get_master(index)->init(), "failed master init!", return NC_FALSE);
        
        return NC_TRUTH;
    }
    v1bit_t system_t::reset_master(index_t index) {

        if (this->vet_master(index) == NC_FALSE) { return NC_FALSE; }

        NC_CHECK(this->get_master(index)->quit(), "failed master quit!", return NC_FALSE);
        this->masters.set_value(index, NC_NULL);
        
        return NC_TRUTH;
    }
    
    /* actions */

    v1bit_t system_t::init() {
        
        NC_CHECK(this->vet_init() == NC_FALSE, "the system init cannot be called!", return NC_FALSE);

        for (index_t index = 0u; index < this->get_masters_count(); index++) {
            
            if (auto imaster = this->get_master(index)) {
                NC_CHECK(imaster->init(), "failed master init!", {
                    NC_EPUT("index=%d;" NC_STR_ENDL, index);
                    return NC_FALSE;
                });
            }

        }

        this->get_master<entity_t>()->insert_callback_on_setup([](index_t ivalue, index_t oindex)->v1bit_t {
            
            auto entity = master_t<entity_t>::get().get_object<entity_t>(ivalue);
            
            entity->index = ivalue;

        });

        this->get_master<entity_t>()->insert_callback_on_reset([](index_t ivalue, index_t oindex)->v1bit_t {
            
            auto entity = master_t<entity_t>::get().get_object<entity_t>(ivalue);
            
            for (auto iter = system_t::get().get_masters_head(); iter < system_t::get().get_masters_tail(); iter++) {
                if (*iter) { if ((*iter)->vet_object(ivalue)) { (*iter)->reset_object(ivalue); } }
            }

        });
        
        return NC_TRUTH;
    }

    v1bit_t system_t::work() {

        for (auto iter = get_masters_head(); iter < get_masters_tail(); iter++) {
            NC_CHECK((*iter)->work(), "failed master work!", return NC_FALSE);
        }
        
        return NC_TRUTH;
    }

    v1bit_t system_t::quit() {
        
        NC_CHECK(this->vet_quit() == NC_FALSE, "the system quit cannot be called!", return NC_FALSE);
		
        for (index_t index = 0u; index < this->get_masters_count(); index++) {

            if (auto imaster = this->get_master(index)) {
                NC_CHECK(imaster->quit(), "failed master quit!", {
                    NC_EPUT("index=%d;" NC_STR_ENDL, index);
                    return NC_FALSE;
                });
            }

        }
        this->masters.set_count(NC_ZERO);

        return NC_TRUTH;
    }

} }

#endif /* NC_ECS_SYSTEM_CPP */