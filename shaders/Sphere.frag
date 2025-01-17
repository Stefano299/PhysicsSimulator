#version 330 core

in vec3 vertexPos;
in vec3 normalPos;

out vec4 FragColor;

void main() {
    vec3 objColor = vec3(245.f/255, 169.f/255, 27.f/255);

    vec3 lightPos = vec3(-15.0f, 20.0f, 4.0f);
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    float ambientIntensity = 0.5f;

    vec3 viewVec = normalize(lightPos-vertexPos);
    float diffuse = max(dot(viewVec, normalPos), 0.0f)*0.2;
    vec3 result = (diffuse+ambientIntensity)*lightColor;

    FragColor = vec4(result*objColor, 1.0f);
}