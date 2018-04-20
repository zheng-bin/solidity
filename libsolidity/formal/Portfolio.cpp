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

#include <libsolidity/formal/Portfolio.h>

#ifdef HAVE_Z3
#include <libsolidity/formal/Z3Interface.h>
#endif
#ifdef HAVE_CVC4
#include <libsolidity/formal/CVC4Interface.h>
#endif
#if !defined (HAVE_Z3) && !defined (HAVE_CVC4)
#include <libsolidity/formal/SMTLib2Interface.h>
#endif

using namespace std;
using namespace dev;
using namespace dev::solidity::smt;

Portfolio::Portfolio(ReadCallback::Callback const& _readCallback)
{
#ifdef HAVE_Z3
	m_solvers.emplace_back(make_shared<smt::Z3Interface>());
#endif
#ifdef HAVE_CVC4
	m_solvers.emplace_back(make_shared<smt::CVC4Interface>());
#endif
#if !defined (HAVE_Z3) && !defined (HAVE_CVC4)
	m_solvers.emplace_back(make_shared<smt::SMTLib2Interface>(_readFileCallback)),
#endif
	(void)_readCallback;
}

void Portfolio::reset()
{
	for (auto s : m_solvers)
		s->reset();
}

void Portfolio::push()
{
	for (auto s : m_solvers)
		s->push();
}

void Portfolio::pop()
{
	for (auto s : m_solvers)
		s->pop();
}

Expression Portfolio::newFunction(string _name, Sort _domain, Sort _codomain)
{
	for (auto s : m_solvers)
		s->newFunction(_name, _domain, _codomain);
	return SolverInterface::newFunction(move(_name), _domain, _codomain);
}

Expression Portfolio::newInteger(string _name)
{
	for (auto s : m_solvers)
		s->newInteger(_name);
	return SolverInterface::newInteger(move(_name));
}

Expression Portfolio::newBool(string _name)
{
	for (auto s : m_solvers)
		s->newBool(_name);
	return SolverInterface::newBool(move(_name));
}

void Portfolio::addAssertion(Expression const& _expr)
{
	for (auto s : m_solvers)
		s->addAssertion(_expr);
}


pair<CheckResult, vector<string>> Portfolio::check(vector<Expression> const& _expressionsToEvaluate)
{
	CheckResult lastResult = CheckResult::UNKNOWN;
	vector<string> finalValues;
	for (auto s : m_solvers)
	{
		CheckResult result;
		vector<string> values;
		tie(result, values) = s->check(_expressionsToEvaluate);
		if (result <= CheckResult::UNSATISFIABLE)
		{
			// result is SAT or UNSAT for the first time,
			// so we use these results.
			// If solver said UNKNOWN or ERROR we discard it.
			if (lastResult == CheckResult::UNKNOWN)
			{
				lastResult = result;
				finalValues = std::move(values);
			}
			// At this point we're sure that a solver answered
			// SAT whereas another answered UNSAT, since
			// lastResult can never be ERROR.
			else if (lastResult != result)
			{
				solAssert(false, "At least two SMT solvers gave opposing results.");
			}
		}
	}
	return make_pair(lastResult, finalValues);
}











