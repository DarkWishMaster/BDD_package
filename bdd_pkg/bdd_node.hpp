#ifndef BDD_PKG_BDD_NODE_HPP_
#define BDD_PKG_BDD_NODE_HPP_

#include <cstdint>

typedef struct bdd_node_s
{
	uint32_t  		   index;
	struct bdd_node_s* low;
	struct bdd_node_s* high;
} bdd_node;

typedef bdd_node* bdd_node_ptr;

#endif /* BDD_PKG_BDD_NODE_HPP_ */
