#pragma once

#include "cell.hpp"
#include "constant.hpp"

#include "../nonzero_based_array.hpp"

#include <fstream>
#include <string>
#include <array>
#include <stdexcept>
#include <iomanip>

namespace procon{
	class ground{
		using line_type = nonzero_based_array<cell, stone_size + ground_size + stone_size, - stone_size>;

		nonzero_based_array<line_type, stone_size + ground_size + stone_size, - stone_size> _array;

		static const int index_begin = - stone_size;
		static const int index_end = stone_size + ground_size;

		void init_array()
		{
			for(int i = index_begin; i < index_end; i++){
				for(int j = index_begin; j < 0; j++){
					_array[i][j].set_outside();
					_array[j][i].set_outside();
					_array[i][j + index_end].set_outside();
					_array[j + index_end][i].set_outside();
				}
			}
		}

	public:
		ground(const ground &) = default;
		ground &operator=(const ground &) = default;

		ground()
		{
			init_array();
		}

		ground(const std::array<std::string, ground_size> &ground)
		{
			init_array();
			for(int i = 0; i < ground_size; i++){
				auto &line = ground[i];
				for(int j = 0; j < ground_size; j++){
					if(line[j] == '1'){
						_array[i][j].set_barrier();
					}
				}
			}
		}

		line_type operator[](int index)
		{
			return _array[index];
		}

		const line_type operator[](int index) const
		{
			return _array[index];
		}

		static std::array<std::string, ground_size> read(std::ifstream &ifs)
		{
			std::array<std::string, ground_size> result;
			int i;

			for(i = 0; i < ground_size && ifs; i++){
				std::getline(ifs, result[i]);
			}

			if(i != ground_size)
				throw std::runtime_error("invalid problem file format");

			return result;
		}

		friend std::ostream &operator<<(std::ostream &os, ground &g)
		{
			for(auto &line : g._array){
				for(auto &cell : line){
					os << std::setbase(16) << static_cast<std::uint32_t>(cell) << ' ';
				}
				os << std::endl;
			}

			return os;
		}
	};
}
