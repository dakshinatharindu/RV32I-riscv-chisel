int main()
{

    int n1 = 53, n2 = 34, max;

    // maximum number between n1 and n2 is stored in max
    max = (n1 > n2) ? n1 : n2;

    while (1)
    {
        if ((max % n1 == 0) && (max % n2 == 0))
        {
            break;
        }
        ++max;
    }
    return 0;

    // char a = 'a';
    // char b = 'b';
    // char c[2];
    // c[1] = a;
    // c[2] = b;
    // return 0;
}

// int main() {
//     int a,i,j;
//     int a1 = 25;
//     int a2 = 11;
//     int a3 = 7;
//     int a4 = 75;
//     int a5 = 56;
//     int a6 = 34;
//     int arr[] = {a1, a2, a3, a4, a5, a6};
//     int n = sizeof(arr) / sizeof(arr[0]);
//     for (i = 0; i < n; ++i) {
//         for (j = i + 1; j < n; ++j) {
//             if (arr[i] > arr[j]) {
//                 a = arr[i];
//                 arr[i] = arr[j];
//                 arr[j] = a;
//             }
//         }
//     }
//     return 0;
// }