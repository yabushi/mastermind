void make4digits(int x[]) {
    int i, j, val;

    for (i = 0; i < 4; i++) {
        do{
            val = rand() % 10;
            for (j = 0; j < i; j++) {
                if (val == x[i]) break;
            }
        } while (j < i);
        x[i] = val;
    }
}