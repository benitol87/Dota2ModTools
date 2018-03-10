#include "abilityparser.h"
#include "stringelement.h"

#include <fstream>

namespace dota2 {
    namespace parser {

        AbilityParser::AbilityParser(): file(nullptr)
        {
        }

        std::vector<PairElement> AbilityParser::parseFile(std::string filename)
        {
            std::vector<PairElement> result;
            this->file = new std::ifstream(filename);

            // Initialization
            this->lineIndex = 1;
            this->columnIndex = 0;

            // Test if file was opened correctly
            if(!this->file->is_open()) {
                std::cerr << "ERROR: Could not open file for reading " << filename << std::endl;
                throw new std::exception();
            }

            // Get first non-space character
            this->nextNonSpaceChar();

            // Parse a list of pairs key/value
            while(!this->file->eof()) {
                PairElement* elem(this->parsePairElement());
                result.push_back(*elem);
                delete elem;
            }

            // Close the file
            this->file->close();
            delete this->file;
            this->file = nullptr;

            return result;
        }

        void AbilityParser::writeFile(std::string filename, std::vector<PairElement> data)
        {
            std::ofstream file(filename);

            if(!file.is_open()) {
                std::cerr << "ERROR: Could not open file for writing : " << filename << std::endl;
                return;
            }

            for (auto& elem : data) {
                file << elem.toString() << std::endl;
            }

            file.close();
        }

        PairElement* AbilityParser::parsePairElement()
        {
            std::string key("");
            ValueElement* value = nullptr;

            // Parse the key
            key = this->parseString();

            // Parse the value
            // TODO memory leak
            value = this->parseValue();

            PairElement* pair = new PairElement(key, *value);
            return pair;
        }

        std::string AbilityParser::parseString()
        {
            std::string result("");

            // Must start with a "
            if (this->lastCharRead != '"') {
                this->throwParsingException("Expected \" ");
            }

            // Take every following char until the next "
            this->readChar();
            while(this->lastCharRead!='"') {
                // Must end with a "
                if (this->file->eof()) {
                    this->throwParsingException("Unexpected end of file, missing \"");
                }

                result += this->lastCharRead;

                this->readChar();
            }

            // Skip all following spaces/comments
            this->nextNonSpaceChar();

            return result;
        }

        ValueElement* AbilityParser::parseValue()
        {
            ValueElement* result = nullptr;

            //TODO memory leak
            // Check first character of this token to see what must be parsed
            if (this->lastCharRead == '"') {
                std::string str = this->parseString();
                result = new StringElement(str);
            } else if (this->lastCharRead == '{') {
                result = this->parseObject();
            } else {
                this->throwParsingException(std::string("Unexpected character: ") + this->lastCharRead);
            }

            return result;
        }

        ObjectElement* AbilityParser::parseObject()
        {
            ObjectElement* result = new ObjectElement();

            // Must start with a {
            if (this->lastCharRead != '{') {
                this->throwParsingException("Expected {");
            }
            this->nextNonSpaceChar();

            // Parse every pair until a } is reached
            while (this->lastCharRead != '}') {
                PairElement* pair = this->parsePairElement();
                result->addPair(*pair);
                delete pair; // delete it since a copy is made

                // Must end with a }
                if(this->file->eof()) {
                    this->throwParsingException("Unexpected end of file, missing }");
                }
            }

            // Read the first character of the next token
            this->nextNonSpaceChar();

            return result;
        }

        void AbilityParser::nextNonSpaceChar()
        {
            // Read a character
            readChar();

            // Skip all spaces and comments
            while( (this->lastCharRead==' ' || this->lastCharRead=='\t' ||
                  this->lastCharRead=='\n' || this->lastCharRead=='/')
                    && !this->file->eof()) {
                if (this->lastCharRead=='/') {
                    this->skipComment();
                } else {
                    readChar();
                }
            }
        }

        void AbilityParser::readChar()
        {
            // Read a character in the file open
            this->file->read(&(this->lastCharRead), 1);

            if(this->file->eof()) {
                return;
            }

            // Update the line and column variables for error messages
            this->columnIndex++;
            if (this->lastCharRead=='\n') {
                this->lineIndex++;
                this->columnIndex = 0;
            }
        }

        void AbilityParser::skipComment()
        {
            this->readChar();
            if(this->lastCharRead != '/') {
                this->throwParsingException("Stray '/'");
            }
            this->skipLine();
        }

        void AbilityParser::skipLine()
        {
            while(this->lastCharRead != '\n' &&
                  !this->file->eof()) {
                //this->lastCharRead != EOF) {
                this->readChar();
            }
            this->readChar();
        }

        void AbilityParser::throwParsingException(std::string message)
        {
            std::cerr << "ERROR: "<< message <<" at line " << this->lineIndex <<" column "
                      << this->columnIndex << "." << std::endl;
            throw new std::exception();
        }

    }
}
