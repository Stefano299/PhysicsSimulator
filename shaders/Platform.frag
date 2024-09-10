#version 330 core

in vec3 vertexPos;
in vec3 normalPos;

out vec4 FragColor;

void main() {
    vec3 lightPos = vec3(-15.0f, 20.0f, 4.0f);
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    vec3 objColor = vec3(185.f/255, 185.f/255, 185.f/255);
    float ambientIntensity = 0.4f;

    vec3 viewVec = normalize(lightPos-vertexPos);
    float diffuse = max(dot(viewVec, normalPos), 0.0f);
    vec3 result = (diffuse+ambientIntensity)*lightColor;

    FragColor = vec4(result*objColor, 1.0f);
}