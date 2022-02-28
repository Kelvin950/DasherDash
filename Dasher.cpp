#include "raylib.h"

struct  AnimData
{

    /* data */

Rectangle rec;
Vector2 pos ; 
int frame;
float updateTime;
float runningTime;

};


int main(){

 const int windowWidth = 512 ;
 const int windowHeight=  380;


    InitWindow(windowWidth ,windowHeight, "Dapper Dash" );

    //acceleration due gravity  
const int gravity = 1000 ;

   
   //mebula anim variables

 int nebframe = 0 ;
 float nebUpdateTime =  10/12.0;
 float nebRunningTime = 0.0;
  
   
    int velocity= 0;
    //pixels/sec
const int jumpVel =  -600;
const int nebvel = -200;
bool isInAir;

//nebula variables 
Texture2D nebula =  LoadTexture("./textures/12_nebula_spritesheet.png");
Rectangle nebulaRec;
nebulaRec.width =nebula.width/8 ;
nebulaRec.height=nebula.height/8 ;
nebulaRec.x = 0 ;
nebulaRec.y = 0 ;

Vector2 nebulaPos;
nebulaPos.x = windowWidth;
nebulaPos.y =  windowHeight-nebulaRec.height;

//scarfy variables
Texture2D scarfy =  LoadTexture("./textures/scarfy.png");

AnimData scarfyData; 
scarfyData.rec.width =scarfy.width/6;
scarfyData.rec.height =   scarfy.height;
scarfyData.rec.x = 0 ; 
scarfyData.rec.y = 0 ;
scarfyData.pos.x  =  windowWidth/2 -  scarfyData.rec.width/2 ;
scarfyData.pos.y =  windowHeight - scarfyData.rec.height;
scarfyData.frame =   0 ;
scarfyData.updateTime = 1.0/12.0;
scarfyData.runningTime = 0.0;
// Rectangle scarfyRec =;

// scarfyRec.width =  ; 
// scarfyRec.height =;
// scarfyRec.x = 0 ;
// scarfyRec.y = 0 ;
// Vector2 scarfyPos ;
// scarfyPos.x =  windowWidth/2 -  scarfyRec.width/2 ;
// scarfyPos.y =  windowHeight - scarfyRec.height;
//animation frame 
int frame = 0;

const float updateTime = 1.0/12.0;
float  runningTime = 0.0 ; 


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {  /* code */
        BeginDrawing();
        ClearBackground(WHITE);
           const float dt = GetFrameTime();
       
            //ground check
            if(scarfyPos.y>=  windowHeight - scarfyRec.height){
                //rectangle is on the ground
                isInAir =  false;
                velocity =   0 ;
            }else{
                //rectangle is in the air 
               //apply gravity 
               isInAir =  true;
            velocity += gravity * dt;
            }
            //check for jumping
             if(IsKeyPressed(KEY_SPACE) &&    !isInAir){
             velocity += jumpVel ;
           
            }

            //update scarfy position
            scarfyPos.y += velocity * dt;
            runningTime += dt;
            //update animation frame 

            //update nebula position 
          nebulaPos.x +=nebvel*dt;
         
           if(!isInAir){
                if(runningTime >= updateTime){
              
              runningTime = 0.0;
              scarfyRec.x = frame *scarfyRec.width ;
              frame++;
                if(frame > 5){
            frame = 0 ;
        }
        }
           }


           //update nebula animation frame ;
           nebRunningTime +=dt;
           if(nebRunningTime >= nebUpdateTime){

               nebRunningTime = 0.0 ; 
            nebulaRec.x = nebframe * nebulaRec.width;
            nebframe++;
               if(nebframe>7){
                   nebframe = 0;
               }

           }
       
      
        
            DrawTextureRec(scarfy ,scarfyRec ,scarfyPos , WHITE);
            DrawTextureRec(nebula , nebulaRec ,nebulaPos , WHITE);
        EndDrawing();
       
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}