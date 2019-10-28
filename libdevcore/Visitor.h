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
/**
 * Visitor templates.
 */

#pragma once

#include <functional>
#include <variant>

namespace dev
{

/// Generic visitor used as follows:
/// std::visit(GenericVisitor{
///     [](Class1& _c) { _c.f(); },
///     [](Class2& _c) { _c.g(); }
/// }, variant);
/// This one does not have a fallback and will fail at
/// compile-time if you do not specify all variants.

template <typename... Visitables>
struct GenericVisitor: Visitables...
{
	using Visitables::operator() ...;
};

template <typename... Visitables>
GenericVisitor(Visitables...) -> GenericVisitor<Visitables...>;

/// Generic visitor with fallback:
/// std::visit(GenericFallbackVisitor{
///     [](Class1& _c) { _c.f(); },
///     [](Class2& _c) { _c.g(); }
/// }, variant);
/// This one DOES have a fallback and will NOT fail at
/// compile-time if you do not specify all variants.

template <typename... Visitables>
struct GenericFallbackVisitor: Visitables...
{
	using Visitables::operator() ...;

	template <typename T>
	void operator()(T const&) const noexcept {}
};

template <typename... Visitables>
GenericFallbackVisitor(Visitables...) -> GenericFallbackVisitor<Visitables...>;

/// Generic visitor with fallback that can return a value:
/// std::visit(GenericFallbackReturnsVisitor{
///     [](Class1& _c) { return _c.f(); },
///     [](Class2& _c) { return _c.g(); }
/// }, variant);
/// This one DOES have a fallback and will NOT fail at
/// compile-time if you do not specify all variants.
/// The fallback {}-constructs the return value.

template <typename... Visitables>
struct GenericFallbackReturnsVisitor: Visitables...
{
	using Visitables::operator() ...;

	template <typename T>
	decltype(auto) operator()(T const&) const { return {}; }
};

template <typename... Visitables>
GenericFallbackReturnsVisitor(Visitables...) -> GenericFallbackReturnsVisitor<Visitables...>;

/// Delayed Visitation
///
/// Example:
///     auto visitation = visit_delayed(Visitor);
///     visitation(value);

template <typename Visitor>
struct DelayedVisit {
	Visitor const& visitor;
	explicit DelayedVisit(Visitor const& _v) : visitor{_v} {}

	template <typename T>
	decltype(auto) operator()(T const& _value) const { return std::visit(visitor, _value); }
};

template <typename T>
DelayedVisit(T) -> DelayedVisit<T>;

template <typename Visitor>
auto visit(Visitor& _visitor)
{
	return DelayedVisit{_visitor};
}

}
