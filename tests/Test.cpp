#include <gtest/gtest.h>

class TestTemplate : public testing::Test
{
protected:
	TestTemplate() = default;
	virtual ~TestTemplate() = default;
};

TEST_F(TestTemplate, TestGoogleTest)
{
	EXPECT_EQ(true, true);
}