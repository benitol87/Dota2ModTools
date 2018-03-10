#ifndef STRINGELEMENT_H
#define STRINGELEMENT_H

#include "valueelement.h"

namespace dota2 {
    namespace parser {

        /**
         * @brief The StringElement class
         * Simply contains a string
         */
        class TOOLS_API StringElement: public ValueElement
        {
        public:
            /**
             * @brief StringElement
             * Constructor
             * Simply sets this object's string
             *
             * @param str String to initialize this object with
             */
            StringElement(const std::string& str);

            /**
             * @brief toString
             * Converts this object into a string (adds " before and after
             * this object's string).
             *
             * @param indent string to add to the result after each line break
             * @return stringified value
             */
            virtual std::string toString(const std::string& indent="") const;

        private:

            // Attributes

            std::string str;
        };

    }
}

#endif // STRINGELEMENT_H
