#pragma once

#include "ground.hpp"
#include "stone.hpp"

#include <fstream>
#include <tuple>
#include <vector>
#include <cstdint>

namespace procon{
	inline ground read_ground(std::ifstream &ifs)
	{
		return ground(ground::read(ifs));
	}

	inline stone read_stone(std::ifstream &ifs)
	{
		return stone(stone::read(ifs));
	}

	inline std::tuple<ground, std::vector<stone>> read_problem(std::ifstream &ifs)
	{
		auto g = read_ground(ifs);

		ifs.get();

		std::string s;
		std::getline(ifs, s);

		std::size_t num_stone= std::stoull(s);
		std::vector<stone> stones(num_stone);

		for(auto &stone : stones){
			stone = read_stone(ifs);
			ifs.get();
		}

		return std::make_tuple(g, stones);
	}
}
