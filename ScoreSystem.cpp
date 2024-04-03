#include "ScoreSystem.h"

int ScoreSystem::score = 0;

void ScoreSystem::AddScore(int points) {
    score += points;
}

int ScoreSystem::GetScore() {
    return score;
}

void ScoreSystem::ResetScore() {
    score = 0;
}