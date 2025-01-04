#include <cassert>
#include <iostream>
#include <optional.hpp>

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
            std::cout << "constructor of S called" << std::endl;
            constructionCount_++;
        }
        ~S() {
            std::cout << "destructor of S called" << std::endl;
            destructionCount_++;
        }

        S(const S& copy)                                                                             // Copy Constructor
            : constructionCount_(copy.constructionCount_), destructionCount_(copy.destructionCount_) // copy constructor
        {
            std::cout << "copy constructor of S called" << std::endl;
            constructionCount_++;
        }

        S& operator=(const S& copy) // copy assign operator
        {
            constructionCount_ = copy.constructionCount_;
            destructionCount_  = copy.destructionCount_;
            std::cout << "copy assignment operator of S called" << std::endl;
            constructionCount_++;
            return *this;
        }

        S(S&& copy)
            : constructionCount_(copy.constructionCount_),
              destructionCount_(copy.destructionCount_) { // Move Constructor
            std::cout << "Move constructor of S called" << std::endl;
            constructionCount_++;
        }

        S& operator=(S&& copy) { // Move Assignment Operator
            constructionCount_ = copy.constructionCount_;
            destructionCount_  = copy.destructionCount_;
            constructionCount_++;
            return *this;
        }

        int& constructionCount_;
        int& destructionCount_;
    };

    {
        Optional<S> op1 = S(constructionCount, destructionCount);
        op1.destroy();
    }
    assert(constructionCount == 2);
    assert(destructionCount == 2);

    {
        S           s1(constructionCount, destructionCount); // s1 created
        Optional<S> temp1(s1); // temp1 created using copy constructor which created one more S1
        assert(constructionCount == 2);
        {
            S           s2(constructionCount, destructionCount); // s2 created
            Optional<S> temp2(s2); // temp2 created // s2 created using copy constructor which created one more s2
            assert(constructionCount == 4);
            {
                S           s3(constructionCount, destructionCount);
                Optional<S> temp3(s3); // temp3 created
                assert(constructionCount == 6);
            } // temp3 destroyed and so did s3
            assert(destructionCount == 2);
        } // temp2 destroyed and so did s2
        assert(destructionCount == 4);
    } // temp1 destroyed and so did s1
    assert(destructionCount == 6);

    constructionCount = 0;
    destructionCount  = 0;
    {
        S           s1(constructionCount, destructionCount);
        Optional<S> temp1(s1); // temp1 created using param constructor
        assert(temp1.value().constructionCount_ == 2);
        assert(constructionCount == 2);
        {
            Optional<S> temp2(temp1); // temp2 created using copy constructor
            assert(temp2.value().constructionCount_ == 3);
            assert(constructionCount == 3);
        }
        std::cout << "before" << std::endl;
        assert(temp1.value().destructionCount_ == 1); // temp2 destroyed
        std::cout << "after" << std::endl;
    }
    std::cout << "after 2" << std::endl;
    assert(destructionCount == 3); // s1 and temp1 destroyed

    {
        constructionCount = 0;
        destructionCount  = 0;
        S           s1(constructionCount, destructionCount); // s1 created
        Optional<S> temp1(std::move(s1));                    // Move the values
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
    temp = std::move(temp4); // Move Assignment operator
    assert(temp.has_value() == true);
    assert(temp.value() == 2);
}

int main() {
    //  testAllBasic();
    // testWithStruct();
    testWithS();
    return 0;
}