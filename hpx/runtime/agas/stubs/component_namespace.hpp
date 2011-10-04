////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_85B78E29_DD30_4603_8EF5_29EFB32FD10D)
#define HPX_85B78E29_DD30_4603_8EF5_29EFB32FD10D

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/eager_future.hpp>
#include <hpx/runtime/agas/server/component_namespace.hpp>

namespace hpx { namespace agas { namespace stubs
{

struct component_namespace 
{
    // {{{ nested types
    typedef server::component_namespace server_type; 

    typedef server_type::component_id_type component_id_type;
    typedef server_type::prefix_type prefix_type;
    typedef server_type::prefixes_type prefixes_type;
    // }}}

    // {{{ bind_prefix dispatch
    static lcos::promise<response>
    bind_prefix_async(naming::id_type const& gid, std::string const& key,
                      prefix_type prefix)
    {
        typedef server_type::bind_prefix_action action_type;
        return lcos::eager_future<action_type, response>
            (gid, key, prefix);
    }

    static response
    bind_prefix(naming::id_type const& gid, std::string const& key,
                prefix_type prefix, error_code& ec = throws)
    {
        return bind_prefix_async(gid, key, prefix).get(ec);
    } 
    // }}}
    
    // {{{ bind_name dispatch 
    static lcos::promise<response>
    bind_name_async(naming::id_type const& gid, std::string const& key)
    {
        typedef server_type::bind_name_action action_type;
        return lcos::eager_future<action_type, response>(gid, key);
    }
    
    static response
    bind_name(naming::id_type const& gid, std::string const& key,
              error_code& ec = throws)
    { return bind_name_async(gid, key).get(ec); } 
    // }}}

    // {{{ resolve_id dispatch
    static lcos::promise<response>
    resolve_id_async(naming::id_type const& gid, component_id_type key)
    {
        typedef server_type::resolve_id_action action_type;
        return lcos::eager_future<action_type, response>(gid, key);
    }
    
    static response
    resolve_id(naming::id_type const& gid, component_id_type key,
               error_code& ec = throws)
    { return resolve_id_async(gid, key).get(ec); } 
    // }}}

    // {{{ resolve_name dispatch 
    static lcos::promise<response>
    resolve_name_async(naming::id_type const& gid,
                       std::string const& key)
    {
        typedef server_type::resolve_name_action action_type;
        return lcos::eager_future<action_type, response>(gid, key);
    }
    
    static response
    resolve_name(naming::id_type const& gid, std::string const& key,
                 error_code& ec = throws)
    { return resolve_name_async(gid, key).get(ec); } 
    // }}}

    // {{{ unbind dispatch 
    static lcos::promise<response>
    unbind_async(naming::id_type const& gid, std::string const& key,
                 error_code& ec = throws)
    {
        typedef server_type::unbind_action action_type;
        return lcos::eager_future<action_type, response>(gid, key);
    }
    
    static response
    unbind(naming::id_type const& gid, std::string const& key,
           error_code& ec = throws)
    { return unbind_async(gid, key).get(ec); } 
    // }}}
};            

}}}

#endif // HPX_85B78E29_DD30_4603_8EF5_29EFB32FD10D
