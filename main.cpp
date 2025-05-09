#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<vector<int>> table;

struct Result {
    int value;
    int parenthesis;
    int left_value;
    int right_value;
};

int operate(int x, int y) {
    return table[x-1][y-1];
}

Result findResult(int matrix_size, int sequence_size, int desired_result, int sequence[], vector<vector<vector<Result>>>& possibilities) {

    for (int diagonal = 0; diagonal < sequence_size; diagonal++) {
        int line = 0;
        for (int column = diagonal; column < sequence_size; line++, column++) {
            vector<Result>& current_cell = possibilities[line][column];
            int current_cell_size = 0;
            // diagonal principal
            if (line == column) {
                Result result;
                result.value = sequence[line];
                result.parenthesis = result.left_value = result.right_value = -1;
                current_cell.push_back(result);
                current_cell_size++;
                if (line == 0 && column == sequence_size-1 && result.value == desired_result) {
                    cout << 1 << endl;
                    return result;
                }
                continue;
            }

            vector<int> values_found(matrix_size, 0);
            for (int i = 1; line <= column-i && current_cell_size < matrix_size; i++) {
                vector<Result>& cell1 = possibilities[line][column-i];
                vector<Result>& cell2 = possibilities[column-i+1][column];
                int cell1_size = cell1.size();
                int cell2_size = cell2.size();

                for (int cell1_poss = 0; cell1_poss < cell1_size && current_cell_size < matrix_size; cell1_poss++) {
                    for (int cell2_poss = 0; cell2_poss < cell2_size && current_cell_size < matrix_size; cell2_poss++) {
                        Result result;
                        int left_value = cell1[cell1_poss].value;
                        int right_value = cell2[cell2_poss].value;
                        result.value = operate(left_value, right_value);

                        if (values_found[result.value-1] == 0) {
                            values_found[result.value-1] = 1;
                            result.parenthesis = column-i;
                            result.left_value = left_value;
                            result.right_value = right_value;
                            current_cell.push_back(result);
                            current_cell_size++;
                        }
                        // se estiver na ultima celula e encontrar o resultado desejado
                        if (line == 0 && column == sequence_size-1 && result.value == desired_result) {
                            cout << 1 << endl;
                            return result;
                        }
                    }
                }
            }
        }
    }
    cout << 0 << endl;
    Result nothing;
    nothing.value = -1;
    return nothing;
}

string findSequence(Result* result, int line, int column, vector<vector<vector<Result>>>& possibilities) {
    if (line == column) {
        return to_string(result->value);
    }
    vector<Result> left_cell = possibilities[line][result->parenthesis];
    vector<Result> right_cell = possibilities[result->parenthesis+1][column];
    Result *left_result = nullptr;
    Result *right_result = nullptr;

    for (int i = 0; i < (int) left_cell.size(); i++) {
        if (left_cell[i].value == result->left_value) {
            left_result = &left_cell[i];
            break;
        }
    }
    for (int i = 0; i < (int) right_cell.size(); i++) {
        if (right_cell[i].value == result->right_value) {
            right_result = &right_cell[i];
            break;
        }
    }

    return "(" + findSequence(left_result, line, result->parenthesis, possibilities) + ' ' +
        findSequence(right_result, result->parenthesis+1, column, possibilities) + ")";

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    auto start = high_resolution_clock::now();

    int matrix_size, sequence_size, desired_result;
    cin >> matrix_size >> sequence_size;

    // Resize the outer vector
    table.resize(matrix_size);

    // Resize each inner vector
    for (int i = 0; i < matrix_size; ++i) {
        table[i].resize(matrix_size);
    }

    int sequence[sequence_size];

    // guardar tabela
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            cin >> table[i][j];
        }
    }

    // guardar sequencia
    for (int i = 0; i < sequence_size; i++) {
        cin >> sequence[i];
    }

    cin >> desired_result;

    // initialize matrix with possibilities
    vector<vector<vector<Result>>> possibilities(sequence_size, vector<vector<Result>>(
        sequence_size, vector<Result>()));


    Result result = findResult(matrix_size, sequence_size, desired_result, sequence, possibilities);
    if (result.value == -1) {
        return 0;
    }

    string output = findSequence(&result, 0, sequence_size-1, possibilities);

    cout << output << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " milliseconds" << endl;
    return 0;
    
}