#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>

std::unordered_map<std::string, int> load = {
    {"red", 12},
    {"green", 13},
    {"blue", 14}
};

/* read input file to string */
std::vector<std::string> get_input(const std::string &filepath) {
    std::vector<std::string> games;
    std::ifstream file(filepath);

    if(!file.is_open()) {
        throw std::runtime_error("Failed to open input file");
    }

    std::string line;
    while (std::getline(file, line)) {
        games.push_back(line);
    } 

    return games;
}

std::vector<std::pair<std::string, int>> extract_values(const std::string line) {
    std::vector<std::pair<std::string, int>> result;

    /* matches the numbers and colors in the line */
    std::regex pattern(R"(\b(\d+)\s*([a-zA-Z]+)\b)");

    /* to iterate over the whole string */
    auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
    auto end = std::sregex_iterator();

    /* iterate over the matches and put them in the vector */
    for (auto it = begin; it != end; ++it) {
        std::smatch match = *it;
        int number = std::stoi(match[1].str());
        std::string color = match[2].str();
        result.emplace_back(color, number);
    }

    return result;
}

int possible_games_sum(std::vector<std::string> games) {
    int possible_games = 0;
    int id = 0;

    /* check every game */
    for (const auto &i: games) {
        id++;
        /* extract values from the game */
        std::vector<std::pair<std::string, int>> values = extract_values(i);
        bool is_possible = true;

        /* check if any extracted value is bigger then the load */
        for (const auto &pair: values) {
            if (pair.second > load[pair.first]) {
                /* the game is not possible */
                is_possible = false;
                break;
            }
        }

        if (is_possible) {
            std::cout << i << " IS POSSIBLE ID: " << id << std::endl;
            possible_games += id;
        }
    }

    return possible_games;
}

/* PART TWO*/
int minimal_load_needed(std::vector<std::string> games) {
    int power_of_cubes = 0;
    int id = 0;

    /* find max value of each cube by game */ 
    for (const auto &i: games) {
        id++;
        /* extract values from the game */
        std::vector<std::pair<std::string, int>> values = extract_values(i);
        std::unordered_map<std::string, int> minimal_load = {
            {"red", 0},
            {"green", 0},
            {"blue", 0}
        };

        for (const auto &pair: values) {
            if (pair.second > minimal_load[pair.first]) {
                minimal_load[pair.first] = pair.second;
            }
        }

        /* calc the power of the game and sum it up */
        int power = minimal_load["red"] * minimal_load["green"] * minimal_load["blue"];
        std::cout << "Game " << id << " Power: " << power << std::endl;
        power_of_cubes += power;
    }

    return power_of_cubes;
}

int main() {
    std::vector<std::string> games;
    int possible_games = 0;
    int minimal_load = 0;

    /* try reading the input */
    try {
        games = get_input("./input");
    } catch (std::exception &e) {
        std::cout << "Error occured: " << e.what() << std::endl;
        return 1;
    }

    possible_games = possible_games_sum(games);
    minimal_load = minimal_load_needed(games);

    std::cout << "Possible games total: " << possible_games << std::endl;
    std::cout << "Possible games total: " << minimal_load << std::endl;

    return 0;
}