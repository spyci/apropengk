#version 450 core
struct Light{
	vec3 lightColor;
};
out vec4 FragColor;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform Light light;
void main()
{
	FragColor = vec4(light.lightColor, 1.0f);
}
