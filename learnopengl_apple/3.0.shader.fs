#version 300 core
out lowp vec4 FragColor;

in lowp vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0f);
}
