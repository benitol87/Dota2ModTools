#ifndef OBJECTELEMENT_H
#define OBJECTELEMENT_H

#include <vector>

#include "valueelement.h"
#include "pairelement.h"

namespace dota2 {
    namespace parser {

        /**
         * @brief The ObjectElement class
         */
        class TOOLS_API ObjectElement: public ValueElement
        {
        public:
            /**
             * @brief ObjectElement
             */
            ObjectElement();

            /**
             * @brief toString
             * @param indent
             * @return
             */
            virtual std::string toString(const std::string& indent = "") const;

            /**
             * @brief addPair
             * @param key
             * @param value
             */
            void addPair(std::string& key, ValueElement& value) {
                this->pairs.push_back(PairElement(key,value));
            }

            /**
             * @brief addPair
             * @param pair
             */
            void addPair(const PairElement& pair) {
                this->pairs.push_back(pair);
            }

            /**
             * @brief getPairs
             * @return
             */
            std::vector<PairElement>& getPairs() {return this->pairs;}

        private:

            // Attributes

            std::vector<PairElement> pairs;
        };

    }
}

#endif // OBJECTELEMENT_H
