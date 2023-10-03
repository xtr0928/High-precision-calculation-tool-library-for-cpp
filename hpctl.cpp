#include<stdio.h>
#include<string>
#include<iostream>
#include<vector>
#include <numeric>
#include<math.h>
#include<cmath>
using namespace std;
struct number {
    vector<short> data;
    uint64_t size = 0;
    //size means Integer data of bits
    int pom = 0;
    //pom means plus or minus
};
inline number number_get() {
    number number;
    number.size = 0;
    char ch = getchar();
    if (ch == '-') {
        number.pom = -1;
        ch = getchar();
    }
    else if (ch >= '0' && ch <= '9') {
        number.pom = 1;
        number.data.push_back(ch - '0');
        ch = getchar();
        if (ch == '.') {
            number.size = 1;
            ch = getchar();
        }
    }
    while (ch >= '0' && ch <= '9') {
        number.data.push_back(ch - '0');
        ch = getchar();
        if (ch == '.') {
            number.size = number.data.size();
            ch = getchar();
        }
    }
    if (number.size == 0) {
        number.size = number.data.size();
    }
    return number;
}
inline long long  i_read() {
    long long s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch>'9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}
inline long double f_read() {
    long double s = 0, w = 1;
    char ch = getchar();
    if (ch == '-') {
        w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = s * 10.0 + ch - '0';
        ch = getchar();
    }
    if (ch == '.') {
        ch = getchar();
        long double f = 0;
        long long i = 0;
        while (ch >= '0' && ch <= '9') {
            f = f * 10.0 + ch - '0';
            i++;
            ch = getchar();
        }
        for (int j = 0; j < i; j++) {
            f /= 10.0;
        }
        s += f;
    }
    return w * s;
}
inline number str_to_number(string str) {
    number finally_number;
    bool flag = true;
    if (str.size() == 0) {
        printf("error:this str is empty");
    }
    if (str[0] == '-') {
        finally_number.pom = -1;
        if (str[1] <= '9' && str[1] >= '0') {
            finally_number.data.push_back(str[1] - '0');
        }
        else {
            printf("error:there have non-numeric character");
        }
        for (uint64_t x = 2; x < str.size(); x++) {
            if (str[x] <= '9' && str[x] >= '0') {
                finally_number.data.push_back(str[x] - '0');
            }
            else {
                if (str[x] == '.') {
                    finally_number.size = x - 1;
                    flag = false;
                }
                else {
                    printf("error:there have non-numeric character");
                }
            }
        }
    }
    else {
        if (str[0] <= '9' && str[0] >= '0') {
            finally_number.data.push_back(str[0] - '0');
        }
        else {
            printf("error:there have non-numeric character");
        }
        for (uint64_t x = 1; x < str.size(); x++) {
            if (str[x] <= '9' && str[x] >= '0') {
                finally_number.data.push_back(str[x] - '0');
            }
            else {
                if (str[x] == '.') {
                    finally_number.size = x;
                    flag = false;
                }
                else {
                    printf("error:there have non-numeric character");
                }
            }
        }
    }
    if (flag) {
        finally_number.size = finally_number.data.size();
    }
    return finally_number;
}
inline void  number_out_wt(number outnumber) {
    uint64_t  size = outnumber.size - 1;
    bool flag = false;
    if (outnumber.pom == -1) {
        printf("-");
    }
    for (uint64_t x = 0; x < outnumber.data.size(); x++) {
        printf("%d", outnumber.data[x]);
        if (!flag) {
            if (size) {
                size -= 1;
            }
            else if (x != outnumber.data.size() - 1) {
                printf(".");
                flag = true;
            }
        }
    }
}
inline number accurate_to(number number, uint64_t i) {
    if (number.data.size() - number.size <= i) {
        uint64_t nop = i - (number.data.size() - number.size);
        //the number of operations
        for (int x = 0; x < nop; x++) {
            number.data.push_back(0);
        }
    }
    else {
        if (number.data[number.size + i] >= 5) {
            number.data[number.size + i - 1] += 1;
            for (uint64_t x = number.size + i - 1; x > 0; x--) {
                if (number.data[x] > 9) {
                    number.data[x] %= 10;
                    number.data[x - 1] ++;
                }
                else {
                    break;
                }
                if (x == 0)break;
            }
        }
        number.data.erase(number.data.begin() + number.size + i - 1, number.data.end());
        for (uint64_t x = number.size + i - 2; x > 0; x--) {
            if (number.data[x] == 0) {
                number.data.pop_back();
            }
            else {
                break;
            }
        }
    }
    while (number.data.size() < number.size) {
        number.data.push_back(0);
    }
    return number;
}
inline void  number_test_out(number outnumber) {
    for (uint64_t x = 0; x < outnumber.data.size(); x++) {
        printf("%d", outnumber.data[x]);
        cout << " ";
    }
}
inline void print(number original_number, uint64_t i) {
    number print_number = accurate_to(original_number, i);
    number_out_wt(print_number);
}
inline void print(number original_number) {
    number print_number = accurate_to(original_number, 30);
    number_out_wt(print_number);
}
inline number add(number number1, number number2) {
    number finally_number;
    if (number1.pom == number2.pom) {
        finally_number.pom = number1.pom;
        uint64_t linob = 0, sinob = 0, ldp = 0, sdp = 0, typei = 0, typed = 0;
        //Please forgive my poor English and machine translation
        //lonob:Large integer data of bits
        //sinob:Small integer data of bits
        //ldp:Large decimal places
        //sdp:Small decimal places
        //typei:The type of size case of the integer part
        //typed:The type size of the fractional part
        uint64_t size1 = number1.data.size(), size2 = number2.data.size();
        uint64_t size1_1 = size1 - 1, size2_1 = size2 - 1;
        if (number1.size > number2.size) {
            linob = number1.size;
            sinob = number2.size;
        }
        else {
            linob = number2.size;
            sinob = number1.size;
            typei = 1;
        }
        if (size1 - number1.size > size2 - number2.size) {
            ldp = size1 - number1.size;
            sdp = size2 - number2.size;
        }
        else {
            ldp = size2 - number2.size;
            sdp = size1 - number1.size;
            typed = 1;
        }
        uint64_t  sizef_1 = linob + ldp, sizef_2 = sizef_1 - 1;
        for (uint64_t x = 0; x <= linob + ldp; x++) {
            finally_number.data.push_back(0);
        }
        uint64_t ldp_sdp = ldp - sdp, sinob_sdp = sinob + sdp, linob_sinob = linob - sinob, sinob_ldp = sinob + ldp;
        if (!typei && typed) {
            for (uint64_t x = 0; x < ldp_sdp; x++) {
                finally_number.data[sizef_1 - x] = number2.data[size2_1 - x];
            }
            for (uint64_t x = 0; x < sinob_sdp; x++) {
                finally_number.data[sizef_1 - x - ldp_sdp] += (number1.data[size1_1 - x] + number2.data[size2_1 - x - ldp_sdp]);
                finally_number.data[sizef_2 - x - ldp_sdp] = finally_number.data[sizef_1 - x - ldp_sdp] / 10;
                finally_number.data[sizef_1 - x - ldp_sdp] %= 10;
            }
            for (uint64_t x = 0; x < linob_sinob; x++) {
                finally_number.data[sizef_1 - sinob_ldp - x] += number1.data[size1_1 - sinob_sdp - x];
                finally_number.data[sizef_2 - sinob_ldp - x] = finally_number.data[sizef_1 - sinob_ldp - x] / 10;
                finally_number.data[sizef_1 - sinob_ldp - x] %= 10;
            }
        }
        if (typei && !typed) {
            for (uint64_t x = 0; x < ldp_sdp; x++) {
                finally_number.data[sizef_1 - x] = number1.data[size1_1 - x];
            }
            for (uint64_t x = 0; x < sinob_sdp; x++) {
                finally_number.data[sizef_1 - x - ldp_sdp] += (number1.data[size1_1 - x - ldp_sdp] + number2.data[size2_1 - x]);
                finally_number.data[sizef_2 - x - ldp_sdp] = finally_number.data[sizef_1 - x - ldp_sdp] / 10;
                finally_number.data[sizef_1 - x - ldp_sdp] %= 10;
            }
            for (uint64_t x = 0; x < linob_sinob; x++) {
                finally_number.data[sizef_1 - sinob_ldp - x] += number2.data[size2_1 - sinob_sdp - x];
                finally_number.data[sizef_2 - sinob_ldp - x] = finally_number.data[sizef_1 - sinob_ldp - x] / 10;
                finally_number.data[sizef_1 - sinob_ldp - x] %= 10;
            }
        }
        if (typei && typed) {
            for (uint64_t x = 0; x < ldp_sdp; x++) {
                finally_number.data[sizef_1 - x] = number2.data[size2_1 - x];
            }
            for (uint64_t x = 0; x < sinob_sdp; x++) {
                finally_number.data[sizef_1 - x - ldp_sdp] += (number1.data[size1_1 - x] + number2.data[size2_1 - x - ldp_sdp]);
                finally_number.data[sizef_2 - x - ldp_sdp] = finally_number.data[sizef_1 - x - ldp_sdp] / 10;
                finally_number.data[sizef_1 - x - ldp_sdp] %= 10;
            }
            for (uint64_t x = 0; x < linob_sinob; x++) {
                finally_number.data[sizef_1 - sinob_ldp - x] += number2.data[size2_1 - sinob_ldp - x];
                finally_number.data[sizef_2 - sinob_ldp - x] = finally_number.data[sizef_1 - sinob_ldp - x] / 10;
                finally_number.data[sizef_1 - sinob_ldp - x] %= 10;
            }
        }
        if (!typei && !typed) {
            for (uint64_t x = 0; x < ldp_sdp; x++) {
                finally_number.data[sizef_1 - x] = number1.data[size1_1 - x];
            }
            for (uint64_t x = 0; x < sinob_sdp; x++) {
                finally_number.data[sizef_1 - x - ldp_sdp] += (number1.data[size1_1 - x - ldp_sdp] + number2.data[size2_1 - x]);
                finally_number.data[sizef_2 - x - ldp_sdp] = finally_number.data[sizef_1 - x - ldp_sdp] / 10;
                finally_number.data[sizef_1 - x - ldp_sdp] %= 10;
            }
            for (uint64_t x = 0; x < linob_sinob; x++) {
                finally_number.data[sizef_1 - sinob_ldp - x] += number1.data[size1_1 - sinob_ldp - x];
                finally_number.data[sizef_2 - sinob_ldp - x] = finally_number.data[sizef_1 - sinob_ldp - x] / 10;
                finally_number.data[sizef_1 - sinob_ldp - x] %= 10;
            }
        }
        if (finally_number.data[0] == 0) {
            finally_number.data.erase(finally_number.data.begin());
            finally_number.size = linob;
        }
        else {
            finally_number.size = linob + 1;
        }
    }
    else {
        int type = 0;
        uint64_t size1 = number1.data.size(), size2 = number2.data.size();
        number numbers, numberb;
        if (number1.size > number2.size) {
            finally_number.pom = number1.pom;
            numberb = number1;
            numbers = number2;
        }
        else if (number1.size < number2.size) {
            finally_number.pom = number2.pom;
            numbers = number1;
            numberb = number2;
        }
        else {
            uint64_t  minsize = min(size1, size2);
            int flag = 0;
            for (int x = 0; x < minsize; x++) {
                if (number1.data[x] > number2.data[x]) {
                    flag = 1;
                    numberb = number1;
                    numbers = number2;
                    break;
                }
                else if (number1.data[x] < number2.data[x]) {
                    flag = 2;
                    numbers = number1;
                    numberb = number2;
                    break;
                }
            }
            if (flag == 0) {
                if (size1 > size2) {
                    numberb = number1;
                    numbers = number2;
                }
                else if (size2 > size1) {
                    numbers = number1;
                    numberb = number2;
                }
                else {
                    finally_number.data.push_back(0);
                    finally_number.pom = 1;
                }
            }
        }
        uint64_t sizeb = numberb.data.size(), sizes = numbers.data.size();
        uint64_t sizeb_1 = sizeb - 1, sizes_1 = sizes - 1, sizeb_2 = sizeb - 2;
        uint64_t ldp = 0, sdp = 0, ldp_sdp = 0;
        if (sizeb - numberb.size >= sizes - numbers.size) {
            sdp = sizes - numbers.size;
            ldp = sizeb - numberb.size;
            ldp_sdp = ldp - sdp;
            for (uint64_t x = 0; x < sizeb; x++) {
                finally_number.data.push_back(0);
            }
            for (uint64_t x = 0; x < ldp_sdp; x++) {
                finally_number.data[finally_number.data.size() - 1 - x] = numberb.data[sizeb_1 - x];
            }
            for (uint64_t x = 0; x < sizes; x++) {
                if (numberb.data[sizeb_1 - ldp_sdp - x] < numbers.data[sizes_1 - x]) {
                    numberb.data[sizeb_1 - ldp_sdp - x] += 10;
                    numberb.data[sizeb_2 - ldp_sdp - x] -= 1;
                }
                finally_number.data[finally_number.data.size() - 1 - ldp_sdp - x] = numberb.data[sizeb_1 - ldp_sdp - x] - numbers.data[sizes_1 - x];
            }
            for (uint64_t x = 0; x < sizeb - ldp_sdp - sizes; x++) {
                finally_number.data[sizeb_1 - ldp_sdp - sizes - x] = numberb.data[sizeb_1 - ldp_sdp - sizes - x];
            }
        }
        else {
            for (uint64_t x = 0; x < numberb.size + sizes - numbers.size; x++) {
                finally_number.data.push_back(0);
            }
            sdp = sizeb - numberb.size;
            ldp = sizes - numbers.size;
            ldp_sdp = ldp - sdp;
            finally_number.data[finally_number.data.size() - 1] = 10 - numbers.data[numbers.data.size() - 1];
            numberb.data[numberb.data.size() - 1] -= 1;

            for (uint64_t x = 0; x < ldp_sdp - 1; x++) {
                finally_number.data[finally_number.data.size() - 2 - x] = 9 - numbers.data[sizes_1 - x - 1];
            }
            for (uint64_t x = 0; x < sdp + numbers.size; x++) {
                if (numberb.data[sizeb_1 - x] < numbers.data[sizes_1 - ldp_sdp - x]) {
                    numberb.data[sizeb_1 - x] += 10;
                    numberb.data[sizeb_2 - x] -= 1;
                }
                finally_number.data[finally_number.data.size() - 1 - ldp_sdp - x] = numberb.data[sizeb_1 - x] - numbers.data[sizes_1 - ldp_sdp - x];
            }
            for (uint64_t x = 0; x < sizeb + ldp_sdp - sizes; x++) {
                finally_number.data[sizeb_1 + ldp_sdp - sizes - x] = numberb.data[sizeb_1 + ldp_sdp - sizes - x];
            }
        }
        if (finally_number.data[0] == 0) {
            finally_number.data.erase(finally_number.data.begin());
            finally_number.size = numberb.size - 1;
        }
        else {
            finally_number.size = numberb.size;
        }
    }
    return finally_number;
}
inline number subtract(number number1, number number2) {
    if (number2.pom == 1) {
        number2.pom = -1;
    }
    else {
        number2.pom = 1;
    }
    return add(number1, number2);
}
inline bool number_greater(number number1, number number2) {
    int type = 0;
    uint64_t size1 = number1.data.size(), size2 = number2.data.size();
    number numbers, numberb;
    if (number1.size > number2.size) {
        return true;
    }
    else if (number1.size < number2.size) {
        return false;
    }
    else {
        uint64_t  minsize = min(size1, size2);
        for (uint64_t x = 0; x < minsize; x++) {
            if (number1.data[x] > number2.data[x]) {
                return true;
            }
            else if (number1.data[x] < number2.data[x]) {
                return false;
            }
        }
        if (size1 > size2) {
            return true;
        }
        else if (size2 > size1) {
            return false;
        }
        else {
            return false;
        }
    }
}
inline bool number_less(number number1, number number2) {
    int type = 0;
    uint64_t size1 = number1.data.size(), size2 = number2.data.size();
    number numbers, numberb;
    if (number1.size > number2.size) {
        return false;
    }
    else if (number1.size < number2.size) {
        return true;
    }
    else {
        uint64_t  minsize = min(size1, size2);
        for (uint64_t x = 0; x < minsize; x++) {
            if (number1.data[x] > number2.data[x]) {
                return false;
            }
            else if (number1.data[x] < number2.data[x]) {
                return true;
            }
        }
        if (size1 > size2) {
            return false;
        }
        else if (size2 > size1) {
            return true;
        }
        else {
            return false;
        }
    }
}
inline bool equal(number number1, number number2) {
    int type = 0;
    uint64_t size1 = number1.data.size(), size2 = number2.data.size();
    number numbers, numberb;
    if (number1.size > number2.size) {
        return false;
    }
    else if (number1.size < number2.size) {
        return false;
    }
    else {
        uint64_t  minsize = min(size1, size2);
        for (uint64_t x = 0; x < minsize; x++) {
            if (number1.data[x] > number2.data[x]) {
                return false;
            }
            else if (number1.data[x] < number2.data[x]) {
                return false;
            }
        }
        if (size1 > size2) {
            return false;
        }
        else if (size2 > size1) {
            return false;
        }
        else {
            return true;
        }
    }
}
inline bool equaltozero(number number) {
    for (uint64_t x = 0; x < number.data.size(); x++) {
        if (number.data[x] != 0)return false;
    }
    return true;
}
inline number multiplication(number number1, number number2) {
    number finally_number;
    if (equaltozero(number1) || equaltozero(number2)) {
        finally_number.data.push_back(0);
        finally_number.size = 1;
        finally_number.pom = 1;
        return finally_number;
    }
    for (uint64_t x = 0; x < number1.data.size() + number2.data.size(); x++) {
        finally_number.data.push_back(0);
    }
    for (uint64_t x = number1.data.size() - 1; x >= 0; x--) {
        for (uint64_t y = number2.data.size() - 1; y >= 0; y--) {
            finally_number.data[x + y + 1] += number1.data[x] * number2.data[y];
            finally_number.data[x + y] += finally_number.data[x + y + 1] / 10;
            finally_number.data[x + y + 1] %= 10;
            if (y == 0)break;
        }
        if (x == 0) {
            break;
        }
    }
    if (finally_number.data[0] == 0) {
        finally_number.data.erase(finally_number.data.begin());
        finally_number.size = number1.size + number2.size - 1;
    }
    else {
        finally_number.size = number1.size + number2.size;
    }
    if (number1.pom == number2.pom) {
        finally_number.pom = 1;
    }
    else {
        finally_number.pom = -1;
    }
    finally_number = accurate_to(finally_number, 100);
    return finally_number;
}
inline number multiplication(number number1, number number2, uint64_t i) {
    number finally_number;
    if (equaltozero(number1) || equaltozero(number2)) {
        finally_number.data.push_back(0);
        finally_number.size = 1;
        finally_number.pom = 1;
        return finally_number;
    }
    for (uint64_t x = 0; x < number1.data.size() + number2.data.size(); x++) {
        finally_number.data.push_back(0);
    }
    for (uint64_t x = number1.data.size() - 1; x >= 0; x--) {
        for (uint64_t y = number2.data.size() - 1; y >= 0; y--) {
            finally_number.data[x + y + 1] += number1.data[x] * number2.data[y];
            finally_number.data[x + y] += finally_number.data[x + y + 1] / 10;
            finally_number.data[x + y + 1] %= 10;
            if (y == 0)break;
        }
        if (x == 0) {
            break;
        }
    }
    if (finally_number.data[0] == 0) {
        finally_number.data.erase(finally_number.data.begin());
        finally_number.size = number1.size + number2.size - 1;
    }
    else {
        finally_number.size = number1.size + number2.size;
    }
    if (number1.pom == number2.pom) {
        finally_number.pom = 1;
    }
    else {
        finally_number.pom = -1;
    }
    finally_number = accurate_to(finally_number, i);
    return finally_number;
}
inline number division(number number1, number number2) {
    number finally_number;
    int npo = 0; // the number of operations
    finally_number.pom = number1.pom * number2.pom;
    number1.pom = 1;
    number2.pom = 1;
    if (number1.size < number2.size) {
        for (int x = 0; x < number2.size - number1.size; x++) {
            finally_number.data.push_back(0);
        }
        finally_number.size = 1;
        npo = 101 - number2.size + number1.size;
    }
    else {
        finally_number.size = number1.size - number2.size + 1;
        npo = 101 + number1.size - number2.size;
    }
    //除数
    number div[10];
    div[0].data.push_back(0);
    div[0].size = 1;
    div[0].pom = 1;
    number2.size = number2.data.size();
    for (short i = 1; i <= 9; i++) {
        number tmp;
        tmp.data.push_back(i);
        tmp.size = 1;
        tmp.pom = 1;
        div[i] = multiplication(number2, tmp);
        div[i] = accurate_to(div[i], div[i].size);
    }
    //余数
    number rem;
    int idx;
    for (idx = 0; idx < number2.data.size(); idx++) {
        if (idx >= number1.data.size()) {
            rem.data.push_back(0);
        }
        else {
            rem.data.push_back(number1.data[idx]);
        }
    }
    number ten;
    ten.data.push_back(1);
    ten.data.push_back(0);
    ten.size = 2;
    ten.pom = 1;
    rem.size = rem.data.size();
    rem.pom = 1;
    int rem_start = 0;
    int div_start = 0;
    for (uint64_t x = 0; x < npo; x++) {
        //试除法，0-9中找最大的数
        int left = 0, right = 9;
        while (left < right) {
            int mid = (left + right) / 2 + 1;
            if (number_greater(div[mid], rem)) {
                right = mid - 1;
            }
            else {
                left = mid;
            }
        }
        finally_number.data.push_back(left);
        if (left > 0) {
            rem = subtract(rem, div[left]);
            rem.pom = 1;
        }
        //小数点向右移位
        rem = multiplication(rem, ten);
        if (idx < number1.data.size()) {
            number tmp;
            tmp.data.push_back(number1.data[idx]);
            tmp.size = 1;
            tmp.pom = 1;
            rem = add(rem, tmp);
        }
        idx += 1;
        /// 去掉前导0
        while (rem.size > 1 && rem.data[0] == 0) {
            rem.data.erase(rem.data.begin());
            rem.size -= 1;
        }
    }
    return finally_number;
}
inline number division(number number1, number number2,uint64_t npo) {
    number finally_number;
    finally_number.pom = number1.pom * number2.pom;
    number1.pom = 1;
    number2.pom = 1;
    if (number1.size < number2.size) {
        for (int x = 0; x < number2.size - number1.size; x++) {
            finally_number.data.push_back(0);
        }
        finally_number.size = 1;
        npo = npo - number2.size + number1.size;
    }
    else {
        finally_number.size = number1.size - number2.size + 1;
        npo = npo + number1.size - number2.size;
    }
    //除数
    number div[10];
    div[0].data.push_back(0);
    div[0].size = 1;
    div[0].pom = 1;
    number2.size = number2.data.size();
    for (short i = 1; i <= 9; i++) {
        number tmp;
        tmp.data.push_back(i);
        tmp.size = 1;
        tmp.pom = 1;
        div[i] = multiplication(number2, tmp);
        div[i] = accurate_to(div[i], div[i].size);
    }
    //余数
    number rem;
    int idx;
    for (idx = 0; idx < number2.data.size(); idx++) {
        if (idx >= number1.data.size()) {
            rem.data.push_back(0);
        }
        else {
            rem.data.push_back(number1.data[idx]);
        }
    }
    number ten;
    ten.data.push_back(1);
    ten.data.push_back(0);
    ten.size = 2;
    ten.pom = 1;
    rem.size = rem.data.size();
    rem.pom = 1;
    int rem_start = 0;
    int div_start = 0;
    for (uint64_t x = 0; x < npo; x++) {
        //试除法，0-9中找最大的数
        int left = 0, right = 9;
        while (left < right) {
            int mid = (left + right) / 2 + 1;
            if (number_greater(div[mid], rem)) {
                right = mid - 1;
            }
            else {
                left = mid;
            }
        }
        finally_number.data.push_back(left);
        if (left > 0) {
            rem = subtract(rem, div[left]);
            rem.pom = 1;
        }
        //小数点向右移位
        rem = multiplication(rem, ten);
        if (idx < number1.data.size()) {
            number tmp;
            tmp.data.push_back(number1.data[idx]);
            tmp.size = 1;
            tmp.pom = 1;
            rem = add(rem, tmp);
        }
        idx += 1;
        /// 去掉前导0
        while (rem.size > 1 && rem.data[0] == 0) {
            rem.data.erase(rem.data.begin());
            rem.size -= 1;
        }
    }
    return finally_number;
}
