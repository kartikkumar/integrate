/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef INTEGRATE_TEST_STATE_HPP
#define INTEGRATE_TEST_STATE_HPP

#include <vector>

namespace integrate
{
namespace tests
{

typedef double Real;
typedef std::vector< Real > Vector;

class State
{
public:

    State( const Vector& aVector )
        : vector( aVector )
    { }

    const int size( ) const { return vector.size( ); }
    const Real operator[ ] ( const int i ) const { return vector[ i ]; }

    State& operator=( const State& rightHandSide );
    State& operator+=( const State& rightHandSide );

    bool operator==( const State& rightHandSide ) const;
    bool operator<( const State& rightHandSide ) const;
    bool operator<( const Real rightHandSide ) const;
    bool operator>( const State& rightHandSide ) const;
    bool operator>( const Real rightHandSide ) const;

    friend State operator+( const State& leftHandSide, const State& rightHandSide );
    friend State operator*( const Real multiplier, const State& state );
    friend State operator*( const State& state, const Real multiplier );

protected:
private:

    Vector vector;
};

} // namespace tests
} // namespace integrate

#endif // INTEGRATE_TEST_STATE_HPP
