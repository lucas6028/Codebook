bool on_path(int z, int u, int v) {
    return dist(u, z) + dist(z, v) == dist(u, v);
}
 