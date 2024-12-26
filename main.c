#include <raylib.h>

void adj_windo()
{
    int height = 800;int width = 1280;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE|FLAG_WINDOW_MINIMIZED|FLAG_WINDOW_MAXIMIZED);
    InitWindow(GetScreenWidth(),GetScreenHeight(),"poop-pong"); 
    SetWindowMinSize(width,height);
    SetWindowMaxSize(GetScreenWidth()-1,GetScreenHeight()-1);
    SetTargetFPS(60);
}//made a adjustable window.
int  i=0,j=0,sx=10,sy=10,x,y,redus=50;//for ball
void ball_move_co()
{
    x=(GetScreenWidth()/2)+i;
    y = (GetScreenHeight()/2)+j;
    DrawCircle(x,y,redus,WHITE);
    if(y+redus>=GetScreenHeight()||y-redus<=0)
    {
        sy=sy*-1;
    }
    if(x+redus>=GetScreenWidth()||x-redus<=0)
    {
        sx=sx*-1;
    }

}//draw and move a ball and colide with wall

void ball_update()
{
    i=i+sx;
    j=j+sy;
}//to update the ball position

int up=0,up_lmt;//for player handel
void move_phand()
{
    up_lmt=(GetScreenHeight()/2)+up;
    DrawRectangle(GetScreenWidth()-35,up_lmt,25,100,BLACK);//made a player handel 
    if (IsKeyDown(KEY_UP))
    {
        up=up-10;
        if(up_lmt<=0)
        {
            up=up+10;
        }
    }
     if (IsKeyDown(KEY_DOWN))
    {
        up=up+10;
        if(up_lmt>=GetScreenHeight()-100)
        {
            up=up-10;
        }
    }
}
int aiup_lmt;// for ai paddel
void move_aihand()
{
    DrawRectangle(10,aiup_lmt,25,100,BLACK);//made ai handel 
    if (x<GetScreenWidth()/4)
    {
        if(aiup_lmt>y)
        {
            aiup_lmt=aiup_lmt-10;
        }
        if(aiup_lmt==y)
        {
            aiup_lmt=y;
        }
        if(aiup_lmt+100<y)
        {
            aiup_lmt=aiup_lmt+10;
        }
    }
}//made ai paddel move

void win_los(int *p,int *ai)
{
    while(WindowShouldClose()==false)
{
    BeginDrawing();
    
    if(*p>*ai)
    {
        ClearBackground(BLUE);
        DrawText("You Won!!!!!",GetScreenWidth()/4,GetScreenHeight()/4,250,WHITE);
        DrawText("press s to restart",GetScreenWidth()/4,GetScreenHeight()/2,50,WHITE);
        
    }
    if(*ai>*p)
    {
        ClearBackground(BLACK);
        DrawText("You lose!!!!!",GetScreenWidth()/4,GetScreenHeight()/4,250,RED);
        DrawText("press s to restart",GetScreenWidth()/4,GetScreenHeight()/2,50,WHITE);
        
    }
    if (IsKeyDown(KEY_S))
    {
        *p=0,*ai=0;
        break;
    }
    EndDrawing();

}
}//exit menue

int main () {

    
    adj_windo();
    while(WindowShouldClose()==false)
    {
        BeginDrawing();
        ClearBackground(YELLOW);
        DrawText("Press S to start",GetScreenWidth()/4,GetScreenHeight()/4,50,BLACK);
        if(IsKeyDown(KEY_S))
        {
            break;
        }
        EndDrawing();
    }//start menue 
    
    int pscore=0;
    aiup_lmt=(GetScreenHeight()/2)-100;
    up_lmt = up_lmt-50;
    int aiscore=0;
   
while(WindowShouldClose()==false)
{
    
    BeginDrawing();
    if (IsKeyDown(KEY_P))
    {
        while (WindowShouldClose()==false)
        {
            BeginDrawing();
            ClearBackground(YELLOW);
            DrawText("Press S to start",GetScreenWidth()/4,GetScreenHeight()/4,50,BLACK);
            if(IsKeyDown(KEY_S))
            {
                break;
            }
            EndDrawing();
        }    
    }
    ClearBackground(RED);//made window red
    DrawLine((GetScreenWidth()/2),0,(GetScreenWidth()/2),GetScreenHeight(),BLACK);
    DrawText(TextFormat("Press P to pause "),GetScreenWidth()*(4.0/9),10,20,BLACK);
    DrawText(TextFormat("Player Score: %i",pscore),GetScreenWidth()-200,10,20,BLACK);//made ai score bord
    DrawText(TextFormat("CPU Score: %i",aiscore),10,10,20,BLACK);//made player score board
    ball_move_co();//made a ball and ball collision int up=0; with wall
    
    move_phand();//made player handel move
    if(x+redus>=GetScreenWidth()-35 && (y+redus>=up_lmt && y-redus<=up_lmt+100))
    {
        if(sx>0)
        {
        sx=sx*-1;
        }
    }//collission with the player paddel
   
    

    if(x-redus<=35 && (y+redus>=aiup_lmt && y-redus<=aiup_lmt+100))
    {
        if(sx<0)
        {
        sx=sx*-1;
        }
    }//collision with the ai paddel
    
    
    move_aihand();//made ai handel move
   
    if(x+redus>=GetScreenWidth())
    {
        aiscore=aiscore+1;
    }
    
    if(x-redus<=0)
    {
        pscore=pscore+1;
    }
    ball_update();//update ball movement
    
 
    EndDrawing();
    if(pscore >=10||aiscore >=10)
    {
        win_los(&pscore,&aiscore);
    }
    
}


    CloseWindow();
    return 0 ;

}