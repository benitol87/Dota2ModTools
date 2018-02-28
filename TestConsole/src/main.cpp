#include <QCoreApplication>
#include <iostream>

#include "stringelement.h"
#include "pairelement.h"
#include "objectelement.h"
#include "valueelement.h"
#include "abilityparser.h"

using dota2::parser::AbilityParser;
using dota2::parser::ObjectElement;
using dota2::parser::PairElement;
using dota2::parser::StringElement;
using dota2::parser::ValueElement;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AbilityParser parser;

    try {
        std::vector<PairElement> fileContent = parser.parseFile(
            "../snippets/simple1.txt");

        std::cout << "START" << std::endl;
        for(auto& pair: fileContent) {
            std::cout << "PAIR: " << std::endl;
            std::cout << pair.toString() << std::endl;
        }
        std::cout << "END" << std::endl;
    } catch(std::exception* e) {
        std::cout << "Exception raised" << std::endl;
    }



    return a.exec();
}
