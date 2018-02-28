#ifndef OBJECTELEMENT_H
#define OBJECTELEMENT_H

#include <vector>

#include "valueelement.h"
#include "pairelement.h"

namespace dota2 {
    namespace parser {

        class TOOLS_API ObjectElement: public ValueElement
        {
        public:
            ObjectElement();

            virtual std::string toString(const std::string& indent = "") const;

            void addPair(std::string& key, ValueElement& value) {
                this->pairs.push_back(PairElement(key,value));
            }

            void addPair(const PairElement& pair) {
                this->pairs.push_back(pair);
            }

            std::vector<PairElement>& getPairs() {return this->pairs;}

        private:
            std::vector<PairElement> pairs;
        };

    }
}

#endif // OBJECTELEMENT_H
