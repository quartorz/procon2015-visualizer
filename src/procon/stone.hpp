#pragma once

#include "constant.hpp"
#include "cell.hpp"

#include <array>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iomanip>

namespace procon{
	class stone{
		using line_type = std::array<cell, stone_size>;

		std::array<line_type, stone_size> _array;

	public:
		stone() = default;
		stone(const stone &) = default;
		stone &operator=(const stone &) = default;

		stone(const std::array<std::string, stone_size> &stone)
		{
			for(int i = 0; i < stone_size; i++){
				auto &line = stone[i];
				for(int j = 0; j < stone_size; j++){
					if(line[j] == '1'){
						_array[i][j].set_block();
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

		static std::array<std::string, stone_size> read(std::ifstream &ifs)
		{
			std::array<std::string, stone_size> result;
			int i;

			for(i = 0; i < stone_size && ifs; i++){
				std::getline(ifs, result[i]);
			}

			if(i != stone_size)
				throw std::runtime_error("invalid problem file format");

			return result;
		}

		friend std::ostream &operator<<(std::ostream &os, stone &s)
		{
			for(auto &line : s._array){
				for(auto &cell : line){
					os << std::setbase(16) << static_cast<std::uint32_t>(cell) << ' ';
				}
				os << std::endl;
			}

			return os;
		}
	};
}
