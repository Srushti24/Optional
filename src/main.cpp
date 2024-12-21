#include <Optional.hpp>
#include <cassert>
#include <iostream>

void testWithStruct() {
    struct S {
        S(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {}
        ~S() {}
        int m_a;
        int m_b;
        int m_c;
    };

    S           s(1, 2, 3);
    Optional<S> temp1(s); // Constructor
    assert(temp1.has_value() == true);
    assert(temp1.value().m_a == 1);
    assert(temp1.value().m_b == 2);
    assert(temp1.value().m_c == 3);
    Optional<S> temp2 = temp1;
    assert(temp2.has_value() == true);
    assert(temp2.value().m_a == 1);
    assert(temp2.value().m_b == 2);
    assert(temp2.value().m_c == 3);
}

// Copy Constructor
void testAllBasic() {
    Optional<int> temp = 2; // param constructor
    assert(temp.has_value() == true);
    assert(temp.value() == 2);
    Optional<int> temp2(temp); // copy constructor check
    assert(temp2.has_value() == true);
    assert(temp2.value() == 2);
    Optional<int> temp3;
    assert(temp3.has_value() == false);
    temp3 = temp; // Copy Assignment operator
    assert(temp3.has_value() == true);
    assert(temp3.value() == 2);
    Optional<int> temp4(std::move(temp)); // Move constructor
    assert(temp4.has_value() == true);
    assert(temp4.value() == 2);
    assert(temp.has_value() == false);
    assert(temp.value() == 0);
    temp = std::move(temp4); // Move Assignment operator
    assert(temp.has_value() == true);
    assert(temp.value() == 2);
    assert(temp4.has_value() == false);
    assert(temp4.value() == 0);
}

int main() {
    //  testAllBasic();
    testWithStruct();
    return 0;
}