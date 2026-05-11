#include "TugOfWarBar.h"
#include <iostream>
#include <string>
#include <iomanip>

TugOfWarBar::TugOfWarBar() : position_(0) {
}

void TugOfWarBar::applyPull(int direction, int strength) {
    position_ += direction * strength;
    if (position_ >  MAX_POSITION) position_ =  MAX_POSITION;
    if (position_ < -MAX_POSITION) position_ = -MAX_POSITION;
}

void TugOfWarBar::applyPenalty(int direction, int penaltyStrength) {
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

void TugOfWarBar::drawRope() const {
    const int totalWidth = 21;
    int knotIndex = position_ + MAX_POSITION;  // map -10..+10 to 0..20

    std::cout << "  |";
    for (int i = 0; i < totalWidth; ++i) {
        std::cout << (i == knotIndex ? 'O' : '~');
    }
    std::cout << "|  \n";
}

void TugOfWarBar::display(const std::string& player1Name,
                          const std::string& player2Name) const {
                              // Determine lean direction based on position
                              // Player 2 is on the left, Player 1 is on the right
                              // Positive position = Player 1 winning = Player 2 being dragged right
                              // Negative position = Player 2 winning = Player 1 being dragged left

                              // Stick figure rows - change posture based on who is winning
                              std::string p2_head, p2_body, p2_legs;
                              std::string p1_head, p1_body, p1_legs;

                              if (position_ > 3) {
                                  // Player 1 winning - P2 dragged hard right, P1 pulling strongly
                                  p2_head = "  \\o  ";   // P2 leaning right (being dragged)
                                  p2_body = "  /|  ";
                                  p2_legs = "  / \\ ";

                                  p1_head = "  o/  ";   // P1 leaning back pulling
                                  p1_body = "  |\\  ";
                                  p1_legs = " /|   ";

                              } else if (position_ < -3) {
                                  // Player 2 winning - P1 dragged hard left, P2 pulling strongly
                                  p2_head = "  \\o  ";   // P2 leaning back pulling
                                  p2_body = "  /|  ";
                                  p2_legs = "   |\\  ";

                                  p1_head = "  o/  ";   // P1 leaning left (being dragged)
                                  p1_body = "  /|  ";
                                  p1_legs = "  /|  ";

                              } else {
                                  // Roughly even - both standing and pulling
                                  p2_head = "  \\o  ";
                                  p2_body = "  /|  ";
                                  p2_legs = "  /\\  ";

                                  p1_head = "  o/  ";
                                  p1_body = "  |\\  ";
                                  p1_legs = "  /\\  ";
                              }

                              // Truncate names if too long
                              std::string p2 = player2Name.length() > 10 ? player2Name.substr(0, 10) : player2Name;
                              std::string p1 = player1Name.length() > 10 ? player1Name.substr(0, 10) : player1Name;

                              std::cout << "\n";
                              std::cout << "  +---------------------------------------------------------+\n";
                              std::cout << "  |                  MATH TUG OF WAR                       |\n";
                              std::cout << "  +---------------------------------------------------------+\n";

                              // Row 1: names
                              std::cout << "  " << std::left << std::setw(12) << p2
                              << "                               "
                              << std::right << std::setw(12) << p1 << "\n";

                              // Row 2: heads
                              std::cout << "  " << p2_head
                              << "                           "
                              << p1_head << "\n";

                              // Row 3: rope
                              drawRope();

                              // Row 4: bodies
                              std::cout << "  " << p2_body
                              << "                           "
                              << p1_body << "\n";

                              // Row 5: legs
                              std::cout << "  " << p2_legs
                              << "                           "
                              << p1_legs << "\n";

                              // Row 6: position indicator
                              std::cout << "\n";
                              if (position_ > 0) {
                                  std::cout << "  >>> " << p1 << " is winning! (+" << position_ << ")\n";
                              } else if (position_ < 0) {
                                  std::cout << "  >>> " << p2 << " is winning! (" << position_ << ")\n";
                              } else {
                                  std::cout << "  >>> Dead even! Fight for it!\n";
                              }
                              std::cout << "  +---------------------------------------------------------+\n\n";
                          }

                          void TugOfWarBar::reset() {
                              position_ = 0;
                          }
