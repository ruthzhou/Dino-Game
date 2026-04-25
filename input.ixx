// Input.ixx
export module Input;

import <string>;
import <regex>;

// Utility class to validate user input (username format)
export class InputValidator {
public:
    static bool isValidUsername(const std::string& username);
};