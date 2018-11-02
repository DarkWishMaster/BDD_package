#include <bdd.hpp>


#include <iostream>

using namespace std;

bdd bdd::bdd_one;
bdd bdd::bdd_zero;
hash_table bdd::unique_table;


bdd::bdd()
{
	this->root = nullptr;
}

/* Simple node creation for a variable with children to 0 and 1 */
bdd::bdd(uint32_t index)
{
	this->root = unique_table.find_or_add_unique(index, bdd_zero.root, bdd_one.root);
}

bdd_node* bdd::get_root()
{
	return this->root;
}

uint32_t bdd::get_index()
{
	return this->root->index;
}

bdd bdd::get_low()
{
	bdd b;
	b.root = this->root->low;
	return b;
}

bdd bdd::get_high()
{
	bdd b;
	b.root = this->root->high;
	return b;
}

bool bdd::empty()
{
	return this->root == nullptr;
}

void bdd::bdd_init(unsigned int num_var)
{
	bdd_zero.root = unique_table.find_or_add_unique(num_var,     nullptr, nullptr);
	bdd_one.root  = unique_table.find_or_add_unique(num_var + 1, nullptr, nullptr);
}

void bdd::bdd_exit()
{
	unique_table.clear();
	bdd_zero.root = nullptr;
	bdd_one.root  = nullptr;
}

static inline uint32_t min(uint32_t a, uint32_t b)
{
	return a < b ? a : b;
}

/* Returns the positive subfunction F(..., xv = 1, xv+1, xv+2 ...)
 * Note that in case v is the top variable of F,
 * then the positive subfunction is returned.
 * Otherwise that means that v > top variable of F,
 * so F doesn't depend on v => F is returned.
 */
static inline bdd_node* getFv(uint32_t v, bdd_node* F)
{
	return (v == F->index)  ? F->high : F;
}

/* Returns the negative subfunction F(..., xv = 0, xv+1, xv+2 ...) */
static inline bdd_node* getFn(uint32_t v, bdd_node* F)
{
	return (v == F->index)  ? F->low : F;
}

/* If-Then-Else operator implementation
 * ite(F, G, H) = ite(v, ite(Fv, Gv, Hv), ite(Fn, Gn, Hn))
 * where v = top variable for F, G, and V (variable with the lowest index),
 * and n = not(v).
 */
bdd bdd::ite(bdd f,  bdd g, bdd h)
{
	bdd result;
	result.root = ite(f.root, g.root, h.root);
	return result;
}

bdd_node* bdd::ite(bdd_node* f, bdd_node* g, bdd_node* h)
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
		bdd_node* Fv = getFv(v, f);
		bdd_node* Gv = getFv(v, g);
		bdd_node* Hv = getFv(v, h);
		bdd_node* T  = ite(Fv, Gv, Hv);


		bdd_node* Fn = getFn(v, f);
		bdd_node* Gn = getFn(v, g);
		bdd_node* Hn = getFn(v, h);
		bdd_node* E  = ite(Fn, Gn, Hn);


		if (T == E)
		{
			/* nodes with equal children are discarded
			 * since the it's value doesn't matter, it always
			 * will go to the same children if xv=0 or xv = 1;
			 */
			return T;
		}

		/* Don't create duplicate nodes if they already exists
		 * (keeps bdd reduced and saves space)
		 */
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


inline bool operator==(const bdd& f, const bdd& g)
{
	return (f.root == g.root);
}

bdd& bdd::operator=(const bdd& g)
{
	this->root = g.root;
	return *this;
}


static void print_dfs(string path, bdd_node* r, unordered_set<bdd_node*>& visited)
{
	bool is_visited = false;
	if (visited.find(r) != visited.end())
	{
		is_visited = true;
	}
	else
	{
		visited.insert(r);
	}

	if (r != nullptr && !is_visited)
	{
		cout << std::setw(8) << path << " " << r << " " << r->index << " " << r->low << " " << r->high << endl;
		print_dfs(path + "L", r->low,  visited);
		print_dfs(path + "H", r->high, visited);
	}
}

void bdd::print()
{
	unordered_set<bdd_node*> visited;
	print_dfs("", this->root, visited);
}




