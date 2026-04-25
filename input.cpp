// Input.cpp
module Input;

// Validate username: starts with letter, 3–12 alphanumeric characters
bool InputValidator::isValidUsername(const std::string& username) {
    std::regex pattern("^[A-Za-z][A-Za-z0-9]{2,11}$");
    return std::regex_match(username, pattern);
}