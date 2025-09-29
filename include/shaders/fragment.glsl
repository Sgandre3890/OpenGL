#version 330 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    vec4 tex = texture(texture1, fragTexCoord);
    // Combine vertex color and texture (optional). If you only want the texture, use tex directly.
    FragColor = tex * vec4(fragColor, 1.0);
}
