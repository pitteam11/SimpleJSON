#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>


struct Person {
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;

    void fromString(std::string json) {
        firstName = getValue(json, "\"firstName\"");
        lastName = getValue(json, "\"lastName\"");
        phoneNumber = getValue(json, "\"phoneNumber\"");
    }

    std::string getValue(std::string json, std::string name_param) {
        int pos1 = json.find(name_param);
        if (int(pos1) < 0)
            return "";
        pos1 += name_param.length() + 2;
        return json.substr(pos1, json.substr(pos1).find(","));
    }

    void show() {
        std::cout << firstName << " " << lastName << " " << phoneNumber << "\n";
    }
};

void fun1(int argc, char* argv[]) {
    std::cout << "Hello World!\n";
    for (int k = 0; k < argc; ++k) 
        std::cout << argv[k] << std::endl;
}

void fun2(int argc, char* argv[]) {
    for (int k = 0; k < argc; ++k) {
        if (strcmp(argv[k], "--help") == 0) {
            std::cout << "This is help for our proj." << std::endl;
        }
        if (strcmp(argv[k], "--version") == 0) {
            std::cout << "Version: 1.0" << std::endl;
        }
        if (strcmp(argv[k], "--sum") == 0) {
            if ((k + 2) < argc) {
                std::cout << atoi(argv[k + 1]) + atoi(argv[k + 2]);
            }
        }
    }
}


void doJSON1() {
    std::string myjson = "{";
    myjson += "\"firstName\": \"Иван\",";
    myjson += "\"lastName\": \"Иванов\",";
    myjson += "\"phoneNumber\": \"812 123-1234\",";
    myjson += "}";

    std::cout << myjson << std::endl;

    std::string firstName;
    std::string lastName;
    std::string phoneNumber;

    Person any_person;

    firstName = any_person.getValue(myjson, "\"firstName\"");
    lastName = any_person.getValue(myjson, "\"lastName\"");
    phoneNumber = any_person.getValue(myjson, "\"phoneNumber\"");

    std::cout << firstName << " " << lastName << " " << phoneNumber << "\n";


    /*
    std::string name_param = "\"firstName\"";
    int pos1 =  myjson.find(name_param);
    pos1 += name_param.length() + 2;
    //int pos2 = myjson.substr(pos1).find(",") + pos1; // pos1 - лишнее (сначала добавили)
    //std::cout << pos1 << " " << pos2 << std::endl;
    //std::cout << myjson.substr(pos1, pos2 - pos1);  // pos1 - лишнее (потом отняли)
    std::cout << myjson.substr(pos1, myjson.substr(pos1).find(","));
    //std::cout << (int)myjson.find("Tomas") << std::endl;
    */

    //std::cout << myjson.find("\"lastName\"") << std::endl;
    //std::cout << myjson.find("\"phoneNumber\"") << std::endl;
}




int main(int argc, char* argv[]) {   
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);

    std::string myjson;/* = "{";
    myjson += "\"firstName\": \"Иван\",";
    myjson += "\"lastName\": \"Иванов\",";
    myjson += "\"phoneNumber\": \"812 123-1234\",";
    myjson += "}";*/
    std::ifstream fin;
    fin.open("pesrsons.txt");
    if (fin.is_open()) {
        while (!fin.eof()) {
            std::getline(fin, myjson);
            std::cout << myjson << std::endl;
        }
    }
    else {
        std::cout << "Error! can not open the file." << std::endl;
    }

    //std::cout << myjson << std::endl;

    Person any_person;
    any_person.fromString(myjson);
    any_person.show();
}