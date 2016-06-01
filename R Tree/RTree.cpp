#ifdef SJTU_RTREE_HPP

#ifndef SJTU_RTREE_CPP
#define SJTU_RTREE_CPP

template<class M, class D>
RTreeNode* Find_Leaf(HyperBound<D> &key, RTreeNode *t)
{
	if(t -> level == 0)
	{
		HyperBound<D> *X;
		for(int i = 0; i < t -> size; i++)
		{
			X = static_cast<HyperBound<D>*>(t -> child[i] -> second);
			if(X == &key) 
				return t;
		}
		return NULL;
	}
	else
	{
		HyperBound<D> Y;
		RTreeNode *P;
		for(int i = 0; i < t -> size; i++)
		{
			Y = t -> child[i] -> first;
			if(Y.Inside(key))
			{
				P = static_cast<RTreeNode*>(t -> child[i] -> second);
				RTreeNode *Z;
				Z = Find_Leaf(p, P);
				if(Z != NULL)
				{
					return Z;
				}
			}
		}
	}
}

#endif

#endif
