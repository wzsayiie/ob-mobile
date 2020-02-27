#pragma once

#include "cqdraw2d.h"

CQ_C_LINK cq_tex *cq_img_from_data(const uint8_t *data, int32_t len);
CQ_C_LINK cq_tex *cq_img_from_file(const char *path);
