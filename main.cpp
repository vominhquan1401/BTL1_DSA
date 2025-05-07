#include "kNN.hpp"

void tc1() {
    Dataset dataset;
    int nRows, nCols;
    dataset.loadFromCSV("D:/HCMUT/HCMUT_2_2/DSA/BTL1/init/init/mnist.csv");
    Dataset dataset_extract = dataset.extract(30, 20, 0, -1);
    Dataset dataset_extract2 = dataset_extract;
    dataset_extract2.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}
int main() {
    tc1();
    return 0;
}