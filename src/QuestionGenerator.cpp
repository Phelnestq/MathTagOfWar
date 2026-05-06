#include "QuestionGenerator.h"
#include <cstdlib>  // for rand()
#include <string>

QuestionGenerator::QuestionGenerator() {
}

Question QuestionGenerator::generate(Difficulty difficulty) const {
    switch (difficulty) {
        case Difficulty::PRIMARY_EASY:   return generatePrimaryEasy();
        case Difficulty::PRIMARY_HARD:   return generatePrimaryHard();
        case Difficulty::SECONDARY_EASY: return generateSecondaryEasy();
        case Difficulty::SECONDARY_HARD: return generateSecondaryHard();
    }
    return generatePrimaryEasy();
}

// Addition and subtraction with small numbers (1–20)
Question QuestionGenerator::generatePrimaryEasy() const {
    int a = rand() % 10 + 1;
    int b = rand() % 10 + 1;
    int op = rand() % 2;  // 0 = add, 1 = subtract

    if (op == 0) {
        return Question(std::to_string(a) + " + " + std::to_string(b) + " = ?",
                        static_cast<double>(a + b),
                        Difficulty::PRIMARY_EASY);
    } else {
        if (a < b) std::swap(a, b);  // keep result non-negative
        return Question(std::to_string(a) + " - " + std::to_string(b) + " = ?",
                        static_cast<double>(a - b),
                        Difficulty::PRIMARY_EASY);
    }
}

// Multiplication and division with small numbers (2–12)
Question QuestionGenerator::generatePrimaryHard() const {
    int a = rand() % 11 + 2;
    int b = rand() % 11 + 2;
    int op = rand() % 2;  // 0 = multiply, 1 = divide

    if (op == 0) {
        return Question(std::to_string(a) + " x " + std::to_string(b) + " = ?",
                        static_cast<double>(a * b),
                        Difficulty::PRIMARY_HARD);
    } else {
        int product = a * b;  // divide product back to guarantee whole number
        return Question(std::to_string(product) + " / " + std::to_string(a) + " = ?",
                        static_cast<double>(b),
                        Difficulty::PRIMARY_HARD);
    }
}

// TODO (Phase 2): implement algebra and fractions
Question QuestionGenerator::generateSecondaryEasy() const {
    return Question("5x = 25, x = ?", 5.0, Difficulty::SECONDARY_EASY);
}

// TODO (Phase 2): implement harder algebra and geometry
Question QuestionGenerator::generateSecondaryHard() const {
    return Question("2x^2 = 18, x = ?", 3.0, Difficulty::SECONDARY_HARD);
}
