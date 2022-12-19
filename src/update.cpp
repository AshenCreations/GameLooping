#include "update.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ BEGIN DECLARATIONS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void update(void);
void spawn_enemy(void);
void update_enemy(void);
void screenclip_enemy(void);
void update_player(void);
void screenclip_player(void);
Vec2 move_up(void);
Vec2 move_down(void);
Vec2 move_left(void);
Vec2 move_right(void);
Vec2 move_stop(void);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END DECLARATIONS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void update(void)
{
    spawn_enemy();
    update_enemy();
    screenclip_enemy();

    update_player();
    screenclip_player();
}

// spawn enemies
void spawn_enemy(void)
{
    if((app.eSpawn.numberSpawned < app.eSpawn.maxSpawns) && (app.eSpawn.cooldown < 0))
    {
        app.enemy[app.eSpawn.numberSpawned].alive = true;
        app.enemy[app.eSpawn.numberSpawned].pos = app.eSpawn.pos;
        app.enemy[app.eSpawn.numberSpawned].vel = move_down() + (move_right() * 1.58f);
        app.enemy[app.eSpawn.numberSpawned].speed = app.eSpawn.spawnedSpeed;

        app.enemy[app.eSpawn.numberSpawned].dest = WAYPOINT_1;
        
        app.eSpawn.numberSpawned++;
        app.eSpawn.cooldown = 1000;
        app.enemyCount++;
        
        // nope @ last enemy spawned
        if(app.enemyCount == app.eSpawn.maxSpawns)
            play_sound(app.sounds.nope);
    }
    app.eSpawn.cooldown--;
}

// update enemy position
void update_enemy(void)
{
    for(int i = 0; i < app.enemyCount; i++)
    {
       	// diagonal movement
        if(app.enemy[i].vel.x != 0 && app.enemy[i].vel.y != 0)
        {
            app.enemy[i].vel = unit_Vec2(app.enemy[i].vel);
        }

        app.enemy[i].pos += app.enemy[i].vel * (app.enemy[i].speed * app.dt);
    }
}

void screenclip_enemy(void)
{
	Vec2 r;

    for(int i = 0; i < app.enemyCount; i++)
    {
        bool collide = false;
        if(app.enemy[i].pos.x < 0 + app.smiley->w / 2.0f)
        {
            r = {1, 0};
            collide = true;
        }
        if(app.enemy[i].pos.x > SCREEN_WIDTH - app.smiley->w / 2.0f)
        {
            r = {-1, 0};
            collide = true;
        }
        if(app.enemy[i].pos.y < 0 + app.smiley->h / 2.0f)
        {
            r = {0, 1};
            collide = true;
        }
        if(app.enemy[i].pos.y > SCREEN_HEIGHT - app.smiley->h / 2.0f)
        {
            r = {0, -1};
            collide = true;
        }
        
        if(collide)
        {
            app.enemy[i].vel = app.enemy[i].vel - (r * 2.0f) * dot_product(app.enemy[i].vel, r);
            
            // bruh on screenedge reflect
            if(app.enemyCount < app.eSpawn.maxSpawns)
                play_sound(app.sounds.bruh);
        }
    }
}

void update_player(void)
{
    // update position    
    app.player.pos = app.player.pos + app.player.vel * (app.player.speed * app.dt);
}

void screenclip_player(void)
{
	Vec2 r;
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

