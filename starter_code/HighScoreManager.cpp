#include "HighScoreManager.h"

HighScoreManager::HighScoreManager(const std::string& filename) {
    loadHighScoresFromFile(filename);
}

void HighScoreManager::loadHighScoresFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string name;
        int score;
        while (file >> name >> score) {
            highScores.push_back(std::make_pair(name, score));
        }
        file.close();
    }
}

void HighScoreManager::saveHighScoresToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : highScores) {
            file << pair.first << " " << pair.second << std::endl;
        }
        file.close();
    }
}

void HighScoreManager::addHighScore(const std::string& name, int score) {
    highScores.push_back(std::make_pair(name, score));
    std::sort(highScores.begin(), highScores.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Sort in descending order of scores
    });
}

void HighScoreManager::displayHighScores() const {
    std::cout << "The highest scores are: " << std::endl;
    for (int i = 0; i < std::min(10, static_cast<int>(highScores.size())); ++i) {
        std::cout << highScores[i].first << ": " << highScores[i].second << std::endl;
    }
}
