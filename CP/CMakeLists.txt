cmake_minimum_required(VERSION 3.31)
project(CP)

set(CMAKE_CXX_STANDARD 20)

add_executable(CP Clean/geo.cpp
        "Data Structure/DSU.cpp"
        "Geometry/Polar Angle.cpp"
        "Geometry/Angle Between Vectors.cpp"
        "Geometry/Area of Polygon.cpp"
        "Geometry/Area of Triangle.cpp"
        Geometry/bisector.cpp
        "Geometry/Dist from point to line.cpp"
        "Geometry/Dist from point to seg.cpp"
        "Geometry/Dist Between 2 Segment.cpp"
        "Geometry/Intersec Between 2 line.cpp"
        "Geometry/vector length.cpp"
        "Geometry/Equation Line passing through 2 points.cpp"
        "Geometry/Equation Line by point and vector.cpp"
        "Geometry/Is the point on line.cpp"
        "Geometry/Is the point on ray.cpp"
        "Geometry/Is point on segment.cpp"
        "Geometry/Is 2 points on same side of line.cpp"
        "Geometry/Distance between rays.cpp"
        Graph/Bridges.cpp
        Graph/articulation_points.cpp
        Tree/diameter.cpp
        Graph/SCC_Kosaraju.cpp
        Graph/SCC_Tarjan's.cpp
        Tree/lca.cpp
        Graph/BCC.cpp
        "Geometry/Location of Point in line.cpp"
        "Geometry/Is 2 Segment Intersect.cpp"
        Geometry/Point_Location_Relative_to_Polygon.
        "Geometry/Lattice Points.cpp"
        "Geometry/Polar Sort.cpp"
        "Geometry/winding Number.cpp"
        "Geometry/WindingNumber for Integers.cpp"
        "Geometry/type of intersection between Circle and Line.cpp"
        "Geometry/struct line.cpp"
        "Data Structure/Sparse_Table.cpp"
        Math/MatrixExpo.cpp
        Math/Fast_Power.cpp
        "Number Theory/linearSieve.cpp"
        Combinatorics/nCr.cpp
        Combinatorics/stars_and_bars.cpp
        "Number Theory/is_prime.cpp"
        "Data Structure/Monotonic Stack.cpp"
        "Data Structure/Order Set.cpp"
        Strings/KMP.cpp
        Strings/compute_automaton.cpp
        Strings/Trie01.cpp
        Strings/Trie.cpp
        Random/random_range.cpp
        "Data Structure/Segment Tree.cpp"
        "Data Structure/Lazy Segment Tree.cpp"
        Strings/Hashing.cpp
        "Strings/Hashing2D.cpp"
        main.cpp
        "Data Structure/coordinate compression.cpp"
        "Data Structure/Dynamic Segment Tree.cpp"
        "Number Theory/Miller-Rabin.cpp"
        Graph/Floyed.cpp
        "Data Structure/Monotonic Queue.cpp"
        "Data Structure/sqrt.cpp"
        "Data Structure/Sparse Segment Tree.cpp"
        "Data Structure/MO.cpp"
        "Geometry/Center Circle Pass 3 points.cpp"
        "Number Theory/PrimeFactorization.cpp"
        "Geometry/Intersection between two segments.cpp"
        Strings/Suffux_Array.cpp
        Strings/SuffixArrayWithSparseTable.cpp
        Math/bezout'sIdentity.cpp
        Strings/SuffixArrayWithVectorInt.cpp
        Tree/eular_tour.cpp
        "Number Theory/Euler's_totient.cpp"
        "Geometry/Intersection between circle and line.cpp"
        "Geometry/intersection between 2 Circle.cpp"
        "Graph/small to large.cpp"
        "Data Structure/Max Sum in Subarray With update.cpp"
        "Data Structure/Segtree Tree Iterative.cpp"
        "Data Structure/Merge sort tree.cpp"
        Clean/clean.cpp
        "Geometry/Check if polygon is rectangle and Square.cpp"
        "Data Structure/DSU with array sz.cpp"
        "Data Structure/4D prefix sum.cpp"
        "fast/dp bitset.cpp"
        stress.cpp
        "Number Theory/divisors.cpp"
        "Strings/KMP for integer.cpp"
        "Tree/LCA with Sparse Tables.cpp"
        Geometry/MEC.cpp
        "Tree/Max Query by LCA.cpp"
        "Data Structure/Merge Sort Tree With update.cpp"
        "Geometry/Finding common tangents to two circles.cpp"
        "Geometry/Length of the union of segments.cpp"
        "Geometry/Minkowski sum of convex polygons.cpp"
        "Geometry/Distance between 2 polygons.cpp"
        "Geometry/Intersection between line and segment.cpp"
        "Math/XOR Basis.cpp"
        Graph/Bellman-Ford.cpp
        "Data Structure/Segment Tree Beats.cpp"
        "Data Structure/Treap persistent.cpp"
        "Data Structure/Persistent Trie.cpp"
        "Data Structure/Palindromic Tree Persistent.cpp"
        "Math/NTT.cpp"
        "DP Optimization/Convex Hull Trick.cpp"
        "Number Theory/Pollard Rho.cpp"
        "Graph/Dinics Algorithm.cpp"
        "Graph/Hungarian Algorithm.cpp"
)
