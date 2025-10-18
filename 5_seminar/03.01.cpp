#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

struct Point
{
    double x = 0;
    double y = 0;
};

struct Rectangle
{
    Point left_upper;
    Point right_lower;
};


double intersection_square(const std::vector<Rectangle>& rectangles)
{
    if (rectangles.empty())
    {
        return 0;
    }

    double left   = rectangles[0].left_upper.x;
    double top    = rectangles[0].left_upper.y;
    double right  = rectangles[0].right_lower.x;
    double bottom = rectangles[0].right_lower.y;

    for (std::size_t i = 1; i < rectangles.size(); ++i)
    {
        left   = std::max(left,   rectangles[i].left_upper.x);
        top    = std::max(top,    rectangles[i].left_upper.y);
        right  = std::min(right,  rectangles[i].right_lower.x);
        bottom = std::min(bottom, rectangles[i].right_lower.y);
    }

    double width  = right  - left;
    double height = bottom - top;

    if (width <= 0 || height <= 0)
    {
        return 0;
    }

    return width * height;
}


Rectangle bounding_rectangle(const std::vector<Rectangle>& rectangles)
{
    assert(!rectangles.empty());

    double left   = rectangles[0].left_upper.x;
    double top    = rectangles[0].left_upper.y;
    double right  = rectangles[0].right_lower.x;
    double bottom = rectangles[0].right_lower.y;

    for (std::size_t i = 1; i < rectangles.size(); ++i)
    {
        left   = std::min(left,   rectangles[i].left_upper.x);
        top    = std::min(top,    rectangles[i].left_upper.y);
        right  = std::max(right,  rectangles[i].right_lower.x);
        bottom = std::max(bottom, rectangles[i].right_lower.y);
    }

    return { { left, top }, { right, bottom } };
}


int main()
{
//--------------------------------------------------------------------------------------------------------//

    std::vector<Rectangle> rects = {
        { {1.0, 1.0}, {4.0, 4.0} },
        { {2.0, 2.0}, {5.0, 5.0} },
        { {3.0, 0.0}, {6.0, 3.0} }
    };

    double inter_area = intersection_square(rects);
    assert(inter_area == 1);

    Rectangle bound = bounding_rectangle(rects);
    //std::cout << (bound.right_lower.x - bound.left_upper.x) * (bound.right_lower.y - bound.left_upper.y);
    assert((bound.right_lower.x - bound.left_upper.x) * (bound.right_lower.y - bound.left_upper.y) - 25 < 1e-3);

//--------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------------//

    std::vector<Rectangle> simple_rects = {
        { {0, 0},   {1, 1} },
        { {0.5, 0}, {1.5, 1} }
    };

    inter_area = intersection_square(simple_rects);
    assert(inter_area - 0.5 < 1e-3);

    bound = bounding_rectangle(simple_rects);
    assert((bound.right_lower.x - bound.left_upper.x) * (bound.right_lower.y - bound.left_upper.y) - 1.5 < 1e-3);

//--------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------------//

    std::vector<Rectangle> disjoint = {
        { {0, 0}, {2, 2} },
        { {3, 3}, {4, 4} }
    };

    assert(intersection_square(disjoint) < 1e-6);

//--------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------------//

    std::vector<Rectangle> inner_rects = {
        { {0.1, 0.1}, {0.2, 0.2} },
        { {0.1, 0.1}, {0.5, 0.5} },
        { {0, 0},   {1, 1} }
    };

    inter_area = intersection_square(inner_rects);
    assert(inter_area - 0.01 < 1e-3);

    bound = bounding_rectangle(inner_rects);
    assert(bound.left_upper.x * bound.left_upper.y + bound.right_lower.x * bound.right_lower.y - 1 < 1e-3);

//--------------------------------------------------------------------------------------------------------//

    return 0;
}
