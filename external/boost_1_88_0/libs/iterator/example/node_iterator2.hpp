// Copyright David Abrahams 2004. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef NODE_ITERATOR2_DWA2004110_HPP
# define NODE_ITERATOR2_DWA2004110_HPP

# include "node.hpp"
# include <boost/iterator/iterator_facade.hpp>
# include <type_traits>

template <class Value>
class node_iter
  : public boost::iterator_facade<
        node_iter<Value>
      , Value
      , boost::forward_traversal_tag
    >
{
 private:
    struct enabler {};  // a private type avoids misuse

 public:
    node_iter()
      : m_node(0) {}

    explicit node_iter(Value* p)
      : m_node(p) {}

    template <class OtherValue>
    node_iter(
        node_iter<OtherValue> const& other
      , typename std::enable_if<
            std::is_convertible<OtherValue*,Value*>::value
          , enabler
        >::type = enabler()
    )
      : m_node(other.m_node) {}

    template <class OtherValue>
    bool equal(node_iter<OtherValue> const& other) const
    {
        return this->m_node == other.m_node;
    }

    void increment() { m_node = m_node->next(); }

    Value& dereference() const { return *m_node; }

# ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
 public:
# else
 private:
    template <class> friend class node_iter;
# endif
    Value* m_node;
};

typedef node_iter<node_base> node_iterator;
typedef node_iter<node_base const> node_const_iterator;

#endif // NODE_ITERATOR2_DWA2004110_HPP
