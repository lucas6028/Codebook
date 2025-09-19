int add(int i, int j) {
    if ((i += j) >= MOD)
        i -= MOD;
    return i;
}

int sub(int i, int j) {
    if ((i -= j) < 0)
        i += MOD;
    return i;
}