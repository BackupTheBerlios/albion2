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

#ifndef __CNET_H__
#define __CNET_H__

#ifdef WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <engine.h>
#include <msg.h>
#include <core.h>
#include <gfx.h>
#include <event.h>
#include <camera.h>
#include <a2emodel.h>
#include <scene.h>
#include <ode.h>
#include <ode_object.h>
#include <light.h>
#include <shader.h>
#include <a2emap.h>
#include <net.h>
#include "csystem.h"
#include "cgui.h"
using namespace std;

class cnet {
public:
	cnet(engine* e, csystem* cs, cgui* cg);
	~cnet();

	enum PACKET_TYPE {
		PT_TEST,
		PT_NEW_CLIENT,
		PT_QUIT_CLIENT,
		PT_CHAT_MSG,
		PT_FLAG,
		PT_VU_LIST,
		PT_VO_LIST
	};

	enum FLAGS {
		F_SUCCESS_LOGIN,
		F_WRONG_UNAME,
		F_WRONG_PW,
		F_GET_MAP,
		F_GET_POS,
		F_GET_ROT,
		F_POST_MAP,
		F_POST_POS,
		F_POST_ROT,
		F_MOVE_FORWARD,
		F_MOVE_BACK
	};

	int process_packet(char* data, unsigned int max_len);
	void send_packet(PACKET_TYPE type);
	void handle_server();
	void run();

	void close();

	// used for setting packet data from other classes
	stringstream* get_data();
	void clear_data();

protected:
	engine* e;
	msg* m;
	core* c;
	net* n;
	csystem* cs;
	cgui* cg;
	gui* agui;

	unsigned int max_packet_size;

	stringstream* buffer;
	stringstream* data;

};

#endif
