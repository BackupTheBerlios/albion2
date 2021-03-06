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

#ifndef __MODEL_LOADER_H__
#define __MODEL_LOADER_H__

#ifdef WIN32
#include <windows.h>
#endif

#include <iostream>
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
#include <a2emap.h>
#include <scene.h>
#include <ode.h>
#include <ode_object.h>
#include <light.h>
#include <shader.h>
using namespace std;

engine* e;
msg* m;
core* c;
gfx* agfx;
event* aevent;
camera* cam;
ode* o;
shader* s;
scene* sce;

a2emap* mdl_map;

a2ematerial* ground_mat;
a2ematerial* cc_mat;
a2ematerial* scale_mat;
a2emodel* plane;
a2emodel* cottage;
a2emodel* sphere;

ode_object* osphere;
unsigned int refresh_time;

SDL_Event sevent;

bool done = false;
bool wireframe = false;
bool use_a2map = true;

stringstream caption;
stringstream tmp;

int shininess = 64;

#endif
