#include "ip_tools.h"
#include "gtest/gtest.h"

TEST(IPToolsTests, GetNumericalIPTest) {
    const ip_addr_str_t test_ip_str = {"192", "168", "0", "110"};
    ip_addr_num_t test_ip_num;

    get_numerical_ip(test_ip_str, test_ip_num);

    const ip_addr_num_t ref_ip_num = {192, 168, 0, 110};

    for (unsigned int i = 0; i < test_ip_num.size(); i++)
    {
        EXPECT_EQ(test_ip_num[i], ref_ip_num[i]);
    }
}

TEST(IPToolsTests, GenerateIndexTest)
{
    const ip_addr_num_t test_ip_num = {192, 168, 0, 110};
    const index_t ref_index = 0xc0a8006e;

    EXPECT_EQ(ref_index, generate_index(test_ip_num));
}

TEST(IPToolsTests, GenerateIPTEst)
{
    const index_t test_index = 0xc0a8006e;
    ip_addr_num_t test_ip_num;

    generate_ip(test_index, test_ip_num);

    const ip_addr_num_t ref_ip_num = {192, 168, 0, 110};

    for (unsigned int i = 0; i < test_ip_num.size(); i++)
    {
        EXPECT_EQ(test_ip_num[i], ref_ip_num[i]);
    }
}

