#ifndef SHADER_H
#define SHADER_H

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Clone {
    class Shader
    {
    public:
        uint32_t Id;

        Shader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath);

        void Use();
        void SetBool(const std::string &name, bool value);
        void SetInt(const std::string &name, int value);
        void SetFloat(const std::string &name, float value);
        void SetMat4(const std::string &name, const glm::mat4 &matrix);
    };
}

#endif //SHADER_H
