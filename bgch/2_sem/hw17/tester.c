for (k = 0; k < m; k++) {
    //r_k = A @ x_k - b
    rem1 = 0; // r_k @ r_k
    rem2 = 0;

    for (i = 0; i < n; i++) {
        sum = 0; // sum = A[i] @ r_k

        for (j = 0; j < n; j++) {
            sum += A[i * n + j] * r[j];
        }

        rem1 += r[i] * r[i];
        rem2 += r[i] * sum;
        x[i] = sum;
    }

    if (fabs(rem2) > eps) {
        for (i = 0; i < n; i++) {
            x0[i] -= r[i] * rem1 / rem2;
        }
    }

    for (i = 0; i < n; i++) {
        //v1 x[i] = r[i] - x[i] * rem2 / rem1;
        x[i] = r[i] - x[i] * rem1 / rem2;
        //v2 r[i] = r[i] - x[i] * rem2 / rem1;
    }

    //v1 *r = *x;
}
