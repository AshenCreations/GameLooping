#include "update.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ BEGIN DECLARATIONS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void update(void);

// void check_gamestate(void);

void spawn_enemy(void);
void update_enemy(void);
void screenclip_enemy(void);
void update_player(void);
void screenclip_player(void);
void player_collision(void);

Vec2 move_up(void);
Vec2 move_down(void);
Vec2 move_left(void);
Vec2 move_right(void);
Vec2 move_stop(void);
// Vec2 move_to(Vec2 startPos, Vec2 endPos);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END DECLARATIONS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void update(void)
{
    spawn_enemy();
    update_enemy();
    screenclip_enemy();

    update_player();
    screenclip_player();
    player_collision();
}

// void check_gamestate(void)
// {

// }

// spawn enemies
void spawn_enemy(void)
{
    if((app.eSpawn.spawnedIdx < app.eSpawn.maxSpawns) && (app.eSpawn.cooldown <= 0))
    {
        app.enemy[app.eSpawn.spawnedIdx].alive = true;
        app.enemy[app.eSpawn.spawnedIdx].pos = app.eSpawn.pos;
        app.enemy[app.eSpawn.spawnedIdx].speed = app.eSpawn.spawnedSpeed;
        app.enemy[app.eSpawn.spawnedIdx].facing = false;
        app.enemy[app.eSpawn.spawnedIdx].targetPos = app.eSpawn.targetWaypoint;
        app.enemy[app.eSpawn.spawnedIdx].minDistance = 0.9f;

        app.eSpawn.spawnedIdx++;
        app.eSpawn.cooldown = 1000;
        app.enemyCount++;
    }
    app.eSpawn.cooldown--;
}

// update enemy position
void update_enemy(void)
{
    for(u32 i = 0; i < app.enemyCount; i++)
    {
        // waypoint following
        app.enemy[i].vel = unit_Vec2(app.enemy[i].targetPos - app.enemy[i].pos);

        f32 distance = check_distance(app.enemy[i].pos, app.enemy[i].targetPos);
        
        // when waypoint reached, set next waypoint
        if(distance < app.enemy[i].minDistance)
        {
            app.enemy[i].WpIdx++;

            if(app.enemy[i].WpIdx == WAYPOINT_COUNT)
                app.enemy[i].WpIdx = 0;
            
            app.enemy[i].targetPos = app.waypoint[app.enemy[i].WpIdx].pos;
            
            // bruh
            play_sound(app.sounds.bruh);
        }

        app.enemy[i].pos += app.enemy[i].vel * (app.enemy[i].speed * app.dt);

        // check enemy facing dependant on velocity.x value
        if(app.enemy[i].vel.x > 0)
            app.enemy[i].facing = false;

        if(app.enemy[i].vel.x < 0)
            app.enemy[i].facing = true;
    }
}


// Vec2 move_to(Entity e, Vec2 targetPos)
// {
//     Vec2 temp = unit_Vec2(targetPos - e.pos);

//     f32 distance = check_distance(e.pos, targetPos);

//     // when waypoint reached, set next waypoint
//     if(distance < e.minDistance)
//     {
//         e.vel = move_stop();
//     }
// }

// clip enemy position to to bounds of the screen
void screenclip_enemy(void)
{
	Vec2 r = {0};

    for(u32 i = 0; i < app.enemyCount; i++)
    {
        bool collide = false;
        if(app.enemy[i].pos.x < 0 + app.enemySprite->w / 2.0f)
        {
            r = {1, 0};
            collide = true;
        }
        if(app.enemy[i].pos.x > SCREEN_WIDTH - app.enemySprite->w / 2.0f)
        {
            r = {-1, 0};
            collide = true;
        }
        if(app.enemy[i].pos.y < 0 + app.enemySprite->h / 2.0f)
        {
            r = {0, 1};
            collide = true;
        }
        if(app.enemy[i].pos.y > SCREEN_HEIGHT - app.enemySprite->h / 2.0f)
        {
            r = {0, -1};
            collide = true;
        }
        
        if(collide)
        {
            app.enemy[i].vel = app.enemy[i].vel - (r * 2.0f) * dot_product(app.enemy[i].vel, r);
        }
    }
}

// update player position
void update_player(void)
{
    app.player.pos = app.player.pos + app.player.vel * (app.player.speed * app.dt);
}

// clip player position to to bounds of the screen
void screenclip_player(void)
{
	Vec2 r = {0};
    bool collide = false;

    if(app.player.pos.x < 0 + app.playerSprite->w / 2.0f)
    {
        app.player.pos.x = 0 + app.playerSprite->w / 2.0f;
        r = {1, 0};
        collide = true;
    }
	
    if(app.player.pos.x > SCREEN_WIDTH - app.playerSprite->w / 2.0f)
    {
        app.player.pos.x = SCREEN_WIDTH - app.playerSprite->w / 2.0f;
        r = {-1, 0};
        collide = true;
    }

	if(app.player.pos.y < 0 + app.playerSprite->h / 2.0f)
    {
        app.player.pos.y = 0 + app.playerSprite->h / 2.0f;
        r = {0, -1};
        collide = true;
    }

	if(app.player.pos.y > SCREEN_HEIGHT - app.playerSprite->h / 2.0f)
    {
        app.player.pos.y = SCREEN_HEIGHT - app.playerSprite->h / 2.0f;
        r = {0, 1};
        collide = true;
    }

    if(collide)
        app.player.vel = app.player.vel - (r * 2.0f) * dot_product(app.player.vel, r);
}

void player_collision(void)
{
    for(u32 i = 0; i < app.enemyCount; i++)
    {
        // check how close player is to enemies
        f32 distance = check_distance(app.player.pos, app.enemy[i].pos);
        if(distance < ((app.playerSprite->w / 2) + (app.enemySprite->w / 2)))
        {
            // what happens here
        }
    }
}


//^^^^^^^^^^^^^^^^^ basic move instructions ^^^^^^^^^^^^^^^^^^^^^^^^^
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

Vec2 move_stop(void)
{
    return {0, 0};
}
