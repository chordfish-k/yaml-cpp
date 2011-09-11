#ifndef NODE_DETAIL_NODE_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define NODE_DETAIL_NODE_H_62B23520_7C8E_11DE_8A39_0800200C9A66

#if defined(_MSC_VER) || (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || (__GNUC__ >= 4)) // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif


#include "yaml-cpp/dll.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/node/ptr.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include <boost/utility.hpp>

namespace YAML
{
	namespace detail
	{
		class node: private boost::noncopyable
		{
		public:
			node(): m_pRef(new node_ref) {}

			bool is(const node& rhs) const { return m_pRef == rhs.m_pRef; }
			const node_ref *ref() const { return m_pRef.get(); }
			
			NodeType::value type() const { return m_pRef->type(); }
			
			const std::string& scalar() const { return m_pRef->scalar(); }
			
			void set_ref(const node& rhs) { m_pRef = rhs.m_pRef; }
			void set_data(const node& rhs) { m_pRef->set_data(*rhs.m_pRef); }
				
			void set_type(NodeType::value type) { m_pRef->set_type(type); }
			void set_null() { m_pRef->set_null(); }
			void set_scalar(const std::string& scalar) { m_pRef->set_scalar(scalar); }

			// size/iterator
			std::size_t size() const { return m_pRef->size(); }
			
			const_node_iterator begin() const { return static_cast<const node_ref&>(*m_pRef).begin(); }
			node_iterator begin() { return m_pRef->begin(); }
			
			const_node_iterator end() const { return static_cast<const node_ref&>(*m_pRef).end(); }
			node_iterator end() { return m_pRef->end(); }

			// sequence
			void append(node& node, shared_memory_holder pMemory) { m_pRef->append(node, pMemory); }
			void insert(node& key, node& value, shared_memory_holder pMemory) {
				m_pRef->insert(key, value, pMemory);
			}

			// indexing
			template<typename Key> node& get(const Key& key, shared_memory_holder pMemory) const { return static_cast<const node_ref&>(*m_pRef).get(key, pMemory); }
			template<typename Key> node& get(const Key& key, shared_memory_holder pMemory) { return m_pRef->get(key, pMemory); }
			template<typename Key> bool remove(const Key& key, shared_memory_holder pMemory) { return m_pRef->remove(key, pMemory); }
			
			node& get(node& key, shared_memory_holder pMemory) const { return static_cast<const node_ref&>(*m_pRef).get(key, pMemory); }
			node& get(node& key, shared_memory_holder pMemory) { return m_pRef->get(key, pMemory); }
			bool remove(node& key, shared_memory_holder pMemory) { return m_pRef->remove(key, pMemory); }

		private:
			shared_node_ref m_pRef;
		};
	}
}

#endif // NODE_DETAIL_NODE_H_62B23520_7C8E_11DE_8A39_0800200C9A66