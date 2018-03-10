#ifndef PAIRELEMENT_H
#define PAIRELEMENT_H

#include "valueelement.h"

namespace dota2 {
    namespace parser {

        /**
         * @brief The PairElement class
         * Class containing a pair string/value
         *
         * @see StringElement, ValueElement
         */
        class TOOLS_API PairElement
        {
        public:
            /**
             * @brief PairElement
             * Constructor
             * Sets the values of the pair.
             *
             * @param key
             * @param value
             */
            PairElement(const std::string& key, ValueElement& value);

            /**
             * @brief toString
             * Converts this pair into a string.
             *
             * @param indent string to add to the result after each line break
             * @return stringified value
             */
            std::string toString(const std::string& indent="") const;

            /**
             * @brief getKey
             *
             * @return a reference to this pair's key (not a copy)
             */
            std::string& getKey() {return this->key;}

            /**
             * @brief getValue
             * @return a reference to this pair's value (not a copy)
             */
            ValueElement& getValue() {return *(this->value);}

        private:

            // Attributes

            std::string key;
            ValueElement* value;
        };

    }
}

#endif // PAIRELEMENT_H
