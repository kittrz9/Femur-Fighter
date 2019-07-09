#ifndef PLAYERC_H
#define PLAYERC_H
#include <cmath>

enum dir{UP, RIGHT, LEFT};

class playerC {
    public:
        playerC(float x, float y);
        // X and Y positions
        float xPos;
        float yPos;
        // X and Y velocity
        float xVel = 0;
        float yVel = 0;

        // Health (Unsure if this will be in the final thing)
        int health = 100;

        // Gravity multiplier
        float gravMult = 1;

        bool jumping = false;
        bool dashing = false;
        bool hit = false;
        bool invulnerable = false;

        // Function to update stuff about the player
        // (Velocity, position, etc.)
        void updateStuff();

        void jump();

        void punch(dir d, playerC* hitPlayer, float hitboxXPos, float hitboxYpos);

        void reset(float x, float y);

    private:
};

#endif // PLAYERC_H
