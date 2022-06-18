#ifndef LIB_TIME_HPP

#	define LIB_TIME_HPP

#	include "../cfg.hpp"

#	include "chrono"

namespace gt {

	namespace lib {

		constexpr const double clocks_per_sec = static_cast<double>(CLOCKS_PER_SEC);

		class timer_t {

		public:

			using clock_t = std::chrono::high_resolution_clock;

		public:

			inline const double
				get_delta(double scale = 1.0) const
			{
				return this->delta * scale;
			}

			inline const double
				get_start(double scale = 1.0) const
			{
				return this->start * scale;
			}
			inline const double
				get_sewas(double scale = 1.0) const
			{
				return this->sewas * scale;
			}
			inline const double
				get_senow(double scale = 1.0) const
			{
				return this->senow * scale;
			}

			inline const double
				get_speed() const
			{
				return this->speed;
			}

			inline bool
				set_speed(double speed = 1.0)
			{
				this->speed = speed;
				
				return true;
			}

		public:

			inline bool
				init()
			{
				delta = 0.0;
				
				start = static_cast<double>(::clock()) / clocks_per_sec;
				
				sewas = start;
				senow = start;

				tpwas = clock_t::now();
				tpnow = clock_t::now();
				
				speed = 1.0;
				
				return true;
			}
			inline bool
				work()
			{
				delta = std::chrono::duration<double>(tpnow - tpwas).count() * speed;
				tpwas = tpnow;
				tpnow = clock_t::now();

				sewas = senow;
				senow = senow + delta;
				
				return true;
			}
			inline bool
				quit()
			{
				speed = 1.0;

				return true;
			}

		private:

			double delta;
			
			double start;

			double sewas;
			double senow;
			std::chrono::time_point<clock_t> tpwas;
			std::chrono::time_point<clock_t> tpnow;

			double speed;

		};
		
	}

}

#endif /* LIB_TIME_HPP */