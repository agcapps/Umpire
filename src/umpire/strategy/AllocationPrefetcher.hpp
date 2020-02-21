//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_AllocationPrefetcher_HPP
#define UMPIRE_AllocationPrefetcher_HPP

#include <memory>

#include "umpire/strategy/AllocationStrategy.hpp"
#include "umpire/Allocator.hpp"
#include "umpire/op/MemoryOperation.hpp"

namespace umpire {
namespace strategy {

/*!
 *
 * \brief Apply the appropriate "PREFETCH" operation to every allocation.
 */
class AllocationPrefetcher :
  public AllocationStrategy
{
  public:
      AllocationPrefetcher(
        const std::string& name,
        int id,
        Allocator allocator,
        int device_id = 0);

    void* allocate(std::size_t bytes);
    void deallocate(void* ptr);

    std::size_t getCurrentSize() const noexcept;
    std::size_t getHighWatermark() const noexcept;

    Platform getPlatform() noexcept;

    MemoryResourceTraits getTraits() const noexcept;
  private:
    std::shared_ptr<op::MemoryOperation> m_prefetch_operation;
    strategy::AllocationStrategy* m_allocator;
    int m_device;
};

} // end of namespace strategy
} // end namespace umpire

#endif // UMPIRE_AllocationPrefetcher_HPP
