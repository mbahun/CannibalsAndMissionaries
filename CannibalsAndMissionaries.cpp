#include "CannibalsAndMissionaries.h"
using namespace std;

// If there are some missionaries, their number should be >= to the
// number of cannibals.
bool is_combination_correct(unsigned int missionaries, unsigned int cannibals) {
    return missionaries >= cannibals || !missionaries;
}

// If we are trying combination that led us to current combination, skip it.
bool is_combination_reversed(const Combination& c) {
    return  c.parent->parent &&
        c.parent->parent->cannibals == c.cannibals &&
        c.parent->parent->missionaries == c.missionaries;
}

// Will generate vector with all possible missionaries / cannibals permutations.
// It is ok to return vector by values because of move semantics.
vector<Boat> generate_boat_permutations(unsigned int maxPersonsOnBoat) {
    vector<Boat> result;

    for (unsigned int missionaries = 0; missionaries <= maxPersonsOnBoat; missionaries++) {
        for (unsigned int cannibals = 0; cannibals <= maxPersonsOnBoat; cannibals++) {
            if (missionaries + cannibals <= maxPersonsOnBoat &&
                is_combination_correct(missionaries, cannibals) &&
                missionaries + cannibals) {

                result.push_back(Boat(cannibals, missionaries));
            }
        }
    }

    return result;
}

// Result should be reversed but it works both ways so I'm skipping it. :)
// Returns true to exit, false to find next solution.
bool printResult(const Combination& resultCombination) {
    Combination const* c = &resultCombination;
    unsigned int maxc = c->cannibals, maxm = c->missionaries;

    cout << "Result: (C = cannibal, M = missionary, * = boat)" << endl;
    while (c) {
        cout << " Source: " << c->cannibals << "C:" << c->missionaries << "M*";
        cout << " Destination " << maxc - c->cannibals << "C:" << maxm - c->missionaries << "M" << endl;
        // 'c->parent' will allways work as there is at least one combination after init. state.
        c = c->parent;
        cout << " Source: " << maxc - c->cannibals << "C:" << maxm - c->missionaries << "M";
        cout << " Destination " << c->cannibals << "C:" << c->missionaries << "M*" << endl;
        c = c->parent;
    }
    cout << endl;
    return true;
}

// Deallocate memory before exiting. 
void deleteAll(list<Level*> levels) {
    list<Level*>::const_iterator i;

    for (i = levels.cbegin(); i != levels.cend(); i++) {
        (*i)->combinations.remove_if([](Combination* c) {delete c; return true; });
    }
    levels.remove_if([](Level* l) {delete l; return true; });
}

// Main
int main() {
    // Input variables
    unsigned int missioanriesCount = 3;
    unsigned int cannibalsCount = 3;
    unsigned int boatCapacity = 3;

    // List that holds levels and vector with all possible permutations of on boat persons
    list<Level*>levels;
    vector<Boat> boatPermutations = generate_boat_permutations(boatCapacity);

    // Will allocate new level / commbination and push it to lists
    Level* newLevel;
    Combination* newCombination;
    int c = 0, m = 0;

    // Iterators
    list<Combination*>::const_iterator itr_combination;
    list<Level*>::const_iterator itr_level;

    // Init: Create zero level and starting combination
    newLevel = new Level(0);
    newLevel->combinations.push_back(new Combination(cannibalsCount, missioanriesCount, 0));
    levels.push_back(newLevel);
    itr_level = levels.cbegin();

    do {
        levels.push_back(new Level((*itr_level)->level + 1));
        itr_combination = (*itr_level)->combinations.cbegin();

        // If no combination possible or stupid way to assume result is not found, end execution
        if (itr_combination == (*itr_level)->combinations.cend() || levels.size() == 150) {
            cout << "To many levels (" << levels.size() <<
                ") reached or no combination found, probably not solvable..." << endl;
            deleteAll(levels);
            return 0;
        }

        do {
            for (unsigned int i = 0; i < boatPermutations.size(); i++) {
                c = (*itr_combination)->cannibals - boatPermutations[i].cannibals;
                m = (*itr_combination)->missionaries - boatPermutations[i].missionaries;

                if (c < 0 || m < 0)
                    continue;

                newCombination = nullptr;
                Combination tmpCombination(cannibalsCount - c, missioanriesCount - m, *itr_combination);

                // Add new combination only if checks are ok...
                if (is_combination_correct(m, c) &&
                    is_combination_correct(tmpCombination.missionaries, tmpCombination.cannibals) &&
                    !is_combination_reversed(tmpCombination)) {

                    // Check if combination already exist... 
                    auto exists = find_if(
                        levels.back()->combinations.begin(), levels.back()->combinations.end(),
                        [&tmpCombination](Combination* c) {
                            return c->cannibals == tmpCombination.cannibals &&
                                c->missionaries == tmpCombination.missionaries;
                        }
                    );

                    // ... and add it only if it doesn't. 
                    if (exists == levels.back()->combinations.end()) {
                        newCombination = new Combination(tmpCombination);
                        levels.back()->combinations.push_back(newCombination);
                    }
                }

                // Check if result is reached - everybody on destination bank (destination is on odd levels).
                if (newCombination && newCombination->cannibals == cannibalsCount &&
                    newCombination->missionaries == missioanriesCount &&
                    ((*itr_level)->level + 1) % 2) {

                    if (printResult(*newCombination)) {
                        deleteAll(levels);
                        return 0;
                    }
                }
            }

        } while (++itr_combination != (*itr_level)->combinations.cend());
    } while (++itr_level != levels.cend());
}

