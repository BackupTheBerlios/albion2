/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <iostream>
using namespace std;
#include "event.h"

/*! there is no function currently
 */
event::event() {
}

/*! there is no function currently
 */
event::~event() {
}

/*! initializes the event class and sets an sdl_event handler
 *  @param ievent the sdl_event we want to handle
 */
void event::init(SDL_Event ievent) {
	event::event_handle = ievent;
}

/*! returns 1 if the are any sdl events, otherwise it will return 0
 */
int event::is_event() {
	return SDL_PollEvent(&event_handle);
}

/*! returns the sdl_event handle
 */
SDL_Event event::get_event() {
	return event_handle;
}

/*! returns the left mouse button pressed x cord
 */
unsigned int event::get_lm_pressed_x() {
	return event::lm_pressed_x;
}

/*! returns the left mouse button pressed y cord
 */
unsigned int event::get_lm_pressed_y() {
	return event::lm_pressed_y;
}

/*! handles the sdl_events
 *  @param event_type the event type, we want to handle
 */
void event::handle_events(unsigned int event_type) {
	// get events
	switch(event_type)
	{
		// internal engine event handler
		case SDL_MOUSEBUTTONDOWN:
			switch(event::get_event().button.button) {
				case SDL_BUTTON_LEFT:
					if(event::get_event().button.state == SDL_PRESSED) {
						event::lm_pressed_x = event::get_event().button.x;
						event::lm_pressed_y = event::get_event().button.y;
					}
					break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch(event::get_event().button.button) {
				case SDL_BUTTON_LEFT:
					if(event::get_event().button.state == SDL_RELEASED) {
						event::lm_pressed_x = 0;
						event::lm_pressed_y = 0;
					}
					break;
			}
			break;
		case SDL_KEYDOWN:
			break;
	}
}
