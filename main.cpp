#include <iostream>
#include <map>
#include <string>
#include <fstream>

#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

struct Recipe {
    std::string recipeName;
    std::string recipe;
    std::string ingredients;
};

void saveCookbook(std::map<std::string, Recipe>& cookbook) {
    std::ofstream file("cookbook.json");
    nlohmann::json j = cookbook;
    file << j;
    file.close();
}

int main() {
    std::map<std::string, Recipe> cookbook;


    std::string userInput, recipeName, recipe, ingredients;
    std::cout << "Enter a recipe name: ";
    std::getline(std::cin, userInput);
    
    cookbook[userInput] ={recipeName, recipe, ingredients};

    
}
