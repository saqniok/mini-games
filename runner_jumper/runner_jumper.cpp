#include "raylib.h"

struct anim_data // structure for group of components.
{
    Rectangle rec;  // size of rectangle.
    Vector2 pos;    // position of rectangle.
    int frame;      // frame per sec.
    float upd_time; // times for updating frame. In seconds.
    float run_time; // running time after last frame. In seconds.
};

bool is_on_ground(anim_data data, int win_heig) // chekcs that our object on the ground. Added 1 component.
{
    return data.pos.y >= win_heig - data.rec.height; // return = value of formula and changes is_on_ground() value.
                                                     // true if Player on the ground and false if Player in the air.
}

anim_data upd_anim_data(anim_data data, float deltaTime, int max_frame) // update running time. Add 2 more components.
{
    data.run_time += deltaTime;         // track the time elapsed since the last animation update.
    if (data.run_time >= data.upd_time) // it is time to update the Player's animation frame.
    {
        data.run_time = 0.0;                      // reset frame.
        data.rec.x = data.frame * data.rec.width; // update animation frame.
        data.frame++;                             // update frame by 1.
        if (data.frame > max_frame)               // reset frame after cicle to zero.
        {
            data.frame = 0;
        }
    }
    return data; // change value of 'anim_data data'.
}
bool collision{};

