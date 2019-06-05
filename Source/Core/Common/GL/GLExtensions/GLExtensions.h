// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include <string>

#include "CommonTypes.h"

#include "GL/GLExtensions/AMD_pinned_memory.h"
#include "GL/GLExtensions/ARB_ES2_compatibility.h"
#include "GL/GLExtensions/ARB_ES3_compatibility.h"
#include "GL/GLExtensions/ARB_blend_func_extended.h"
#include "GL/GLExtensions/ARB_buffer_storage.h"
#include "GL/GLExtensions/ARB_clip_control.h"
#include "GL/GLExtensions/ARB_compute_shader.h"
#include "GL/GLExtensions/ARB_copy_image.h"
#include "GL/GLExtensions/ARB_debug_output.h"
#include "GL/GLExtensions/ARB_draw_elements_base_vertex.h"
#include "GL/GLExtensions/ARB_framebuffer_object.h"
#include "GL/GLExtensions/ARB_get_program_binary.h"
#include "GL/GLExtensions/ARB_map_buffer_range.h"
#include "GL/GLExtensions/ARB_occlusion_query2.h"
#include "GL/GLExtensions/ARB_sample_shading.h"
#include "GL/GLExtensions/ARB_sampler_objects.h"
#include "GL/GLExtensions/ARB_shader_image_load_store.h"
#include "GL/GLExtensions/ARB_shader_storage_buffer_object.h"
#include "GL/GLExtensions/ARB_sync.h"
#include "GL/GLExtensions/ARB_texture_compression_bptc.h"
#include "GL/GLExtensions/ARB_texture_multisample.h"
#include "GL/GLExtensions/ARB_texture_storage.h"
#include "GL/GLExtensions/ARB_texture_storage_multisample.h"
#include "GL/GLExtensions/ARB_uniform_buffer_object.h"
#include "GL/GLExtensions/ARB_vertex_array_object.h"
#include "GL/GLExtensions/ARB_viewport_array.h"
#include "GL/GLExtensions/EXT_texture_compression_s3tc.h"
#include "GL/GLExtensions/EXT_texture_filter_anisotropic.h"
#include "GL/GLExtensions/HP_occlusion_test.h"
#include "GL/GLExtensions/KHR_debug.h"
#include "GL/GLExtensions/NV_depth_buffer_float.h"
#include "GL/GLExtensions/NV_occlusion_query_samples.h"
#include "GL/GLExtensions/NV_primitive_restart.h"
#include "GL/GLExtensions/gl_1_1.h"
#include "GL/GLExtensions/gl_1_2.h"
#include "GL/GLExtensions/gl_1_3.h"
#include "GL/GLExtensions/gl_1_4.h"
#include "GL/GLExtensions/gl_1_5.h"
#include "GL/GLExtensions/gl_2_0.h"
#include "GL/GLExtensions/gl_2_1.h"
#include "GL/GLExtensions/gl_3_0.h"
#include "GL/GLExtensions/gl_3_1.h"
#include "GL/GLExtensions/gl_3_2.h"
#include "GL/GLExtensions/gl_4_2.h"
#include "GL/GLExtensions/gl_4_3.h"
#include "GL/GLExtensions/gl_4_4.h"
#include "GL/GLExtensions/gl_4_5.h"

class GLContext;

namespace GLExtensions
{
// Initializes the interface
bool Init(GLContext* context);

// Function for checking if the hardware supports an extension
// example: if (GLExtensions::Supports("GL_ARB_multi_map"))
bool Supports(const std::string& name);

// Returns OpenGL version in format 430
u32 Version();
}  // namespace GLExtensions
