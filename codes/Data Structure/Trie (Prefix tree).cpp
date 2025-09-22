struct trie {
    int n = 0;
    trie *a[2];
    trie() {
        a[0] = a[1] = nullptr;
    }
 
    void insert(int k) {
        trie *curr = this;
        for (int i = 63; i >= 0; --i) {
            bool bit = (k & (1LL << i)) > 0;
            if (curr->a[bit] == nullptr) {
                curr->a[bit] = new trie();
            }
            curr = curr->a[bit];
            curr->n++ ;
        }
    }

    void erase(int k) {
        trie *curr = this;
        for (int i = 63; i >= 0; --i) {
            bool bit = (k & (1LL << i)) > 0;
            curr = curr->a[bit];
            curr->n--;
        }
    }
 
    int query(int k) {
        trie *curr = this;
        int x = 0;
        for (int i = 63; i >= 0; --i) {
            x ^= (1LL << i) & k;
            x ^= 1LL << i;
            bool bit = (k & (1LL << i)) == 0;
            if (curr->a[bit] == nullptr || curr->a[bit]->n == 0)
                x ^= 1LL << i, bit ^= 1;
            curr = curr->a[bit];
        }
        return x;
    }
};