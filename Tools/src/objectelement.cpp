#include "objectelement.h"

namespace dota2 {
    namespace parser {

        ObjectElement::ObjectElement()
        {

        }

        std::string ObjectElement::toString(const std::string& indent) const
        {
            std::string result("\n"+indent+"{\n");

            for (auto& pair: this->pairs) {
                result = result + indent + "  " + pair.toString(indent+"  ") + "\n";
            }

            return result + indent + "}\n";
        }
    }
}
