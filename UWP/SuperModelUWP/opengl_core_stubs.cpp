// Core OpenGL function linking for UWP Mesa
// Link against Mesa libraries directly

#ifdef _XBOX_UWP

// Link Mesa OpenGL libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "libgallium_wgl.lib")

#endif // _XBOX_UWP

// Empty compilation unit to avoid warning
void dummy_opengl_stubs() {}
