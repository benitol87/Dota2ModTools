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
         * Allows to read and write such files.
         *
         * The content of those files can be seen as a list of key/value pairs,
         * where a key is a string and the value can be either a string or an object.
         *
         * --------------------------------------------
         * Grammar parsed:
         *   S     --> PAIR S | eof
         *   PAIR  --> STR VALUE
         *   STR   --> quote string quote
         *   VALUE --> STR | OBJ
         *   OBJ   --> obracket LIST cbracket
         *   LIST  --> PAIR LIST | epsilon
         *
         * Non-terminal symbols:
         *   S (axiom), PAIR, STR, VALUE, OBJ, LIST
         *
         * Terminal symbols:
         *   eof (end of file), quote ", string (any string that does not
         *   contain "), obracket {, cbracket }
         * --------------------------------------------
         *
         * @see classes ObjectElement PairElement StringElement ValueElement
         */
        class TOOLS_API AbilityParser
        {
        public:
            /**
             * @brief AbilityParser
             * Constructor
             *
             * Does nothing
             */
            AbilityParser();

            /**
             * @brief parseFile
             * Method that opens a file and parse its content. The file content must
             * respect the expected grammar.
             *
             * @param filename name of the file to open
             * @return a vector of pairs hero name(std::string)/abilities(ValueElement)
             * @throws std::exception if parsing failed (file not found, wrong
             * syntax, ...)
             */
            std::vector<PairElement> parseFile(std::string filename);

            /**
             * @brief writeFile
             * Method that transforms a vector of PairElement objects into a string
             * with the toString() method and then puts it in a file.
             * The file is created if it does not exist.
             *
             * @param filename name of the file in which must be written the data
             * @param data data to save in a file
             * @throws std::exception if the file could not be opened
             */
            void writeFile(std::string filename, std::vector<PairElement> data);

        private:

            // Private methods

            /**
             * @brief parsePairElement
             * Reads the file currently open starting from the last character read
             * in order to parse a pair string/value.
             *
             * After this method has finished, the last read character will be the
             * first of the next token to parse.
             *
             * @return a pointer to a dynamically allocated PairElement object
             * @throws std::exception if the parsing of either the key or the value
             * failed
             */
            PairElement* parsePairElement();

            /**
             * @brief parseString
             * Reads the file currently open starting from the last character read
             * in order to parse a string delimited by two " character.
             *
             * After this method has finished, the last read character will be the
             * first of the next token to parse.
             *
             * @return the string parsed without the "
             * @throws std::exception if the parsing failed
             */
            std::string parseString();

            /**
             * @brief parseValue
             * Reads the file currently open starting from the last character read
             * in order to parse a value (string or object).
             *
             * After this method has finished, the last read character will be the
             * first of the next token to parse.
             *
             * @return a pointer to a dynamically allocated subclass of ValueElement
             * @throws std::exception if the parsing failed
             */
            ValueElement* parseValue();

            /**
             * @brief parseObject
             * Reads the file currently open starting from the last character read
             * in order to parse an object.
             *
             * After this method has finished, the last read character will be the
             * first of the next token to parse.
             *
             * @return a pointer to a dynamically allocated object
             * @throws std::exception if the parsing failed
             */
            ObjectElement* parseObject();

            /**
             * @brief nextNonSpaceChar
             * Read characters in the file currently open until the first non space
             * and non comment character encountered. This character will be placed
             * in this->lastCharRead
             *
             * Stops when the end of file is reached.
             */
            void nextNonSpaceChar();

            /**
             * @brief readChar
             * Reads one character in the file currently open and updates the attributes
             * lineIndex and columnIndex used for error messages.
             */
            void readChar();

            /**
             * @brief skipComment
             * Expects the last character read and the next one to be /
             * Reads characters until a line break is reached.
             */
            void skipComment();

            /**
             * @brief skipLine
             * Reads characters until a line break is reached.
             */
            void skipLine();

            /**
             * @brief throwParsingException
             * Writes an error message on stderr and then throws a std::exception
             *
             * @param message simple error message to display, this method adds
             *                current line and column numbers to it
             * @throws std::exception always
             */
            void throwParsingException(std::string message);

        private:

            // Attributes

            int lineIndex, columnIndex;
            char lastCharRead;
            std::ifstream* file;

        };

    }
}

#endif // ABILITYPARSER_H
