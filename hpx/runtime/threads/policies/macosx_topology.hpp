////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c) 2008-2009 Chirag Dekate, Anshul Tandon
//  Copyright (c)      2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_AE753913_CC4F_4F15_B93B_CA38B59E8CCE)
#define HPX_AE753913_CC4F_4F15_B93B_CA38B59E8CCE

#include <AvailabilityMacros.h>

#ifdef AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
    #include <mach/mach.h>
    #include <mach/mach_error.h>
    #include <mach/thread_policy.h>
#endif

#include <hpx/runtime/threads/topology.hpp>
#include <hpx/exception.hpp>

namespace hpx { namespace threads 
{

struct macosx_topology : topology
{
    std::size_t get_numa_node_number(
        std::size_t thread_num
      , error_code& ec = throws
        ) const
    {
        if (&ec != &throws)
            ec = make_success_code();

        return std::size_t(-1);
    }

    std::size_t get_numa_node_affinity_mask(
        std::size_t thread_num
      , bool numa_sensitive
      , error_code& ec = throws
        ) const
    {
        if (&ec != &throws)
            ec = make_success_code();

        return 0;
    }

    std::size_t get_thread_affinity_mask(
        std::size_t thread_num
      , bool numa_sensitive
      , error_code& ec = throws
        ) const
    {
        if (&ec != &throws)
            ec = make_success_code();

        return 0;
    }

    void set_thread_affinity(
        boost::thread& thrd
      , std::size_t num_thread
      , bool numa_sensitive
      , error_code& ec = throws
        ) const
    {
        if (&ec != &throws)
            ec = make_success_code();
    }

    void set_thread_affinity(
        std::size_t num_thread
      , bool numa_sensitive
      , error_code& ec = throws
        ) const
    {
        #ifdef AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
            thread_extended_policy_data_t epolicy;
            epolicy.timeshare = FALSE;

            kern_return_t ret = thread_policy_set(mach_thread_self(),
                THREAD_EXTENDED_POLICY, (thread_policy_t) &epolicy,
                THREAD_EXTENDED_POLICY_COUNT);

            if (ret != KERN_SUCCESS)
                HPX_THROWS_IF(ec, kernel_error,
                    "hpx::threads::set_thread_affinity"
                  , "failed to set thread affinity");

            if (ec)
                return;

            thread_affinity_policy_data_t policy;
            policy.affinity_tag = num_thread + 1;   // 1...N

            ret = thread_policy_set(mach_thread_self(),
                THREAD_AFFINITY_POLICY, (thread_policy_t) &policy,
                THREAD_AFFINITY_POLICY_COUNT);

            if (ret != KERN_SUCCESS)
                HPX_THROWS_IF(ec, kernel_error,
                    "hpx::threads::set_thread_affinity"
                  , "failed to set thread affinity");

            if (ec)
                return;
            else if (&ec != &throws)
                ec = make_success_code();
        #else
            if (&ec != &throws)
                ec = make_success_code();
        #endif
    }

    std::size_t get_thread_affinity_mask_from_lva(
        naming::address::address_type lva
      , error_code& ec = throws
        ) const
    {
        if (&ec != &throws)
            ec = make_success_code();

        return 0;
    }
};

}}

#endif // HPX_AE753913_CC4F_4F15_B93B_CA38B59E8CCE

