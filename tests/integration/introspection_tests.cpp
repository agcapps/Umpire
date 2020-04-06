#include "gtest/gtest.h"

#include "umpire/config.hpp"
#include "umpire/Umpire.hpp"

TEST(IntrospectionTest, Overlaps)
{
  auto& rm = umpire::ResourceManager::getInstance();
  umpire::Allocator allocator{rm.getAllocator("HOST")};
  umpire::strategy::AllocationStrategy* strategy{
    rm.getAllocator("HOST").getAllocationStrategy()};

  char* data{static_cast<char*>(allocator.allocate(4096))};

  {
    char* overlap_ptr = data+17;
    auto overlap_record = umpire::util::AllocationRecord{overlap_ptr, 4096, strategy};
    rm.registerAllocation(overlap_ptr, overlap_record);

    ASSERT_TRUE(umpire::pointer_overlaps(data, overlap_ptr));

    rm.deregisterAllocation(overlap_ptr);
  }

  {
    char* overlap_ptr = data+4095;
    auto overlap_record = umpire::util::AllocationRecord{overlap_ptr, 128, strategy};
    rm.registerAllocation(overlap_ptr, overlap_record);

    ASSERT_TRUE(umpire::pointer_overlaps(data, overlap_ptr));

    rm.deregisterAllocation(overlap_ptr);
  }

  {
    char* overlap_ptr = data+4096;
    auto overlap_record = umpire::util::AllocationRecord{overlap_ptr, 128, strategy};
    rm.registerAllocation(overlap_ptr, overlap_record);

    ASSERT_FALSE(umpire::pointer_overlaps(data, overlap_ptr));

    rm.deregisterAllocation(overlap_ptr);
  }

  {
    char* overlap_ptr = data+2048;
    auto overlap_record = umpire::util::AllocationRecord{overlap_ptr, 2047, strategy};
    rm.registerAllocation(overlap_ptr, overlap_record);

    ASSERT_FALSE(umpire::pointer_overlaps(data, overlap_ptr));
    rm.deregisterAllocation(overlap_ptr);
  }

  {
    char* overlap_ptr = data+2048;
    auto overlap_record = umpire::util::AllocationRecord{overlap_ptr, 2048, strategy};
    rm.registerAllocation(overlap_ptr, overlap_record);

    ASSERT_FALSE(umpire::pointer_overlaps(data, overlap_ptr));
    rm.deregisterAllocation(overlap_ptr);
  }

  allocator.deallocate(data);
}

TEST(IntrospectionTest, Contains)
{
//  auto& rm = umpire::ResourceManager::getInstance();
//  umpire::Allocator allocator{rm.getAllocator("HOST")};
//  umpire::strategy::AllocationStrategy* strategy{
//    rm.getAllocator("HOST").getAllocationStrategy()};
//
//  char* data{static_cast<char*>(allocator.allocate(4096))};
//
//  {
//    char* contains_ptr = data+2048;
//    ASSERT_FALSE(umpire::pointer_contains(data, contains_ptr));
//  }
//
}