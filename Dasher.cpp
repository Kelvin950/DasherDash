#include "raylib.h"

int main(){

 const int windowWidth = 512 ;
 const int windowHeight=  380;


    InitWindow(windowWidth ,windowHeight, "Dapper Dash" );

    //acceleration due gravity  
const int gravity = 1 ;

    //rectangle dimensions
   

   
    int velocity= 0;
const int jumpVel =  -22;
bool isInAir;
Texture2D scarfy =  LoadTexture("./textures/scarfy.png");
Rectangle scarfyRec ;
scarfyRec.width = scarfy.width/6 ; 
scarfyRec.height = scarfy.height;
scarfyRec.x = 0 ;
scarfyRec.y = 0 ;
Vector2 scarfyPos ;
scarfyPos.x =  windowWidth/2 -  scarfyRec.width/2 ;
scarfyPos.y =  windowHeight - scarfyRec.height;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {  /* code */
        BeginDrawing();
        ClearBackground(WHITE);
           
            //ground check
            if(scarfyPos.y>=  windowHeight - scarfyRec.height){
                //rectangle is on the ground
                isInAir =  false;
                velocity =   0 ;
            }else{
                //rectangle is in the air 
               //apply gravity 
               isInAir =  true;
            velocity += gravity;
            }
            //check for jumping
             if(IsKeyPressed(KEY_SPACE) &&    !isInAir){
             velocity += jumpVel ;
            }

            //update position
            scarfyPos.y += velocity;
            DrawTextureRec(scarfy ,scarfyRec ,scarfyPos , WHITE);
        EndDrawing();
       
    }
    UnloadTexture(scarfy);
    CloseWindow();
}