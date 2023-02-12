#version 430 compatibility
out vec4 FragColor;

in vec3 Pos;
in vec3 Norm;
//uniform sampler2D screen;
uniform vec3 lightPos;

vec4 pointLight()
{
	//vec3 lightPos = vec3(0.0, 2.0, 0.0);
	
	vec3 lightVec = lightPos - Pos;
	//vec3 groundColor = dot(Norm,Pos);
	//vec4 lightColor = vec4(groundColor, 1.0);
	vec4 lightColor = vec4(Pos.x, Pos.y, Pos.z, 1.0f);
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	float ambient = 0.50f;

	vec3 normal = normalize(Norm);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// float specularLight = 0.50f;
	// vec3 viewDirection = normalize(camPos - Pos);
	// vec3 reflectionDirection = reflect(-lightDirection, normal);
	// float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	// float specular = specAmount * specularLight;

	return ((diffuse * inten + ambient)) * lightColor;
}


void main()
{
	FragColor = pointLight();
	//FragColor = vec4(Pos.x, Pos.y, Pos.z, 1.0f);
}