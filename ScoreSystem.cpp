#include "ScoreSystem.h" // ScoreSystem header file

int ScoreSystem::score = 0; // Initialize score to 0

void ScoreSystem::AddScore(int points) { // Add points to score
    score += points; 
}

int ScoreSystem::GetScore() { // Return score
    return score;
}

void ScoreSystem::ResetScore() { // Reset score to 0
    score = 0;
}