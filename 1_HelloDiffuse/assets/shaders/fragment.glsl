#version 330 core
out vec4 FragColor;
in vec2 uvPos;
in vec3 normal;

uniform sampler2D texture1;
uniform sampler2D texture2;

// 光源参数
uniform vec3 lightDirection;
uniform vec3 lightColor;

void main()
{

  vec4 objectColor = mix(texture(texture1, uvPos), texture(texture2, uvPos), 1.0);
  vec3 temp = objectColor.xyz;
  vec3 normalN = normalize(normal);
  vec3 lightDirN = normalize(lightDirection);
  float diffuse = clamp(dot(-lightDirN, normalN), 0.0, 1.0);
  vec3 finalColor = lightColor * diffuse * temp;

  FragColor = vec4(finalColor, 1.0);
}