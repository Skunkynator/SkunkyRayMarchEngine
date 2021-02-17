
#version 330 core

layout (location = 0) in vec2 aPos;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos,0,1);
    TexCoord = aPos;
}
