#include "../g.hpp"

#include "access/heaptuple.hpp"

TEST(test_pod, pod)
{
	EXPECT_TRUE(std::is_pod_v<HeapTupleData>);
}
