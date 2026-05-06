#pragma once
#include <memory>
#include "Player.h"
#include "QuestionGenerator.h"
#include "TugOfWarBar.h"
#include "ScoreTracker.h"
#include "Difficulty.h"

// Orchestrates the full game loop.
// Owns the two players via unique_ptr (accepts either Player or ComputerPlayer).
class Game {
public:
    Game(std::unique_ptr<Player> player1,
         std::unique_ptr<Player> player2,
         Difficulty difficulty);

    void run();

private:
    // Holds one player's result for a simultaneous round.
    struct RoundResult {
        double answer;      // the value the player submitted
        double timeSecs;    // seconds from question display to answer
        bool   correct;     // whether the answer passed checkAnswer()
        int    pull;        // calculated pull strength (0 if wrong)
    };

    void playSimultaneousRound();
    RoundResult collectAnswer(Player& player, const Question& q,
                              double questionStartSecs) const;
    void displayStatus() const;

    // Applies the pull strength formula: base_points / answer_time_seconds
    int calculatePull(int basePoints, double answerTimeSeconds) const;

    std::unique_ptr<Player> player1_;
    std::unique_ptr<Player> player2_;
    QuestionGenerator questionGen_;
    TugOfWarBar tugBar_;
    ScoreTracker scoreTracker_;
    Difficulty difficulty_;
};
