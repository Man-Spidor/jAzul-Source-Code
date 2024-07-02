//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H

// -----------------------------------------------------------------------------
// DO NOT MODIFY
// -----------------------------------------------------------------------------
// Warning levels turned on for Wall... that Should be supressed globally
//     Set here to avoid surpressing them in the settings
// -----------------------------------------------------------------------------

#pragma warning( disable : 5266 ) // 'const' qualifier on return type has no effect
#pragma warning( disable : 5219 ) // 'LONGLONG' to 'float', possible loss of data
#pragma warning( disable : 4365 ) // '=': conversion, signed / unsigned mismatch	
#pragma warning( disable : 4471 ) // a forward declaration of an unscoped enumeration must have an underlying type
#pragma warning( disable : 5204 ) // class has virtual functions, but its trivial destructor is not virtual
#pragma warning( disable : 4596 ) // illegal qualified name in member declaration
#pragma warning( disable : 4946 ) // illegal qualified name in member declaration
#pragma warning( disable : 4061 ) // enumerator in switch of enum is not handled by a case label

// --------------------------------------
// General includes
// --------------------------------------

#include <assert.h>


#endif 

// ---  End of File ---------------
