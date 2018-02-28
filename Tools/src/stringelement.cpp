#include "stringelement.h"

namespace dota2 {
    namespace parser {

        StringElement::StringElement(const std::string& str):
            str(str)
        {

        }

        std::string StringElement::toString(const std::string&) const
        {
            return "\"" + this->str + "\"";
        }
    }
}
