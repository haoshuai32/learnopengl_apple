//
//  Texture.hpp
//  learnopengl_apple
//
//  Created by haoshuai on 2022/8/17.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>

class Texture {
public:
    unsigned int texture;
    Texture(const char* texturePath){};
    virtual ~Texture() {};
};

#endif /* Texture_hpp */
