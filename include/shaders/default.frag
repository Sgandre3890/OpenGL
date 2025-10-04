#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

void main()
{
    // ambient lighting
    float ambient = 0.20;

    // diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0);

    // specular lighting
    float specularLight = 0.50;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 8);
    float specular = specAmount * specularLight;

    // combine the lighting factors
    float lighting = clamp(diffuse + ambient + specular, 0.0, 1.0);

    // sample the texture (RGB only)
    vec3 texColor = texture(tex0, texCoord).rgb;

    // apply light color (RGB only)
    vec3 result = texColor * lightColor.rgb * lighting;

	//FragColor = vec4(texColor * vec3(1,0,0), 1.0);
	//FragColor = vec4(vec3(diffuse), 1.0);
	//FragColor = vec4(texColor, 1.0); // should display the texture exactly as-is
    FragColor = vec4(result, 1.0); // final color with solid alpha
	//FragColor = lightColor;

}