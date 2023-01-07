#include "update.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ BEGIN DECLARATIONS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void update(void);

void spawn_enemy(void);
void update_enemy(void);
void move_to(Player *player);
void update_player(void);
void screenclip_enemy(void);
void screenclip_player(void);
void player_collision(void);

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

    if(app.player.hasTarget)
        move_to(&app.player);

    update_player();
    screenclip_player();
    player_collision();
}

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
        app.enemy[app.eSpawn.spawnedIdx].minDistance = ENEMY_WAYPOINT_MIN_DISTANCE;
        app.enemy[app.eSpawn.spawnedIdx].collider = {{app.eSpawn.pos}, (f32)app.enemySprite->h / 2};
        app.enemy[app.eSpawn.spawnedIdx].currentHP = app.enemy[app.eSpawn.spawnedIdx].maxHP = 100;

        app.eSpawn.spawnedIdx++;
        app.eSpawn.cooldown = ONE_SECOND;
        app.enemyCount++;
    }
    app.eSpawn.cooldown--;
}

// update enemy position using semi-inplicit Euler integration
void update_enemy(void)
{
    for(s32 i = 0; i < app.enemyCount; i++)
    {
        if(app.enemy[i].alive)
        {
            // check enemy health
            if(app.enemy[i].currentHP <= 0)
            {
                app.enemy[i].alive = false;
            }
            
            // waypoint following
            app.enemy[i].vel = unit_Vec2(app.enemy[i].targetPos - app.enemy[i].pos);

            Circle a = {app.enemy[i].targetPos, app.enemy[i].minDistance};
            Circle b = {app.enemy[i].pos, app.enemy[i].minDistance};
            if(circle_in_circle(a, b))
            {
                // when waypoint reached, set next waypoint
                app.enemy[i].WpIdx++;

                if(app.enemy[i].WpIdx == WAYPOINT_COUNT)
                    app.enemy[i].WpIdx = 0;

                app.enemy[i].targetPos = app.waypoint[app.enemy[i].WpIdx].pos;
            }

            // store current position before calculating new position
            app.enemy[i].oldPos = app.enemy[i].pos;
            app.enemy[i].pos += app.enemy[i].vel * (app.enemy[i].speed * app.dt);
            // find difference of current & old positions for renderer
            app.enemy[i].dPos = app.enemy[i].pos - app.enemy[i].oldPos;

            // check enemy facing dependant on velocity.x value
            if(app.enemy[i].vel.x > 0)
                app.enemy[i].facing = false;
            if(app.enemy[i].vel.x < 0)
                app.enemy[i].facing = true;
        }
    }
}

// moveplayer if has targetPos
void move_to(Player *player)
{
    player->vel = unit_Vec2(player->targetPos - player->pos);

    Circle a = {player->targetPos, player->minDistance};
    Circle b = {player->pos, player->minDistance};

    // when reach target get next waypoint if queue !empty, or stop if queue empty
    if(circle_in_circle(a, b))
    {
        player->vel = move_stop();
        player->hasTarget = false;

        if(dequeue(&player->moveQueue) && !queue_is_empty(&player->moveQueue))
        {
            player->targetPos = queue_front(&player->moveQueue);
            player->hasTarget = true;
        }
        if(queue_is_empty(&player->moveQueue))
        {
            reset_queue(&player->moveQueue);
        }
    }
}

// clip enemy position to to bounds of the screen
void screenclip_enemy(void)
{
	Vec2 r = {0};

    for(s32 i = 0; i < app.enemyCount; i++)
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

// update player position using semi-inplicit Euler integration
void update_player(void)
{
    // store current position before calculating new position
    app.player.oldPos = app.player.pos;
    // update position
    app.player.pos += app.player.vel * (app.player.speed * app.dt);
    // find difference of current & old positions for renderer
    app.player.dPos = app.player.pos - app.player.oldPos;

    // player facing
    if(app.player.vel.x > 0)
        app.player.facing = true;
    if(app.player.vel.x < 0)
        app.player.facing = false;

    // transform moveQueue to seperate linear array for easier rendering
    ring_to_linear_array(&app.player.moveQueue);

    app.player.damageCooldown--;
    if(app.player.damageCooldown <= 0)
        app.player.damageCooldown = -1;

}

// clip player position to screen bounds
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

// semi working player collision
void player_collision(void)
{
    for(s32 i = 0; i < app.enemyCount; i++)
    {
        if(app.enemy[i].alive)
        {
            // check if player collides with enemies
            Circle a = {app.player.pos, app.player.collider.radius};
            Circle b = {app.enemy[i].pos, app.enemy[i].collider.radius};
            if(circle_in_circle(a, b))
            {
                // do collision stuff here
                if(app.player.damageCooldown <= 0)
                {
                    app.enemy[i].currentHP -= app.player.damage;
                    app.player.damageCooldown = ONE_SECOND;
                }
                play_sound(app.sounds.bruh);
            }
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
