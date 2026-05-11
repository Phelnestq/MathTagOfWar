#include "Game.h"
#include "ComputerPlayer.h"
#include <iostream>
#include <chrono>

Game::Game(std::unique_ptr<Player> player1,
           std::unique_ptr<Player> player2,
           Difficulty difficulty)
: player1_(std::move(player1)),
player2_(std::move(player2)),
difficulty_(difficulty) {
}

void Game::run() {
    std::cout << "=== Math Tug of War ===\n";
    std::cout << player1_->getName() << " vs " << player2_->getName() << "\n\n";

    while (!tugBar_.isGameOver()) {
        playSimultaneousRound();
        displayStatus();
    }

    int winner = tugBar_.getWinner();
    if (winner == 1) {
        scoreTracker_.recordWin(1);
        std::cout << player1_->getName() << " wins the round!\n";
    } else {
        scoreTracker_.recordWin(2);
        std::cout << player2_->getName() << " wins the round!\n";
    }

    scoreTracker_.display();
}

void Game::playSimultaneousRound() {
    Question q = questionGen_.generate(difficulty_);

    std::cout << "\nQuestion: " << q.getProblemText() << "\n";

    auto questionStart = std::chrono::steady_clock::now();
    double questionStartSecs =
    std::chrono::duration<double>(questionStart.time_since_epoch()).count();

    std::cout << player1_->getName() << ", enter your answer: ";
    RoundResult r1 = collectAnswer(*player1_, q, questionStartSecs);

    std::cout << player2_->getName() << ", enter your answer: ";
    RoundResult r2 = collectAnswer(*player2_, q, questionStartSecs);

    const int penalty = q.getBasePoints() / 4;

    if (r1.correct) r1.pull = calculatePull(q.getBasePoints(), r1.timeSecs);
    if (r2.correct) r2.pull = calculatePull(q.getBasePoints(), r2.timeSecs);

    if (r1.correct && r2.correct) {
        if (r1.timeSecs <= r2.timeSecs) {
            tugBar_.applyPull(+1, r1.pull);
            player1_->addScore(r1.pull);
            std::cout << player1_->getName() << " was faster! Pull strength: " << r1.pull << "\n";
        } else {
            tugBar_.applyPull(-1, r2.pull);
            player2_->addScore(r2.pull);
            std::cout << player2_->getName() << " was faster! Pull strength: " << r2.pull << "\n";
        }

    } else if (r1.correct && !r2.correct) {
        tugBar_.applyPull(+1, r1.pull);
        tugBar_.applyPenalty(-1, penalty);
        player1_->addScore(r1.pull);
        std::cout << player1_->getName() << " correct (pull: " << r1.pull << "). "
        << player2_->getName() << " wrong (penalty: " << penalty << ").\n";
        std::cout << "The answer was " << q.getAnswer() << "\n";

    } else if (!r1.correct && r2.correct) {
        tugBar_.applyPull(-1, r2.pull);
        tugBar_.applyPenalty(+1, penalty);
        player2_->addScore(r2.pull);
        std::cout << player2_->getName() << " correct (pull: " << r2.pull << "). "
        << player1_->getName() << " wrong (penalty: " << penalty << ").\n";
        std::cout << "The answer was " << q.getAnswer() << "\n";

    } else {
        tugBar_.applyPenalty(+1, penalty);
        tugBar_.applyPenalty(-1, penalty);
        std::cout << "Both wrong! Both players take a penalty of " << penalty << ".\n";
        std::cout << "The answer was " << q.getAnswer() << "\n";
    }
}

Game::RoundResult Game::collectAnswer(Player& player, const Question& q,
                                      double questionStartSecs) const {
                                          RoundResult result{};

                                          if (player.isComputer()) {
                                              ComputerPlayer& cp = static_cast<ComputerPlayer&>(player);
                                              result.timeSecs = cp.simulateAnswerTime();
                                              result.answer   = cp.simulateAnswer(q);
                                              std::cout << "(Computer answered: " << result.answer
                                              << " in " << result.timeSecs << "s)\n";
                                          } else {
                                              auto answerTime = std::chrono::steady_clock::now();
                                              std::cin >> result.answer;
                                              auto endTime = std::chrono::steady_clock::now();

                                              double answerStartSecs =
                                              std::chrono::duration<double>(answerTime.time_since_epoch()).count();
                                              double answerEndSecs =
                                              std::chrono::duration<double>(endTime.time_since_epoch()).count();
                                              result.timeSecs = answerEndSecs - questionStartSecs + (answerEndSecs - answerStartSecs);
                                          }

                                          result.correct = q.checkAnswer(result.answer);
                                          result.pull    = 0;
                                          return result;
                                      }

                                      // ONE LINE CHANGED: pass player names to display()
                                      void Game::displayStatus() const {
                                          tugBar_.display(player1_->getName(), player2_->getName());
                                      }

                                      int Game::calculatePull(int basePoints, double answerTimeSeconds) const {
                                          if (answerTimeSeconds <= 0.0) return basePoints;
                                          int pull = static_cast<int>(basePoints / answerTimeSeconds);
                                          return pull < 1 ? 1 : pull;
                                      }
