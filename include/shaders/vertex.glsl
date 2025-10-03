#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 fragColor;
out vec2 fragTexCoord;

uniform mat4 ViewMatrix;

void main()
{
    gl_Position = ViewMatrix * vec4(aPos, 1.0);
    fragColor = color;
    fragTexCoord = texCoord;
}
