/*
 * NAME: Sprague-Grundy Theorem / Nim Theory
 * USE WHEN: an impartial combinatorial game (both players have the same
 *           moves available from any position) asks who wins with optimal
 *           play, or the game decomposes into independent sub-games
 *           (then XOR their Grundy numbers — that's the whole point).
 * KEY FACTS (memorize — this is the part people blank on live):
 *   - A position is LOSING (P-position, previous player wins) iff its
 *     Grundy number is 0.
 *   - Grundy(position) = mex{ Grundy(next position) : all legal moves }
 *     where mex = smallest non-negative integer NOT in that set.
 *   - For several independent games played as one combined game, the
 *     combined Grundy number = XOR of each game's individual Grundy
 *     number. Combined position is losing iff that XOR is 0.
 *   - Plain Nim (piles of stones, remove any positive amount from one
 *     pile) has Grundy(pile of size n) = n, so the whole game's Grundy
 *     = XOR of pile sizes — you often don't need memoized recursion at all.
 * COMPLEXITY: O(states * avg transitions) for memoized mex, O(1) for plain Nim
 * GOTCHAS:
 *   - Misere Nim (last player to move LOSES instead of wins) flips the
 *     answer only when ALL piles have size <= 1 — don't blanket-flip
 *     the normal-play result.
 *   - mex is over the SET of reachable Grundy values — dedupe first,
 *     or a naive scan over a vector with duplicates still works but
 *     wastes time.
 */
#include <bits/stdc++.h>
using namespace std;

int mex(vector<int>& reachable){
    int cap = reachable.size();
    vector<bool> seen(cap + 1, false);
    for (int x : reachable) if (x <= cap) seen[x] = true;
    int m = 0;
    while (m <= cap && seen[m]) m++;
    return m;
}

// Generic template: adapt getMoves() to your game's state representation.
unordered_map<int,int> memo;
int grundy(int state, vector<int>(*getMoves)(int)){
    auto it = memo.find(state);
    if (it != memo.end()) return it->second;
    vector<int> vals;
    for (int nxt : getMoves(state)) vals.push_back(grundy(nxt, getMoves));
    return memo[state] = mex(vals);
}

/*
 * USAGE EXAMPLE 1 (plain multi-pile Nim, no recursion needed):
 * int piles[] = {3, 4, 5};
 * int nimXor = 0;
 * for (int p : piles) nimXor ^= p;
 * bool firstPlayerWins = (nimXor != 0);
 *
 * USAGE EXAMPLE 2 (custom game state, memoized):
 * vector<int> movesFromState(int s) { ... return list of reachable states ...; }
 * int g = grundy(startState, movesFromState);
 * bool firstPlayerWins = (g != 0);
 *
 * USAGE EXAMPLE 3 (several independent sub-games combined):
 * int total = 0;
 * for (auto& subgame : subgames) total ^= grundy(subgame.start, subgame.moves);
 * bool firstPlayerWins = (total != 0);
 */
