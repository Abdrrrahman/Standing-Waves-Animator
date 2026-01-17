#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720

struct String
{
    int length;
    double density;
    Vector2 point1;
    Vector2 point2;
} myString;

struct PropagatingWave
{
    double amplitude;
    int num_loops;
    double tension;
} ogWave;

struct StandingWave
{
    double velocity;
    double frequency;
    double omega;
    double waveLength;
    double waveNumber;
} stWave;

void InitString(struct String *);
void GetInputs(struct PropagatingWave *);
void CalculateDerives(struct StandingWave *, struct PropagatingWave *,struct String *);

int main(void)
{
    struct String *p_string = &myString;
    InitString(p_string);

    struct PropagatingWave *p_pWave = &ogWave;
    GetInputs(p_pWave);

    struct StandingWave *p_stWave = &stWave;
    CalculateDerives(p_stWave, p_pWave, p_string);

    InitWindow(WIDTH, HEIGHT, "Standing Waves");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawLine(0, p_string->point1.y, WIDTH, p_string->point2.y, DARKGRAY);

        // Drawing the wave using 50 points
        Vector2 currenctPoint = {0.0, HEIGHT/2};
        Vector2 pastPoint = {0.0, HEIGHT/2};
        double pointStep = 0.25;
        double amplifier = 5.5;
        for (; currenctPoint.x < WIDTH; currenctPoint.x += pointStep)
        {
            int new_amp = (2 * (p_pWave->amplitude) - HEIGHT/2) * sin(p_stWave->waveNumber * currenctPoint.x);
            currenctPoint.y = (new_amp * cos(p_stWave->omega * GetTime())*amplifier) + HEIGHT/2;
            // DrawPixel(currenctPoint.x, currenctPoint.y, RED);
            DrawLine(currenctPoint.x, currenctPoint.y, pastPoint.x, pastPoint.y, WHITE);    
            pastPoint.x = currenctPoint.x;
            pastPoint.y = currenctPoint.y;
        }


        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void InitString(struct String *p_string)
{
    p_string->length = 800;
    p_string->density = 0.00013;
    int border = (WIDTH - p_string->length) / 2;
    p_string->point1.x = border;
    p_string->point1.y = HEIGHT / 2;
    p_string->point2.x = WIDTH - border;
    p_string->point2.y = HEIGHT / 2;
}

void GetInputs(struct PropagatingWave *p_pWave)
{
    p_pWave->amplitude = 200;
    p_pWave->num_loops = 2;
    p_pWave->tension = 275;
}

void CalculateDerives(struct StandingWave *p_stWave, struct PropagatingWave *p_pWave, struct String *p_string)
{
    p_stWave->velocity = sqrt(p_pWave->tension / p_string->density);
    p_stWave->frequency = (p_pWave->num_loops / 2 * p_string->length) * p_stWave->velocity;
    p_stWave->omega = 2 * PI * p_stWave->frequency;
    p_stWave->waveLength = 2 * p_string->length / p_pWave->num_loops;
    p_stWave->waveNumber = 2 * PI / p_stWave->waveLength;
}
