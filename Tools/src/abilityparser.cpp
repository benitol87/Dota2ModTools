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
            //std::cout << "DEBUG: parseFile" << std::endl;
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
            //while(this->lastCharRead != EOF) {
                PairElement* elem(this->parsePairElement());
                result.push_back(*elem);
                delete elem;
            }

            // Close the file
            this->file->close();
            delete this->file;
            this->file = nullptr;

            //std::cout << "DEBUG: parseFile end" << std::endl;
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
            //std::cout << "DEBUG: parsePair" << std::endl;
            std::string key("");
            ValueElement* value = nullptr;

            key = this->parseString();
            value = this->parseValue();

            PairElement* pair = new PairElement(key, *value);
            //std::cout << "DEBUG: parsePair end" << std::endl;
            return pair;
        }

        std::string AbilityParser::parseString()
        {
            //std::cout << "DEBUG: parseString" << std::endl;
            std::string result("");

            if (this->lastCharRead != '"') {
                this->throwParsingException("Expected \" ");
            }

            this->readChar();

            while(this->lastCharRead!='"') {
                if (this->file->eof()) {
                //if (this->lastCharRead==EOF) {
                    this->throwParsingException("Unexpected end of file, missing \"");
                }

                result += this->lastCharRead;

                this->readChar();
            }

            // Skip all spaces/comments
            this->nextNonSpaceChar();

            return result;
        }

        ValueElement* AbilityParser::parseValue()
        {
            //std::cout << "DEBUG: parseValue" << std::endl;
            ValueElement* result = nullptr;

            //TODO memory leak
            if (this->lastCharRead == '"') {
                std::string str = this->parseString();
                result = new StringElement(str);
            } else if (this->lastCharRead == '{') {
                result = this->parseObject();
            } else {
                this->throwParsingException(std::string("Unexpected character: ") + this->lastCharRead);
            }

            //std::cout << "DEBUG: parseValue end" << std::endl;
            return result;
        }

        ObjectElement* AbilityParser::parseObject()
        {
            //std::cout << "DEBUG: parseObject" << std::endl;
            ObjectElement* result = new ObjectElement();

            if (this->lastCharRead != '{') {
                this->throwParsingException("Expected {");
            }
            this->nextNonSpaceChar();

            while (this->lastCharRead != '}') {
                PairElement* pair = this->parsePairElement();
                result->addPair(*pair);
                delete pair;

                if(this->file->eof()) {
                    this->throwParsingException("Unexpected end of file, missing }");
                }
            }

            this->nextNonSpaceChar();

            //std::cout << "DEBUG: parseObject end" << std::endl;
            return result;
        }

        void AbilityParser::nextNonSpaceChar()
        {
            readChar();
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
            this->file->read(&(this->lastCharRead), 1);
            //(*this->file) >> this->lastCharRead;
            //std::cout << "DEBUG: read " << this->lastCharRead << " "
            //          << (unsigned short) this->lastCharRead << " "
            //          << this->file->eof() << std::endl;

            if(this->file->eof()) {
                return;
            }

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
