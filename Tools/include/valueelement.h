#ifndef VALUEELEMENT_H
#define VALUEELEMENT_H

#include <string>

#include "dll_include.h"

namespace dota2 {
    namespace parser {

        /**
         * @brief The ValueElement class
         * @abstract
         *
         * Base class for value elements of the pairs parsed
         */
        class TOOLS_API ValueElement
        {
        public:
            virtual std::string toString(const std::string& indent="") const = 0;
        protected:
            ValueElement() {}
        };

    }
}

#endif // VALUEELEMENT_H
