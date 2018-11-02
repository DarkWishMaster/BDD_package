#ifndef BDD_PKG_BDD_NODE_HPP_
#define BDD_PKG_BDD_NODE_HPP_

#include <cstdint>

/* Represent a node of BDD with associated
 * variable index and pointers to it's low and high BDDs
 * (v, LO, HI)
 */
typedef struct bdd_node_s
{
	uint32_t  		   index;
	struct bdd_node_s* low;
	struct bdd_node_s* high;
} bdd_node;

#endif /* BDD_PKG_BDD_NODE_HPP_ */
