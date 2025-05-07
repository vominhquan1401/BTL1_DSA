#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
void train_test_split(Dataset& X, Dataset& Y, double test_size,
     Dataset& X_train, Dataset& X_test, Dataset& Y_train, Dataset& Y_test)
{
    if (X.getData()->length() != Y.getData()->length() || test_size <= 0 || test_size >= 1)
        return;

    int nRow1, nCol1;
    int nRow2, nCol2;
    X.getShape(nRow1, nCol1);
    Y.getShape(nRow2, nCol2);

    double x_row = double(((1 - test_size) * nRow1));
    double y_row = double((1 - test_size) * nRow2);

    X_train = X.extract(0, x_row - 1, 0, -1);
    X_test = X.extract(x_row, nRow1, 0, -1);

    Y_train = Y.extract(0, y_row - 1, 0, -1);
    Y_test = Y.extract(y_row, nRow2, 0, -1);
}

