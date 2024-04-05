#pragma once

class ScoreSystem {
public:
    static void AddScore(int points); // Add points to score
    static int GetScore(); // Return score
    static void ResetScore(); // Reset score to 0
private:
    static int score; // Score variable
};