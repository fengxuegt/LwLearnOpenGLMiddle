#version 330 core
out vec4 FragColor;

in vec2 uv; // uv坐标，一般是放到VBO中的，每个顶点不一样
in vec3 normal; // 发现，同样是放入VBO中的， 每个顶点不一样
in vec3 worldPosition;// 世界坐标， 每个顶点的世界坐标

uniform sampler2D sampler;  // diffuse
uniform sampler2D texture2; // specular mask

uniform vec3 ambientColor; // 环境光

uniform vec3 cameraPosition;// 相机世界位置
uniform float shiness; // 光强度

struct DirectionalLight {
  vec3 direction;
  vec3 color;
  float specularIntensity;
};

struct PointLight {
  vec3 position;
  vec3 color;
  float specularIntensity;
  float k2;
  float k1;
  float kc;
};

struct SpotLight {
  vec3 position;
  vec3 targetDirection;
  vec3 color;

  float outerLine;
  float innerLine;
  float specularIntensity;
};

// 计算漫反射光照
uniform DirectionalLight directionalLight;
vec3 calculateDiffuse(vec3 lightColor, vec3 objectColor, vec3 lightDir, vec3 normal) {
  float diffuse = clamp(dot(-lightDir, normal), 0.0f, 1.0f);
  vec3 diffuseColor = lightColor * diffuse * objectColor;
  return diffuseColor;
}

// 计算镜面反射光照
vec3 calculateSpecular(vec3 lightColor, vec3 lightDir, vec3 normal, vec3 viewDir, float intensity) {
  //1 防止背面光效果
  float dotResult = dot(-lightDir, normal);
  float flag = step(0.0, dotResult);
  vec3 lightReflect = normalize(reflect(lightDir,normal));

  //2 jisuan specular
  float specular = max(dot(lightReflect,-viewDir), 0.0);

  //3 控制光斑大小
  specular = pow(specular, shiness);

  //4 计算最终颜色
  vec3 specularColor = lightColor * specular * flag * intensity;

  return specularColor;
}

vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 viewDir){
  //计算光照的通用数据
  vec3 objectColor  = texture(sampler, uv).xyz;
  vec3 lightDir = normalize(worldPosition - light.position);
  vec3 targetDir = normalize(light.targetDirection);

  //计算spotlight的照射范围
  float cGamma = dot(lightDir, targetDir);
  float intensity =clamp( (cGamma - light.outerLine) / (light.innerLine - light.outerLine), 0.0, 1.0);

  //1 计算diffuse
  vec3 diffuseColor = calculateDiffuse(light.color,objectColor, lightDir,normal);

  //2 计算specular
  vec3 specularColor = calculateSpecular(light.color, lightDir,normal, viewDir,light.specularIntensity);

  return (diffuseColor + specularColor)*intensity;
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal ,vec3 viewDir){
  //计算光照的通用数据
  vec3 objectColor  = texture(sampler, uv).xyz;
  vec3 lightDir = normalize(light.direction);

  //1 计算diffuse
  vec3 diffuseColor = calculateDiffuse(light.color,objectColor, lightDir,normal);

  //2 计算specular
  vec3 specularColor = calculateSpecular(light.color, lightDir,normal, viewDir,light.specularIntensity);

  return diffuseColor + specularColor;
}

vec3 calculatePointLight(PointLight light, vec3 normal ,vec3 viewDir){
  //计算光照的通用数据
  vec3 objectColor  = texture(sampler, uv).xyz;
  vec3 lightDir = normalize(worldPosition - light.position);

  //计算衰减
  float dist = length(worldPosition - light.position);
  float attenuation = 1.0 / (light.k2 * dist * dist + light.k1 * dist + light.kc);

  //1 计算diffuse
  vec3 diffuseColor = calculateDiffuse(light.color,objectColor, lightDir,normal);

  //2 计算specular
  vec3 specularColor = calculateSpecular(light.color, lightDir,normal, viewDir,light.specularIntensity);

  return (diffuseColor + specularColor)*attenuation;
}

void main()
{
  vec3 result = vec3(0.0,0.0,0.0);

  //计算光照的通用数据
  vec3 normalN = normalize(normal);
  vec3 viewDir = normalize(worldPosition - cameraPosition);

  result += calculateDirectionalLight(directionalLight,normalN, viewDir);

  //环境光计算
  vec3 objectColor  = texture(sampler, uv).xyz;
  vec3 ambientColor = objectColor * ambientColor;

  vec3 finalColor = result + ambientColor;

  FragColor = vec4(finalColor, 1.0);
}
