#ifndef ECS_SYSTEM_HPP

#	define ECS_SYSTEM_HPP


namespace gt {
	
    using index_t	= uint64_t;

}

namespace gt { namespace ecs {

	/* entity_t: entity type;
	 * description:
	 - relying on data oriented design we use it as an index only;
	 - for our programms an entity is only a key to get a bunch of components;
	 - no logic is needed here, only use this as an index;
	*/
	struct entity_t {

		public: /* typedef */

		using this_t 	= entity_t;
		using this_c_t 	= const this_t;

		public: /* methods */

		/* codetor */
		
		inline constexpr entity_t(index_t index = 0) : index(index) {}

		inline constexpr entity_t(this_c_t& copy) : this_t(copy.index) {}
		inline constexpr entity_t(this_t&& copy) : this_t(copy.index) {}

		/* operators */
		
		/** asign **/

		inline constexpr this_t& operator=(this_c_t& copy) 	{ memcpy(this, &copy, sizeof(this_t)); return *this; }
		inline constexpr this_t& operator=(this_t&& copy) 	{ memcpy(this, &copy, sizeof(this_t)); return *this; }
		
		/** logic **/

		inline constexpr bool operator==(index_t index) const	{ return this->index == index; }
		inline constexpr bool operator==(this_c_t& copy) const	{ return this->index == copy.index; }
		
		/** tcast **/

		inline constexpr operator index_t()	const	{ return this->index; }
		
		public: /* members */

		index_t index;

	};
	using entity_c_t = const entity_t;

} }

namespace gt { namespace ecs {

	/* system_t: entity component system type;
	 * description:
	*/
	class system_t {
		
		public: /* types */

		/* this */
		
		using this_t 	= system_t;
		using this_c_t 	= const this_t;

		/* util */

		template<typename type_t>
		using array_t = std::vector<type_t>;
		
        typedef struct  iokey_t { index_t ikey, okey; };
		typedef const   iokey_t iokey_c_t;

		/* masters */

		using master_a_t 	= ::nc::lib::master_a_t;
		using master_c_a_t 	= const master_a_t;
		template<typename compon_t>
		using master_t 		= ::nc::lib::master_t<compon_t>;
		template<typename compon_t>
		using master_c_t 	= const master_t<compon_t>;

		using masters_t 	= array_t<master_a_t*>;
		using masters_c_t 	= const masters_t;
		
		public:		/* methods */

		public:		/* codetor */

		system_t();

		virtual ~system_t();

		public:		/* setters-interface */

		/* entitys */

    	inline entity_t* create_entity()			{ return get_master<entity_t>()->create_object<entity_t>(get_entitys_count()); }

		inline v1bit_t setup_entity(index_t index)	{ return get_master<entity_t>()->setup_object(index); }
		inline v1bit_t reset_entity(index_t index)	{ return get_master<entity_t>()->reset_object(index); }

		/* compons */

		template<class c_t> c_t* create_compon(entity_t* e)					{ return create_compon<c_t>(*e); }
		template<class c_t> c_t* create_compon(index_t e)					{ return get_master<c_t>()->template create_object<c_t>(e); }

		template<class c_t> v1bit_t set_compon(entity_t* e, const c_t& c)	{ return set_compon<c_t>(*e, c); }
		template<class c_t> v1bit_t set_compon(index_t e, const c_t& c)		{ return set_compon(e, get_master_index<c_t>(), &c); }

		template<class c_t> v1bit_t setup_compon(entity_t* e)				{ return setup_compon<c_t>(*e); }
		template<class c_t> v1bit_t setup_compon(index_t e)					{ return get_master<c_t>()->setup_object(e); }
		template<class c_t> v1bit_t reset_compon(entity_t* e)				{ return reset_compon<c_t>(*e); }
		template<class c_t> v1bit_t reset_compon(index_t e)					{ return get_master<c_t>()->reset_object(e); }
		
		/* masters */

		template<class c_t> master_a_t* create_master()	{ return setup_master<c_t>()?masters[get_master_index<c_t>()]:NC_NULL; }

		template<class c_t> v1bit_t setup_master()		{ return setup_master(get_master_index<c_t>(), &master_t<c_t>::get()); }
		template<class c_t> v1bit_t reset_master()		{ return reset_master(get_master_index<c_t>()); }

		private:	/* setters-internal */
		
		/* entitys */

		/* compons */

		inline v1bit_t set_compon(index_t e, index_t c, const v1nil_t* d)	{ return get_master(c)->set_object(e, d); }

		inline v1bit_t setup_compon(index_t e, index_t c)					{ return get_master(c)->setup_object(e); }
		inline v1bit_t reset_compon(index_t e, index_t c)					{ return get_master(c)->reset_object(e); }

		/* masters */

		v1bit_t setup_master(index_t index, master_a_t* master);
		v1bit_t reset_master(index_t index);

		public: 	/* getters-interface */

		/* entitys */

		inline count_t get_entitys_count() const		{ return get_master<entity_t>()->get_objects_count(); }
		inline count_t get_entitys_space() const		{ return get_master<entity_t>()->get_objects_space(); }

		inline entity_t* get_entitys_iter(index_t i)	{ return get_master<entity_t>()->get_objects_iter<entity_t>(i); }
		inline entity_t* get_entitys_head()				{ return get_master<entity_t>()->get_objects_head<entity_t>(); }
		inline entity_t* get_entitys_back()				{ return get_master<entity_t>()->get_objects_back<entity_t>(); }
		inline entity_t* get_entitys_tail()				{ return get_master<entity_t>()->get_objects_tail<entity_t>(); }
		
