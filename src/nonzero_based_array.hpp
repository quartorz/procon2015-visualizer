#pragma once

#include <array>
#include <initializer_list>
#include <utility>
#include <type_traits>

template <typename T, std::size_t Size, int Base>
class nonzero_based_array{
	std::array<T, Size> _array;

public:
	using value_type = T;

	nonzero_based_array() = default;
	nonzero_based_array(const nonzero_based_array &) = default;
	//nonzero_based_array(nonzero_based_array &&) = default;

	template <typename U, typename = typename std::enable_if<std::is_convertible<U, T>::value>::type>
	nonzero_based_array(std::initializer_list<U> list)
		: _array(list)
	{
	}

	typename std::array<T, Size>::iterator begin()
	{
		return _array.begin();
	}
	typename std::array<T, Size>::const_iterator begin() const
	{
		return _array.cbegin();
	}
	typename std::array<T, Size>::const_iterator cbegin() const
	{
		return _array.cbegin();
	}
	typename std::array<T, Size>::reverse_iterator rbegin()
	{
		return _array.rbegin();
	}
	typename std::array<T, Size>::const_reverse_iterator crbegin() const
	{
		return _array.crbegin();
	}
	typename std::array<T, Size>::iterator end()
	{
		return _array.end();
	}
	typename std::array<T, Size>::const_iterator end() const
	{
		return _array.cend();
	}
	typename std::array<T, Size>::const_iterator cend() const
	{
		return _array.cend();
	}
	typename std::array<T, Size>::reverse_iterator rend()
	{
		return _array.rend();
	}
	typename std::array<T, Size>::const_reverse_iterator crend() const
	{
		return _array.crend();
	}

	T &operator[](int index)
	{
		return _array[index - Base];
	}

	const T &operator[](int index) const
	{
		return _array[index - Base];
	}
};
