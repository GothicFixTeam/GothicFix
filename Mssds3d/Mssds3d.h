#ifndef _MSS_DS3D_
#define _MSS_DS3D_

MSS_SAMPLE_CALLBACK __stdcall M3D_set_3D_EOS(M3D_SAMPLE client, M3D_SAMPLE samp, MSS_SAMPLE_CALLBACK cb);
uInt __stdcall M3D_3D_sample_query_attribute(M3D_SAMPLE samp, M3D_ATTRIB index);
int __stdcall M3D_3D_set_sample_preference(M3D_SAMPLE samp, M3D_ATTRIB preference, void const * value);
void __stdcall M3D_set_3D_speaker_type(int speaker_type);
int __stdcall M3D_3D_speaker_type(void);
void __stdcall M3D_set_3D_sample_obstruction(M3D_SAMPLE samp, float obstruction);
float __stdcall M3D_3D_sample_obstruction(M3D_SAMPLE samp);
void __stdcall M3D_set_3D_sample_occlusion(M3D_SAMPLE samp, float occlusion);
float __stdcall M3D_3D_sample_occlusion(M3D_SAMPLE samp);
void __stdcall M3D_set_3D_sample_cone(M3D_SAMPLE samp, float inner_angle, float outer_angle, int outer_volume);
void __stdcall M3D_3D_sample_cone(M3D_SAMPLE samp, float* inner_angle, float* outer_angle, int* outer_volume);

uInt __stdcall PROVIDER_query_attribute(M3D_ATTRIB index);
M3D_RESULT __stdcall M3D_startup(void);
const char* __stdcall M3D_error(void);
M3D_RESULT __stdcall M3D_shutdown(void);
int __stdcall M3D_set_provider_preference(M3D_ATTRIB preference, void const* value);
M3D_RESULT __stdcall M3D_activate(int enable);
M3D_SAMPLE __stdcall M3D_allocate_3D_sample_handle(void);
void __stdcall M3D_release_3D_sample_handle(M3D_SAMPLE samp);
void __stdcall M3D_start_3D_sample(M3D_SAMPLE samp);
void __stdcall M3D_stop_3D_sample(M3D_SAMPLE samp);
void __stdcall M3D_resume_3D_sample(M3D_SAMPLE samp);
void __stdcall M3D_end_3D_sample(M3D_SAMPLE samp);
int __stdcall M3D_set_3D_sample_data(M3D_SAMPLE samp, const M3D_SOUNDINFO* info);
void __stdcall M3D_set_3D_sample_volume(M3D_SAMPLE samp, G32 volume);
void __stdcall M3D_set_3D_sample_playback_rate(M3D_SAMPLE samp, int playback_rate);
void __stdcall M3D_set_3D_sample_offset(M3D_SAMPLE samp, uInt offset);
void __stdcall M3D_set_3D_sample_loop_count(M3D_SAMPLE samp, uInt loops);
void __stdcall M3D_set_3D_sample_loop_block(M3D_SAMPLE S, int loop_start_offset, int loop_end_offset);
uInt __stdcall M3D_3D_sample_status(M3D_SAMPLE samp);
G32 __stdcall M3D_3D_sample_volume(M3D_SAMPLE samp);
int __stdcall M3D_3D_sample_playback_rate(M3D_SAMPLE samp);
uInt __stdcall M3D_3D_sample_offset(M3D_SAMPLE samp);
uInt __stdcall M3D_3D_sample_length(M3D_SAMPLE samp);
uInt __stdcall M3D_3D_sample_loop_count(M3D_SAMPLE samp);
void __stdcall M3D_set_3D_sample_distances(M3D_SAMPLE samp, float max_dist, float min_dist);
void __stdcall M3D_3D_sample_distances(M3D_SAMPLE samp, float * max_dist, float * min_dist);
int __stdcall M3D_active_3D_sample_count(void);
M3D_OBJECT* __stdcall M3D_3D_open_listener(void);
void __stdcall M3D_3D_close_listener(M3D_OBJECT* listener);
M3D_OBJECT* __stdcall M3D_3D_open_object(void);
void __stdcall M3D_3D_close_object(M3D_OBJECT* obj);
void __stdcall M3D_set_3D_position(M3D_OBJECT* obj, float X, float Y, float Z);
void __stdcall M3D_set_3D_velocity(M3D_OBJECT* obj, float dX_per_ms, float dY_per_ms, float dZ_per_ms, float magnitude);
void __stdcall M3D_set_3D_velocity_vector(M3D_OBJECT* obj, float dX_per_ms, float dY_per_ms, float dZ_per_ms);
void __stdcall M3D_set_3D_orientation(M3D_OBJECT* obj, float X_face, float Y_face, float Z_face, float X_up, float Y_up, float Z_up);
void __stdcall M3D_3D_position(M3D_OBJECT*  obj, float *X, float *Y, float *Z);
void __stdcall M3D_3D_velocity(M3D_OBJECT* obj, float *dX_per_ms, float *dY_per_ms, float *dZ_per_ms);
void __stdcall M3D_3D_orientation(M3D_OBJECT*  obj, float *X_face, float *Y_face, float *Z_face, float *X_up, float *Y_up, float *Z_up);
void __stdcall M3D_3D_update_position(M3D_OBJECT* obj, float dt_milliseconds);
void __stdcall M3D_3D_auto_update_position(M3D_OBJECT* obj, int enable);

int __stdcall M3D_3D_room_type(void);
void __stdcall M3D_set_3D_room_type(int EAX_room_type);
void __stdcall M3D_set_3D_sample_effects_level(M3D_SAMPLE samp, float effects_level);
float __stdcall M3D_3D_sample_effects_level(M3D_SAMPLE samp);

#endif