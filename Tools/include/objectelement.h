#ifndef OBJECTELEMENT_H
#define OBJECTELEMENT_H

#include <vector>

#include "valueelement.h"
#include "pairelement.h"

namespace dota2 {
    namespace parser {

        /**
         * @brief The ObjectElement class
         * Class containing an object with regards to the grammar
         * parsed by the ability parser class, i.e. a list of pairs.
         *
         * @see PairElement AbilityParser
         */
        class TOOLS_API ObjectElement: public ValueElement
        {
        public:
            /**
             * @brief ObjectElement
             * Construtor
             *
             * Does nothing
             */
            ObjectElement();

            /**
             * @brief toString
             * Converts this object into a string.
             *
             * @param indent string to add to the result after each line break
             * @return stringified value
             */
            virtual std::string toString(const std::string& indent = "") const;

            /**
             * @brief addPair
             * Adds a pair to the list of this object.
             *
             * @param key
             * @param value
             */
            void addPair(std::string& key, ValueElement& value) {
                this->pairs.push_back(PairElement(key,value));
            }

            /**
             * @brief addPair
             * Adds a pair to the list of this object.
             * The pair passed is copied.
             *
             * @param pair
             */
            void addPair(const PairElement& pair) {
                this->pairs.push_back(pair);
            }

            /**
             * @brief getPairs
             * @return a reference to the vector of PairElement this object
             * uses (no copy is made in this method).
             */
            std::vector<PairElement>& getPairs() {return this->pairs;}

        private:

            // Attributes

            std::vector<PairElement> pairs;
        };

    }
}

#endif // OBJECTELEMENT_H
