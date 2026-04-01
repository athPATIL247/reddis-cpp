#include "parser.h"
#include <sstream>

std::vector<std::string> Parser::parseRESP(const std::string& input) {
    std::vector<std::string> result;
    std::istringstream stream(input);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.empty()) continue;

        // Ignore RESP markers (*, $)
        if (line[0] == '*' || line[0] == '$') continue;

        // Remove \r if present
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        result.push_back(line);
    }

    return result;
}