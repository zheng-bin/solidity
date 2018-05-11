/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <string>

namespace dev {

/// Simple generic result that holds a value and an optional error message.
/// The convenient usage of this class relies on implicite type conversion
/// that will work most of the time:
///
/// Result<bool> check()
/// {
///		if (false)
///			return Result<bool>(false, "Error message.")
///		return true;
/// }
///
template <class T>
class Result
{
public:
	Result(T const& _value, std::string const& _error = ""):
		m_value(_value),
		m_error(_error)
	{
	}

	T const& get() const { return m_value; }
	std::string const& error() const { return m_error; }
private:
	T m_value;
	std::string m_error;
};

}


