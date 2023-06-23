#include "s21_test_containers.h"

// test vector
TEST(vectorConstructorsTest, defaultConstructor) {
  s21::vector<int> x;
  EXPECT_EQ(0, x.size());
  EXPECT_EQ(1, x.empty());
}

TEST(vectorConstructorsTest, parameterizedConstructor) {
  s21::vector<int> x(5);
  EXPECT_EQ(5, x.size());
  EXPECT_EQ(0, x.empty());
}

TEST(vectorConstructorsTest, initializerListConstructorConstructor) {
  s21::vector<int> x = {1, 2, 3};
  s21::vector<int> y = {1, 2, 3};

  for (size_t i = 0; i < x.size(); ++i) {
    EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
  }
}

TEST(vectorConstructorsTest, copyConstructor) {
  s21::vector<int> x = {1, 2, 3};
  s21::vector<int> y = x;
  for (size_t i = 0; i < x.size(); ++i) {
    EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
  }
}

TEST(vectorCapacityTest, funcSize) {
  s21::vector<int> x(5);
  s21::vector<int> y(5);
  EXPECT_EQ(x.size(), y.size());
}

TEST(vectorCapacityTest, funcCapacity) {
  s21::vector<char> x = {'D', 'e', 'n'};
  EXPECT_EQ(3, x.capacity());
}

TEST(vectorTest, AtThrowsExceptionWhenOutOfRange) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_THROW(v.at(3), CustomException);
}

TEST(VectorTest, OperatorAccessesElement) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(v[1], 2);
}

TEST(vectorTest, FrontAccessesFirstElement) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.front(), 1);
}

TEST(vectorTest, BackAccessesLastElement) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.back(), 3);
}

TEST(vectorTest, DataAccessesInternalArray) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.data()[1], 2);
}

TEST(vectorTest, BeginReturnsIteratorToBeginning) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(*v.begin(), 1);
}

TEST(vectorTest, EndReturnsIteratorToEnd) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(*(v.end() - 1), 3);
}

TEST(vectorTest, EmptyReturnsTrueForEmptyVector) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
}

TEST(vectorTest, EmptyReturnsFalseForNonEmptyVector) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_FALSE(v.empty());
}

TEST(vectorTest, SizeReturnsCorrectSize) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.size(), 3);
}

// TEST(vectorTest, MaxSizeReturnsMaxSize) {
//   s21::vector<int> v{1, 2, 3};
//   EXPECT_EQ(v.max_size(),
//   std::numeric_limits<vector<int>::size_type>::max());
// }

TEST(vectorTest, ReserveReservesMemory) {
  s21::vector<int> v{1, 2, 3};
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);
}

TEST(vectorTest, CapacityReturnsCurrentCapacity) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.capacity(), 3);
}

TEST(vectorTest, ShrinkToFitReducesCapacityToSize) {
  s21::vector<int> v{1, 2, 3};
  v.reserve(10);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 3);
}

TEST(vectorTest, ClearRemovesAllElements) {
  s21::vector<int> v{1, 2, 3};
  v.clear();
  EXPECT_TRUE(v.empty());
}

// test list
TEST(listConstructorsTest, defaultConstructor) {
  s21::list<char> x;
  EXPECT_EQ(0, x.size());
  EXPECT_EQ(1, x.empty());
}

TEST(listConstructorsTest, parameterizedConstructor) {
  s21::list<char> x(5);
  EXPECT_EQ(5, x.size());
  EXPECT_EQ(0, x.empty());
}

TEST(listTest, PushBackTest) {
  s21::list<int> my_list;
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);

  EXPECT_EQ(my_list.size(), 3);
  EXPECT_EQ(my_list.back(), 3);
}

TEST(listTest, PopBackTest) {
  s21::list<int> my_list;
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);

  my_list.pop_back();
  EXPECT_EQ(my_list.size(), 2);
  EXPECT_EQ(my_list.back(), 2);

  my_list.pop_back();
  EXPECT_EQ(my_list.size(), 1);
  EXPECT_EQ(my_list.back(), 1);

  my_list.pop_back();
  EXPECT_EQ(my_list.size(), 0);
  EXPECT_TRUE(my_list.empty());
}

// test stack
TEST(constructorTests, defaultConstructor) {
  s21::stack<int> s;
  EXPECT_TRUE(s.size() == 0);
}

TEST(constructorTests, copyConstructor) {
  s21::stack<int> s1;
  s1.push(1);
  s21::stack<int> s2 = s1;
  EXPECT_TRUE(s1 == s2);
}

TEST(constructorTests, initializerListConstructor) {
  s21::stack<int> s = {1, 2, 3};
  EXPECT_TRUE(s.size() == 3);
}

TEST(constructorTests, destructor) {
  s21::stack<int> s;
  s.push(1);
  s.~stack();
  EXPECT_TRUE(s.size() == 0);
}

TEST(methodsTests, pushANDpopANDtop) {
  s21::stack<int> s;
  s.push(1);
  s.push(2);
  EXPECT_TRUE(s.top() == 2);
  s.pop();
  EXPECT_TRUE(s.top() == 1);
}

TEST(methodsTests, emptyANDclearANDsize) {
  s21::stack<int> s;
  s.push(1);
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s.size() == 1);
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s.size() == 0);
}

TEST(methodsTests, swap) {
  s21::stack<int> s1 = {1, 2, 3, 4};
  s21::stack<int> s2 = {5, 6, 7};
  s1.swap(s2);
  EXPECT_TRUE(s2.top() == 1);
  EXPECT_TRUE(s1.top() == 5);
}

TEST(methodsTests, beginANDend) {
  s21::stack<int> s = {6, 2, 3, 4};
  s21::stack<int>::iterator iter = s.begin();
  s21::stack<int>::iterator iter2 = s.end();
  EXPECT_TRUE(*iter == 6);
  for (; iter != iter2; ++iter) {
  }
  EXPECT_TRUE(iter == iter2);
}

// test queue
TEST(methodsTests, pushANDpop) {
  s21::queue<int> q;
  q.push(1);
  q.push(3);
  q.pop();
  EXPECT_TRUE(q.front() == 3);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
