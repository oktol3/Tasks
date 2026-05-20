#include "../ConsoleApplication15/vector.h"
#include "../ConsoleApplication15/point.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    TEST_CLASS(PointTests)
    {

public:

    TEST_METHOD(Point_Constructor_Default_Success)
    {
        point p;

        Assert::AreEqual(0.0, p.x());
        Assert::AreEqual(0.0, p.y());
        Assert::AreEqual(0.0, p.z());
    }

    TEST_METHOD(Point_Constructor_Parameters_Success)
    {
        // Arrange
        double x = 1.5, y = 2.5, z = 3.5;

        // Act
        point p(x, y, z);

        // Assert
        Assert::AreEqual(x, p.x());
        Assert::AreEqual(y, p.y());
        Assert::AreEqual(z, p.z());
    }

    TEST_METHOD(Point_CopyConstructor_Success)
    {
        // Arrange
        point original(2.0, 4.0, 6.0);

        // Act
        point copy(original);

        // Assert
        Assert::AreEqual(original.x(), copy.x());
        Assert::AreEqual(original.y(), copy.y());
        Assert::AreEqual(original.z(), copy.z());
    }

    TEST_METHOD(Point_MoveConstructor_Success)
    {
        // Arrange
        point original(3.0, 5.0, 7.0);
        double expectedX = original.x();
        double expectedY = original.y();
        double expectedZ = original.z();

        // Act
        point moved(std::move(original));

        // Assert
        Assert::AreEqual(expectedX, moved.x());
        Assert::AreEqual(expectedY, moved.y());
        Assert::AreEqual(expectedZ, moved.z());
    }

    TEST_METHOD(Point_AssignmentCopy_Success)
    {
        // Arrange
        point source(1.0, 2.0, 3.0);
        point target(0.0, 0.0, 0.0);

        // Act
        target = source;

        // Assert
        Assert::AreEqual(source.x(), target.x());
        Assert::AreEqual(source.y(), target.y());
        Assert::AreEqual(source.z(), target.z());
    }

    TEST_METHOD(Point_AssignmentMove_Success)
    {
        // Arrange
        point source(4.0, 5.0, 6.0);
        point target(0.0, 0.0, 0.0);
        double expectedX = source.x();
        double expectedY = source.y();
        double expectedZ = source.z();

        // Act
        target = std::move(source);

        // Assert
        Assert::AreEqual(expectedX, target.x());
        Assert::AreEqual(expectedY, target.y());
        Assert::AreEqual(expectedZ, target.z());
    }

    TEST_METHOD(Point_Move_Success)
    {
        // Arrange
        point p(1.0, 2.0, 3.0);

        // Act
        p.move(0.5, 1.0, 1.5);

        // Assert
        Assert::AreEqual(2.5, p.x());  // 1.0 + 1.5
        Assert::AreEqual(3.0, p.y());  // 2.0 + 1.0
        Assert::AreEqual(3.5, p.z());  // 3.0 + 0.5
    }

    TEST_METHOD(Point_Equal_Operator_True_Success)
    {
        // Arrange
        point p1(1.0, 2.0, 3.0);
        point p2(1.0, 2.0, 3.0);

        // Act & Assert
        Assert::IsTrue(p1 == p2);
    }

    TEST_METHOD(Point_Equal_Operator_False_Success)
    {
        // Arrange
        point p1(1.0, 2.0, 3.0);
        point p2(4.0, 5.0, 6.0);

        // Act & Assert
        Assert::IsFalse(p1 == p2);
    }

    TEST_METHOD(Point_NotEqual_Operator_Success)
    {
        // Arrange
        point p1(1.0, 2.0, 3.0);
        point p2(4.0, 5.0, 6.0);

        // Act & Assert
        Assert::IsTrue(p1 != p2);
    }
};

