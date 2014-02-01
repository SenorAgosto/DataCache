#pragma once

namespace DataCache { namespace Details {
  
    // A tag type indicating that we should increment the type when
    // any object is created.
    struct CountAllObjects {};
    
    // A tag type indicating we do not wish to increment the type count
    // used for copy constructor.
    struct NoIncrement {};

}}