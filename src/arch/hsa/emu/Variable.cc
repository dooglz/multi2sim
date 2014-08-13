/*
 *  Multi2Sim
 *  Copyright (C) 2014  Yifan Sun (yifansun@coe.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Emu.h"
#include "Variable.h"

namespace HSA
{

Variable::~Variable()
{
}


Variable::Variable(const std::string& name, unsigned short type, unsigned size,
		unsigned address = 0) :
		name(name),
		type(type),
		size(size),
		address(address)
{
}

template<typename T>
void Variable::DumpValue(std::ostream &os = std::cout) const
{
	// Get the buffer of the value
	mem::Memory *memory = Emu::getInstance()->getMemory();
	T *buffer = (T*)memory->getBuffer(address, size,
			mem::Memory::AccessWrite);

	// Dump the value
	os << *buffer;
}


void Variable::Dump(std::ostream &os = std::cout) const
{
	// Dump input or output
	if (this->isInput())
	{
		os << "Input ";
	}


	// Dump information of the argument.
	os << misc::fmt("    %s %s(0x%x)", BrigEntry::type2str(type).c_str(),
			name.c_str(), address);

	// If address is allocated
	if (address)
	{
		os << " = ";
		switch (type)
		{
		case BRIG_TYPE_U8:

			DumpValue<unsigned char>(os);
			break;

		case BRIG_TYPE_U16:

			DumpValue<unsigned short>(os);
			break;

		case BRIG_TYPE_U32:

			DumpValue<unsigned int>(os);
			break;

		case BRIG_TYPE_U64:

			DumpValue<unsigned long>(os);
			break;

		case BRIG_TYPE_S8:

			DumpValue<char>(os);
			break;

		case BRIG_TYPE_S16:

			DumpValue<short>(os);
			break;

		case BRIG_TYPE_S32:

			DumpValue<int>(os);
			break;

		case BRIG_TYPE_S64:

			DumpValue<long>(os);
			break;

		case BRIG_TYPE_F32:

			DumpValue<float>(os);
			break;

		case BRIG_TYPE_F64:

			DumpValue<double>(os);
			break;

		default:
			throw misc::Panic("Unimplemented variable type.");
			break;
		}
	}

	// New line
	os << "\n";

}

}  // namespace HSA
