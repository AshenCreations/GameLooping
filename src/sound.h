#pragma once
#include "common.h"

Mix_Music* load_music(const char* file);
Mix_Chunk* load_sound(const char* file);
void play_music(Mix_Music *music);
void play_sound(Mix_Chunk *sound);


enum SoundChannels
{
	CHANNEL_MUSIC,
	CHANNEL_SFX_1,
	CHANNEL_SFX_2,
	CHANNEL_SFX_3,
	CHANNEL_SFX_4,
	CHANNEL_SFX_5,
	CHANNEL_SFX_6,
	CHANNEL_UI,

	CHANNEL_COUNT
};
