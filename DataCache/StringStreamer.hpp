#pragma once
#include <sstream>
#include <string>

namespace DataCache {
    
    class StringStreamer
    {
    public:
        // Return the contents we've built.
        inline std::string str(void) const
        {
            return ss.str();
        }
        
        // Convert a StringStreamer to std::string.
        inline operator std::string()
        {
            return str();
        }

        // Invoke the insertion operator for type T passing the contents
        // to our member stringstream.
        template<typename T>
        inline StringStreamer& operator<<(const T& t)
        {
            ss << t;
            return *this;
        }
        
    private:
        std::stringstream ss;
    };
}
