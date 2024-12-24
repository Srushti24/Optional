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

void testWithS() {
    int constructionCount = 0;
    int destructionCount  = 0;

    struct S {
        S(int& constructionCount, int& destructionCount)
            : constructionCount_(constructionCount), destructionCount_(destructionCount) {
            std::cout << "constructor called" << std::endl;
            constructionCount_++;
        }
        ~S() {
            std::cout << "destructor called" << std::endl;
            destructionCount_++;
        }
        int& constructionCount_;
        int& destructionCount_;
    };
    {
        S           s1(constructionCount, destructionCount);
        Optional<S> temp1(s1); // temp1 created
        assert(constructionCount == 1);
        {
            S           s2(constructionCount, destructionCount);
            Optional<S> temp2(s2); // temp2 created
            assert(constructionCount == 2);
            {
                S           s3(constructionCount, destructionCount);
                Optional<S> temp3(s3); // temp3 created
                assert(constructionCount == 3);
            } // temp3 destroyed
            assert(destructionCount == 2);
        } // temp2 destroyed
        assert(destructionCount == 4);
    }
    assert(destructionCount == 6);

    {

        S           s1(constructionCount, destructionCount);
        Optional<S> temp1(s1); // temp1 created
        Optional<S> temp2;
        Optional<S> temp3(s1);
        assert(temp1.has_value() == true);
        assert(temp2.has_value() == false);
        temp1 = temp2;
        assert(temp1.has_value() == false);
        temp2 = temp3; // Copy Assign Operator
        assert(temp2.value().constructionCount_ == 4);
    }
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
    temp = std::move(temp4); // Move Assignment operator
    assert(temp.has_value() == true);
    assert(temp.value() == 2);
    assert(temp4.has_value() == false);
}

int main() {
    testAllBasic();
    testWithStruct();
    testWithS();
    return 0;
}