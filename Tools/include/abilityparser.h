#ifndef ABILITYPARSER_H
#define ABILITYPARSER_H

#include <vector>
#include <iostream>
#include "pairelement.h"
#include "objectelement.h"

namespace dota2 {
    namespace parser {

        /**
         * @brief The AbilityParser class
         * Parser for the files containing hero abilities
         */
        class TOOLS_API AbilityParser
        {
        public:
            /**
             * @brief AbilityParser
             */
            AbilityParser();

        private:
            /**
             * @brief parsePairElement
             * @return
             */
            PairElement* parsePairElement();
            std::string parseString();
            ValueElement* parseValue();
            ObjectElement* parseObject();

            /**
             * @brief getNextChar
             * @return
             */
            void nextNonSpaceChar();
            void readChar();
            void skipComment();
            void skipLine();
            void throwParsingException(std::string message);

        public:
            /**
             * @brief parseFile
             * @param filename
             * @return a vector of pairs hero name(std::string)/abilities(ValueElement)
             */
            std::vector<PairElement> parseFile(std::string filename);

            /**
             * @brief writeFile
             * @param filename
             * @param data
             * Writes data in a file
             */
            void writeFile(std::string filename, std::vector<PairElement> data);

        private:
            int lineIndex, columnIndex;
            char lastCharRead;
            std::ifstream* file;

        };

    }
}

#endif // ABILITYPARSER_H
