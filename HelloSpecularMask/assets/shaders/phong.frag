#version 330 core
out vec4 FragColor;
in vec2 uvPos;
in vec3 normal;

uniform sampler2D texture1;  // diffuse
uniform sampler2D texture2; // specular mask

// 光源参数
uniform vec3 lightDirection;
uniform vec3 lightColor;

// 世界坐标
in vec3 worldPosition;

// 相机世界位置
uniform vec3 cameraPosition;
uniform float lightIntensity;
uniform vec3 ambientColor;

uniform float specularIntensity;
uniform float shiness;

void main()
{

  // 通用数据
//  vec4 objectColor = mix(texture(texture1, uvPos), texture(texture2, uvPos), 1.0);
  vec4 objectColor = texture(texture1, uvPos);
  vec3 temp = objectColor.xyz; // 物体的颜色
  vec3 normalN = normalize(normal); // 法线方向
  vec3 lightDirN = normalize(lightDirection); // 光线方向
  vec3 viewDir = normalize(worldPosition - cameraPosition); // 求视线方向

  // Diffuse
  float diffuse = clamp(dot(-lightDirN, normalN), 0.0, 1.0);
  vec3 diffuseColor = lightColor * diffuse * temp;

  // Specular
  float dotResult = dot(-lightDirN, normalN);
  float flag = step(0.0, dotResult);
  vec3 lightReflect = normalize(reflect(lightDirN, normalN));
  float specular = pow(max(dot(lightReflect, -viewDir), 0.0), shiness);

  // 蒙版
  float specularMask = texture(texture2, uvPos).r;

  vec3 specularColor = lightColor * specular * flag * lightIntensity * specularMask;

  // ambient
  vec3 ambientColor = ambientColor * temp;

  vec3 finalColor = diffuseColor + specularColor + ambientColor;


//  FragColor = vec4(specularMask,specularMask, specularMask,  1.0);
    FragColor = vec4(finalColor, 1.0);
}
