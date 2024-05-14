#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <string.h>
using namespace std;

list<list<string>> swap_recursive(list<string> input) {
    list<list<string>> all_combos;
    list<list<string>> new_combos;
    list<string> tmp = input;
    list<string> tmp2;
    string save_last;

    if (input.size() == 1) {
        all_combos.push_back(tmp);
        return (all_combos);
    }
    if (input.size() == 2) {
        all_combos.push_back(tmp);
        tmp2.push_back(input.back());
        tmp2.push_back(input.front());
        all_combos.push_back(tmp2);
        return (all_combos);
    }
    for (size_t i = 0; i < input.size(); i++) {
        tmp2 = tmp;
        tmp2.erase(tmp2.begin());
        new_combos = swap_recursive(tmp2);
        for (list<list<string>>::iterator comb = new_combos.begin(); comb != new_combos.end(); comb++) {
            comb->insert(comb->begin(), tmp.front());
        }
        all_combos.insert(all_combos.end(), new_combos.begin(), new_combos.end());
        save_last = tmp.back();
        tmp.pop_back();
        tmp.insert(tmp.begin(), save_last);
    }
    return (all_combos);
}

list<string> parse_word(int argc, const char **argv) {
    char *default_sep = (char *)" ";
    list<string> word_list;

    if (argc > 3 || argc <= 1) {
        cerr << "Invalid arg count.";
        return ((list<string>){});
    }
    if (argc == 3)
        default_sep = (char *)argv[2];
    for (char *tok = strtok((char *)argv[1], default_sep); tok != NULL; tok = strtok(NULL, default_sep))
        word_list.push_back(string(tok));
    return (word_list);
}

int main(int argc, const char **argv) {
    list<string> parsed_array = parse_word(argc, argv);
    list<list<string>> all_combos;
    const char *default_sep = ((argc == 3) ? argv[2] : (char *)" ");

    if (parsed_array.size() == 0)
        return (1);
    all_combos = swap_recursive(parsed_array);
    for (list<list<string>>::iterator i = all_combos.begin(); i != all_combos.end(); i++) {
        for (list<string>::iterator j = i->begin(); j != i->end(); j++) {
            cout << *j->data();
            cout << ((j == --i->end()) ? "" : default_sep);
        }
        cout << "\n"; 
    }
    return (0);
}