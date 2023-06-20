#pragma once

#define SAFE_DELETE_POINTER(p) { assert(p); delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p)	{ assert(p) delete[] p; p = nullptr; }

#define DELETE_POINTER(p) { delete p; p = nullptr; }
#define DELETE_ARRAY(p)	{ delete[] p; p = nullptr; }


namespace engine
{
	namespace memory::safe
	{
		template<typename T, UINT Size>
		void DeleteArray(T* (&arr)[Size])
		{
			for (UINT i = 0; i < Size; ++i)
			{
				SAFE_DELETE_POINTER(arr[i]);
			}
		}

		template<typename Pointer>
		void DeleteVec(std::vector<Pointer>& vec)
		{
			for (size_t i = 0; i < vec.size(); ++i)
			{
				SAFE_DELETE_POINTER(vec[i]);
			}

			vec.clear();
		}

		template<typename Key, typename Pointer>
		void DeleteUnorderedMap(std::unordered_map<Key, Pointer>& map)
		{
			for (auto& value : map)
			{
				SAFE_DELETE_POINTER(value.second);
			}

			map.clear();
		}
	}

	namespace memory::unsafe
	{
		template<typename T, UINT Size>
		void DeleteArray(T* (&arr)[Size])
		{
			for (UINT i = 0; i < Size; ++i)
			{
				DELETE_POINTER(arr[i]);
			}
		}

		template<typename T>
		void DeleteVec(std::vector<T>& vec)
		{
			for (size_t i = 0; i < vec.size(); ++i)
			{
				DELETE_POINTER(vec[i]);
			}

			vec.clear();
		}

		template<typename Key, typename T>
		void DeleteUnorderedMap(std::unordered_map<Key, T>& map)
		{
			for (auto& value : map)
			{
				DELETE_POINTER(value.second);
			}

			map.clear();
		}
	}
}
