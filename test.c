#include "aiv_unit_test.h"
#include "math.h"
#include "rasterizer.h"

#define triangle(x0, y0, z0, x1, y1, z1, x2, y2, z2) \
    triangle_new(                                    \
        vertex_new(vector3_new(x0, y0, z0)),         \
        vertex_new(vector3_new(x1, y1, z1)),         \
        vertex_new(vector3_new(x2, y2, z2)))

TEST(screen_space_to_pixel_conversion)
{
    point2_t result = screen_space_to_pixel(0.5, 0.5, 400, 400);

    ASSERT_THAT(result.x == 300);
    ASSERT_THAT(result.y == 300);
}

TEST(screen_space_to_pixel_conversion_negative)
{
    point2_t result = screen_space_to_pixel(-0.5, -0.5, 400, 400);

    ASSERT_THAT(result.x == 100);
    ASSERT_THAT(result.y == 100);
}

TEST(screen_space_to_pixel_overflow)
{
    point2_t result = screen_space_to_pixel(2, 2, 400, 400);

    ASSERT_THAT(result.x == -1);
    ASSERT_THAT(result.y == -1);
}

TEST(screen_space_to_pixel_overflow_negative)
{
    point2_t result = screen_space_to_pixel(-2, -2, 400, 400);

    ASSERT_THAT(result.x == -1);
    ASSERT_THAT(result.y == -1);
}

TEST(vector3_init)
{
    vector3_t vec = vector3_new(1, 2, 3);
    ASSERT_THAT(vec.x == 1);
    ASSERT_THAT(vec.y == 2);
    ASSERT_THAT(vec.z == 3);
}

TEST(vertex_init)
{
    vector3_t vec = vector3_new(1, 2, 3);
    vertex_t vertex = vertex_new(vec);

    ASSERT_THAT(vertex.position.x == 1);
    ASSERT_THAT(vertex.position.x == 2);
    ASSERT_THAT(vertex.position.x == 3);
}

TEST(triangle_init)
{
    vector3_t vec = vector3_new(1, 2, 3);
    vector3_t vec2 = vector3_new(4, 5, 6);
    vector3_t vec3 = vector3_new(7, 8, 9);
    vertex_t vertex = vertex_new(vec);
    vertex_t vertex2 = vertex_new(vec2);
    vertex_t vertex3 = vertex_new(vec3);

    triangle_t triangle = triangle_new(vertex, vertex2, vertex3);

    // A
    ASSERT_THAT(triangle.a.position.x == 1);
    ASSERT_THAT(triangle.a.position.y == 2);
    ASSERT_THAT(triangle.a.position.z == 3);
    // B
    ASSERT_THAT(triangle.b.position.x == 4);
    ASSERT_THAT(triangle.b.position.y == 5);
    ASSERT_THAT(triangle.b.position.z == 6);
    //C
    ASSERT_THAT(triangle.c.position.x == 7);
    ASSERT_THAT(triangle.c.position.y == 8);
    ASSERT_THAT(triangle.c.position.z == 9);
}

TEST(lerp_first)
{
    float value = lerp(1, 2, 0.5);

    ASSERT_THAT(value == 1.5);
}

TEST(lerp_second)
{
    float value = lerp(-1, -3, 0.5);

    ASSERT_THAT(value == -2);
}

TEST(sort_first)
{
    context_t ctx;
    ctx.width = 300;
    ctx.height = 300;

    triangle_t tris = triangle(
        0.0, -1.0, 0,
        -1.0, 1.0, 0,
        1.0, 1.0, 0);

    sort_triangle(&ctx, &tris);

    ASSERT_THAT(tris.a.pixel_point.x == 150);
    ASSERT_THAT(tris.a.pixel_point.y == 0);

    ASSERT_THAT(tris.b.pixel_point.x == 0);
    ASSERT_THAT(tris.b.pixel_point.y == 300);

    ASSERT_THAT(tris.c.pixel_point.x == 300);
    ASSERT_THAT(tris.c.pixel_point.y == 300);
}

TEST(swap_point)
{
    point2_t point1;
    point1.x = 10;
    point1.y = 20;

    point2_t point2;
    point2.x = 30;
    point2.y = 40;

    swap_point(&point1, &point2);

    ASSERT_THAT(point1.x == 30);
    ASSERT_THAT(point1.y == 40);

    ASSERT_THAT(point2.x == 10);
    ASSERT_THAT(point2.y == 20);
}

int main(int argc, char **argv)
{
    RUN_TEST(screen_space_to_pixel_conversion);
    RUN_TEST(screen_space_to_pixel_conversion_negative);
    RUN_TEST(screen_space_to_pixel_overflow);
    RUN_TEST(screen_space_to_pixel_overflow_negative);
    RUN_TEST(vector3_init);
    RUN_TEST(triangle_init);
    RUN_TEST(lerp_first);
    RUN_TEST(lerp_second);
    RUN_TEST(sort_first);
    RUN_TEST(swap_point);

    PRINT_TEST_RESULTS();
    return 0;
}
