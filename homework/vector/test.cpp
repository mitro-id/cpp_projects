#include "func.h"

int test() {
    std::cout << "=== Demontration ===\n\n";
    
    std::cout << "1. Create vector:\n";
    double data1[3] = {1.0, 2.0, 3.0};
    double data2[3] = {0.5, 1.5, 2.5};
    
    Vector<double, 3> v1(data1);
    Vector<double, 3> v2(data2);
    
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    
    std::cout << "\n2. operations:\n";
    Vector<double, 3> sum = v1 + v2;
    Vector<double, 3> scaled = 2.0 * v1;
    double dot_product = v1 ^ v2;
    
    std::cout << "v1 + v2 = " << sum << std::endl;
    std::cout << "2 * v1 = " << scaled << std::endl;
    std::cout << "v1 * 3 = " << (v1 * 3.0) << std::endl;
    std::cout << "v1 ^ v2 (dot product) = " << dot_product << std::endl;
    std::cout << "-v1 = " << (-v1) << std::endl;
    
    std::cout << "\n3. norm and sum:\n";
    std::cout << "norm v1: " << v1.norm() << std::endl;
    std::cout << "sum v1: " << v1.sum() << std::endl;
    
    std::cout << "\n4. exp:\n";
    Vector<double, 3> v_exp = v1;
    std::cout << "before exp(): " << v_exp << std::endl;
    v_exp.exp();
    std::cout << "after exp(): " << v_exp << std::endl;
    
    std::cout << "\n5. Softmax:\n";
    Vector<double, 3> v_soft = v1;
    std::cout << "before softmax(): " << v_soft << std::endl;
    v_soft.softmax();
    std::cout << "after softmax(): " << v_soft << std::endl;
    std::cout << "sum softmax: " << v_soft.sum() << "\n";
    
    std::cout << "\n6. operator +=:\n";
    Vector<double, 3> v3 = v1;
    std::cout << "before +=: " << v3 << std::endl;
    v3 += v2;
    std::cout << "after v3 += v2: " << v3 << std::endl;
    
    std::cout << "\n7. input/output:\n";
    Vector<double, 3> input_vec;
    
    std::cout << "Enter vector. Format (num, num, ..., num): ";
    std::cin >> input_vec;
    std::cout << input_vec;

    
    std::cout << "\n=== End ===\n";
    
    return 0;
}
