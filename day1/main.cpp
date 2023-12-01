#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

std::unordered_map<std::string, std::string> letters = {
    {"one", "1"},
    {"two", "2"},
    {"three", "3"},
    {"four", "4"},
    {"five", "5"},
    {"six", "6"},
    {"seven", "7"},
    {"eight", "8"},
    {"nine", "9"}
};

std::vector<std::string> digits {
    {"1"},
    {"2"},
    {"3"},
    {"4"},
    {"5"},
    {"6"},
    {"7"},
    {"8"},
    {"9"},
    {"one"},
    {"two"},
    {"three"},
    {"four"},
    {"five"},
    {"six"},
    {"seven"},
    {"eight"},
    {"nine"}
};

/* read input file to string */
std::string get_input(const std::string &filepath) {
    std::ifstream file(filepath);

    if(!file.is_open()) {
        throw std::runtime_error("Failed to open input file");
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

int get_calibration(const std::string &line) {
    std::string digit;
    std::size_t low_pos = std::string::npos;
    std::size_t max_pos = std::string::npos;

    std::size_t pos;
    std::size_t rpos;

    std::string low;
    std::string high;

    /* find first and last digit in line */
    for (auto &i: digits) {
        pos = line.find(i);
        rpos = line.rfind(i);

        if (pos < low_pos || low_pos == std::string::npos) {
            low_pos = pos;
            low = i;
        }

        if (rpos != std::string::npos) {
            if (rpos > max_pos  || max_pos == std::string::npos) {
                max_pos = rpos;
                high = i;
            }
        } 
    }


    /* convert to int */
    if (low.length() > 1) {
       low = letters[low]; 
    }

    if (high.length() > 1) {
        high = letters[high];
    }

    digit = low + high;

    return std::stoi(digit); 
}

int main() {
    std::string input;
    int calibration = 0;

    /* try reading the input */
    try {
        input = get_input("./test_input");
    } catch (std::exception &e) {
        std::cout << "Error occured: " << e.what() << std::endl;
        return 1;
    }

    /* read input line by line */
    std::istringstream f(input);
    std::string line;
    while(std::getline(f, line)) {
        /* calculate the calibration for every line */
        int line_calibration = get_calibration(line);

        std::cout << line << " CL = " << line_calibration << std::endl;

        calibration += line_calibration;
    }

    std::cout << "Calibration = " << calibration << std::endl;

    return 0;
}