#include "renderUtils.h"
#include <math.h>

#define PI 3.1416

void drawArrow(SDL_Renderer *renderer, float fromX, float fromY, float toX, float toY) {
    float arrowAngle = 0.9;
    float dx = toX - fromX;
    float dy = toY - fromY;
    float arctangent = atan2f(dy, dx);
    float angle = arctangent + PI;
    float headLength = 5;

    //first arrow head line
    int x0 = (int)(headLength*cos(angle - arrowAngle) + toX);
    int y0 = (int)(headLength*sin(angle - arrowAngle) + toY);
    //second arrow head line
    int x1 = (int)(headLength*cos(angle + arrowAngle) + toX);
    int y1 = (int)(headLength*sin(angle + arrowAngle) + toY);
    SDL_RenderDrawLine(renderer, (int)fromX, (int)fromY, (int)toX, (int)toY); 
    SDL_RenderDrawLine(renderer, (int)toX, (int)toY, x0, y0); 
    SDL_RenderDrawLine(renderer, (int)toX, (int)toY, x1, y1); 
    SDL_RenderDrawLine(renderer, (int)toX, (int)toY, x1, y1); 
}
