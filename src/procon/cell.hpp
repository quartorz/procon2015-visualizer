#pragma once

#include <cstdint>

namespace procon{
	enum class cell_info: std::uint32_t{
		empty = 0x00000000,
		barrier = 0x00000001,
		block = 0x00000002,
		neighbor = 0x00000004,
		outside = 0x00000008,
	};

	cell_info operator|(cell_info lhs, cell_info rhs)
	{
		return static_cast<cell_info>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
	}
	cell_info operator&(cell_info lhs, cell_info rhs)
	{
		return static_cast<cell_info>(static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs));
	}
	cell_info operator~(cell_info c)
	{
		return static_cast<cell_info>(~static_cast<std::uint32_t>(c));
	}
	cell_info operator|=(cell_info &lhs, cell_info rhs)
	{
		return lhs = lhs | rhs;
	}
	cell_info operator&=(cell_info &lhs, cell_info rhs)
	{
		return lhs = lhs & rhs;
	}

	class cell{
		cell_info _cell;

	public:
		cell()
			: _cell(cell_info::empty)
		{
		}

		cell(cell_info c)
			: _cell(c)
		{
		}

		operator std::uint32_t() const
		{
			return static_cast<std::uint32_t>(_cell);
		}

		void set_empty()
		{
			_cell = cell_info::empty;
		}
		void set_barrier()
		{
			_cell |= cell_info::barrier;
		}
		void set_block()
		{
			_cell |= cell_info::block;
		}
		void set_neighbor()
		{
			_cell |= cell_info::neighbor;
		}
		void set_outside()
		{
			_cell |= cell_info::outside;
		}

		bool is_empty() const
		{
			return _cell == cell_info::empty;
		}
		bool is_barrier() const
		{
			return (_cell & cell_info::barrier) == cell_info::barrier;
		}
		bool is_block() const
		{
			return (_cell & cell_info::block) == cell_info::block;
		}
		bool is_neighbor() const
		{
			return _cell == cell_info::neighbor;
		}
		bool is_outside() const
		{
			return (_cell & cell_info::outside) == cell_info::outside;
		}
	};
}
