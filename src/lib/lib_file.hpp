#ifndef LIB_FILE_HPP

#	define LIB_FILE_HPP

#	include "../cfg.hpp"

#	include "fstream"
#	include "iostream"
#	include "filesystem"

namespace gt {

	namespace lib {

		using fpath_t = std::filesystem::path;

		using fdata_t = void*;
		using fsize_t = msize_t;

		template<typename ftype_t> inline bool
			save_bin(const fpath_t& fpath, const ftype_t* fdata, fsize_t fsize)
		{
			GT_CHECK(fdata != nullptr && fsize > 0ul, "nothing to save from!", return false);

			std::ofstream stream;

			stream.open(fpath, std::ios::binary | std::ios::out);
			GT_CHECK(stream.good(), "cannot open file path for save!", return false);

			stream.write(static_cast<const char*>(fdata), fsize);
			GT_CHECK(stream.good(), "cannot save file!", return false);

			stream.close();

			return true;
		}
		template<typename ftype_t> inline bool
			save_str(const fpath_t& fpath, const ftype_t* fdata, fsize_t fsize)
		{
			GT_CHECK(fdata != nullptr && fsize > 0ul, "nothing to save from!", return false);

			std::ofstream stream;

			stream.open(fpath, std::ios::out);
			GT_CHECK(stream.good(), "cannot open file path for save!", return false);

			stream.write(static_cast<const char*>(fdata), fsize);
			GT_CHECK(stream.good(), "cannot save file!", return false);

			stream.close();

			return true;
		}
		template<typename ftype_t> extern bool
			save(const fpath_t& fpath, const ftype_t* fdata);

		template<typename ftype_t> inline bool
			load_bin(const fpath_t& fpath, ftype_t** fdata, fsize_t* fsize = nullptr)
		{
			GT_CHECK(fdata != nullptr, "nothing to load into!", return false);
			GT_CHECK(*fdata == nullptr, "we should not load files into the used memory!", return false);
			std::ifstream stream;

			stream.open(fpath, std::ios::binary | std::ios::in);
			GT_CHECK(stream.good(), "cannot open file path for save!", return false);

			stream.seekg(0, std::ios::end);
			msize_t msize = stream.tellg();
			stream.seekg(0, std::ios::beg);
			if (fsize) { *fsize = msize; }

			*fdata = new ftype_t[msize];
			memset(*fdata, 0, msize);
			stream.read(static_cast<char*>(*fdata), msize);

			stream.close();
			
			return true;
		}
		template<typename ftype_t> inline bool
			load_str(const fpath_t& fpath, ftype_t** fdata, fsize_t* fsize = nullptr)
		{
			GT_CHECK(fdata != nullptr, "nothing to load into!", return false);
			GT_CHECK(*fdata == nullptr, "we should not load files into the used memory!", return false);
			std::ifstream stream;

			stream.open(fpath, std::ios::in);
			GT_CHECK(stream.good(), "cannot open file path for save!", return false);

			stream.seekg(0, std::ios::end);
			msize_t msize = stream.tellg();
			stream.seekg(0, std::ios::beg);
			if (fsize) { *fsize = msize; }

			*fdata = new ftype_t[msize];
			memset(*fdata, 0, msize);
			stream.read(static_cast<char*>(*fdata), msize);

			stream.close();

			return true;
		}
		template<typename ftype_t> extern bool
			load(const fpath_t& fpath, ftype_t* fdata);
		
	}

}

#endif /* LIB_FILE_HPP */