#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 uvCor;
layout (location = 2) in vec3 aNormal;

out vec2 uv;
out vec3 normal;


// 世界坐标
out vec3 worldPosition;

uniform mat4 transform;
uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;
uniform mat3 normalMatrix;
void main()
{
   vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   pos = transform * pos;
   worldPosition = pos.xyz;
   uv = uvCor;
   // normal = transpose(inverse(mat3(transform))) * aNormal;
   normal =  normalMatrix * aNormal;
   gl_Position = perspectiveMatrix * viewMatrix * pos;
}