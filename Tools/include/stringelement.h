#ifndef STRINGELEMENT_H
#define STRINGELEMENT_H

#include "valueelement.h"

namespace dota2 {
    namespace parser {

        /**
         * @brief The StringElement class
         */
        class TOOLS_API StringElement: public ValueElement
        {
        public:
            /**
             * @brief StringElement
             * @param str
             */
            StringElement(const std::string& str);

            /**
             * @brief toString
             * @param indent
             * @return
             */
            virtual std::string toString(const std::string& indent="") const;

        private:

            // Attributes

            std::string str;
        };

    }
}

#endif // STRINGELEMENT_H
