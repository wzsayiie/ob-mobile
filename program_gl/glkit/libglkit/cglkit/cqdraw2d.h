#pragma once

#include "cqcbasis.h"

//global:

CQ_C_LINK float cq_gl_x_from_ui(float w, float x);
CQ_C_LINK float cq_gl_y_from_ui(float h, float y);

CQ_C_LINK void cq_enable_alpha(bool enabled);

//texture:

struct cq_tex;

//parameters [pw, ph] is pixel size.
CQ_C_LINK struct cq_tex *cq_new_tex    (int32_t pw, int32_t ph, const void *data);
CQ_C_LINK struct cq_tex *cq_new_rgb_tex(int32_t pw, int32_t ph, const void *data);

CQ_C_LINK int32_t cq_tex_pw(struct cq_tex *tex);
CQ_C_LINK int32_t cq_tex_ph(struct cq_tex *tex);

CQ_C_LINK void cq_del_tex(struct cq_tex *tex);

//frame buffer object:

struct cq_fbo;

CQ_C_LINK struct cq_fbo *cq_new_fbo    (int32_t pw, int32_t ph, const void *data);
CQ_C_LINK struct cq_fbo *cq_new_rgb_fbo(int32_t pw, int32_t ph, const void *data);

CQ_C_LINK struct cq_tex *cq_fbo_tex(struct cq_fbo *fbo);

CQ_C_LINK void cq_del_fbo(struct cq_fbo *fbo);

//draw fbo:

//default screen frame buffer.
extern struct cq_fbo *const CQ_SCREEN_FBO;

CQ_C_LINK void cq_begin_draw_fbo(float w, float h, struct cq_fbo *fbo);
CQ_C_LINK void cq_end_draw_fbo(void);

CQ_C_LINK void cq_clear_current(float r, float g, float b, float a);

CQ_C_LINK void cq_set_draw_color(float r, float g, float b, float a);

//draw polygon on fbo:
CQ_C_LINK void cq_draw_path_start(float x, float y);
CQ_C_LINK void cq_draw_path_add  (float x, float y);
CQ_C_LINK void cq_draw_path_stop (float x, float y);

//draw texture on fbo:
CQ_C_LINK void cq_draw_tex(float x, float y, float w, float h, struct cq_tex *tex);
