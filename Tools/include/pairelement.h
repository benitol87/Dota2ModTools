#ifndef PAIRELEMENT_H
#define PAIRELEMENT_H

#include "valueelement.h"

namespace dota2 {
    namespace parser {

        /**
         * @brief The PairElement class
         */
        class TOOLS_API PairElement
        {
        public:
            /**
             * @brief PairElement
             * @param key
             * @param value
             */
            PairElement(const std::string& key, ValueElement& value);

            /**
             * @brief toString
             * @param indent
             * @return
             */
            std::string toString(const std::string& indent="") const;

            /**
             * @brief getKey
             * @return
             */
            std::string& getKey() {return this->key;}

            /**
             * @brief getValue
             * @return
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
