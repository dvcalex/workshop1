#pragma once

namespace cube
{
/*
 * - center of cube is (0, 0, 0)
 * - layout is [(x, y, z), (u, v)]
 * - CCW winding
 * - face ordering: front, back, left, right, top, bottom
 * - right-handed coordinate system
 */
constexpr float Vertices[] = {
    -0.5f, -0.5f, 0.5f,  0.f, 0.f, // f0
    0.5f,  -0.5f, 0.5f,  1.f, 0.f, // f1
    0.5f,  0.5f,  0.5f,  1.f, 1.f, // f2
    -0.5f, 0.5f,  0.5f,  0.f, 1.f, // f3

    0.5f,  -0.5f, -0.5f, 0.f, 0.f, // ba0
    -0.5f, -0.5f, -0.5f, 1.f, 0.f, // ba1
    -0.5f, 0.5f,  -0.5f, 1.f, 1.f, // ba2
    0.5f,  0.5f,  -0.5f, 0.f, 1.f, // ba3

    -0.5f, -0.5f, -0.5f, 0.f, 0.f, // l0
    -0.5f, -0.5f, 0.5f,  1.f, 0.f, // l1
    -0.5f, 0.5f,  0.5f,  1.f, 1.f, // l2
    -0.5f, 0.5f,  -0.5f, 0.f, 1.f, // l3

    0.5f,  -0.5f, 0.5f,  0.f, 0.f, // r0
    0.5f,  -0.5f, -0.5f, 1.f, 0.f, // r1
    0.5f,  0.5f,  -0.5f, 1.f, 1.f, // r2
    0.5f,  0.5f,  0.5f,  0.f, 1.f, // r3

    -0.5f, 0.5f,  0.5f,  0.f, 0.f, // t0
    0.5f,  0.5f,  0.5f,  1.f, 0.f, // t1
    0.5f,  0.5f,  -0.5f, 1.f, 1.f, // t2
    -0.5f, 0.5f,  -0.5f, 0.f, 1.f, // t3

    0.5f,  -0.5f, 0.5f,  0.f, 0.f, // bo0
    -0.5f, -0.5f, 0.5f,  1.f, 0.f, // bo1
    -0.5f, -0.5f, -0.5f, 1.f, 1.f, // bo2
    0.5f,  -0.5f, -0.5f, 0.f, 1.f, // bo3
};
constexpr unsigned int VertexCount = 24;

constexpr unsigned int Indices[] = {
    0,  1,  2,  2,  3,  0,  // front
    4,  5,  6,  6,  7,  4,  // back
    8,  9,  10, 10, 11, 8,  // left
    12, 13, 14, 14, 15, 12, // right
    16, 17, 18, 18, 19, 16, // top
    20, 21, 22, 22, 23, 20  // bottom
};
constexpr unsigned int IndexCount = 36;

// helpers to get sizes
constexpr size_t getVertexDataSize() { return sizeof(Vertices); }
constexpr size_t getIndexDataSize() { return sizeof(Indices); }

} // namespace cube
