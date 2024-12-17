#include <iostream>
#include <string>
#include <sstream>

void processSignup(const std::string& input) {
    std::string command, signup;
    std::istringstream iss(input);
    iss >> command >> signup;
    
    if (signup != "signup") {
        std::cout << "Invalid command." << std::endl;
        return;
    }

    std::string username, password;
    std::string word;
    
    while (iss >> word) {
        if (word == "username") {
            iss >> word;
            username = word.substr(1, word.size() - 2); // Remove the quotes
        } else if (word == "password") {
            iss >> word;
            password = word.substr(1, word.size() - 2); // Remove the quotes
        }
    }

    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
}

int main() {
    std::string input;
    std::cout << "Please enter the command: ";
    std::getline(std::cin, input);

    processSignup(input);

    return 0;
}
