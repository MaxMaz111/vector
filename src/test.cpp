#define CATCH_CONFIG_MAIN
#include "../util/catch.hpp"
#include "vector.hpp"

TEST_CASE("Vector is initially empty", "[vector]") {
    Vector<int> vec;

    REQUIRE(vec.GetSize() == 0);
    REQUIRE(vec.IsEmpty() == true);
    REQUIRE(vec.GetCapacity() == 0);
}

TEST_CASE("Adding elements with push_back increases size and capacity", "[vector]") {
    Vector<int> vec;

    vec.PushBack(10);
    vec.PushBack(20);
    vec.PushBack(30);

    REQUIRE(vec.GetSize() == 3);
    REQUIRE(vec.IsEmpty() == false);

    REQUIRE(vec.GetCapacity() >= vec.GetSize());

    REQUIRE(vec[0] == 10);
    REQUIRE(vec[1] == 20);
    REQUIRE(vec[2] == 30);
}

TEST_CASE("Accessing elements with operator[]", "[vector]") {
    Vector<int> vec;

    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);

    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);

    REQUIRE_THROWS_AS(vec[3], std::out_of_range);
}

TEST_CASE("pop_back reduces size", "[vector]") {
    Vector<int> vec;

    vec.PushBack(10);
    vec.PushBack(20);
    vec.PushBack(30);

    REQUIRE(vec.GetSize() == 3);

    vec.PopBack();
    REQUIRE(vec.GetSize() == 2);
    REQUIRE(vec[0] == 10);
    REQUIRE(vec[1] == 20);

    vec.PopBack();
    REQUIRE(vec.GetSize() == 1);

    vec.PopBack();
    REQUIRE(vec.GetSize() == 0);
    REQUIRE(vec.IsEmpty() == true);
}

TEST_CASE("Vector clear() method works", "[vector]") {
    Vector<int> vec;

    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);

    REQUIRE(vec.GetSize() == 3);

    vec.Clear();
    REQUIRE(vec.GetSize() == 0);
    REQUIRE(vec.IsEmpty() == true);

    vec.PushBack(4);
    REQUIRE(vec.GetSize() == 1);
    REQUIRE(vec[0] == 4);
}

TEST_CASE("Vector dynamically resizes as needed", "[vector]") {
    Vector<int> vec;

    for (int i = 0; i < 100; ++i) {
        vec.PushBack(i);
    }

    REQUIRE(vec.GetSize() == 100);
    REQUIRE(vec.GetCapacity() >= 100);

    for (int i = 0; i < 100; ++i) {
        REQUIRE(vec[i] == i);
    }
}

TEST_CASE("Copy assignment operator", "[vector]") {
    Vector<int> vec1;
    vec1.PushBack(1);
    vec1.PushBack(2);
    vec1.PushBack(3);

    Vector<int> vec2;
    vec2 = vec1;

    REQUIRE(vec2.GetSize() == 3);
    REQUIRE(vec2[0] == 1);
    REQUIRE(vec2[1] == 2);
    REQUIRE(vec2[2] == 3);

    vec1[0] = 10;
    REQUIRE(vec2[0] == 1);
}

TEST_CASE("Move assignment operator", "[vector]") {
    Vector<int> vec1;
    vec1.PushBack(1);
    vec1.PushBack(2);
    vec1.PushBack(3);

    Vector<int> vec2;
    vec2 = std::move(vec1);

    REQUIRE(vec2.GetSize() == 3);
    REQUIRE(vec2[0] == 1);
    REQUIRE(vec2[1] == 2);
    REQUIRE(vec2[2] == 3);

    REQUIRE(vec1.GetSize() == 0);
    REQUIRE(vec1.GetCapacity() == 0);
}

TEST_CASE("shrink_to_fit reduces capacity to size", "[vector]") {
    Vector<int> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);

    size_t original_capacity = vec.GetCapacity();

    REQUIRE(original_capacity > vec.GetSize());

    vec.ShrinkToFit();
    REQUIRE(vec.GetCapacity() == vec.GetSize());

    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
}

TEST_CASE("Self-move assignment operator", "[vector]") {
    Vector<int> vec;
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);

    vec = std::move(vec);

    REQUIRE(vec.GetSize() == 3);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);

    REQUIRE(vec.GetCapacity() >= vec.GetSize());
}

TEST_CASE("Stress test for vector", "[vector][stress]") {
    const size_t num_elements = 1000000;

    Vector<int> vec;

    for (size_t i = 0; i < num_elements; ++i) {
        vec.PushBack(static_cast<int>(i));
    }

    REQUIRE(vec.GetSize() == num_elements);

    REQUIRE(vec[0] == 0);
    REQUIRE(vec[num_elements / 2] == static_cast<int>(num_elements / 2));
    REQUIRE(vec[num_elements - 1] == static_cast<int>(num_elements - 1));

    for (size_t i = 1; i <= num_elements; ++i) {
        REQUIRE(vec.Back() == num_elements - i);
        vec.PopBack();
    }

    REQUIRE(vec.GetSize() == 0);
    REQUIRE(vec.IsEmpty() == true);

    vec.ShrinkToFit();
    REQUIRE(vec.GetCapacity() == 0);
}