#ifdef SJTU_RTREE_HPP

#ifndef SJTU_RTREE_CPP
#define SJTU_RTREE_CPP

template<class T, size_t M, size_t D>
RTreeNode* Find_Leaf_Exist(HyperBound<D> &key, RTreeNode *t)
{
	if(!(t -> level))
	{
		pair<HyperBound<D>, T> *X;
		for(int i = 0; i < t -> size; i++)
		{
			X = static_cast< pair<HyperBound<D>, T>* >(t -> child[i]);
			if(X -> first == key) 
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
			P = static_cast<RTreeNode*>(t -> child[i]);
			Y = P -> box;
			if(Y.Inside(key))
			{
				RTreeNode *Z;
				Z = Find_Leaf_Exist(key, P);
				if(Z != NULL)
				{
					return Z;
				}
			}
		}
	}
}

template<class T, size_t M, size_t D>
void CondenseTree(RTreeNode *t, vector<RTreeNode*> &Q)
{
	if(t != root)
	{
		RTreeNode *parent = t -> father;
		int p;
		RTreeNode *Y;
		for(p = 0; p < parent -> size; p++)
		{
			Y = static_cast<RTreeNode*>(parent -> child[p]);
			if(Y == t)
				break;
		}
		if(t -> size < (M >> 1))
		{
			for(int j = p; j < (parent -> size) - 1; j++)
			{
				parent -> child[j] = parent -> child[j + 1];
			}
			--(parent -> size);
			Q.push_back(t);
		}
		else
		{
			Y = static_cast<RTreeNode*>(parent -> child[0]);
			parent -> box = Y -> box;
			for(int i = 1; i < parent -> size; i++)
			{
				Y = static_cast<RTreeNode*>(parent -> child[i]);
				parent -> box = parent -> box + Y -> box;
			}
		}
		CondenseTree(parent, Q);
	} else
	if(t == root && Q.size() > 0)
	{
		int len = Q.size();
		for(int i = 0; i < len; i++)
		{
			if(!(Q[i] -> level))
			{
				pair<HyperBound<D>, T> *X;
				for(int j = 0; j < Q[i] -> size; j++)
				{
					X = static_cast< pair<HyperBound<D>, T>* >(Q[i] -> child[j]);
					insert(X -> first, X -> second);
				}
			}
		}
		for(int i = 0; i < len; i++)
		{
			delete Q[i];
		}
	}
}

template<class T, size_t M, size_t D>
bool remove(const HyperBound<D> &key)
{
	RTreeNode *P;
	P = Find_Leaf_Exist(key, root);
	if(P == NULL)
		return false;
	
	int p;
	pair<HyperBound<D>, T> *X;
	for(p = 0; p < P -> size; p++)
	{
		X = static_cast< pair<HyperBound<D>, T>* >(P -> child[p]);
		if(X -> first == key)
			break;
	}
	
	delete X;
	for(int i = p; i < (P -> size) - 1; i++)
	{
		P -> child[i] = P -> child[i + 1];
	}
	--(P -> size);
	
	vector<RTreeNode*> Q;
	CondenseTree(P, Q);

	if(root -> size == 1)
	{
		RTreeNode *U = root;
		root = static_cast<RTreeNode*>(root -> child[0]);
		delete U;
	}
	
	return true;
		
} 

#endif

#endif
