#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <numeric>

// 判断是否为质数
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// 计算最大公约数 (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 计算模逆
int mod_inverse(int e, int phi_n) {
    int t1 = 0, t2 = 1, r1 = phi_n, r2 = e;
    while (r2 > 0) {
        int q = r1 / r2;
        t1 = t1 - q * t2;
        r1 = r1 - q * r2;
        if (r1 < 0) {
            t1 = t1 + phi_n;
        }
        std::swap(t1, t2);
        std::swap(r1, r2);
    }
    return t1;
}

std::vector<int> generate_primes(int start, int end) {
    std::vector<int> primes;
    for (int i = start; i <= end; ++i) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}

int main() {
    // 创建文件输出流
    // 或者使用外部存储路径
    std::ofstream outfile("/storage/emulated/0/rdpm1hund_test.csv");
    if (!outfile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1; // Exit if file can't be opened
    }

    // 写入 CSV 文件的表头
    outfile << "p,q,n,phi_n,e,d,m,c\n";

    // 生成质数 p 和 q（范围是 0 到 100）
    std::vector<int> primes = generate_primes(50,100);

    // 穷举 p 和 q
    for (int p : primes) {
        for (int q : primes) {
            if (p != q) {
                int n = p * q;  // n = p * q
                int phi_n = (p - 1) * (q - 1);  // 欧拉函数 φ(n)

                // 寻找合法的 e
                for (int e = 2; e < phi_n; ++e) {
                    if (gcd(e, phi_n) == 1) {
                        // 寻找 d
                        int d = mod_inverse(e, phi_n);  // 求 e 的模反元素 d

                        // 穷举 m (加密前的消息)
                        for (int m = 1; m < n; ++m) {
                            if (m < n) {
                                // 加密过程 c = m^e % n
                                int c = static_cast<int>(std::pow(m, e)) % n;
                                if (m == c) {
                                    // 打印符合条件的参数
                                    std::cout << "p=" << p << ", q=" << q << ", n=" << n
                                        << ", phi(n)=" << phi_n << ", e=" << e
                                        << ", d=" << d << ", m=" << m << ", c=" << c << std::endl;

                                    // 写入符合条件的参数到 CSV 文件
                                    outfile << p << "," << q << "," << n << "," << phi_n << ","
                                        << e << "," << d << "," << m << "," << c << "\n";
                                }
                                else {
                                    std::cout << "Warning: m=" << m << " does not match c=" << c << ", it will be abandoned" << std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    outfile.close();  // Ensure the file is closed after all writes
    std::cout << "参数已成功写入 RSA Disabled Parameter Matching Dataset 文件！" << std::endl;
    return 0;
}
