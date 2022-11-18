#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

std::string trim(std::string str1);

struct Person {
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;

    void fromString(std::string json) {
        firstName = trim(getValue(json, "firstName"));
        lastName = trim(getValue(json, "lastName"));
        phoneNumber = trim(getValue(json, "phoneNumber"));
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
}

std::string read_JSONfomFile(std::string filename) {
    std::string myjson;
    std::ifstream fin;
    fin.open(filename);
    std::string line;
    if (fin.is_open()) {
        while (!fin.eof()) {
            std::getline(fin, line);
            myjson += line;
            std::cout << myjson << std::endl;
        }
    }
    else {
        std::cout << "Error! can not open the file." << std::endl;
    }
    return myjson;
}

void doIt(int argc, char* argv[]) {
    std::string filename;
    for (int k = 0; k < argc; k++) {
        if (strcmp(argv[k], "-rf") == 0) {
            if (k + 1 < argc) {
                filename = argv[k + 1];
            }
        }
    }
    std::string myjson = read_JSONfomFile(filename);
    Person any_person;
    any_person.fromString(myjson);
    any_person.show();
}

std::string trim(std::string str1) {
    int pos1 = 0, pos2 = str1.size() - 1;
    for (int k = 0; k < str1.size(); k++) {
        if (str1[k] != ' ' || str1[k] != '\n' || str1[k] != '\t') {
            pos1 = k;
            break;
        }
    }
    for (int k = str1.size() - 1; k > pos1; k--) {
        if (str1[k] != ' ') {
            pos2 = k;
            break;
        }
    }
    return str1.substr(pos1, pos2 - pos1 + 1);
}

void test_trim() {
    std::string str1 = "str ing";
    std::string str2 = "string";
    std::string str3 = "";

    // variant 1 не подходит так как удаляет пробелы в середине строки
/*
    for (int k = 0; k < str1.size(); k++) {
        if (str1[k] != ' ' || str1[k] != '\n' || str1[k] != '\t') {
            str3.push_back(str1[k]);
        }
    }
*/
//variant 2
    std::cout << "|" << trim(str1) << "|" << std::endl;
}


int main(int argc, char* argv[]) {        
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    doIt(argc, argv);
}