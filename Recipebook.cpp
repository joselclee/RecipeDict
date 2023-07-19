#include "BST.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void displayRecipes(const BSTNode<Recipe>* node) {
    if (node == nullptr) {
        return;
    }

    displayRecipes(node->left);

    std::cout << "Name: " << node->data.Name << std::endl;
    std::cout << "------------------------------\n";

    displayRecipes(node->right);
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void readRecipes(const std::string& filename, BST<Recipe>& recipeBook) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::string name, ingredients, instructions;

        // Read the name
        name = trim(line);

        // Read the ingredients
        std::ostringstream ingredientsStream;
        while (std::getline(file, line) && !line.empty()) {
            ingredientsStream << trim(line) << "\n";
        }
        ingredients = ingredientsStream.str();

        // Read the instructions
        std::ostringstream instructionsStream;
        while (std::getline(file, line) && !line.empty()) {
            instructionsStream << trim(line) << "\n";
        }
        instructions = instructionsStream.str();

        Recipe recipe;
        recipe.Name = name;
        recipe.Ingredients = ingredients;
        recipe.Instructions = instructions;
        recipeBook.insert(recipe);
    }
    file.close();
}

void saveRecipes(const std::string& filename, const BSTNode<Recipe>* node) {
	std::ofstream file(filename, std::ios::app);

	if (!file) {
		std::cerr << "Failed to open file for saving recipes: " << filename << std::endl;
		return;
	}

	if (node == nullptr) {
		return;
	}

	saveRecipes(filename, node->left);

	file << node->data.Name << std::endl;
	file << node->data.Ingredients << std::endl;
	file << node->data.Instructions << std::endl;
	file << "\n";

	saveRecipes(filename, node->right);

	file.close();
}

int main() {
    BST<Recipe> RecipeList;
    char selection;
    std::string item;

    readRecipes("RecipeBook.txt", RecipeList);

    do {
        std::cout << "Lee Recipe Book!" << std::endl
            << "------------------------------" << std::endl
            << "Options: " << std::endl
            << "'s' | search\n"
            << "'l' | view list\n"
            << "'a' | add a recipe\n"
            << "'q' | quit\n"
            << "------------------------------" << std::endl;

        std::cin >> selection;
        std::cout << std::endl;

        if (selection == 's' || selection == 'S') {
            std::cout << "Name: \n";
            std::cin.ignore();
            std::getline(std::cin, item);

            if (RecipeList.search(item)) {
                std::cout << "Recipe found:\n";
                std::cout << RecipeList.getRoot()->data.Name << std::endl;
                std::cout << RecipeList.getRoot()->data.Ingredients << std::endl;
                std::cout << RecipeList.getRoot()->data.Instructions << std::endl;
            }
            else {
                std::cout << "Recipe not found.\n";
            }
        }
        else if (selection == 'l' || selection == 'L') {
            std::cout << "Recipe List" << std::endl;
            displayRecipes(RecipeList.getRoot());
        }
		else if (selection == 'a' || selection == 'A') {
			Recipe newRep;
			std::cout << "What is the name of the recipe?\n";
			std::cin.ignore();
			std::getline(std::cin, newRep.Name);
			std::cout << "Please list the ingredients, separated by a comma.\n";
			std::cin.ignore();
			std::getline(std::cin, newRep.Ingredients);
			std::cout << "Please write out the instructions.\n";
			std::cin.ignore();
			std::getline(std::cin, newRep.Instructions);

			RecipeList.insert(newRep);
            saveRecipes("RecipeBook.txt", RecipeList.getRoot());
		}
		else if (selection == 'q' || selection == 'Q') {
			std::cout << "Goodbye." << std::endl;
		}
		else {
			std::cout << "Error." << std::endl;
		}

    } while (selection != 'q' && selection != 'Q');

    return 0;
}