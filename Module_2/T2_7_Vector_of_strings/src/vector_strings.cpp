#include "vector_strings.hpp"

#include <iostream>
#include <vector>

void Adder(std::vector<std::string>& names) {
    std::string name;
    std::cout<<"Enter a name:"<<std::endl;
//    std::cout<<"    ";
    std::cin>>name;

    names.push_back(name);

    std::cout<<"Number of names in the vector:"<<std::endl;
//    std::cout<<"    "<< names.size() <<std::endl;
    std::cout<< names.size() <<std::endl;
}

void Remover(std::vector<std::string>& names) {
    std::cout<<"Removing the last element:"<<std::endl;
    std::cout<<names[names.size()-1]<<std::endl;
    names.pop_back();
  
}

void Printer(std::vector<std::string>& names) {
    for(unsigned i=0 ; i<names.size() ; i++){
        std::cout<<names[i]<<std::endl;
    }
  
}

void CMDReader() {
    std::string input_command;

    std::vector<std::string> names;

    std::cout<<"Commands: ADD, PRINT, REMOVE, QUIT"<<std::endl;
    std::cout<<"Enter a command"<<std::endl;
//    std::cout<<"    ";
    std::cin >> input_command;

    while(input_command!="QUIT"){

        if(input_command=="ADD"){

            Adder(names);

        } else if(input_command=="PRINT") {

            Printer(names);

        } else if(input_command=="REMOVE") {

            Remover(names);

        } else {
            std::cout << "Wrong command please input again, Commands: ADD, PRINT, REMOVE, QUIT" << std::endl;

        }

        std::cout<<"Enter a command"<<std::endl;
//        std::cout<<"    ";
        std::cin >> input_command;
    }


}
