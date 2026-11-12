#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Figure.hpp"
#include "InputMethod.hpp"
#include "InputFactory.hpp"
#include "FigureFactory.hpp"
#include "StringConvertible.hpp"

void print_figures(const std::vector<std::unique_ptr<Figure>>& figures, std::ostream& output) {
    for (std::size_t i = 0; i < figures.size(); ++i) {
        const auto* string_convertible = dynamic_cast<const String_Convertible*>(figures[i].get());

        if (string_convertible == nullptr) {
            throw std::runtime_error("Figure does not implement StringConvertible");
        }

        output << string_convertible->to_string() << '\n';
    }
}

std::size_t read_index(std::size_t figures_count) {
    std::string line;
    std::size_t index;

    std::cout << "Enter figure index: ";

    if (!std::getline(std::cin, line)) {
        throw std::runtime_error("Failed to read index");
    }

    std::istringstream input(line);

    if (!(input >> index) || (input >> std::ws && !input.eof())) {
        throw std::invalid_argument("Invalid index");
    }

    if (index >= figures_count) {
        throw std::out_of_range("Figure index does not exist");
    }

    return index;
}

std::size_t read_figure_count() {
    std::string line;
    std::size_t count;

    std::cout << "How many figures do you want to read? ";

    if (!std::getline(std::cin, line)) {
        throw std::runtime_error("Failed to read figure count");
    }

    std::istringstream input(line);

    if (!(input >> count) || (input >> std::ws && !input.eof())) {
        throw std::invalid_argument("Invalid figure count");
    }

    return count;
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
        std::cout << "Choose input method and write it down:\n";
        std::cout << "1.Random\n2.STDIN3.\nFile <filename>\n";

        std::string input_string;

        if (!std::getline(std::cin, input_string)) {
            throw std::runtime_error("Failed to read input method");
        }

        InputFactory input_factory;
        auto input_method =  input_factory.create_input_from_string(input_string);

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

            std::string command;

            if (!std::getline(std::cin, command)) {
                break;
            }

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
            }else if (command == "5") {
                break;
            }
            else {
                std::cout << "Unknown command.\n";
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