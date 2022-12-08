#include "update.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ BEGIN DECLARATIONS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void update(State currentState, f64 t, f64 dt);
void spawn_enemy(void);
void move_enemy(f64 dt);
void clip_enemy(void);
Vec2 move_to(Vec2 start, Vec2 destination);

Vec2 move_up(void);
Vec2 move_down(void);
Vec2 move_left(void);
Vec2 move_right(void);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END DECLARATIONS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void update(State currentState, f64 t, f64 dt)
{
    spawn_enemy();
    move_enemy(dt);
    clip_enemy();
}

// spawn enemies
// TODO pathfinding O_o
void spawn_enemy(void)
{
    Vec2 temp = {0.0f, 0.0f};

    if((app.eSpawn.numberSpawned < app.eSpawn.maxSpawns) && (app.eSpawn.cooldown == 0))
    {
        app.enemy[app.eSpawn.numberSpawned].alive = true;
        app.enemy[app.eSpawn.numberSpawned].pos = app.eSpawn.pos;
        app.enemy[app.eSpawn.numberSpawned].dest = WAYPOINT_2;
        app.enemy[app.eSpawn.numberSpawned].velocity *= ENEMY_VELOCITY;
        
        // app.enemy[app.eSpawn.numberSpawned].velocity = move_right() + move_up();
        // Vec2 something = move_to(WAYPOINT_1, WAYPOINT_2);
       
       
        app.eSpawn.numberSpawned += 1;
        app.eSpawn.cooldown = 120;
        app.enemyCount += 1;
    }

    app.eSpawn.cooldown -= 1;
}

// update enemy position
void move_enemy(f64 dt)
{
    for(int i = 0; i < app.enemyCount; i++)
    {
        app.enemy[i].pos = app.enemy[i].pos + app.enemy[i].velocity * dt;
    }
}

// TODO need to fix this!
void clip_enemy(void)
{
    for(int i = 0; i < app.enemyCount; i++)
    {
        if(app.enemy[i].pos.x > SCREEN_WIDTH - 100)
        {
            app.enemy[i].pos.x = SCREEN_WIDTH - 100;
            app.enemy[i].velocity.x *= -1;
        }
        if(app.enemy[i].pos.x < 0)
        {
            app.enemy[i].pos.x = 200;
            app.enemy[i].velocity.x *= -1;
        }
        if(app.enemy[i].pos.y < 0)
        {
            app.enemy[i].pos.y = 0;
            app.enemy[i].velocity.y *= -1;
        }
        
        if(app.enemy[i].pos.y > SCREEN_HEIGHT - 100)
        {
            app.enemy[i].pos.y = SCREEN_HEIGHT - 100;
            app.enemy[i].velocity.y *= -1;
        }
    }
}

Vec2 move_up(void)
{
    return {0, -1};
}

Vec2 move_down(void)
{
    return {0, 1};
}

Vec2 move_left(void)
{
    return {-1, 0};
}

Vec2 move_right(void)
{
    return {1, 0};
}

Vec2 move_to(Vec2 start, Vec2 destination)
{
    Vec2 temp = {777.0f, 777.0f};
    return temp;
}
