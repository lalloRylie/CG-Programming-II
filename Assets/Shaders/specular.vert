#version 330 core

//https://en.wikibooks.org/wiki/GLSL_Programming/GLUT/Multiple_Lights
//https://developer.valvesoftware.com/wiki/Constant-Linear-Quadratic_Falloff
//TODO: point lights...
//TODO: attenuation...
//TODO: spot lights
//TODO: per pixel lighting...
//TODO: multiple lights in scene...

//TODO: next week, Introduction to antialiasing and texture mipmapping
//Last week, sun and moon scene. show off projects...

layout(location = 0) in vec3 vertPos;
layout(location = 2) in vec3 vertNorm;

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat4 normMatrix;

uniform float glow = 0.0f;
uniform float objRefl = 0.03f;
uniform float objSpecRefl = 1.0f;
uniform int shininess = 72;

uniform vec3 lightPos = vec3(1.0f, 0.0f, 0.0f);
uniform vec3 viewPos = vec3(0.0f, 1.0f, 0.0f);
uniform vec3 lightCol = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 objColor = vec3(0.7f, 0.5f, 0.8f);

out vec3 vertColor;

void main(){
	vec3 normal = normalize((normMatrix * vec4(vertNorm, 1)).xyz);
	vec3 viewDir = normalize(viewPos - vertPos);
	vec3 half = normalize(lightDir + viewDir);
	float nDotL = max(dot(normal, lightDir), 0);
	float facing = ((nDotL > 0.0f) ? 1 : 0);
	vec3 emissive = objColor * glow;										
	vec3 ambient= objRefl * lightCol;										
	vec3 diffuse = objColor * lightCol * nDotL;		
	vec3 specular = objSpecRefl * lightCol * facing * pow(max(dot(normal,half), 0),shininess);	

	vertColor = emissive + ambient + diffuse + specular;
	gl_Position = MVPMatrix * vec4(vertPos, 1);
}