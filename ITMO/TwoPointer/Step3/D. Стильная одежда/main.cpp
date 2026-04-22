#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Item {
    int color;
    int type;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> clothes(4);
    for (int i = 0; i < 4; ++i) {
        int n;
        cin >> n;
        clothes[i].resize(n);
        for (int j = 0; j < n; ++j) {
            cin >> clothes[i][j];
        }
    }

    vector<Item> all;
    all.reserve(400000); // максимум 4*100000
    for (int type = 0; type < 4; ++type) {
        for (int val : clothes[type]) {
            all.push_back({val, type});
        }
    }

    sort(all.begin(), all.end(), [](const Item& a, const Item& b) {
        return a.color < b.color;
    });

    vector<int> count(4, 0);
    int types_covered = 0;
    int left = 0;
    int best_diff = INT_MAX;
    int best_left = 0, best_right = -1;

    for (int right = 0; right < (int)all.size(); ++right) {
        if (count[all[right].type] == 0) {
            types_covered++;
        }
        count[all[right].type]++;

        while (types_covered == 4) {
            int current_diff = all[right].color - all[left].color;
            if (current_diff < best_diff) {
                best_diff = current_diff;
                best_left = left;
                best_right = right;
            }

            // shrink left
            count[all[left].type]--;
            if (count[all[left].type] == 0) {
                types_covered--;
            }
            left++;
        }
    }

    // Восстанавливаем ответ из [best_left, best_right]
    vector<int> result(4, -1);
    for (int i = best_left; i <= best_right; ++i) {
        if (result[all[i].type] == -1) {
            result[all[i].type] = all[i].color;
        }
    }

    cout << result[0] << " "
         << result[1] << " "
         << result[2] << " "
         << result[3] << "\n";

    return 0;
}