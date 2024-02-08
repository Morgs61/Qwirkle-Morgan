#ifndef HIGH_SCORE_MANAGER_H
#define HIGH_SCORE_MANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

class HighScoreManager {
private:
    std::vector<std::pair<std::string, int>> highScores;

public:
    HighScoreManager(const std::string& filename);

    void loadHighScoresFromFile(const std::string& filename);

    void saveHighScoresToFile(const std::string& filename);

    void addHighScore(const std::string& name, int score);

    void displayHighScores() const;
};

#endif // HIGH_SCORE_MANAGER_H
