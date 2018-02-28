#include "pairelement.h"

namespace dota2 {
    namespace parser {
        PairElement::PairElement(const std::string& key, ValueElement& value):
            key(key), value(&value)
        {

        }

        std::string PairElement::toString(const std::string& indent) const
        {
            return "\"" + this->key + "\" " + this->value->toString(indent);
        }
    }
}
