#ifdef SJTU_RTREE_HPP

#ifndef SJTU_RTREE_CPP
#define SJTU_RTREE_CPP

template<class M, class D>
RTreeNode* Find_Leaf(HyperPoint *p, RTreeNode *t)
{
	if(t -> level == 0)
	{
		HyperPoint *X;
		for(int i = 0; i < t -> size; i++)
		{
			X = static_cast<HyperPoint*>(child[i]);
			if(X == p) 
				return t;
		}
		return NULL;
	}
	else
	{
		HyperRectangle Y;
		RTreeNode *P;
		for(int i = 0; i < t -> size; i++)
		{
			Y = t -> box[i];
			if(Y.Inside(p))
			{
				P = static_cast<RTreeNode*>(child[i]);
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
