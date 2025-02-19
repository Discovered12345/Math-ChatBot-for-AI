#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <regex>

// Function to evaluate basic arithmetic expressions (addition, subtraction, multiplication, division)
double evaluate_expression(const std::string& expr) {
    std::istringstream ss(expr);
    double result = 0.0;
    double current_number = 0.0;
    char operation = '+';
    
    while (ss >> current_number) {
        if (operation == '+') {
            result += current_number;
        } else if (operation == '-') {
            result -= current_number;
        } else if (operation == '*') {
            result *= current_number;
        } else if (operation == '/') {
            if (current_number != 0) {
                result /= current_number;
            } else {
                std::cout << "Error: Division by zero is not allowed!" << std::endl;
                return 0;
            }
        }
        
        ss >> operation;  // get next operation (e.g., '+', '-', etc.)
    }
    
    return result;
}

// Function to handle temperature conversions (Celsius to Fahrenheit and vice versa)
std::string convert_temperature(const std::string& problem) {
    if (problem.find("celsius to fahrenheit") != std::string::npos) {
        double celsius;
        std::sscanf(problem.c_str(), "celsius to fahrenheit %lf", &celsius);
        double fahrenheit = (celsius * 9/5) + 32;
        return std::to_string(celsius) + " degrees Celsius is equal to " + std::to_string(fahrenheit) + " degrees Fahrenheit.";
    }
    if (problem.find("fahrenheit to celsius") != std::string::npos) {
        double fahrenheit;
        std::sscanf(problem.c_str(), "fahrenheit to celsius %lf", &fahrenheit);
        double celsius = (fahrenheit - 32) * 5/9;
        return std::to_string(fahrenheit) + " degrees Fahrenheit is equal to " + std::to_string(celsius) + " degrees Celsius.";
    }
    return "Sorry, I couldn't understand the temperature conversion.";
}

// Function to calculate angular speed
std::string calculate_angular_speed(const std::string& problem) {
    if (problem.find("angular speed") != std::string::npos) {
        double angular_distance, time;
        std::sscanf(problem.c_str(), "angular speed %lf %lf", &angular_distance, &time);
        double angular_speed = angular_distance / time;
        return "The angular speed is: " + std::to_string(angular_speed) + " radians per second.";
    }
    return "Sorry, I couldn't understand the angular speed calculation.";
}

// Function to calculate linear speed
std::string calculate_linear_speed(const std::string& problem) {
    if (problem.find("linear speed") != std::string::npos) {
        double radius, angular_speed;
        std::sscanf(problem.c_str(), "linear speed %lf %lf", &radius, &angular_speed);
        double linear_speed = radius * angular_speed;
        return "The linear speed is: " + std::to_string(linear_speed) + " meters per second.";
    }
    return "Sorry, I couldn't understand the linear speed calculation.";
}

// Function to calculate area (for various shapes)
std::string calculate_area(const std::string& problem) {
    if (problem.find("area of circle") != std::string::npos) {
        double radius;
        std::sscanf(problem.c_str(), "area of circle %lf", &radius);
        double area = M_PI * radius * radius;
        return "The area of the circle is: " + std::to_string(area) + " square units.";
    }
    if (problem.find("area of rectangle") != std::string::npos) {
        double length, width;
        std::sscanf(problem.c_str(), "area of rectangle %lf %lf", &length, &width);
        double area = length * width;
        return "The area of the rectangle is: " + std::to_string(area) + " square units.";
    }
    if (problem.find("area of square") != std::string::npos) {
        double side;
        std::sscanf(problem.c_str(), "area of square %lf", &side);
        double area = side * side;
        return "The area of the square is: " + std::to_string(area) + " square units.";
    }
    return "Sorry, I didn't understand the area calculation.";
}

