#include "ui.h"

// IMGUI system
void do_gui(void)
{
//	do_menu(menuType, menuRect, menuState, numButtons, buttonS);
}




// menu
void do_menu(void)
{
	GPU_Rect menuRect, buttonRect;
	f32 numButtons, buttonH, buttonSpacing, menuH, menuW;

	numButtons = 3;
	buttonSpacing = 8;
	menuW = 276;
	buttonH = app.button[BUTTON_QUITAPP].texture->h;
	menuH = (numButtons * (buttonH + buttonSpacing)) + buttonSpacing;

	menuRect = {(SCREEN_WIDTH / 2) - menuW / 2, (SCREEN_HEIGHT / 2) - menuH / 2, menuW, menuH};
	draw_menu(menuRect);

	// buttons
	buttonRect = {menuRect.x += buttonSpacing, menuRect.y += buttonSpacing, menuRect.w -= buttonSpacing * 2, buttonH};
	if(do_button(app.button[BUTTON_QUITAPP].index, buttonRect, 2))
		do_event(EVENT_QUIT);
}

// button draw logic
bool do_button(s32 index, GPU_Rect rect, s32 bsize)
{
	SDL_Color color = {0};
	f32 bx, by;
	bool result = do_button_logic(index, rect);

	// drawing button
	GPU_Rect dest;
	dest = {rect.x - 2, rect.y - 2, rect.w + 4, rect.h + 4};
	draw_ui_component_rectangleF(rect, COLOR_BLACK);
	do_button_border(rect, bsize, COLOR_RADIO_GREY3);

	// button text - centered
	bx = rect.x + (rect.w / 2);
	by = rect.y + (rect.h / 2) - 2;
	blit(app.button[index].texture, bx, by);

	// if hot draw a button highlight
	if(app.ui_context.hot.index == index)
	{	
		color = {200, 100, 0, 255};
		do_button_border(rect, bsize, color);
	}

	// TODO: If hot draw a tooltip
	return result;
}

// draws an internal border of width size on edge of button
void do_button_border(GPU_Rect rect, s32 size, SDL_Color color)
{
	for(int i = 0; i < size; i++)
	{
		GPU_Rectangle2(app.renderTarget, rect, color);
		rect.x += 1, rect.y += 1, rect.w -= 2, rect.h -= 2;
	}
}

// use menuRect to draw a menu in the style of Pfui
void draw_menu(GPU_Rect menuRect)
{
	GPU_SetShapeBlendMode(GPU_BLEND_NORMAL_ADD_ALPHA);
	GPU_RectangleFilled2(app.renderTarget, menuRect, {0, 0, 0, 235});
	GPU_SetShapeBlendMode(GPU_BLEND_NORMAL);
	do_button_border(menuRect, 2, COLOR_BLACK);
	menuRect = {menuRect.x + 2, menuRect.y + 2, menuRect.w - 4, menuRect.h - 4};
	do_button_border(menuRect, 2, {125, 75, 25, 255});
}

// logic to see if button has been pressed
bool do_button_logic(s32 index, GPU_Rect mouseRect)
{
	bool activated = false;	
	s32 *hotptr = &app.ui_context.hot.index;
	s32 *actptr = &app.ui_context.active.index;

	// hot/active/activated logic
	if(get_mouse_zone(mouseRect))	// if mouse inside button
		*hotptr = index;			// set hot
	else
		*hotptr = -1;				// set not hot

	if(*actptr == index)			// if active
	{
		if(app.mouse.buttons == 0)	// if lmb up
		{
			if(*hotptr == index)	// if hot
			{
				activated = true;	// button activated
				*actptr = -1;		// set not active
			}
			else
			{
				*hotptr = *actptr = -1;	// if not hot, can't be active either
			}
		}
	}
	else if(*hotptr == index)	// if hot
	{
		if(app.mouse.buttons == SDL_BUTTON_LEFT)	// if lmb down
			*actptr = index;		// set active
	}

	return activated ? true : false;	// return if button was pressed or not
}
