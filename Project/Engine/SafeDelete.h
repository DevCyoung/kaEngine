#pragma once

#define DELETE_POINTER(p) { assert(p); delete p; p = nullptr; }
#define DELETE_ARRAY(p)	{ assert(p) delete[] p; p = nullptr; }

namespace engine
{
	namespace safe
	{
		template<typename T, UINT Size>
		void DeleteArray(T* (&arr)[Size])
		{
			for (UINT i = 0; i < Size; ++i)
			{
				delete arr[i];
				arr[i] = nullptr;
			}
		}

		template<typename Pointer>
		void DeleteVec(std::vector<Pointer>& vec)
		{
			for (size_t i = 0; i < vec.size(); ++i)
			{
				assert(vec[i]);

				delete vec[i];
				vec[i] = nullptr;
			}
			vec.clear();
		}

		template<typename Key, typename Pointer>
		void DeleteUnorderedMap(std::unordered_map<Key, Pointer>& map)
		{
			for (auto& value : map)
			{
				assert(value.second);

				delete value.second;
				value.second = nullptr;
			}

			map.clear();
		}
	}
}