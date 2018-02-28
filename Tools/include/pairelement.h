#ifndef PAIRELEMENT_H
#define PAIRELEMENT_H

#include "valueelement.h"

namespace dota2 {
    namespace parser {

        class TOOLS_API PairElement
        {
        public:
            PairElement(const std::string& key, ValueElement& value);

            std::string toString(const std::string& indent="") const;

            std::string& getKey() {return this->key;}
            ValueElement& getValue() {return *(this->value);}

        private:
            std::string key;
            ValueElement* value;
        };

    }
}

#endif // PAIRELEMENT_H
