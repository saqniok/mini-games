#include "raylib.h"
int main() 
{

    // window size.
    int wid = 1000;
    int heid = 800;
    InitWindow(wid, heid, "Test window");

    int cir_x{20}; // X cirlce position.
    int cir_y{ heid / 2}; // Y circle position.
    int cir_r{20}; // circle radius.

    //text & lenght.
    const char* txt = "Game Over!";
    int txt_len = MeasureText(txt, 40);

    // circle edges.
    int lcu_l_circle_x{cir_x - cir_r}; // left-up X circle edge.
    int rcu_r_circle_x{cir_x + cir_r}; // right-up X circle edge.
    int rcu_u_circle_y{cir_y - cir_r}; // right-up Y circle edge.
    int rcd_b_circle_y{cir_y + cir_r}; // righ-down Y circle edge.

    int xdir1{8}; // 1st X square speed.
    int ydir1{8}; // 1st Y square speed.

    int xdir2{10}; // 2nd X square speed.
    int ydir2{10}; // 2nd Y square speed.

    int xdir3{12}; // 3rd X square speed.
    int ydir3{12}; // 3rd Y square speed.
    
    
    int sqr_size{40}; // square size.
    
    // 1st square.
    int sqr1_x{wid - sqr_size};
    int sqr1_y{heid - sqr_size};
    // 1st square edges.
    int la1d_l_sqr_x{sqr1_x};
    int ra1d_r_sqr_x{sqr1_x + sqr_size};
    int la1u_u_sqr_y{sqr1_y};
    int la1d_b_sqr_y{sqr1_y + sqr_size};
   
    // 2nd square.
    int sqr2_x{(wid - sqr_size) / 2};
    int sqr2_y{heid - sqr_size};
    // 2nd square edges.
    int la2d_l_sqr_x{sqr2_x};
    int ra2d_r_sqr_x{sqr2_x + sqr_size};
    int la2u_u_sqr_y{sqr2_y};
    int la2d_b_sqr_y{sqr2_y + sqr_size};
    
    // 3rd square.
    int sqr3_x{wid - sqr_size};
    int sqr3_y{(heid - sqr_size) / 5};
    // 3rd suqare edges.
    int la3d_l_sqr_x{sqr3_x};
    int la3d_r_sqr_x{sqr3_x + sqr_size};
    int la3d_u_sqr_y{sqr3_y};
    int la3d_b_sqr_y{sqr3_y + sqr_size};

    // impact with squares.
    // 1st square.
    bool sqr1_go = (la1u_u_sqr_y <= rcd_b_circle_y) && (la1d_b_sqr_y >= rcu_u_circle_y) && (la1d_l_sqr_x <= rcu_r_circle_x) && (ra1d_r_sqr_x >= lcu_l_circle_x);
    // 2nd square.
    bool sqr2_go = (la2u_u_sqr_y <= rcd_b_circle_y) && (la2d_b_sqr_y >= rcu_u_circle_y) && (la2d_l_sqr_x <= rcu_r_circle_x) && (ra2d_r_sqr_x >= lcu_l_circle_x);
    // 3rd square.
    bool sqr3_go = (la3d_u_sqr_y <= rcd_b_circle_y) && (la3d_b_sqr_y >= rcu_u_circle_y) && (la3d_l_sqr_x <= rcu_r_circle_x) && (la3d_r_sqr_x >= lcu_l_circle_x);
    // all suqares.
    bool coll_with_sqr = sqr1_go || sqr2_go || sqr3_go; // collision with suqares.



    SetTargetFPS(60); // frame FPS.
    while (!WindowShouldClose()) // This function is from -raylib, "!" because bool is true.
    {
        // star game logic.
        BeginDrawing();
        
        // background.
        ClearBackground(RED);

        if (coll_with_sqr)
        {
            DrawText(txt, (wid / 2) - (txt_len / 2), heid / 2, 40, WHITE); // text after collision_with_squares - coll_with_sqr.
            DrawText("Press SPACE to Restart", wid / 2 - MeasureText("Press SPACE to Restart", 20) / 2, heid / 2 + 50, 20, WHITE);

            if (IsKeyDown(KEY_SPACE))
            {
                cir_x = 20; // X cirle position.
                cir_y =  heid / 2; // Y circle position.
                cir_r = 20; // circle radius.
                
                // all suqares edges.
                sqr1_x = wid - sqr_size;
                sqr1_y = heid - sqr_size;
                sqr2_x = (wid - sqr_size) / 2;
                sqr2_y = heid - sqr_size;
                sqr3_x = wid - sqr_size;
                sqr3_y = (heid - sqr_size) / 2;
                coll_with_sqr = false; 
            }
        }
        else 
        {
            //Edges update every frame.
            int lcu_l_circle_x = cir_x - cir_r;
            int rcu_r_circle_x = cir_x + cir_r;
            int rcu_u_circle_y = cir_y - cir_r;
            int rcd_b_circle_y = cir_y + cir_r;

            int la1u_u_sqr_y = sqr1_y;
            int la1d_b_sqr_y = sqr1_y + sqr_size;
            int la1d_l_sqr_x = sqr1_x; 
            int ra1d_r_sqr_x = sqr1_x + sqr_size;

            int la2u_u_sqr_y = sqr2_y;
            int la2d_b_sqr_y = sqr2_y + sqr_size;
            int la2d_l_sqr_x = sqr2_x; 
            int ra2d_r_sqr_x = sqr2_x + sqr_size;

            int la3d_u_sqr_y = sqr3_y;
            int la3d_b_sqr_y = sqr3_y + sqr_size;
            int la3d_l_sqr_x = sqr3_x; 
            int la3d_r_sqr_x = sqr3_x + sqr_size;

            // update coll_with_sqr.
            int sqr1_go = (la1u_u_sqr_y <= rcd_b_circle_y) && (la1d_b_sqr_y >= rcu_u_circle_y) && (la1d_l_sqr_x <= rcu_r_circle_x) && (ra1d_r_sqr_x >= lcu_l_circle_x);
            int sqr2_go = (la2u_u_sqr_y <= rcd_b_circle_y) && (la2d_b_sqr_y >= rcu_u_circle_y) && (la2d_l_sqr_x <= rcu_r_circle_x) && (ra2d_r_sqr_x >= lcu_l_circle_x);
            int sqr3_go = (la3d_u_sqr_y <= rcd_b_circle_y) && (la3d_b_sqr_y >= rcu_u_circle_y) && (la3d_l_sqr_x <= rcu_r_circle_x) && (la3d_r_sqr_x >= lcu_l_circle_x);
            coll_with_sqr = sqr1_go || sqr2_go || sqr3_go;

            DrawCircle( cir_x, cir_y, cir_r, WHITE); // Drawing white cirle.
            
            DrawRectangle(sqr1_x, sqr1_y, sqr_size, sqr_size, BLACK); // Drawing 1st black sqaure.
            
            sqr1_x -= xdir1; // 1st square move X position.
            sqr1_y -= ydir1; // 1st suqare move Y position.
            
            if (sqr1_y < 0 || sqr1_y > (heid - sqr_size)) // 1st square Y edge collision with window.
            {
                ydir1 = -ydir1;
            }
            
            if(sqr1_x < 0 || sqr1_x > (wid - sqr_size)) // 1st square X edge collision with window.
            {
                xdir1 = -xdir1;
            }
           
            DrawRectangle(sqr2_x, sqr2_y, sqr_size, sqr_size, BLACK); // Drawing 2nd black suare.

            sqr2_x -= xdir2; // 2st square move X position.
            sqr2_y -= ydir2; // 2st suqare move Y position.
            
            if (sqr2_y < 0 || sqr2_y > (heid - sqr_size)) // 2nd square Y edge collision with window.
            {
                ydir2 = -ydir2;
            }
            
            if(sqr2_x < 0 || sqr2_x > (wid - sqr_size)) // 2nd square X edge collision with window.
            {
                xdir2 = -xdir2;
            }
            
            DrawRectangle(sqr3_x, sqr3_y, sqr_size, sqr_size, BLACK); // Drawing 3rd black sqaure.

            sqr3_x -= xdir3; // 3rd square move X position.
            sqr3_y -= ydir3; // 3rd suqare move Y position.

            if (sqr3_y < 0 || sqr3_y > (heid - sqr_size)) // 3rd square Y edge collision with window.
            {
                ydir3 = -ydir3;
            }
            if (sqr3_x < 0 || sqr3_x > (wid - sqr_size)) // 3rd square X edge collision with window.
            {
                xdir3 = -xdir3;
            }

            // Key to move circle.
            if (IsKeyDown(KEY_D) && cir_x < (wid - cir_r))
            {
                cir_x += 10;
            }

            if (IsKeyDown(KEY_A) && cir_x > cir_r)
            {
                cir_x -= 10;
            }

            if (IsKeyDown(KEY_W) && cir_y > (cir_r))
            {
                cir_y -= 10;
            } 
            
            if (IsKeyDown(KEY_S) && cir_y < (heid - cir_r))
            {
                cir_y += 10;
            }
        }   
        // End game logic.
        EndDrawing();
    
    }
    CloseWindow();

    return 0;
}
