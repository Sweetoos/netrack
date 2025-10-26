#include <gtest/gtest.h>
#include "RingBuffer.h"

class RingBufferFixture : public ::testing::Test
{
protected:
    static constexpr int BUFFER_SIZE = 4;
    RingBuffer buffer;

public:
    RingBufferFixture() : buffer(BUFFER_SIZE) {}
};

TEST_F(RingBufferFixture, IsInittialyEmpty)
{
    ASSERT_TRUE(buffer.isEmpty());
    ASSERT_FALSE(buffer.isFull());
}

TEST_F(RingBufferFixture, PushAndPop)
{
    const uint8_t my_data[] = {0x00, 0x04, 0x08, 0x0C};
    PacketData sent_packet(my_data, sizeof(my_data));
    ASSERT_TRUE(buffer.tryPush(sent_packet));

    PacketData received;
    ASSERT_TRUE(buffer.tryPop(received));
    ASSERT_EQ(received.len, sent_packet.len);
    ASSERT_NE(received.data, nullptr);

    ASSERT_EQ(memcmp(received.data, sent_packet.data, sent_packet.len), 0);
}

TEST_F(RingBufferFixture, FullBufferHandling)
{
    const uint8_t my_data[] = {0xFF};
    PacketData test_packet(my_data, sizeof(my_data));
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ASSERT_TRUE(buffer.tryPush(test_packet));
    }

    ASSERT_TRUE(buffer.isFull());
    ASSERT_EQ(buffer.getSize(), BUFFER_SIZE);

    ASSERT_FALSE(buffer.tryPush(test_packet));

    ASSERT_TRUE(buffer.isFull());
    ASSERT_EQ(buffer.getSize(), BUFFER_SIZE);
}

TEST_F(RingBufferFixture, EmptyBufferHandling)
{
    PacketData received;
    ASSERT_FALSE(buffer.tryPop(received));
    ASSERT_TRUE(buffer.isEmpty());
    ASSERT_EQ(buffer.getSize(), 0);
}
TEST_F(RingBufferFixture, WrappingAndFIFO)
{
    for (int i = 1; i <= 3; i++)
    {
        ASSERT_TRUE(buffer.tryPush(PacketData(nullptr, i)));
    }

    for (int i = 1; i <= 2; i++)
    {
        PacketData received;
        ASSERT_TRUE(buffer.tryPop(received));
        ASSERT_EQ(received.len, i);
    }
    for (int i = 4; i <= 6; i++)
    {
        ASSERT_TRUE(buffer.tryPush(PacketData(nullptr, i)));
    }
    int expected_id = 3;
    while (!buffer.isEmpty())
    {
        PacketData received;
        ASSERT_TRUE(buffer.tryPop(received));
        ASSERT_EQ(received.len, expected_id);
        expected_id++;
    }
}