// Function to calculate volume and surface area (for various shapes)
std::string calculate_volume_surface_area(const std::string& problem) {
    if (problem.find("volume of sphere") != std::string::npos) {
        double radius;
        std::sscanf(problem.c_str(), "volume of sphere %lf", &radius);
        double volume = (4.0 / 3.0) * M_PI * std::pow(radius, 3);
        double surface_area = 4 * M_PI * radius * radius;
        return "The volume of the sphere is: " + std::to_string(volume) + " cubic units, and the surface area is: " + std::to_string(surface_area) + " square units.";
    }
    if (problem.find("volume of cylinder") != std::string::npos) {
        double radius, height;
        std::sscanf(problem.c_str(), "volume of cylinder %lf %lf", &radius, &height);
        double volume = M_PI * radius * radius * height;
        double surface_area = 2 * M_PI * radius * (radius + height);
        return "The volume of the cylinder is: " + std::to_string(volume) + " cubic units, and the surface area is: " + std::to_string(surface_area) + " square units.";
    }
    return "Sorry, I didn't understand the volume or surface area calculation.";
}

// Function to generate chatbot's response based on the problem type
std::string generate_response(const std::string& user_input) {
    // Convert input to lowercase for easier matching
    std::string lower_input = user_input;
    for (auto& c : lower_input) {
        c = tolower(c);
    }

    // If the user says "hello"
    if (lower_input == "hello") {
        return "Hello! How can I help you?";
    }

    // Handle different types of problems
    if (lower_input.find("celsius to fahrenheit") != std::string::npos ||
        lower_input.find("fahrenheit to celsius") != std::string::npos) {
        return convert_temperature(user_input);
    }

    if (lower_input.find("angular speed") != std::string::npos) {
        return calculate_angular_speed(user_input);
    }

    if (lower_input.find("linear speed") != std::string::npos) {
        return calculate_linear_speed(user_input);
    }

    if (lower_input.find("area") != std::string::npos) {
        return calculate_area(user_input);
    }

    if (lower_input.find("volume") != std::string::npos ||
        lower_input.find("surface area") != std::string::npos) {
        return calculate_volume_surface_area(user_input);
    }

    // Otherwise, treat as a regular math expression
    if (lower_input.find("what is") != std::string::npos || lower_input.find("calculate") != std::string::npos) {
        std::string math_expr = user_input.substr(user_input.find_first_of("0123456789"));
        try {
            double result = evaluate_expression(math_expr);
            return "The result is: " + std::to_string(result);
        } catch (...) {
            return "Sorry, I couldn't understand that math expression.";
        }
    }

    // Default response for when the chatbot doesn't understand the input
    return "That's an interesting topic! Tell me more!";
}

// Function to handle common typos
std::string correct_typo(const std::string& input) {
    std::string corrected = input;

    // Common typo corrections (extend as needed)
    corrected = std::regex_replace(corrected, std::regex("waat"), "what");
    corrected = std::regex_replace(corrected, std::regex("wat"), "what");
    corrected = std::regex_replace(corrected, std::regex("wat is"), "what is");
    
    return corrected;
}

int main() {
    std::string user_input;
    std::string user_name;

    // Start conversation
    std::cout << "Chatbot: Hello! How can I help you with your math today?\n";
    std::cout << "Chatbot: What's your name?\n";
    std::getline(std::cin, user_name);  // Get user's name
    std::cout << "Chatbot: Nice to meet you, " << user_name << "! How can I assist you today?\n";
    
    while (true) {
        std::cout << user_name << ": ";
        std::getline(std::cin, user_input); // Get the user's input
        
        // Correct common typos
        user_input = correct_typo(user_input);

        // Check for exit condition
        if (user_input == "bye") {
            std::cout << "Chatbot: Goodbye " << user_name << "! It was nice talking to you. Take care!" << std::endl;
            break;
        }
        else if (user_input == "goodbye") {
            std::cout << "Chatbot: Goodbye " << user_name << "! It was nice talking to you. Take care!" << std::endl;
            break;
        }

        // Generate and print the chatbot's response
        std::cout << "Chatbot: " << generate_response(user_input) << std::endl;

        // Ask if they need help with anything else
        std::cout << "Chatbot: Do you need help with anything else (Y/N)?\n";
        std::string response;
        std::getline(std::cin, response);

        if (response == "N" || response == "n") {
            std::cout << "Chatbot: Ok, goodbye!" << std::endl;
            break;
        } else if (response == "Y" || response == "y") {
            std::cout << "Chatbot: Great! What can I help you with next?\n";
        } else {
            std::cout << "Chatbot: I didn't quite understand that. Let's continue! What math problem would you like help with?\n";
        }
    }

    return 0;
}
