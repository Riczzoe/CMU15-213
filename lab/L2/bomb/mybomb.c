#include <stdio.h>

void phase_1(string input) {
    string exp = "Border relations with Canada have never been better.";
    int isNotWqual = strings_not_equal(input, exp);

    if (isNotWqual) {
        explode_bomb();
    }
}

int strings_not_equal(string input , string exp) {
    int inputLen = string_length(input);
    int expLen = string_length(exp);

    if (expLen != inputLen) {
        return 1;
    }


}

int main(int argc, char* argv[]) {

    return 0;
}