int main()
{
    // Window dimensions.
    int win_width = 512;  // Window Width.
    int win_height = 256; // Window Height.

    InitWindow(win_width, win_height, "Runner-Jumper"); // initialize the window from Array.

    const int gravity{960};        // acceleration due to gravity, (P / S) / S, (Pixel / Sec) / Sec.
    const int jump_velocity{-500}; // jump velocity, Pixel Per Second = PPS.

    // Load image with Fire assets.
    Texture2D fire_texture = LoadTexture("'YOUR PATH'\\13_vortex_spritesheet.png");

    const int number_of_fire{3}; // number of Fires in minigame.

    anim_data fire_info[number_of_fire]{}; // Using struct of anim_data, for creating loop with Fire data info.

    for (int i = 0; i < number_of_fire; i++)
    {
        fire_info[i].rec.x = 0.0;                                         // X coordinates for loading image from Fire asset.
        fire_info[i].rec.y = 0.0;                                         // Y coordinates for loading image from Fire asset.
        fire_info[i].rec.width = float(fire_texture.width / 8);           // Width of loaded asset.
        fire_info[i].rec.height = float(fire_texture.height / 8);         // Height of loaded asset.
        fire_info[i].pos.x = win_width + (300 * i);                       // position of Fire in X line and the subsequents Fire.
        fire_info[i].pos.y = float(win_height - fire_texture.height / 8); // position of Fire in Y line.
        fire_info[i].frame = 0;                                           // FPS.
        fire_info[i].run_time = 0.0;                                      // times for updating frame. In seconds.
        fire_info[i].upd_time = 1.0 / 16.0;                               // time after last frame. In seconds.
    };

    float finish_line{fire_info[number_of_fire - 1].pos.x};

    // Loading Player asset.
    Texture2D player = LoadTexture("'YOUR PATH'\\run2.png");
    anim_data playerData;                                        // Using struct of anim_data, for creating information about Player.
    playerData.rec.width = player.width / 8;                     // Width of player asset.
    playerData.rec.height = player.height;                       // Height of player asset.
    playerData.rec.x = 0;                                        // X coordinates for loading image from Player asset.
    playerData.rec.y = 0;                                        // Y coordinates for loading image from Player asset.
    playerData.pos.x = win_width / 3 - playerData.rec.width / 2; // Player position in X line.
    playerData.pos.y = win_height - playerData.rec.height;       // Player position in Y line.
    playerData.frame = 0;                                        // FPS.
    playerData.upd_time = 0.9 / 12.0;                            // time for update frame. In seconds.
    playerData.run_time = 0.0;                                   // time after last frame. In seconds.

    int velocity{0};      // velocity in PPS.
    int fire_speed{-200}; // Fire X line velocity, PPS.

    // load back ground image.
    Texture2D hills_texture1 = LoadTexture("'YOUR PATH'\\Hills Layer 01.png");
    // Load middle ground.
    Texture2D hills_texture2 = LoadTexture("'YOUR PATH'\\Hills Layer 02.png");
    // Load foreground.
    Texture2D hills_texture3 = LoadTexture("'YOUR PATH'\\Hills Layer 03.png");
    // Load hills lyaer 04.
    Texture2D hills_texture4 = LoadTexture("'YOUR PATH'\\Hills Layer 04.png");
    // Load ground. Hills layer 05..
    Texture2D ground_texture = LoadTexture("'YOUR PATH'\\Hills Layer 05.png");
    // Load bushes. Hills Layer 06.
    Texture2D bushes_texture = LoadTexture("'YOUR PATH'\\Hills Layer 06.png");
    float hill2{};
    float hill3{};
    float hill4{};
    float bushes{};
    float ground{};

    bool isInAir{}; // bool always "false" with empty {};.

    SetTargetFPS(60);
    while (!WindowShouldClose())
    /*      This function is from RayLib.
     *
     *       bool WindowShouldClose(void)
     *   {
     *       if (CORE.Window.ready) return CORE.Window.shouldClose;
     *       else return true;
     *   }
     */
    {

        const float dT{GetFrameTime()}; // delta time.
        BeginDrawing();
        ClearBackground(WHITE);

        hill2 -= 30 * dT;  // velocity for hills_texture2.
        hill3 -= 40 * dT;  // velocity for hills_texture3.
        hill4 -= 50 * dT;  // velocity for hill_texture4.
        bushes -= 60 * dT; // velocity for bushes bushes tecture.
        ground -= 70 * dT; // velocity for ground texture.

        if (hill2 <= -hills_texture2.width) // Scroll hills_texture2.
        {
            hill2 = 0.0;
        }

        if (hill3 <= -hills_texture3.width) // Scroll hills_texture3.
        {
            hill3 = 0.0;
        }

        if (hill4 <= -hills_texture4.width)
        {
            hill4 = 0.0;
        }

        if (bushes <= -bushes_texture.width)
        {
            bushes = 0.0;
        }

        if (ground <= -ground_texture.width)
        {
            ground = 0.0;
        }
        // draw back gound
        DrawTextureEx(hills_texture1, (Vector2){0.0, 0.0}, 0.0, 1.0, WHITE);

        // draw hills_texture2.
        Vector2 hil2Pos{hill2, 0.0};
        Vector2 hil2Pos2{hill2 + hills_texture2.width, 0.0};
        DrawTextureEx(hills_texture2, hil2Pos, 0.0, 1.0, WHITE);
        DrawTextureEx(hills_texture2, hil2Pos2, 0.0, 1.0, WHITE);

        // draw hills_texture3.
        Vector2 hil3Pos{hill3, 0.0};
        Vector2 hil3Pos2{hill3 + hills_texture3.width, 0.0};
        DrawTextureEx(hills_texture3, hil3Pos, 0.0, 1.0, WHITE);
        DrawTextureEx(hills_texture3, hil3Pos2, 0.0, 1.0, WHITE);

        // draw hills_texture4.
        Vector2 hil4Pos{hill4, 0.0};
        Vector2 hil4Pos2{hill4 + hills_texture4.width, 0.0};
        DrawTextureEx(hills_texture4, hil4Pos, 0.0, 1.0, WHITE);
        DrawTextureEx(hills_texture4, hil4Pos2, 0.0, 1.0, WHITE);

        // draw bushes texture.
        Vector2 bushesPos{bushes, 0.0};
        Vector2 bushesPos2{bushes + bushes_texture.width, 0.0};
        DrawTextureEx(bushes_texture, bushesPos, 0.0, 1.0, WHITE);
        DrawTextureEx(bushes_texture, bushesPos2, 0.0, 1.0, WHITE);

        // draw ground texture.
        Vector2 groundPos{ground, 0.0};
        Vector2 groundPos2{ground + ground_texture.width, 0.0};
        DrawTextureEx(ground_texture, groundPos, 0.0, 1.0, WHITE);
        DrawTextureEx(ground_texture, groundPos2, 0.0, 1.0, WHITE);

        if (is_on_ground(playerData, win_height)) // condition for Player position in Y line.
        {
            playerData.pos.y = win_height - playerData.rec.height; // ground coordinates logic, by Player position in Y line.
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // apply gravity with delta time, because we need velocity per second. Otherwise any PC will show different frame rate.
            velocity += gravity * dT;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir) // Space key for Jump and jump logic. So if we are on the ground, we can use jump + jump velocity.
        {
            velocity += jump_velocity; // jump velocity.
        }

        // standart loop. i++ gives everytime +1 to 'i'. and if 'i' will be greater the number of Fires, loop will be terminated.
        for (int i = 0; i < number_of_fire; i++)
        {
            fire_info[i].pos.x += fire_speed * dT;
            // Using anim_data's object. anim_data fire_info[number_of_fire]{}.
        }

        finish_line += fire_speed * dT; // update finish Line.

        playerData.pos.y += velocity * dT; // update Player Y position by delta time.

        if (!isInAir) // This block of code working only if Player is on the ground.
        {
            playerData = upd_anim_data(playerData, dT, 7); // using function, with updated anim_data, delta time and max frame for Player.
        }

        // standart loop. i++ gives everytime +1 to i. and if i will be greater the number of fires, loop will be terminated.
        for (int i = 0; i < number_of_fire; i++)
        {
            fire_info[i] = upd_anim_data(fire_info[i], dT, 7); // using function, with updated anim_data, delta time and max frame for Fire.
        }

        for (anim_data firee : fire_info)
        {
            float pad{50};
            Rectangle fireRec{
                firee.pos.x + pad,
                firee.pos.y + pad,
                firee.rec.width - pad * 2,
                firee.rec.height - pad * 2,
            };
            Rectangle playerRec{
                playerData.pos.x - 70,
                playerData.pos.y,
                playerData.rec.width,
                playerData.rec.height,
            };
            if (CheckCollisionRecs(fireRec, playerRec))
            {
                collision = true;
            };
        }
        if (collision)
        {
            // lose the game.
            DrawText("Game Over", win_width / 2 - MeasureText("Game Over", 30) / 2, win_height / 2 - 15, 30, BLACK);
            /*
            Using structure from anim_data fire_info[number_of_fire]{}
            We can make however many Fires in the game, just chages [number_of_fire] in any int number.
            */
        }
        else if (playerData.pos.x >= finish_line) // condition for winning.
        {
            // draw the text for winning game.
            DrawText("You win!", win_width / 2 - MeasureText("You win!", 30) / 2, win_height / 2 - 15, 30, BLACK);
        }
        else
        {
            // continue draw player and fire if collision = flase.
            for (int i = 0; i < number_of_fire; i++)
                DrawTextureRec(fire_texture, fire_info[i].rec, fire_info[i].pos, WHITE);
            DrawTextureRec(player, playerData.rec, playerData.pos, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(player);
    UnloadTexture(fire_texture);
    UnloadTexture(hills_texture1);
    UnloadTexture(hills_texture2);
    UnloadTexture(hills_texture3);
    UnloadTexture(hills_texture4);
    UnloadTexture(bushes_texture);
    UnloadTexture(ground_texture);
    CloseWindow();

    return 0;
}
