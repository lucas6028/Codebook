CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wshadow \\
            -g -fsanitize=address,undefined -D LOCAL

MAKE_FLAG := --no-print-directory

# Rule: make A → compile A.cpp into A.out, run on all *.in files, then delete it
%: EXE = $@.out
%:
    @make $(MAKE_FLAG) $(EXE)
    @for f in *.in; do \\
        echo ">>> Running on $$f"; \\
        ./$(EXE) < $$f; \\
    done
    @rm -f $(EXE)

# Compile rule: A.cpp → A.out
%.out: %.cpp
    ++ $(CXXFLAGS) -o $@ $<

# Create input file if missing
%.in:
    vim $@