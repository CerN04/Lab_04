#include "Array.hpp"
#include "Figure.hpp"
#include "Octagon.hpp"
#include "Square.hpp"
#include "Triangle.hpp"

#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <string>


int main() {
    try {
        std::cout << "Welcome to Lab4OOPTemplateFigureWorkerProgramm_V1!" << std::endl;
        Array<std::shared_ptr<Figure<double>>> sp;
        std::string menu = "0. Exit\n1. Add triangle\n2. Add square\n3. Add oktagon\n4. Print all figures\n5. "
                           "Print total area\n6. Delete figure\n7. Menu";
        int choice = 0;
        std::cout << "Select an action:\n" << menu << std::endl;
        std::cin >> choice;
        while (choice != 0) {
            switch (choice) {
            case 1: {
                auto triang = std::make_shared<Triangle<double>>();
                std::cout << "Please, enter 3 vertices for the triangle:" << std::endl;
                std::cin >> *triang;
                sp.PushItem(triang);
                std::cout << "Added a triangle" << std::endl;
                break;
            }
            case 2: {
                auto sq = std::make_shared<Square<double>>();
                std::cout << "Please, enter 4 vertices for the square:" << std::endl;
                std::cin >> *sq;
                sp.PushItem(sq);
                std::cout << "Added a square" << std::endl;
                break;
            }
            case 3: {
                auto oct = std::make_shared<Octagon<double>>();
                std::cout << "Please, enter 8 vertices for the octagon:" << std::endl;
                std::cin >> *oct;
                sp.PushItem(oct);
                std::cout << "Added a octagone" << std::endl;
                break;
            }
            case 4: {
                std::cout << "All figures:\n";
                for (size_t i = 0; i < sp.GetSize(); ++i) {
                    std::cout << "Figure " << i + 1 << "\n";
                    sp[i]->print(std::cout);
                    std::cout << "Geometric center - " << (sp[i])->geomCenter();
                    std::cout << "; Area - " << static_cast<double>(*sp[i]);
                    std::cout << std::endl;
                }
                break;
            }
            case 5: {
                double total_area = 0.0;
                for (size_t i = 0; i < sp.GetSize(); ++i) {
                    total_area += static_cast<double>(*sp[i]);
                }
                std::cout << "Total area of all figures: " << total_area << std::endl;
                break;
            }
            case 6: {
                std::cout << "Enter index of the figure to delete: ";
                size_t ind;
                std::cin >> ind;
                if (ind > 0 && ind <= sp.GetSize()) {
                    sp.DeleteItem(ind - 1);
                    std::cout << "Figure at index " << ind << " deleted." << std::endl;
                } else {
                    std::cout << "Invalid index." << std::endl;
                }
                break;
            }
            case 7: {
                std::cout << menu << std::endl;
                break;
            }
            }
            std::cout << "\nSelect an action: " << std::endl;
            std::cin >> choice;
        }
        std::cout << "Bye!" << std::endl;
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}