TEST_CLASS(VectorTests)
{

public:

    TEST_METHOD(Vector_Constructor_Default_Success)
    {
        // Arrange & Act
        vector v;

        // Assert
        Assert::AreEqual(0.0, v.i());
        Assert::AreEqual(0.0, v.j());
        Assert::AreEqual(0.0, v.k());
    }

    TEST_METHOD(Vector_Constructor_Parameters_Success)
    {
        // Arrange
        point A(1.0, 2.0, 3.0);
        point B(4.0, 5.0, 6.0);

        // Act
        vector v(A, B);

        // Assert
        Assert::AreEqual(3.0, v.i());
        Assert::AreEqual(3.0, v.j());
        Assert::AreEqual(3.0, v.k());
    }

    TEST_METHOD(Vector_CopyConstructor_Success)
    {
        // Arrange
        point A(0.0, 0.0, 0.0);
        point B(2.0, 4.0, 6.0);
        vector original(A, B);

        // Act
        vector copy(original);

        // Assert
        Assert::AreEqual(original.i(), copy.i());
        Assert::AreEqual(original.j(), copy.j());
        Assert::AreEqual(original.k(), copy.k());
    }

    TEST_METHOD(Vector_MoveConstructor_Success)
    {
        // Arrange
        point A(0.0, 0.0, 0.0);
        point B(3.0, 6.0, 9.0);
        vector original(A, B);
        double expectedI = original.i();
        double expectedJ = original.j();
        double expectedK = original.k();

        // Act
        vector moved(std::move(original));

        // Assert
        Assert::AreEqual(expectedI, moved.i());
        Assert::AreEqual(expectedJ, moved.j());
        Assert::AreEqual(expectedK, moved.k());
    }

    TEST_METHOD(Vector_AssignmentCopy_Success)
    {
        // Arrange
        point A(0.0, 0.0, 0.0);
        point B(1.0, 2.0, 3.0);
        vector source(A, B);
        vector target;

        // Act
        target = source;

        // Assert
        Assert::AreEqual(source.i(), target.i());
        Assert::AreEqual(source.j(), target.j());
        Assert::AreEqual(source.k(), target.k());
    }

    TEST_METHOD(Vector_AssignmentMove_Success)
    {
        // Arrange
        point A(0.0, 0.0, 0.0);
        point B(4.0, 5.0, 6.0);
        vector source(A, B);
        vector target;
        double expectedI = source.i();
        double expectedJ = source.j();
        double expectedK = source.k();

        // Act
        target = std::move(source);

        // Assert
        Assert::AreEqual(expectedI, target.i());
        Assert::AreEqual(expectedJ, target.j());
        Assert::AreEqual(expectedK, target.k());
    }

    TEST_METHOD(Vector_SelfAssignment_NoChange)
    {
        // Arrange
        point A(1.0, 2.0, 3.0);
        point B(5.0, 7.0, 9.0);
        vector v(A, B);
        double expectedI = v.i();
        double expectedJ = v.j();
        double expectedK = v.k();

        // Act
        v = v;  // Самоприсваивание

        // Assert
        Assert::AreEqual(expectedI, v.i());
        Assert::AreEqual(expectedJ, v.j());
        Assert::AreEqual(expectedK, v.k());
    }

    TEST_METHOD(Vector_Getters_Success)
    {
        // Arrange
        point A(1.0, 2.0, 3.0);
        point B(4.0, 7.0, 11.0);

        // Act
        vector v(A, B);

        // Assert
        Assert::AreEqual(3.0, v.i());
        Assert::AreEqual(5.0, v.j());
        Assert::AreEqual(8.0, v.k());
    }

    TEST_METHOD(Vector_Equal_Operator_True_Success)
    {
        // Arrange
        point A1(0.0, 0.0, 0.0);
        point B1(2.0, 4.0, 6.0);
        point A2(0.0, 0.0, 0.0);
        point B2(2.0, 4.0, 6.0);
        vector v1(A1, B1);
        vector v2(A2, B2);

        // Act & Assert
        Assert::IsTrue(v1 == v2);
    }

    TEST_METHOD(Vector_Equal_Operator_False_Success)
    {
        // Arrange
        point A1(0.0, 0.0, 0.0);
        point B1(1.0, 2.0, 3.0);
        point A2(0.0, 0.0, 0.0);
        point B2(4.0, 5.0, 6.0);
        vector v1(A1, B1);
        vector v2(A2, B2);

        // Act & Assert
        Assert::IsFalse(v1 == v2);
    }

    TEST_METHOD(Vector_NotEqual_Operator_Success)
    {
        // Arrange
        point A1(0.0, 0.0, 0.0);
        point B1(1.0, 1.0, 1.0);
        point A2(0.0, 0.0, 0.0);
        point B2(2.0, 2.0, 2.0);
        vector v1(A1, B1);
        vector v2(A2, B2);

        // Act & Assert
        Assert::IsTrue(v1 != v2);
    }

    TEST_METHOD(Vector_Addition_Success)
    {
        // Arrange
        point A1(0.0, 0.0, 0.0);
        point B1(1.0, 2.0, 3.0);
        point A2(0.0, 0.0, 0.0);
        point B2(4.0, 5.0, 6.0);
        vector v1(A1, B1);
        vector v2(A2, B2);

        // Act
        vector result = v1 + v2;

        // Assert
        Assert::AreEqual(5.0, result.i());
        Assert::AreEqual(7.0, result.j());
        Assert::AreEqual(9.0, result.k());
    }

    TEST_METHOD(Vector_Subtraction_Success)
    {
        // Arrange
        point A1(0.0, 0.0, 0.0);
        point B1(5.0, 7.0, 9.0);
        point A2(0.0, 0.0, 0.0);
        point B2(1.0, 2.0, 3.0);
        vector v1(A1, B1);
        vector v2(A2, B2);

        // Act
        vector result = v1 - v2;

        // Assert
        Assert::AreEqual(4.0, result.i());
        Assert::AreEqual(5.0, result.j());
        Assert::AreEqual(6.0, result.k());
    }

    TEST_METHOD(Vector_Multiply_ByScalar_Success)
    {
        // Arrange
        point A(0.0, 0.0, 0.0);
        point B(2.0, 3.0, 4.0);
        vector v(A, B);
        double scalar = 2.5;

        // Act
        vector result = v * scalar;

        // Assert
        Assert::AreEqual(5.0, result.i());
        Assert::AreEqual(7.5, result.j());
        Assert::AreEqual(10.0, result.k());
    }

    TEST_METHOD(Vector_Multiply_ScalarByVector_Success)
    {
        // Arrange
        point A(0.0, 0.0, 0.0);
        point B(1.0, 2.0, 3.0);
        vector v(A, B);
        double scalar = 3.0;

        // Act
        vector result = scalar * v;

        // Assert
        Assert::AreEqual(3.0, result.i());
        Assert::AreEqual(6.0, result.j());
        Assert::AreEqual(9.0, result.k());
    }

    TEST_METHOD(Vector_ComplexExpression_Success)
    {
        // Arrange
        point A1(0.0, 0.0, 0.0);
        point B1(1.0, 1.0, 1.0);
        point A2(0.0, 0.0, 0.0);
        point B2(2.0, 2.0, 2.0);
        point A3(0.0, 0.0, 0.0);
        point B3(3.0, 3.0, 3.0);
        vector v1(A1, B1);
        vector v2(A2, B2);
        vector v3(A3, B3);
        // (v1 + v2) * 2 - v3 = (3,3,3)*2 - (3,3,3) = (6,6,6) - (3,3,3) = (3,3,3)

        // Act
        vector result = (v1 + v2) * 2.0 - v3;

        // Assert
        Assert::AreEqual(3.0, result.i());
        Assert::AreEqual(3.0, result.j());
        Assert::AreEqual(3.0, result.k());
    }

    TEST_METHOD(Vector_ZeroVector_Success)
    {
        // Arrange
        point A(0.0, 0.0, 0.0);
        point B(0.0, 0.0, 0.0);
        vector zero(A, B);
        vector v(point(0, 0, 0), point(5.0, 5.0, 5.0));

        // Act
        vector sum = zero + v;
        vector diff = v - zero;

        // Assert
        Assert::AreEqual(v.i(), sum.i());
        Assert::AreEqual(v.j(), sum.j());
        Assert::AreEqual(v.k(), sum.k());
        Assert::AreEqual(v.i(), diff.i());
        Assert::AreEqual(v.j(), diff.j());
        Assert::AreEqual(v.k(), diff.k());
    }

    TEST_METHOD(Vector_NegativeScalar_Success)
    {
        // Arrange
        point A(0.0, 0.0, 0.0);
        point B(2.0, 4.0, 6.0);
        vector v(A, B);

        // Act
        vector result = v * (-2.0);

        // Assert
        Assert::AreEqual(-4.0, result.i());
        Assert::AreEqual(-8.0, result.j());
        Assert::AreEqual(-12.0, result.k());
    }

    TEST_METHOD(Vector_FromNonZeroStart_Success)
    {
        // Arrange
        point A(2.0, 3.0, 4.0);
        point B(5.0, 7.0, 11.0);

        // Act
        vector v(A, B);

        // Assert
        Assert::AreEqual(3.0, v.i());
        Assert::AreEqual(4.0, v.j());
        Assert::AreEqual(7.0, v.k());
    }

    TEST_METHOD(Vector_NegativeCoordinates_Success)
    {
        // Arrange
        point A(-1.0, -2.0, -3.0);
        point B(-4.0, -5.0, -6.0);

        // Act
        vector v(A, B);

        // Assert
        Assert::AreEqual(-3.0, v.i());
        Assert::AreEqual(-3.0, v.j());
        Assert::AreEqual(-3.0, v.k());
    }
	};
}
