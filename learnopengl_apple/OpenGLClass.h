//
//  OpenGLClass.h
//  learnopengl_apple
//
//  Created by haoshuai on 2022/8/16.
//

#ifndef OpenGLClass_h
#define OpenGLClass_h

typedef void* OpenGLClass;

#ifdef __cplusplus
extern "C" {
#endif
OpenGLClass OpenGL_init(const char* vertexPath, const char* fragmentPath);
void OpenGL_deinit(OpenGLClass objc);
void OpenGL_vertex(OpenGLClass objc,
                   const float *vertices,int vertices_count,
                   const int *indices, int indices_count);
void OpenGL_texture_image(OpenGLClass objc,
                          const char* texturePath1, const char* texturePath2);
void OpenGL_update(OpenGLClass objc);
void OpenGL_render(OpenGLClass objc);
void OpenGL_clear_color();
void OpenGL_delete_vertex(OpenGLClass objc);
#ifdef __cplusplus
}
#endif

#endif /* OpenGLClass_h */
