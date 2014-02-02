#include <DataCache/Exception/Exceptions.hpp>
#include <DataCache/StringStreamer.hpp>

namespace DataCache { namespace Exception {
  
    AccessingUnRegisteredFieldId::AccessingUnRegisteredFieldId(const std::size_t fieldId)
        : std::runtime_error(StringStreamer() << "Attempted to access an unregistered field id: " << fieldId)
    {
    }
}}
