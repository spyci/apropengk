#version 450 core
#define NR_POINT_LIGHTS 4
struct PointLight{
	vec3 pos;
	vec3 attn;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct DirLight{
	vec3 dir;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
/*
struct Light {
	vec3 attn;
 	vec3 lightDir;
	vec3 SpotDir;
	float cutoff;
	float outtercutoff;
	vec3 lightColor;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
*/
struct Material {
	sampler2D diffuse;
	vec3 ambient;	
	vec3 objectColor;
	sampler2D specular;
	float shininess;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_diffuse4;
uniform sampler2D texture_diffuse5;
uniform sampler2D texture_diffuse6;
uniform sampler2D texture_diffuse7;
uniform sampler2D texture_diffuse8;
uniform sampler2D texture_diffuse9;
uniform sampler2D texture_diffuse10;
uniform sampler2D texture_diffuse11;
uniform sampler2D texture_diffuse12;
uniform sampler2D texture_diffuse13;
uniform sampler2D texture_diffuse14;
uniform sampler2D texture_diffuse15;
uniform sampler2D texture_diffuse16;
uniform sampler2D texture_diffuse17;
uniform sampler2D texture_diffuse18;
uniform sampler2D texture_diffuse19;
uniform sampler2D texture_diffuse20;
uniform sampler2D texture_diffuse21;
uniform sampler2D texture_diffuse22;
uniform sampler2D texture_diffuse23;
uniform sampler2D texture_diffuse24;
uniform sampler2D texture_diffuse25;
uniform sampler2D texture_diffuse26;
uniform sampler2D texture_diffuse27;
uniform sampler2D texture_diffuse28;
uniform sampler2D texture_diffuse29;
uniform sampler2D texture_diffuse30;
uniform sampler2D texture_diffuse31;
uniform sampler2D texture_diffuse32;

uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;
uniform sampler2D texture_specular4;
uniform sampler2D texture_specular5;
uniform sampler2D texture_specular6;
uniform sampler2D texture_specular7;
uniform sampler2D texture_specular8;
uniform sampler2D texture_specular9;
uniform sampler2D texture_specular10;
uniform sampler2D texture_specular11;
uniform sampler2D texture_specular12;
uniform sampler2D texture_specular13;
uniform sampler2D texture_specular14;
uniform sampler2D texture_specular15;
uniform sampler2D texture_specular16;
uniform sampler2D texture_specular17;
uniform sampler2D texture_specular18;
uniform sampler2D texture_specular19;
uniform sampler2D texture_specular20;
uniform sampler2D texture_specular21;
uniform sampler2D texture_specular22;
uniform sampler2D texture_specular23;
uniform sampler2D texture_specular24;
uniform sampler2D texture_specular25;
uniform sampler2D texture_specular26;
uniform sampler2D texture_specular27;
uniform sampler2D texture_specular28;
uniform sampler2D texture_specular29;
uniform sampler2D texture_specular30;
uniform sampler2D texture_specular31;
uniform sampler2D texture_specular32;

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
uniform vec3 objectColor;
uniform Material material;
uniform mat4 view;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 FragPos, mat4 view, Material material, vec2 TexCoords)
{
	vec3 TexVec = vec3(texture(material.diffuse, TexCoords));
	vec3 lightDirView = vec3(view  * vec4(normalize(light.dir), 0.0f));
	vec3 ambient = light.ambient * TexVec; 
	
	float diff = max(dot(normal, lightDirView), 0);
	vec3 diffuse =  diff * light.diffuse * TexVec;
	
	vec3 reflect = reflect(-lightDirView, normal);
	float spec = pow(max(dot(normalize(-FragPos), reflect), 0), material.shininess);
	vec3 specular = spec * light.specular * vec3(texture(material.specular, TexCoords));
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 FragPos, mat4 view, Material material, vec2 TexCoords)
{
	vec3 TexVec = vec3(texture(material.diffuse, TexCoords));
	vec3 lightPosView = vec3(view * vec4(light.pos, 1.0f));
	float distance = length(lightPosView - FragPos);
	float atten = 1.0/(light.attn.x + light.attn.y * distance + light.attn.z * distance * distance);
	
	vec3 ambient = light.ambient * TexVec;

	vec3 lightDir_ = normalize(lightPosView-FragPos);
	float diff = max(dot(normal, lightDir_), 0.0);
	vec3 diffuse = diff * light.diffuse * TexVec;

	
	vec3 reflect = reflect(-lightDir_, normal);
	float spec = pow(max(dot(reflect,normalize(-FragPos)), 0), material.shininess);
	vec3 specular = spec * light.specular * vec3(texture(material.specular, TexCoords));

	return atten * (ambient + diffuse + specular);
}

void main()
{
	//Precalculate
	vec3 norm = normalize(Normal);
	vec3 result = CalcDirLight(dirLight, norm, FragPos, view, material, TexCoords);
	for(int i = 0; i<NR_POINT_LIGHTS; i++)
			result += CalcPointLight(pointLights[i], norm, FragPos, view, material, TexCoords);
	FragColor = vec4(result, 1.0f);
}

