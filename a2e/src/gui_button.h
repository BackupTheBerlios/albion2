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
 
#ifndef __GUI_BUTTON_H__
#define __GUI_BUTTON_H__

#include <iostream>
#include <SDL/SDL.h>
#include "msg.h"
#include "core.h"
#include "gfx.h"
#include "engine.h"
#include "image.h"
#include "gui_text.h"
#include "gui_object.h"
#include "gui_style.h"
using namespace std;

#include "win_dll_export.h"

/*! @class gui_button
 *  @brief gui button element functions
 *  @author flo
 *  @todo more functions
 *  
 *  the gui_button class
 */

class A2E_API gui_button : public gui_object
{
public:
	gui_button(engine* e, gui_style* gs);
	~gui_button();

	// gui button element variables functions
	void set_image_scaling(bool state);
	bool get_image_scaling();

protected:
	msg* m;
	core* c;
	engine* e;
	gfx* g;

	bool img_scale;

};

#endif
