// O(3^n)

int m = 0b10110; // binary: 10110, decimal: 22

cout << "Mask: " << bitset<5>(m) << " (" << m << ")\\n";

// Enumerate all submasks
for (int s = m; s; s = (s - 1) & m) {
    cout << bitset<5>(s) << " (" << s << ")\\n";
}

// Optionally include the empty submask
cout << bitset<5>(0) << " (0)\\n";