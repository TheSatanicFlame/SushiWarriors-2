#pragma once

class ScoreSystem {
public:
    static void AddScore(int points);
    static int GetScore();
    static void ResetScore();
private:
    static int score;
};