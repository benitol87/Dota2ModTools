#ifndef STRINGELEMENT_H
#define STRINGELEMENT_H

#include "valueelement.h"

namespace dota2 {
    namespace parser {

        class TOOLS_API StringElement: public ValueElement
        {
        public:
            StringElement(const std::string& str);

            virtual std::string toString(const std::string& indent="") const;

        private:
            std::string str;
        };

    }
}

#endif // STRINGELEMENT_H
