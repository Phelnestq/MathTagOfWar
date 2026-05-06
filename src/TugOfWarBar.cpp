#include "TugOfWarBar.h"
#include <iostream>
#include <string>

TugOfWarBar::TugOfWarBar() : position_(0) {
}

void TugOfWarBar::applyPull(int direction, int strength) {
    position_ += direction * strength;

    // Clamp to [-MAX_POSITION, +MAX_POSITION]
    if (position_ >  MAX_POSITION) position_ =  MAX_POSITION;
    if (position_ < -MAX_POSITION) position_ = -MAX_POSITION;
}

void TugOfWarBar::applyPenalty(int direction, int penaltyStrength) {
    // Penalty pushes opposite to the offending player's direction.
    applyPull(-direction, penaltyStrength);
}

int TugOfWarBar::getPosition() const {
    return position_;
}

bool TugOfWarBar::isGameOver() const {
    return position_ == MAX_POSITION || position_ == -MAX_POSITION;
}

int TugOfWarBar::getWinner() const {
    if (position_ ==  MAX_POSITION) return  1;
    if (position_ == -MAX_POSITION) return -1;
    return 0;
}

// Displays a simple ASCII tug-of-war bar in the console.
// Example:  P2 <====|=========> P1  (rope knot shown as 'O')
void TugOfWarBar::display() const {
    const int totalWidth = 21;  // -10 to +10 = 21 positions
    int knotIndex = position_ + MAX_POSITION;  // map to 0–20

    std::cout << "P2 <";
    for (int i = 0; i < totalWidth; ++i) {
        std::cout << (i == knotIndex ? 'O' : '=');
    }
    std::cout << "> P1\n";
    std::cout << "     Position: " << position_ << "\n";
}

void TugOfWarBar::reset() {
    position_ = 0;
}
