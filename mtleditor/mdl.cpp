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

#include "mdl.h"

mdl::mdl(engine* e, scene* sce, camera* cam) {
	mdl::e = e;
	mdl::sce = sce;
	mdl::m = e->get_msg();
	mdl::f = e->get_file_io();
	mdl::cam = cam;

	mdl::model = NULL;
	mdl::amodel = NULL;
	mdl::mat = NULL;
	mdl::ani = false;

	mdl::mdl_ld = false;
}

mdl::~mdl() {
	if(mdl::model != NULL) {
		sce->delete_model(model);
		delete model;
	}
	if(mdl::amodel != NULL) {
		sce->delete_model(amodel);
		delete amodel;
	}
	if(mdl::mat != NULL) {
		delete mat;
	}
}

void mdl::close_model() {
	if(model != NULL) {
		sce->delete_model(model);
		delete model;
		model = NULL;
	}
	else if(amodel != NULL) {
		sce->delete_model(amodel);
		delete amodel;
		amodel = NULL;
	}

	if(mdl::mat != NULL) {
		delete mat;
	}

	mdl::mat = NULL;
	mdl::ani = false;
	mdl::mdl_ld = false;

	mat_fname = "";
}

void mdl::load_model(char* filename, char* ani_filename) {
	if(model != NULL) {
		sce->delete_model(model);
		delete model;
		model = NULL;
	}
	else if(amodel != NULL) {
		sce->delete_model(amodel);
		delete amodel;
		amodel = NULL;
	}

	ani = sce->is_a2eanim(filename);

	if(!ani) {
		model = sce->create_a2emodel();
		model->load_model(filename, true);
		sce->add_model(model);
	}
	else {
		amodel = sce->create_a2eanim();
		amodel->load_model(filename, true);
		amodel->add_animation(ani_filename);
		sce->add_model(amodel);
	}

	mdl::mdl_ld = true;

	// reset cam
	core::aabbox* bbox = ani ? amodel->get_bounding_box() : model->get_bounding_box();
	vertex3* p = ani ? amodel->get_position() : model->get_position();
	vertex3* et = new vertex3(bbox->vmax - bbox->vmin);

	cam->set_position(-(p->x + et->x), -(p->y + et->y), -(p->z + et->z));
	cam->set_rotation(0.0f, 45.0f, 0.0f);

	delete et;
}

void mdl::set_material(char* filename) {
	if(mat != NULL) {
		delete mat;
	}

	mat = new a2ematerial(e);
	mat->load_material(filename);

	if(!ani) {
		model->set_material(mat);
	}
	else {
		amodel->set_material(mat);
	}

	mat_fname = filename;
}

a2ematerial* mdl::get_material() {
	return mdl::mat;
}

void mdl::save_material(const char* filename) {
	mdl::f->open_file((char*)filename, file_io::OT_WRITE_BINARY);

	mdl::f->write_block("A2EMATERIAL", 11);

	unsigned int object_count = ani ? amodel->get_object_count() : model->get_object_count();
	mdl::f->put_uint(object_count);
	for(unsigned int i = 0; i < object_count; i++) {
		char mtype = mat->get_material_type(i);
		mdl::f->put_char(mtype);

		a2ematerial::texture_elem* te = mat->get_tex_elem(i);
		unsigned int tex_count = mat->get_texture_count(i);

		if(mtype == 0x04) {
			mdl::f->put_uint(tex_count);

			for(unsigned int j = 0; j < tex_count; j++) {
				mdl::f->put_char(mat->get_color_type(i, j));
				mdl::f->put_char(te->rgb_combine[j]);
				mdl::f->put_char(te->alpha_combine[j]);

				unsigned int argc_rgb = 0;
				unsigned int argc_alpha = 0;
				switch(te->rgb_combine[j]) {
					case 0x00:
						argc_rgb = 1;
						break;
					case 0x01:
					case 0x02:
					case 0x03:
					case 0x04:
						argc_rgb = 2;
						break;
					case 0x05:
						argc_rgb = 3;
						break;
					case 0xFF:
						argc_rgb = 0;
						break;
				}

				switch(te->alpha_combine[j]) {
					case 0x00:
						argc_alpha = 1;
						break;
					case 0x01:
					case 0x02:
					case 0x03:
					case 0x04:
						argc_alpha = 2;
						break;
					case 0x05:
						argc_alpha = 3;
						break;
					case 0xFF:
						argc_alpha = 0;
						break;
				}

				for(unsigned int k = 0; k < argc_rgb; k++) {
					mdl::f->put_char(te->rgb_source[j][k]);
					mdl::f->put_char(te->rgb_operand[j][k]);
				}

				for(unsigned int k = 0; k < argc_alpha; k++) {
					mdl::f->put_char(te->alpha_source[j][k]);
					mdl::f->put_char(te->alpha_operand[j][k]);
				}
			}
		}
		else {
			for(unsigned int j = 0; j < tex_count; j++) {
				mdl::f->put_char(mat->get_color_type(i, j));
			}
		}
		for(unsigned int j = 0; j < tex_count; j++) {
			mdl::f->write_block((char*)te->tex_names[j].c_str(), (unsigned int)te->tex_names[j].size());
			mdl::f->put_char('�'); // 255/0xFF ... C4309?
		}
	}

	mdl::f->close_file();
}

bool mdl::is_model() {
	return mdl::mdl_ld;
}