		inline entity_t* get_entity(index_t i)			{ return get_master<entity_t>()->get_object<entity_t>(i); }
		
		/* compons */

		template<class c_t> c_t* get_compon(entity_t* e)		{ return get_compon<c_t>(*e); }
		template<class c_t> c_t* get_compon(index_t e)			{ return get_master<c_t>()->template get_object<c_t>(e); }

		template<class c_t> c_t* get_compons_iter(entity_t* e)	{ return get_compons_iter<c_t>(*e); }
		template<class c_t> c_t* get_compons_iter(index_t e) 	{ return get_master<c_t>()->template get_objects_iter<c_t>(e); }
		template<class c_t> c_t* get_compons_head()				{ return get_master<c_t>()->template get_objects_head<c_t>(); }
		template<class c_t> c_t* get_compons_back()				{ return get_master<c_t>()->template get_objects_back<c_t>(); }
		template<class c_t> c_t* get_compons_tail()				{ return get_master<c_t>()->template get_objects_tail<c_t>(); }

		/* masters */
		
		inline masters_t& get_masters()							{ return masters; }
		inline masters_c_t& get_masters() const					{ return masters; }
		inline count_t get_masters_count() const				{ return masters.get_count(); }
		inline count_t get_masters_space() const				{ return masters.get_space(); }

		inline master_a_t* get_master(index_t i)				{ return vet_master(i) ? masters[i] : NC_NULL; }
		inline master_c_a_t* get_master(index_t i) const		{ return vet_master(i) ? masters[i] : NC_NULL; }
		template<class c_t> master_a_t* get_master()			{ return vet_master<c_t>()?masters[get_master_index<c_t>()]:create_master<c_t>(); }
		template<class c_t> master_c_a_t* get_master() const	{ return vet_master<c_t>()?masters[get_master_index<c_t>()]:NC_NULL; }
		
		inline master_a_t** get_masters_iter(index_t i)			{ return masters.get_iter(i); }
		inline master_a_t** get_masters_head()					{ return masters.get_iter(1u); }
		inline master_a_t** get_masters_back()					{ return masters.get_back(); }
		inline master_a_t** get_masters_tail()					{ return masters.get_tail(); }
		
		/* masters */

		template<class c_t> index_t* get_itable_iter(index_t i)	{ return get_master<c_t>()->get_itable_iter(i); }
		template<class c_t> index_t* get_itable_head()			{ return get_master<c_t>()->get_itable_head(); }
		template<class c_t> index_t* get_itable_back()			{ return get_master<c_t>()->get_itable_back(); }
		template<class c_t> index_t* get_itable_tail()			{ return get_master<c_t>()->get_itable_tail(); }

		private:	/* getters-internal */

		/* masters */

		template<class c_t> index_t get_master_index() const	{ static index_t i(get_master_index()++); return i; }
		inline index_t& get_master_index() const				{ static index_t i(NC_ZERO); return i; }

		public:		/* vetters */

		/* this */

		virtual v1bit_t vet_init() const override 	{ return get_entitys_count() != NC_ZERO; }
        virtual v1bit_t vet_quit() const override	{ return get_entitys_count() == NC_ZERO; }
		
		/* entitys */

		inline v1bit_t vet_entity(index_t e) const			{ return get_master<entity_t>()->vet_object(e); }

		inline v1bit_t vet_entitys_count() const			{ return get_master<entity_t>()->vet_objects_count(); }
		inline v1bit_t vet_entitys_count(count_t c) const	{ return get_master<entity_t>()->vet_objects_count(c); }
		inline v1bit_t has_entitys_count(count_t c) const	{ return get_master<entity_t>()->has_objects_count(c); }

		inline v1bit_t vet_entitys_space() const			{ return get_master<entity_t>()->vet_objects_space(); }
		inline v1bit_t vet_entitys_space(count_t s) const	{ return get_master<entity_t>()->vet_objects_space(s); }
		inline v1bit_t has_entitys_space(count_t s) const	{ return get_master<entity_t>()->has_objects_space(s); }

		/* compons */
		
		template<class c_t> v1bit_t vet_compon(entity_t* e) const	{ return get_master<c_t>()->vet_object(*e); }
		template<class c_t> v1bit_t vet_compon(index_t e) const		{ return get_master<c_t>()->vet_object(e); }

		/* masters */

		template<class c_t> v1bit_t vet_master() const		{ return vet_master(get_master_index<c_t>()); }
		inline v1bit_t vet_master(index_t i) const			{ return masters.vet_value(i)?(masters[i]!=NC_NULL):NC_FALSE; }		

		inline v1bit_t vet_masters_count() const			{ return masters.vet_count(); }
		inline v1bit_t vet_masters_count(count_t c) const	{ return masters.vet_count(c); }
		inline v1bit_t has_masters_count(count_t c) const	{ return masters.has_count(c); }
		
		inline v1bit_t vet_masters_space() const			{ return masters.vet_space(); }
		inline v1bit_t vet_masters_space(count_t s) const	{ return masters.vet_space(s); }
		inline v1bit_t has_masters_space(count_t s) const	{ return masters.has_space(s); }

		public: /* actions */

		virtual v1bit_t init() override;
		virtual v1bit_t work() override;
		virtual v1bit_t quit() override;

		private: /* members */

		masters_t masters;

	};

} }

#endif	/* NC_ECS_SYSTEM_HPP */