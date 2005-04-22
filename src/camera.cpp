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

#include "camera.h"
#include "msg.h"
#include <math.h>

/*! there is no function currently
 */
camera::camera() {
	camera::position = new core::vertex3();
	camera::rotation = new core::vertex3();

	// 2 pi / 360� = pi / 180
	piover180 = (float)PI / 180.0f;

	up_down = 0.0f;
}

/*! there is no function currently
 */
camera::~camera() {
	m.print(msg::MDEBUG, "camera.cpp", "freeing camera stuff");

	delete camera::position;
	delete camera::rotation;

	m.print(msg::MDEBUG, "camera.cpp", "camera stuff freed");
}

/*! initializes the camera
 *  @param iengine pointer to the engine class for creating an engine handler
 *  @param ievent pointer to the event class for creating an event handler
 */
void camera::init(engine &iengine, event &ievent) {
	camera::event_handler = &ievent;
	camera::engine_handler = &iengine;

	camera::position->x = 0.0f;
	camera::position->y = 0.0f;
	camera::position->z = 0.0f;
	
	camera::rotation->x = 0.0f;
	camera::rotation->y = 0.0f;
	camera::rotation->z = 0.0f;
}

/*! runs the camera (expected to be called every draw)
 */
void camera::run() {
	// recalculate the cameras position

	if(event_handler->is_key_right()) {
		position->x += (float)sin((rotation->y - 90.0f) * piover180) * 0.75f;
		position->z += (float)cos((rotation->y - 90.0f) * piover180) * 0.75f;
	}

	if(event_handler->is_key_left()) {
		position->x -= (float)sin((rotation->y - 90.0f) * piover180) * 0.75f;
		position->z -= (float)cos((rotation->y - 90.0f) * piover180) * 0.75f;
	}
	
	if(event_handler->is_key_up()) {
		position->x += (float)sin(rotation->y * piover180) * 0.75f;
		position->y += (float)sin(rotation->x * piover180) * 0.75f;
		position->z += (float)cos(rotation->y * piover180) * 0.75f;
	}
	
	if(event_handler->is_key_down()) {
		position->x -= (float)sin(rotation->y * piover180) * 0.75f;
		position->y -= (float)sin(rotation->x * piover180) * 0.75f;
		position->z -= (float)cos(rotation->y * piover180) * 0.75f;
	}
	 
	// calculate the rotation via the current mouse cursor position
	int cursor_pos_x = 0;
	int cursor_pos_y = 0;
	SDL_GetMouseState((int*)&cursor_pos_x, (int*)&cursor_pos_y);

	float xpos = (1.0f / (float)engine_handler->get_screen()->w) * (float)cursor_pos_x;
	float ypos = (1.0f / (float)engine_handler->get_screen()->h) * (float)cursor_pos_y;

	if(xpos < 0.5f || xpos > 0.5f || ypos < 0.5f || ypos > 0.5f) {
		rotation->x += (0.5f - ypos) * 100.0f;
		rotation->y += (0.5f - xpos) * 100.0f;
		SDL_WarpMouse(engine_handler->get_screen()->w/2, engine_handler->get_screen()->h/2);
	}

	// rotate
	glRotatef(360.0f - rotation->x, 1.0f, 0.0f , 0.0f);
	glRotatef(360.0f - rotation->y, 0.0f, 1.0f , 0.0f);

	// reposition
	engine_handler->set_position(camera::position->x, -camera::position->y, camera::position->z);
}

/*! sets the position of the camera
 *  @param x x coordinate
 *  @param y y coordinate
 *  @param z z coordinate
 */
void camera::set_position(float x, float y, float z) {
	camera::position->x = x;
	camera::position->y = y;
	camera::position->z = z;
}

/*! returns the position of the camera
 */
core::vertex3* camera::get_position() {
	return camera::position;
}
