#ifndef VALUEELEMENT_H
#define VALUEELEMENT_H

#include <string>

#include "dll_include.h"

namespace dota2 {
    namespace parser {

        /**
         * @brief The abstract ValueElement class
         * @abstract
         *
         * Base class for value elements of the pairs parsed, can
         * correspond to a string or an object.
         *
         * @see StringElement, ObjectElement, AbilityParser
         */
        class TOOLS_API ValueElement
        {
        public:
            /**
             * @brief toString
             * Converts this value into a string.
             * Unimplemented method to re-implement in subclasses
             *
             * @param indent string to add to the result after each line break
             * @return stringified value
             */
            virtual std::string toString(const std::string& indent="") const = 0;

        protected:
            /**
             * @brief ValueElement
             * Constructor
             *
             * Does nothing
             */
            ValueElement() {}
        };

    }
}

#endif // VALUEELEMENT_H
