/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <catch.hpp>

#include <functional>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "integrate/euler.hpp"

#include "testDynamicalModels.hpp"
#include "testState.hpp"

namespace integrate
{
namespace tests
{

TEST_CASE( "Test Euler integrator for zero dynamics", "[euler]" )
{
    const State initialState( { 1.2, 2.3, -3.6 } );
    const Real initialTime = 1.0;
    const Real stepSize = 0.1;

    State currentState = initialState;
    Real currentTime = initialTime;

    ZeroDynamics dynamics;

    using namespace std::placeholders;
    auto stateDerivativePointer = std::bind( &ZeroDynamics::computeStateDerivative,
                                             &dynamics,
                                             _1,
                                             _2 );
    stepEuler< Real, State >( currentTime,
                              currentState,
                              stepSize,
                              stateDerivativePointer );

    REQUIRE( currentTime  == ( initialTime + stepSize ) );
    REQUIRE( currentState == initialState );
}

TEST_CASE( "Test Euler integrator for Burden & Faires: Table 5.1", "[euler]" )
{
    const State initialState( { 0.5 } );
    const Real initialTime = 0.0;
    const Real stepSize = 0.2;

    Real currentTime = initialTime;
    State currentState = initialState;

    const Real testTolerance = 1.0e-7;

    std::map< Real, State > burdenFairesTable5_1Data;
    burdenFairesTable5_1Data.insert( { 0.2 , State( { 0.8000000 } ) } );
    burdenFairesTable5_1Data.insert( { 0.4 , State( { 1.1520000 } ) } );
    burdenFairesTable5_1Data.insert( { 0.6 , State( { 1.5504000 } ) } );
    burdenFairesTable5_1Data.insert( { 0.8 , State( { 1.9884800 } ) } );
    burdenFairesTable5_1Data.insert( { 1.0 , State( { 2.4581760 } ) } );
    burdenFairesTable5_1Data.insert( { 1.2 , State( { 2.9498112 } ) } );
    burdenFairesTable5_1Data.insert( { 1.4 , State( { 3.4517734 } ) } );
    burdenFairesTable5_1Data.insert( { 1.6 , State( { 3.9501281 } ) } );
    burdenFairesTable5_1Data.insert( { 1.8 , State( { 4.4281538 } ) } );
    burdenFairesTable5_1Data.insert( { 2.0 , State( { 4.8657845 } ) } );

    BurdenFaires dynamics;

    using namespace std::placeholders;
    auto stateDerivativePointer = std::bind( &BurdenFaires::computeStateDerivative,
                                             &dynamics,
                                             _1,
                                             _2 );

    for ( const auto& pair : burdenFairesTable5_1Data )
    {
       stepEuler< Real, State >( currentTime,
                                 currentState,
                                 stepSize,
                                 stateDerivativePointer );
        REQUIRE( pair.first == Approx( currentTime ).epsilon( testTolerance ) );
        REQUIRE( pair.second[ 0 ] == Approx( currentState[ 0 ] ).epsilon( testTolerance ) );
    }
}

} // namespace tests
} // namespace integrate
