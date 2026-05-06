#pragma once

// Tracks the tug-of-war position from -10 (player 2 wins) to +10 (player 1 wins).
// Position starts at 0. Positive pulls favour player 1, negative favour player 2.
class TugOfWarBar {
public:
    TugOfWarBar();

    // Correct answer: move the bar in the player's favour.
    // direction: +1 for player 1, -1 for player 2.
    void applyPull(int direction, int strength);

    // Wrong answer: move the bar against the player (opposite direction).
    // direction: +1 for player 1, -1 for player 2.
    void applyPenalty(int direction, int penaltyStrength);

    int getPosition() const;
    bool isGameOver() const;

    // Returns +1 if player 1 won, -1 if player 2 won, 0 if game is not over.
    int getWinner() const;

    void display() const;
    void reset();

private:
    int position_;
    static const int MAX_POSITION = 10;
};
