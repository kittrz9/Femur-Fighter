#include "playerC.h"


const float screenW = 1600;
const float screenH = 900;
const float grav = 0.5;
const float friction = 0.5;
const float jumpForce = 10;

playerC::playerC(float x, float y){
    xPos = x;
    yPos = y;
}

void playerC::updateStuff() {
    // Update velocity with gravity
    yVel -= grav*gravMult;

    // Update velocity with friction
    if(xVel > 0)
        xVel -= friction;
    if(xVel < 0)
        xVel += friction;

    // Set x velocity to 0 if it's close to 0
    // so that velocity doesn't get stuck on
    // something like 0.2
    if(xVel < 0.5 && xVel > -0.5)
        xVel = 0;

    // y velocity cap
    if(!hit){
        if(yVel > 10)
            yVel = 10;
        if(yVel < -10*gravMult)
            yVel = -10*gravMult;

    // x velocity cap
        if(!dashing){
            if(xVel > 10)
                xVel = 10;
            if(xVel < -10)
                xVel = -10;
        } else {
            if(xVel > 30)
                xVel = 30;
            if(xVel < -30)
                xVel = -30;
        }
    }

    // Boundaries and floor
    if(yPos < 0)
        yPos = 0;
    if(yPos > screenH - screenH/8 && yVel <= 0){
        yPos = screenH - screenH/8;
        yVel = 0;
        jumping = false;
        dashing = false;
    }
    if(xPos > screenW - screenW/15)
        xPos = screenW - screenW/15;
    if(xPos < 0)
        xPos = 0;
    yPos -= yVel;
    xPos += xVel;
}


void playerC::jump() {
    if(!jumping){
        yVel = jumpForce;
        jumping = true;
    }
}


void playerC::punch(dir d, playerC* hitPlayer, float hitboxXPos, float hitboxYPos){
    if(((std::abs(hitPlayer->xPos - hitboxXPos) * 2 < (screenW/15 + screenH/20)) &&
        (std::abs((hitPlayer->yPos - screenH/5) - hitboxYPos) * 2 < (screenH/5 + screenW/20))) &&
         !hitPlayer->hit){
        switch(d){
            case LEFT:
                hitPlayer->xVel = -20;
                hitPlayer->yVel = 10;
                if(!hitPlayer->invulnerable)
                    hitPlayer->health -= 5;
                break;
            case RIGHT:
                hitPlayer->xVel = 20;
                hitPlayer->yVel = 10;
                if(!hitPlayer->invulnerable)
                    hitPlayer->health -= 5;
                break;
            case UP:
                hitPlayer->yVel = 20;
                if(!hitPlayer->invulnerable)
                    hitPlayer->health -= 10;
                break;
        }
        hitPlayer->hit = true;
    }
}

void playerC::reset(float x, float y){
    xPos = x;
    yPos = y;
    xVel = 0;
    yVel = 0;
    dashing = false;
    jumping = false;
    health = 100;
}
