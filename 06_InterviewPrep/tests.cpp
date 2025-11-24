#include <vector>
#include <gtest/gtest.h>

using namespace std;

class VectorTest {
public:
    int setup() {
        vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        return vec.size();
    }
};

TEST(VectorTest, size) {
    VectorTest v;
    EXPECT_EQ(v.setup(), 2);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}