#include <gtest/gtest.h>
#include "RingBuffer.h"

#include <cstring>

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
    ASSERT_TRUE(buffer.isEmptyLock());
    ASSERT_FALSE(buffer.isFullLock());
}

TEST_F(RingBufferFixture, PushAndPop)
{
    const uint8_t my_data[] = {0x00, 0x04, 0x08, 0x0C};
    PacketData sent_packet(my_data, sizeof(my_data));
    ASSERT_TRUE(buffer.tryPush(sent_packet));

    PacketData received;
    ASSERT_TRUE(buffer.tryPop(received));
    ASSERT_EQ(received.data.size(), sent_packet.data.size());
    ASSERT_NE(received.data.data(), nullptr);

    ASSERT_EQ(received.data, sent_packet.data);
}

TEST_F(RingBufferFixture, FullBufferHandling)
{
    const uint8_t my_data[] = {0xFF};
    PacketData test_packet(my_data, sizeof(my_data));
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ASSERT_TRUE(buffer.tryPush(test_packet));
    }

    ASSERT_TRUE(buffer.isFullLock());
    ASSERT_EQ(buffer.getSizeLock(), BUFFER_SIZE);

    ASSERT_FALSE(buffer.tryPush(test_packet));

    ASSERT_TRUE(buffer.isFullLock());
    ASSERT_EQ(buffer.getSizeLock(), BUFFER_SIZE);
}

TEST_F(RingBufferFixture, EmptyBufferHandling)
{
    PacketData received;
    ASSERT_FALSE(buffer.tryPop(received));
    ASSERT_TRUE(buffer.isEmptyLock());
    ASSERT_EQ(buffer.getSizeLock(), 0);
}

TEST_F(RingBufferFixture, WrappingAndFIFO)
{
    for (uint8_t i = 1; i <= 3; i++)
    {
        PacketData packet;
        packet.data.push_back(i);
        ASSERT_TRUE(buffer.tryPush(packet));
    }

    for (uint8_t i = 1; i <= 2; i++)
    {
        PacketData received;
        ASSERT_TRUE(buffer.tryPop(received));
        ASSERT_EQ(received.data.size(), 1);
        ASSERT_EQ(received.data[0], i);
    }
    for (uint8_t i = 4; i <= 6; i++)
    {
        PacketData packet;
        packet.data.push_back(i);
        ASSERT_TRUE(buffer.tryPush(packet));
    }
    int expected_id = 3;
    PacketData received;
    while (buffer.tryPop(received))
    {
        ASSERT_EQ(received.data.size(), 1);
        ASSERT_EQ(received.data[0], expected_id);
        expected_id++;
    }
    ASSERT_TRUE(buffer.isEmptyLock());
    ASSERT_EQ(expected_id, 7);
}
