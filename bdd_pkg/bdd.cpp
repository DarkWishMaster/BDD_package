#include <bdd.hpp>


#include <iostream>

using namespace std;

bdd bdd::bdd_one;
bdd bdd::bdd_zero;
hash_table bdd::unique_table;



inline uint32_t min(uint32_t a, uint32_t b)
{
	return a < b ? a : b;
}

inline bdd_node_ptr getFv(uint32_t v, bdd_node_ptr F)
{
	return (v == F->index)  ? F->high : F;
}

inline bdd_node_ptr getFn(uint32_t v, bdd_node_ptr F)
{
	return (v == F->index)  ? F->low : F;
}

bdd bdd::ite(bdd f,  bdd g, bdd h)
{
	bdd result;
	result.root = ite(f.root, g.root, h.root);
	return result;
}

bdd_node_ptr bdd::ite(bdd_node_ptr f, bdd_node_ptr g, bdd_node_ptr h)
{
	if (f == bdd::bdd_one.root)
	{
		return g;
	}
	else if (f == bdd::bdd_zero.root)
	{
		return h;
	}
	else
	{
		uint32_t v = min(min(f->index, g->index), h->index);
		bdd_node_ptr Fv = getFv(v, f);
		bdd_node_ptr Gv = getFv(v, g);
		bdd_node_ptr Hv = getFv(v, h);
		bdd_node_ptr T  = ite(Fv, Gv, Hv);


		bdd_node_ptr Fn = getFn(v, f);
		bdd_node_ptr Gn = getFn(v, g);
		bdd_node_ptr Hn = getFn(v, h);
		bdd_node_ptr E  = ite(Fn, Gn, Hn);
		if (T == E)
		{
			return T;
		}

		return bdd::unique_table.find_or_add_unique(v, E, T);
	}


}

bdd bdd::bdd_not(bdd f)
{
	return ite(f, bdd::bdd_zero, bdd::bdd_one);
}

bdd bdd::bdd_and(bdd f, bdd g)
{
	return ite(f, g, bdd::bdd_zero);
}

bdd bdd::bdd_or(bdd f, bdd g)
{
	return ite(f, bdd::bdd_one, g);
}
