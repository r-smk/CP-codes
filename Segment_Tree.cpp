class ST{
public:
	vector<int> segTree, lazy;

	ST(int size){
		segTree.resize(4 * size);
		lazy.resize(4 * size);
	}

	void build(int arr[], int si, int ss, int se){
		if(ss == se){
			segTree[si] = arr[ss];
			return;
		}
		int mid = ss + (se - ss) / 2;
		build(arr, 2 * si + 1, ss, mid);
		build(arr, 2 * si + 2, mid + 1, se);
		segTree[si] = segTree[2 * si + 1] + segTree[2 * si + 2];
	}

	int query(int si, int ss, int se, int ql, int qr){
		// Whenever you visit a node 
		// Update the node as it will be fresh and updated
		if(lazy[si] != 0){
			segTree[si] += (se - ss + 1) * lazy[si];
			if(ss != se){
				lazy[2 * si + 1] = lazy[si];
				lazy[2 * si + 2] = lazy[si];
			}
			lazy[si] = 0;	
		}	
		// No overlap
		if(ss > qr or se < ql){
			return 0;
		}
		// Complete Overlap
		if(ql <= ss and qr >= se){
			return segTree[si];
		}
		// No Overlap
		int mid = ss + (se - ss) / 2;
		int left = query(2 * si + 1, ss, mid, ql, qr);
		int right = query(2 * si + 2, mid + 1, se, ql, qr);

		return left + right;
	}

	void rangeUpdate(int si, int ss, int se, int ql, int qr, int val){
		// Whenever you visit a node please update the values lazy values
		if(lazy[si] != 0){
			segTree[si] += (se - ss + 1) * lazy[si];
			if(ss != se){
				lazy[2 * si + 1] = lazy[si];
				lazy[2 * si + 2] = lazy[si];
			}
			lazy[si] = 0;	
		}				
		// No Overlap
		if(se < ql or ss > qr){
			return;
		}
		// Complete Overlap
		// Update the visited nodes, Lazily propagate downwards
		if(ql <= ss and qr >= se){
			segTree[si] += (se - ss + 1) * val;
			// If it is not the leaf
			 // then update their childrens lazily.
			if(se != ss){
				lazy[2 * si + 1] += val;
				lazy[2 * si + 2] += val;
			}
			return;
		}

		// No Overlap
		// Just return the left and right
		int mid = ss + (se - ss) / 2;
		rangeUpdate(2 * si + 1, ss, mid, ql, qr, val);
		rangeUpdate(2 * si + 2, mid + 1, se, ql, qr, val);

		segTree[si] = segTree[2 * si + 1] + segTree[2 * si + 2];
	}

	void update(int si, int ss, int se, int idx, int val){
		// If we reach the node please update it
		if(ss == idx and se == idx){
			segTree[si] = val;
			return;
		}
		int mid = ss + (se - ss) / 2;
		// if the index is in the left then go to left child
		if(idx <= mid){
			update(2 * si + 1, ss, mid, idx, val);
		}
		else{
			update(2 * si + 2, mid + 1, se, idx, val);
		}

		// Updating the current value of the node after updating the childs.
		segTree[si] = segTree[2 * si + 1] + segTree[2 * si + 2];
	}
};
