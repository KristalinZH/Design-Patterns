#include <vector>
#include <memory>
#include <limits>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Figure.hpp"
#include "InputMethod.hpp"
#include "InputFactory.hpp"
#include "FigureFactory.hpp"
#include "StringConvertible.hpp"


std::string read_input_method() {
    std::cout << "\nChoose input method:\n";
    std::cout << "1. Random\n";
    std::cout << "2. STDIN\n";
    std::cout << "3. File\n";
    std::cout << "Your choice: ";

    std::string choice;

    if (!std::getline(std::cin, choice)) {
        throw std::runtime_error("Failed to read input method");
    }

    if (choice == "1") {
        return "Random";
    }

    if (choice == "2") {
        return "STDIN";
    }

    if (choice == "3") {
        std::string filename;

        std::cout << "Enter input filename: ";

        if (!std::getline(std::cin, filename) || filename.empty()) {
            throw std::invalid_argument("Invalid filename");
        }

        return "File " + filename;
    }

    throw std::invalid_argument("Invalid input method choice");
}


void print_figures(const std::vector<std::unique_ptr<Figure>>& figures, std::ostream& output) {
    for (const auto& figure : figures) {
        const auto* string_convertible =
            dynamic_cast<const String_Convertible*>(figure.get());

        if (string_convertible == nullptr) {
            throw std::runtime_error(
                "Figure does not implement StringConvertible"
            );
        }

        output << string_convertible->to_string() << '\n';
    }
}


std::size_t read_index(std::size_t figures_count) {
    std::string line;

    std::cout << "Enter figure index: ";

    if (!std::getline(std::cin, line)) {
        throw std::runtime_error("Failed to read index");
    }

    std::istringstream input(line);
    long long index;

    if (!(input >> index) || (input >> std::ws && !input.eof())) {
        throw std::invalid_argument("Invalid index");
    }

    if (index <= 0) {
        throw std::invalid_argument("Index cannot be negative or 0");
    }

    if (static_cast<unsigned long long>(index) > figures_count) {
        throw std::out_of_range("Figure index does not exist");
    }

    return static_cast<std::size_t>(index - 1);
}


std::size_t read_figure_count() {
    std::string line;

    std::cout << "How many figures do you want to read? ";

    if (!std::getline(std::cin, line)) {
        throw std::runtime_error("Failed to read figure count");
    }

    std::istringstream input(line);
    long long count;

    if (!(input >> count) || (input >> std::ws && !input.eof())) {
        throw std::invalid_argument("Invalid figure count");
    }

    if (count < 0) {
        throw std::invalid_argument("Figure count cannot be negative");
    }

    if (static_cast<unsigned long long>(count) >
        std::numeric_limits<std::size_t>::max()) {
        throw std::out_of_range("Figure count is too large");
    }

    return static_cast<std::size_t>(count);
}


void save_figures(const std::vector<std::unique_ptr<Figure>>& figures) {
    std::string filename;

    std::cout << "Enter output filename: ";

    if (!std::getline(std::cin, filename) || filename.empty()) {
        throw std::invalid_argument("Invalid filename");
    }

    std::ofstream output(filename);

    if (!output.is_open()) {
        throw std::runtime_error("Failed to open output file: " + filename);
    }

    print_figures(figures, output);

    if (!output) {
        throw std::runtime_error("Failed to write figures to file");
    }

    std::cout << "Figures saved successfully.\n";
}


int main() {
    try {
        const std::string input_string = read_input_method();

        InputFactory input_factory;

        auto input_method = input_factory.create_input_from_string(input_string);

        auto figure_factory = input_method->create_factory();

        const std::size_t count = read_figure_count();

        std::vector<std::unique_ptr<Figure>> figures;
        figures.reserve(count);

        for (std::size_t i = 0; i < count; ++i) {
            std::cout << "Reading figure " << i + 1 << " of " << count << "...\n";

            figures.push_back(figure_factory->create());
        }

        std::cout << "\nSuccessfully read " << figures.size() << " figures.\n";

        while (true) {
            std::cout << "\n========== MENU ==========\n";
            std::cout << "1. List figures\n";
            std::cout << "2. Clone figure\n";
            std::cout << "3. Delete figure\n";
            std::cout << "4. Save figures to file\n";
            std::cout << "5. Exit\n";
            std::cout << "Your choice: ";

            std::string command;

            if (!std::getline(std::cin, command)) {
                break;
            }

            try {
                if (command == "1") {
                    if (figures.empty()) {
                        std::cout << "There are no figures.\n";
                    } else {
                        print_figures(figures, std::cout);
                    }
                }
                else if (command == "2") {
                    if (figures.empty()) {
                        std::cout << "There are no figures to clone.\n";
                        continue;
                    }

                    const std::size_t index = read_index(figures.size());

                    figures.push_back(figures[index]->clone());

                    std::cout << "Figure cloned successfully.\n";
                }
                else if (command == "3") {
                    if (figures.empty()) {
                        std::cout << "There are no figures to delete.\n";
                        continue;
                    }

                    const std::size_t index = read_index(figures.size());

                    figures.erase(figures.begin() + index);

                    std::cout << "Figure deleted successfully.\n";
                }
                else if (command == "4") {
                    save_figures(figures);
                }
                else if (command == "5") {
                    break;
                }
                else {
                    std::cout << "Unknown command.\n";
                }
            }
            catch (const std::exception& exception) {
                std::cerr << "Error: " << exception.what() << '\n';

                if (std::cin.eof()) {
                    break;
                }
            }
        }

        std::cout << "Goodbye!\n";
    }
    catch (const std::exception& exception) {
        std::cerr << "Error: " << exception.what() << '\n';
        return 1;
    }

    return 0;
}
