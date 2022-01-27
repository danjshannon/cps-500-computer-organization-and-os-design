int leaf_example(int g, int h, int i, int j)
{
    int f;
    f = (g + h) - (i + j);
    return f;
}

int main(void)
{
    leaf_example(0, 1, 2, 3);
    return 0;
}