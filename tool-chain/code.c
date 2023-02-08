int main()
{

    int n1 = 34, n2 = 44, max;

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
}