#include <bdd.hpp>


#include <iostream>

using namespace std;

bdd bdd::bdd_one;
bdd bdd::bdd_zero;
unordered_map<const bdd::table_key, bdd*, bdd::table_hash> bdd::unique_table;

inline uint32_t min(uint32_t a, uint32_t b)
{
	return a < b ? a : b;
}

inline bdd* getFv(uint32_t v, bdd* F)
{
	return (v == F->index)  ? F->high : F;
}

inline bdd* getFn(uint32_t v, bdd* F)
{
	return (v == F->index)  ? F->low : F;
}

bdd* bdd::ite(bdd* f,  bdd* g, bdd* h)
{
	if (f == &bdd::bdd_one)
	{
		return g;
	}
	else if (f == &bdd::bdd_zero)
	{
		return h;
	}
	else
	{
		uint32_t v = min(min(f->index, g->index), h->index);
		bdd* Fv = getFv(v, f);
		bdd* Gv = getFv(v, g);
		bdd* Hv = getFv(v, h);
		bdd* T  = ite(Fv, Gv, Hv);


		bdd* Fn = getFn(v, f);
		bdd* Gn = getFn(v, g);
		bdd* Hn = getFn(v, h);
		bdd* E  = ite(Fn, Gn, Hn);
		if (T == E)
		{
			return T;
		}

		return bdd::find_or_add_unique(v, E, T);
	}


}
