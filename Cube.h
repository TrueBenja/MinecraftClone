#ifndef CUBE_H
#define CUBE_H

#include <array>
#include <cstdint>

namespace Clone {
    class Cube
    {
    public:
        Cube() {}

        static constexpr float vertices[] = {
            -0.5f, 0.5f, 0.5f,  // Front left up    0
            0.5f, 0.5f, 0.5f,   // Front right up   1
            -0.5f, -0.5f, 0.5f, // Front left down  2
            0.5f, -0.5f, 0.5f,  // Front right down 3
            -0.5f, 0.5f, -0.5f, // Back left up     4
            0.5f, 0.5f, -0.5f,  // Back right up    5
            -0.5f, -0.5f, -0.5f,// Back left down   6
            0.5f, -0.5f, -0.5f  // Back right down  7
        };

        static constexpr uint32_t indices[] = {
            0, 3, 1, // Front
            0, 2, 3,
            4, 5, 7, // Back
            4, 6, 7,
            4, 6, 2, // Left
            4, 2, 0,
            1, 3, 7, // Right
            1, 7, 5,
            4, 0, 1, // Top
            4, 1, 5,
            2, 6, 7, // Down
            2, 7, 3
        };
    };
}

#endif //CUBE_H
