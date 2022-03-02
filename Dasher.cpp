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

bool isOnGround(AnimData data , int windowHeight){

    return  data.pos.y >= windowHeight -  data.rec.height;
}

AnimData updateAnimData(AnimData data , float deltaTime , int maxFrame){
       //update running tume 
       data.runningTime +=  deltaTime;
       if(data.runningTime >=  data.updateTime){
           data.runningTime = 0.0 ;
           //update animation frame
        data.rec.x =  data.frame * data.rec.width ; 
        data.frame++;
        if(data.frame > maxFrame ){
            data.frame = 0 ;

        }
       }

       return data ; 
}
int main(){

 const int windowWidth = 512 ;
 const int windowHeight=  380;


    InitWindow(windowWidth ,windowHeight, "Dapper Dash" );

    //acceleration due gravity  
const int gravity = 1000 ;

   
   //mebula anim variables

//  int nebframe = 0 ;
//  float nebUpdateTime =  10/12.0;
//  float nebRunningTime = 0.0;
  
   
    int velocity= 0;
    //pixels/sec
const int jumpVel =  -600;
const int nebvel = -200;
bool isInAir;
 //background image
 Texture2D background =  LoadTexture("./textures/far-buildings.png"); 

//migground
Texture2D  midGround =  
LoadTexture("./textures/back-buildings.png");

//foreground 
Texture2D foregroud= LoadTexture("./textures/foreground.png");

//nebula variables 


Texture2D nebula =  LoadTexture("./textures/12_nebula_spritesheet.png");
// AnimData nebData{{0.0 ,0.0 ,nebula.width/8  ,nebula.height/8  } , {windowWidth ,windowHeight-nebula.height/8 },

// 0 , 1.0/12.0 ,0.0};


// AnimData nebData2{{0.0 ,0.0 ,nebula.width/8  ,nebula.height/8  } , {windowWidth + 300 ,windowHeight-nebula.height/8 },

// 0 , 1.0/16.0 ,0.0};

const int size = 20;
AnimData nebuli[size]{};

for(int  i = 0 ; i<size ;  i++){
    nebuli[i].rec.x  = 0.0;
    nebuli[i].rec.y = 0.0;
    nebuli[i].rec.width = nebula.width/8;
    nebuli[i].rec.height =   nebula.height/8;
    nebuli[i].pos.y =  windowHeight- nebula.height/8;
    nebuli[i].frame = 0 ;
    nebuli->runningTime = 0.0;
    nebuli[i].updateTime =0.0;
nebuli[i].pos.x =  windowWidth + (  i *300);
}

// nebuli[0].pos.x =  windowWidth;
// nebuli[1].pos.x =  windowWidth +300;
// nebuli[2].pos.x =  windowWidth +600;


// Rectangle nebulaRec;
// nebulaRec.width =nebula.width/8 ;
// nebulaRec.height=nebula.height/8 ;
// nebulaRec.x = 0 ;
// nebulaRec.y = 0 ;

// Vector2 nebulaPos;
// nebulaPos.x = windowWidth;
// nebulaPos.y =  windowHeight-nebulaRec.height;

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
// int frame = 0;

// const float updateTime = 1.0/12.0;
// float  runningTime = 0.0 ; 

float bgX = 0;
float mgX =  0 ;
float fgX = 0 ;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {  /* code */
        BeginDrawing();
        ClearBackground(WHITE);
  const float dt = GetFrameTime();
 bgX -= 20 *dt ;
 if(bgX <= -background.width *2){
     bgX = 0.0;
 }
       //Draw the backgroud 
       Vector2 bg1Pos {bgX, 0.0 };
    
       DrawTextureEx(background ,bg1Pos , 0.0 ,  2.0 ,WHITE); 
           Vector2 bg2Pos{bgX + background.width *2 ,0.0 };
        DrawTextureEx(background ,bg2Pos , 0.0 ,  2.0 ,WHITE);

        //draw the midgroud
    mgX -=  40 *dt ; 
     if(mgX <=  -midGround.width *2){
         mgX = 0.0;
     }
        Vector2 mgPos {mgX ,0.0};
        Vector2 mg2Pos{
            mgX + midGround.width*2 , 0.0
        };
        DrawTextureEx(midGround ,mgPos , 0.0 ,2 , WHITE);
    DrawTextureEx(midGround ,mg2Pos , 0.0 ,2 , WHITE);

        //foregroud 
 fgX -= 80*dt ;
     if(fgX <=  -foregroud.width *2){
         fgX = 0.0;
     }
    Vector2 fgPos {
     fgX ,0.0
    };
    Vector2  fg2Pos {
        fgX + foregroud.width *2 , 0.0
    };
    DrawTextureEx(foregroud , fgPos , 0.0 ,2.0 ,WHITE);
      DrawTextureEx(foregroud , fg2Pos , 0.0 ,2.0 ,WHITE);
            //ground check
            if(isOnGround(   scarfyData ,  windowHeight )
               ){
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
            scarfyData.pos.y += velocity * dt;
            scarfyData.runningTime += dt;
            //update animation frame 

            //update nebula position 
            for(int i = 0; i<size ;i++){

  nebuli[i].pos.x +=nebvel*dt;
            }
         
         
           if(!isInAir){
                if(  scarfyData.runningTime >=   scarfyData.updateTime){
              
                scarfyData.runningTime = 0.0;
              scarfyData.rec.x =   scarfyData.frame *scarfyData.rec.width ;
                scarfyData.frame++;
                if(  scarfyData.frame > 5){
              scarfyData.frame = 0 ;
        }
        }
           }
 //update nebula animation frame ;
    for(int i = 0 ; i<size; i++){
  nebuli[i].runningTime  +=dt;
           if(   nebuli[i].runningTime  >=   nebuli[i].updateTime){

                nebuli[i].runningTime  = 0.0 ; 
             nebuli[i].rec.x =   nebuli[i].frame *   nebuli[i].rec.width;
             nebuli[i].frame ++;
               if(  nebuli[i].frame >7){
                    nebuli[i].frame  = 0;
               }

           }
    }
          
           
       
      

        
      
        
            DrawTextureRec(scarfy ,scarfyData.rec ,scarfyData.pos , WHITE);
        for(int i = 0 ;i<size ;i++){ 
DrawTextureRec(nebula , nebuli[i].rec , nebuli[i].pos, WHITE);
        }
            
              
        EndDrawing();
       
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(foregroud);
    UnloadTexture(midGround);
    CloseWindow();
}