//
//  TextureImage.hpp
//  learnopengl_apple
//
//  Created by haoshuai on 2022/8/17.
//

#ifndef TextureImage_hpp
#define TextureImage_hpp

#include <stdio.h>

class TextureImage {
private:
    unsigned int texture;
public:
    TextureImage(const char* texturePath);
    ~TextureImage();
    void active_bind(unsigned int texture);
};

#endif /* TextureImage_hpp */
