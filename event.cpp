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
#include <string.h>

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

	event::gui_event_stack = (event::gevent*)malloc(sizeof(event::gevent)*512);
	cgui_event = 0;

	for(int i = 0; i < 512; i++) {
		event::input_text[i] = 0;
	}
	
	shift = false;
	alt = false;

	event::keyboard_layout = event::US;
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

/*! returns the last left mouse button pressed x cord
 */
unsigned int event::get_lm_last_pressed_x() {
	return event::lm_last_pressed_x;
}

/*! returns the last left mouse button pressed y cord
 */
unsigned int event::get_lm_last_pressed_y() {
	return event::lm_last_pressed_y;
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
						event::lm_last_pressed_x = event::lm_pressed_x;
						event::lm_last_pressed_y = event::lm_pressed_y;
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
			switch(active_element->type) {
				// input box
				case 1: {
					char tmp_text[4];
					for(int i = 0; i < 4; i++) {
						tmp_text[i] = 0;
					}
					switch(event::get_event().key.keysym.sym) {
						case SDLK_LEFT:
							sprintf(tmp_text, "%c", event::LEFT);
							strcat(input_text, tmp_text);
							break;
						case SDLK_RIGHT:
							sprintf(tmp_text, "%c", event::RIGHT);
							strcat(input_text, tmp_text);
							break;
						case SDLK_BACKSPACE:
							sprintf(tmp_text, "%c", event::BACK);
							strcat(input_text, tmp_text);
							break;
						case SDLK_SPACE:
							strcat(input_text, " ");
							break;
						case SDLK_DELETE:
							sprintf(tmp_text, "%c", event::DEL);
							strcat(input_text, tmp_text);
							break;
						case SDLK_HOME:
							sprintf(tmp_text, "%c", event::HOME);
							strcat(input_text, tmp_text);
							break;
						case SDLK_END:
							sprintf(tmp_text, "%c", event::END);
							strcat(input_text, tmp_text);
							break;
						case SDLK_TAB:
						case SDLK_CLEAR:
						case SDLK_RETURN:
						case SDLK_PAUSE:
						case SDLK_ESCAPE:
						case SDLK_EXCLAIM:
						case SDLK_QUOTEDBL:
						case SDLK_HASH:
						case SDLK_DOLLAR:
						case SDLK_AMPERSAND:
						case SDLK_LEFTPAREN:
						case SDLK_RIGHTPAREN:
						case SDLK_ASTERISK:
						case SDLK_PLUS:
						case SDLK_COLON:
						case SDLK_LESS:
						case SDLK_GREATER:
						case SDLK_QUESTION:
						case SDLK_AT:
						case SDLK_CARET:
						case SDLK_UNDERSCORE:
						case SDLK_KP0:
						case SDLK_KP1:
						case SDLK_KP2:
						case SDLK_KP3:
						case SDLK_KP4:
						case SDLK_KP5:
						case SDLK_KP6:
						case SDLK_KP7:
						case SDLK_KP8:
						case SDLK_KP9:
						case SDLK_KP_PERIOD:
						case SDLK_KP_DIVIDE:
						case SDLK_KP_MULTIPLY:
						case SDLK_KP_MINUS:
						case SDLK_KP_PLUS:
						case SDLK_KP_ENTER:
						case SDLK_KP_EQUALS:
						case SDLK_UP:
						case SDLK_DOWN:
						case SDLK_INSERT:
						case SDLK_PAGEUP:
						case SDLK_PAGEDOWN:
						case SDLK_F1:
						case SDLK_F2:
						case SDLK_F3:
						case SDLK_F4:
						case SDLK_F5:
						case SDLK_F6:
						case SDLK_F7:
						case SDLK_F8:
						case SDLK_F9:
						case SDLK_F10:
						case SDLK_F11:
						case SDLK_F12:
						case SDLK_F13:
						case SDLK_F14:
						case SDLK_F15:
						case SDLK_NUMLOCK:
						case SDLK_CAPSLOCK:
						case SDLK_SCROLLOCK:
						case SDLK_RSHIFT:
						case SDLK_LSHIFT:
						case SDLK_RCTRL:
						case SDLK_LCTRL:
						case SDLK_RALT:
						case SDLK_LALT:
						case SDLK_RMETA:
						case SDLK_LMETA:
						case SDLK_RSUPER:
						case SDLK_LSUPER:
						case SDLK_MODE:
						case SDLK_HELP:
						case SDLK_PRINT:
						case SDLK_SYSREQ:
						case SDLK_BREAK:
						case SDLK_MENU:
						case SDLK_POWER:
						case SDLK_EURO:
							//m.print(msg::MDEBUG, NULL, "%s", SDL_GetKeyName(event::get_event().key.keysym.sym));
							break;
						default:
							sprintf(tmp_text, "%s", SDL_GetKeyName(event::get_event().key.keysym.sym));

							if(keyboard_layout == event::DE) {
								switch(event::get_event().key.keysym.sym) {
									case SDLK_QUOTE:
										sprintf(tmp_text, "%s", "�");
										break;
									case SDLK_SEMICOLON:
										sprintf(tmp_text, "%s", "�");
										break;
									case SDLK_LEFTBRACKET:
										sprintf(tmp_text, "%s", "�");
										break;
									case SDLK_RIGHTBRACKET:
										sprintf(tmp_text, "%s", "+");
										break;
									case SDLK_MINUS:
										sprintf(tmp_text, "%s", "�");
										break;
									case SDLK_SLASH:
										sprintf(tmp_text, "%s", "-");
										break;
									case SDLK_BACKSLASH:
										sprintf(tmp_text, "%s", "#");
										break;
									case SDLK_EQUALS:
										sprintf(tmp_text, "%s", "�");
										break;
									case SDLK_BACKQUOTE:
										sprintf(tmp_text, "%s", "^");
										break;
								}
							}

							Uint8 *keys = SDL_GetKeyState(NULL);
							if(keys[SDLK_RSHIFT] == SDL_PRESSED
								|| keys[SDLK_LSHIFT] == SDL_PRESSED) {
								shift = true;
							}
							if(keys[SDLK_RALT] == SDL_PRESSED
								|| keys[SDLK_LALT] == SDL_PRESSED) {
								alt = true;
							}

							char key;
							if(shift) {
								key = toupper(tmp_text[0]);
								if(keyboard_layout == event::DE) {
									switch(key) {
										case '�':
											key = '�';
											break;
										case '�':
											key = '�';
											break;
										case '�':
											key = '�';
											break;
										case '�':
											key = '?';
											break;
										case '1':
											key = '!';
											break;
										case '2':
											key = '"';
											break;
										case '3':
											key = '�';
											break;
										case '4':
											key = '$';
											break;
										case '5':
											key = '%';
											break;
										case '6':
											key = '&';
											break;
										case '7':
											key = '/';
											break;
										case '8':
											key = '(';
											break;
										case '9':
											key = ')';
											break;
										case '0':
											key = '=';
											break;
										case ',':
											key = ';';
											break;
										case '.':
											key = ':';
											break;
										case '-':
											key = '_';
											break;
										case '#':
											key = '\'';
											break;
										case '+':
											key = '*';
											break;
										case '�':
											key = '`';
											break;
										case '^':
											key = '�';
											break;
										/*case '':
											key = '';
											break;
										case '':
											key = '';
											break;*/
									}
								}
							}
							else if(alt) {
								key = tmp_text[0];
								if(keyboard_layout == event::DE) {
									switch(key) {
										case '�':
											key = '\\';
											break;
										case '2':
											key = '�';
											break;
										case '3':
											key = '�';
											break;
										case '7':
											key = '{';
											break;
										case '8':
											key = '[';
											break;
										case '9':
											key = ']';
											break;
										case '0':
											key = '}';
											break;
										case 'q':
											key = '@';
											break;
										case 'm':
											key = '�';
											break;
										case '+':
											key = '~';
											break;
										/*case '':
											key = '';
											break;
										case '':
											key = '';
											break;*/
									}
								}
							}
							else {
								key = tmp_text[0];
							}

							sprintf(tmp_text, "%c", key);
							strcat(input_text, tmp_text);

							shift = false;
							alt = false;
							break;
					}
				}
				break;
				default:
					break;
			}
			break;
	}
}

/*! returns true if there is any gui event in stack
 */
bool event::is_gui_event() {
	// if stack counter is equal to 0, then there are no gui events
	if(cgui_event == 0) { return false; }
	// else there is a gui event - decrement stack pointer
	else { cgui_event--; return true; }
}

/*! returns the current gui event
 */
event::gevent event::get_gui_event() {
	return gui_event_stack[cgui_event+1];
}

/*! adds a gui event to the stack
 *  @param event_type the event type we want to add
 *  @param id the id of the gui element
 */
void event::add_gui_event(GEVENT_TYPE event_type, unsigned int id) {
	cgui_event++;
	gui_event_stack[cgui_event].type = event_type;
	gui_event_stack[cgui_event].id = id;
}

event::gui_element* event::get_active_element() {
	return event::active_element;
}

void event::set_active_element(event::gui_element* active_element) {
	event::active_element = active_element;
}

char* event::get_input_text() {
	char* tmp_text = (char*)malloc(512);
	strcpy(tmp_text, input_text);
	for(int i = 0; i < 512; i++) {
        event::input_text[i] = 0;
	}
	return tmp_text;
}

void event::set_keyboard_layout(IKEY_LAYOUT layout) {
	event::keyboard_layout = layout;
}
