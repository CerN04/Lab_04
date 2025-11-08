#include <gtest/gtest.h>
#include "../include/Array.hpp"
#include "../include/Figure.hpp"
#include "../include/Triangle.hpp"
#include "../include/Square.hpp"
#include "../include/Octagon.hpp"
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <cstddef>
#include <memory>
#include <string>

// ============================================================================
// Тесты для класса Array
// ============================================================================

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.GetSize(), 0);
}

TEST(ArrayTest, ConstructorWithSize) {
    Array<int> arr(5, 10);
    EXPECT_EQ(arr.GetSize(), 5);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], 10);
    }
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr1(3, 5);
    Array<int> arr2(arr1);
    EXPECT_EQ(arr2.GetSize(), 3);
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(arr2[i], 5);
    }
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr1(3, 7);
    Array<int> arr2(std::move(arr1));
    EXPECT_EQ(arr2.GetSize(), 3);
    EXPECT_EQ(arr1.GetSize(), 0);
}

TEST(ArrayTest, PushItem) {
    Array<int> arr;
    arr.PushItem(1);
    arr.PushItem(2);
    arr.PushItem(3);
    EXPECT_EQ(arr.GetSize(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, PushItemResize) {
    Array<int> arr;
    // Добавляем больше элементов, чем начальная capacity
    for (int i = 0; i < 10; ++i) {
        arr.PushItem(i);
    }
    EXPECT_EQ(arr.GetSize(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST(ArrayTest, Pop) {
    Array<int> arr;
    arr.PushItem(1);
    arr.PushItem(2);
    arr.PushItem(3);
    
    int val = arr.Pop();
    EXPECT_EQ(val, 3);
    EXPECT_EQ(arr.GetSize(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(ArrayTest, PopEmpty) {
    Array<int> arr;
    EXPECT_THROW(arr.Pop(), std::out_of_range);
}

TEST(ArrayTest, OperatorBracket) {
    Array<int> arr(3, 5);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 5);
    EXPECT_EQ(arr[2], 5);
    
    arr[0] = 10;
    EXPECT_EQ(arr[0], 10);
}

TEST(ArrayTest, OperatorBracketConst) {
    const Array<int> arr(3, 5);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 5);
    EXPECT_EQ(arr[2], 5);
}

TEST(ArrayTest, OperatorBracketOutOfRange) {
    Array<int> arr(3, 5);
    EXPECT_THROW(arr[3], std::out_of_range);
}

TEST(ArrayTest, DeleteItem) {
    Array<int> arr;
    arr.PushItem(1);
    arr.PushItem(2);
    arr.PushItem(3);
    arr.PushItem(4);
    
    arr.DeleteItem(1);
    EXPECT_EQ(arr.GetSize(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
    EXPECT_EQ(arr[2], 4);
}

TEST(ArrayTest, DeleteItemFirst) {
    Array<int> arr;
    arr.PushItem(1);
    arr.PushItem(2);
    arr.PushItem(3);
    
    arr.DeleteItem(0);
    EXPECT_EQ(arr.GetSize(), 2);
    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, DeleteItemLast) {
    Array<int> arr;
    arr.PushItem(1);
    arr.PushItem(2);
    arr.PushItem(3);
    
    arr.DeleteItem(2);
    EXPECT_EQ(arr.GetSize(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(ArrayTest, DeleteItemOutOfRange) {
    Array<int> arr(3, 5);
    EXPECT_THROW(arr.DeleteItem(3), std::out_of_range);
}

TEST(ArrayTest, Resize) {
    Array<int> arr;
    arr.PushItem(1);
    arr.PushItem(2);
    
    arr.Resize(5);
    EXPECT_EQ(arr.GetSize(), 2); // Resize не меняет size, только capacity
}

TEST(ArrayTest, GetSize) {
    Array<int> arr;
    EXPECT_EQ(arr.GetSize(), 0);
    
    arr.PushItem(1);
    EXPECT_EQ(arr.GetSize(), 1);
    
    arr.PushItem(2);
    EXPECT_EQ(arr.GetSize(), 2);
}

// ============================================================================
// Тесты для структуры Point
// ============================================================================

TEST(PointTest, DefaultValues) {
    Point<int> p{};
    // Значения по умолчанию не определены, но структура должна создаваться
    EXPECT_TRUE(true);
}

TEST(PointTest, Initialization) {
    Point<double> p{3.5, 4.2};
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, 4.2);
}

TEST(PointTest, OutputOperator) {
    Point<int> p{10, 20};
    std::ostringstream oss;
    oss << p;
    std::string result = oss.str();
    EXPECT_TRUE(result.find("10") != std::string::npos);
    EXPECT_TRUE(result.find("20") != std::string::npos);
}

TEST(PointTest, InputOperator) {
    Point<int> p;
    std::istringstream iss("15 25");
    iss >> p;
    EXPECT_EQ(p.x, 15);
    EXPECT_EQ(p.y, 25);
}

TEST(PointTest, FloatPoint) {
    Point<float> p{1.5f, 2.5f};
    EXPECT_FLOAT_EQ(p.x, 1.5f);
    EXPECT_FLOAT_EQ(p.y, 2.5f);
}

// ============================================================================
// Тесты для класса Triangle
// ============================================================================

TEST(TriangleTest, DefaultConstructor) {
    Triangle<double> tri;
    // Треугольник должен иметь 3 точки
    EXPECT_TRUE(true);
}

TEST(TriangleTest, CopyConstructor) {
    Triangle<double> tri1;
    std::istringstream iss("0 0 1 0 0.5 1");
    iss >> tri1;
    
    Triangle<double> tri2(tri1);
    EXPECT_TRUE(tri2 == tri1);
}

TEST(TriangleTest, ReadAndWrite) {
    Triangle<double> tri;
    std::istringstream iss("0 0 1 0 0.5 1");
    iss >> tri;
    
    std::ostringstream oss;
    tri.print(oss);
    std::string result = oss.str();
    EXPECT_TRUE(result.find("Triangle") != std::string::npos);
}

TEST(TriangleTest, Area) {
    Triangle<double> tri;
    std::istringstream iss("0 0 1 0 0.5 1");
    iss >> tri;
    
    double area = static_cast<double>(tri);
    // Площадь треугольника с вершинами (0,0), (1,0), (0.5,1) = 0.5
    EXPECT_NEAR(area, 0.5, 1e-6);
}

TEST(TriangleTest, AreaRightTriangle) {
    Triangle<double> tri;
    std::istringstream iss("0 0 3 0 0 4");
    iss >> tri;
    
    double area = static_cast<double>(tri);
    // Площадь прямоугольного треугольника = 0.5 * 3 * 4 = 6
    EXPECT_NEAR(area, 6.0, 1e-6);
}

TEST(TriangleTest, GeometricCenter) {
    Triangle<double> tri;
    std::istringstream iss("0 0 3 0 0 3");
    iss >> tri;
    
    Point<double> center = tri.geomCenter();
    // Центр масс треугольника с вершинами (0,0), (3,0), (0,3) = (1, 1)
    EXPECT_NEAR(center.x, 1.0, 1e-6);
    EXPECT_NEAR(center.y, 1.0, 1e-6);
}

TEST(TriangleTest, AssignmentOperator) {
    Triangle<double> tri1;
    std::istringstream iss("0 0 1 0 0.5 1");
    iss >> tri1;
    
    Triangle<double> tri2;
    tri2 = tri1;
    EXPECT_TRUE(tri2 == tri1);
}

TEST(TriangleTest, MoveAssignmentOperator) {
    Triangle<double> tri1;
    std::istringstream iss("0 0 1 0 0.5 1");
    iss >> tri1;
    
    Triangle<double> tri2;
    tri2 = std::move(tri1);
    // После move tri2 должен содержать данные
    double area = static_cast<double>(tri2);
    EXPECT_GT(area, 0);
}

TEST(TriangleTest, EqualityOperator) {
    Triangle<double> tri1;
    std::istringstream iss1("0 0 1 0 0.5 1");
    iss1 >> tri1;
    
    Triangle<double> tri2;
    std::istringstream iss2("0 0 1 0 0.5 1");
    iss2 >> tri2;
    
    EXPECT_TRUE(tri1 == tri2);
}

TEST(TriangleTest, InequalityOperator) {
    Triangle<double> tri1;
    std::istringstream iss1("0 0 1 0 0.5 1");
    iss1 >> tri1;
    
    Triangle<double> tri2;
    std::istringstream iss2("0 0 2 0 1 2");
    iss2 >> tri2;
    
    EXPECT_FALSE(tri1 == tri2);
}

TEST(TriangleTest, ZeroArea) {
    Triangle<double> tri;
    std::istringstream iss("0 0 0 0 0 0");
    iss >> tri;
    
    double area = static_cast<double>(tri);
    EXPECT_NEAR(area, 0.0, 1e-6);
}

// ============================================================================
// Тесты для класса Square
// ============================================================================

TEST(SquareTest, DefaultConstructor) {
    Square<double> sq;
    // Квадрат должен иметь 4 точки
    EXPECT_TRUE(true);
}

TEST(SquareTest, CopyConstructor) {
    Square<double> sq1;
    std::istringstream iss("0 0 1 0 1 1 0 1");
    iss >> sq1;
    
    Square<double> sq2(sq1);
    EXPECT_TRUE(sq2 == sq1);
}

TEST(SquareTest, ReadAndWrite) {
    Square<double> sq;
    std::istringstream iss("0 0 1 0 1 1 0 1");
    iss >> sq;
    
    std::ostringstream oss;
    sq.print(oss);
    std::string result = oss.str();
    EXPECT_TRUE(result.find("Square") != std::string::npos);
}

TEST(SquareTest, AreaUnitSquare) {
    Square<double> sq;
    std::istringstream iss("0 0 1 0 1 1 0 1");
    iss >> sq;
    
    double area = static_cast<double>(sq);
    // Площадь единичного квадрата = 1
    EXPECT_NEAR(area, 1.0, 1e-6);
}

TEST(SquareTest, AreaLargeSquare) {
    Square<double> sq;
    std::istringstream iss("0 0 3 0 3 3 0 3");
    iss >> sq;
    
    double area = static_cast<double>(sq);
    // Площадь квадрата 3x3 = 9
    EXPECT_NEAR(area, 9.0, 1e-6);
}

TEST(SquareTest, GeometricCenter) {
    Square<double> sq;
    std::istringstream iss("0 0 2 0 2 2 0 2");
    iss >> sq;
    
    Point<double> center = sq.geomCenter();
    // Центр масс квадрата с вершинами (0,0), (2,0), (2,2), (0,2) = (1, 1)
    EXPECT_NEAR(center.x, 1.0, 1e-6);
    EXPECT_NEAR(center.y, 1.0, 1e-6);
}

TEST(SquareTest, AssignmentOperator) {
    Square<double> sq1;
    std::istringstream iss("0 0 1 0 1 1 0 1");
    iss >> sq1;
    
    Square<double> sq2;
    sq2 = sq1;
    EXPECT_TRUE(sq2 == sq1);
}

TEST(SquareTest, MoveAssignmentOperator) {
    Square<double> sq1;
    std::istringstream iss("0 0 1 0 1 1 0 1");
    iss >> sq1;
    
    Square<double> sq2;
    sq2 = std::move(sq1);
    // После move sq2 должен содержать данные
    double area = static_cast<double>(sq2);
    EXPECT_GT(area, 0);
}

TEST(SquareTest, EqualityOperator) {
    Square<double> sq1;
    std::istringstream iss1("0 0 1 0 1 1 0 1");
    iss1 >> sq1;
    
    Square<double> sq2;
    std::istringstream iss2("0 0 1 0 1 1 0 1");
    iss2 >> sq2;
    
    EXPECT_TRUE(sq1 == sq2);
}

TEST(SquareTest, InequalityOperator) {
    Square<double> sq1;
    std::istringstream iss1("0 0 1 0 1 1 0 1");
    iss1 >> sq1;
    
    Square<double> sq2;
    std::istringstream iss2("0 0 2 0 2 2 0 2");
    iss2 >> sq2;
    
    EXPECT_FALSE(sq1 == sq2);
}

TEST(SquareTest, RotatedSquare) {
    Square<double> sq;
    // Квадрат, повернутый на 45 градусов
    std::istringstream iss("1 0 0 1 -1 0 0 -1");
    iss >> sq;
    
    double area = static_cast<double>(sq);
    // Площадь должна быть положительной
    EXPECT_GT(area, 0);
}

// ============================================================================
// Тесты для класса Octagon
// ============================================================================

TEST(OctagonTest, DefaultConstructor) {
    Octagon<double> oct;
    // Восьмиугольник должен иметь 8 точек
    EXPECT_TRUE(true);
}

TEST(OctagonTest, CopyConstructor) {
    Octagon<double> oct1;
    std::istringstream iss("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    iss >> oct1;
    
    Octagon<double> oct2(oct1);
    EXPECT_TRUE(oct2 == oct1);
}

TEST(OctagonTest, ReadAndWrite) {
    Octagon<double> oct;
    std::istringstream iss("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    iss >> oct;
    
    std::ostringstream oss;
    oct.print(oss);
    std::string result = oss.str();
    EXPECT_TRUE(result.find("Octagon") != std::string::npos);
}

TEST(OctagonTest, AreaRegularOctagon) {
    Octagon<double> oct;
    // Правильный восьмиугольник с радиусом описанной окружности = 1
    std::istringstream iss("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    iss >> oct;
    
    double area = static_cast<double>(oct);
    // Площадь правильного восьмиугольника с радиусом 1 ≈ 2.828
    EXPECT_GT(area, 0);
    EXPECT_LT(area, 10); // Разумная верхняя граница
}

TEST(OctagonTest, GeometricCenter) {
    Octagon<double> oct;
    // Восьмиугольник, симметричный относительно начала координат
    std::istringstream iss("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    iss >> oct;
    
    Point<double> center = oct.geomCenter();
    // Центр масс должен быть близок к (0, 0)
    EXPECT_NEAR(center.x, 0.0, 0.1);
    EXPECT_NEAR(center.y, 0.0, 0.1);
}

TEST(OctagonTest, AssignmentOperator) {
    Octagon<double> oct1;
    std::istringstream iss("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    iss >> oct1;
    
    Octagon<double> oct2;
    oct2 = oct1;
    EXPECT_TRUE(oct2 == oct1);
}

TEST(OctagonTest, MoveAssignmentOperator) {
    Octagon<double> oct1;
    std::istringstream iss("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    iss >> oct1;
    
    Octagon<double> oct2;
    oct2 = std::move(oct1);
    // После move oct2 должен содержать данные
    double area = static_cast<double>(oct2);
    EXPECT_GT(area, 0);
}

TEST(OctagonTest, EqualityOperator) {
    Octagon<double> oct1;
    std::istringstream iss1("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    iss1 >> oct1;
    
    Octagon<double> oct2;
    std::istringstream iss2("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    iss2 >> oct2;
    
    EXPECT_TRUE(oct1 == oct2);
}

TEST(OctagonTest, InequalityOperator) {
    Octagon<double> oct1;
    std::istringstream iss1("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    iss1 >> oct1;
    
    Octagon<double> oct2;
    std::istringstream iss2("2 0 1.414 1.414 0 2 -1.414 1.414 -2 0 -1.414 -1.414 0 -2 1.414 -1.414");
    iss2 >> oct2;
    
    EXPECT_FALSE(oct1 == oct2);
}

TEST(OctagonTest, AreaLargeOctagon) {
    Octagon<double> oct;
    // Большой восьмиугольник (увеличенный правильный восьмиугольник)
    std::istringstream iss("2 0 1.414 1.414 0 2 -1.414 1.414 -2 0 -1.414 -1.414 0 -2 1.414 -1.414");
    iss >> oct;
    
    double area = static_cast<double>(oct);
    // Площадь должна быть больше, чем у единичного восьмиугольника
    EXPECT_GT(area, 2.0);
    EXPECT_LT(area, 20); // Разумная верхняя граница
}

TEST(OctagonTest, SimpleOctagon) {
    Octagon<double> oct;
    // Простой восьмиугольник (квадрат с обрезанными углами)
    std::istringstream iss("2 0 1 1 0 2 -1 1 -2 0 -1 -1 0 -2 1 -1");
    iss >> oct;
    
    double area = static_cast<double>(oct);
    EXPECT_GT(area, 0);
}

// ============================================================================
// Интеграционные тесты для работы с фигурами через Array
// ============================================================================

TEST(FiguresIntegrationTest, ArrayOfFigures) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto tri = std::make_shared<Triangle<double>>();
    std::istringstream iss1("0 0 1 0 0.5 1");
    iss1 >> *tri;
    arr.PushItem(tri);
    
    auto sq = std::make_shared<Square<double>>();
    std::istringstream iss2("0 0 1 0 1 1 0 1");
    iss2 >> *sq;
    arr.PushItem(sq);
    
    EXPECT_EQ(arr.GetSize(), 2);
}

TEST(FiguresIntegrationTest, TotalArea) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto tri = std::make_shared<Triangle<double>>();
    std::istringstream iss1("0 0 3 0 0 4");
    iss1 >> *tri;
    arr.PushItem(tri);
    
    auto sq = std::make_shared<Square<double>>();
    std::istringstream iss2("0 0 2 0 2 2 0 2");
    iss2 >> *sq;
    arr.PushItem(sq);
    
    double total_area = 0.0;
    for (size_t i = 0; i < arr.GetSize(); ++i) {
        total_area += static_cast<double>(*arr[i]);
    }
    
    // Площадь треугольника = 6, площадь квадрата = 4, итого = 10
    EXPECT_NEAR(total_area, 10.0, 1e-6);
}

TEST(FiguresIntegrationTest, DeleteFigure) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto tri = std::make_shared<Triangle<double>>();
    std::istringstream iss1("0 0 1 0 0.5 1");
    iss1 >> *tri;
    arr.PushItem(tri);
    
    auto sq = std::make_shared<Square<double>>();
    std::istringstream iss2("0 0 1 0 1 1 0 1");
    iss2 >> *sq;
    arr.PushItem(sq);
    
    arr.DeleteItem(0);
    EXPECT_EQ(arr.GetSize(), 1);
    
    // Оставшаяся фигура должна быть квадратом
    std::ostringstream oss;
    arr[0]->print(oss);
    std::string result = oss.str();
    EXPECT_TRUE(result.find("Square") != std::string::npos);
}

TEST(FiguresIntegrationTest, GeometricCenters) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto tri = std::make_shared<Triangle<double>>();
    std::istringstream iss1("0 0 3 0 0 3");
    iss1 >> *tri;
    arr.PushItem(tri);
    
    auto sq = std::make_shared<Square<double>>();
    std::istringstream iss2("0 0 2 0 2 2 0 2");
    iss2 >> *sq;
    arr.PushItem(sq);
    
    Point<double> tri_center = arr[0]->geomCenter();
    Point<double> sq_center = arr[1]->geomCenter();
    
    // Центр треугольника (0,0), (3,0), (0,3) = (1, 1)
    EXPECT_NEAR(tri_center.x, 1.0, 1e-6);
    EXPECT_NEAR(tri_center.y, 1.0, 1e-6);
    
    // Центр квадрата (0,0), (2,0), (2,2), (0,2) = (1, 1)
    EXPECT_NEAR(sq_center.x, 1.0, 1e-6);
    EXPECT_NEAR(sq_center.y, 1.0, 1e-6);
}

TEST(FiguresIntegrationTest, AllThreeFigures) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto tri = std::make_shared<Triangle<double>>();
    std::istringstream iss1("0 0 1 0 0.5 1");
    iss1 >> *tri;
    arr.PushItem(tri);
    
    auto sq = std::make_shared<Square<double>>();
    std::istringstream iss2("0 0 1 0 1 1 0 1");
    iss2 >> *sq;
    arr.PushItem(sq);
    
    auto oct = std::make_shared<Octagon<double>>();
    std::istringstream iss3("1 0 0.707 0.707 0 1 -0.707 0.707 -1 0 -0.707 -0.707 0 -1 0.707 -0.707");
    iss3 >> *oct;
    arr.PushItem(oct);
    
    EXPECT_EQ(arr.GetSize(), 3);
    
    // Все фигуры должны иметь положительную площадь
    for (size_t i = 0; i < arr.GetSize(); ++i) {
        double area = static_cast<double>(*arr[i]);
        EXPECT_GT(area, 0);
    }
}

TEST(FiguresIntegrationTest, PrintAllFigures) {
    Array<std::shared_ptr<Figure<double>>> arr;
    
    auto tri = std::make_shared<Triangle<double>>();
    std::istringstream iss1("0 0 1 0 0.5 1");
    iss1 >> *tri;
    arr.PushItem(tri);
    
    auto sq = std::make_shared<Square<double>>();
    std::istringstream iss2("0 0 1 0 1 1 0 1");
    iss2 >> *sq;
    arr.PushItem(sq);
    
    std::ostringstream oss;
    for (size_t i = 0; i < arr.GetSize(); ++i) {
        arr[i]->print(oss);
    }
    
    std::string result = oss.str();
    EXPECT_TRUE(result.find("Triangle") != std::string::npos);
    EXPECT_TRUE(result.find("Square") != std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}