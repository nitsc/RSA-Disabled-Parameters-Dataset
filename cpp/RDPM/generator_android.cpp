#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <numeric>

// �ж��Ƿ�Ϊ����
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// �������Լ�� (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// ����ģ��
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
    // �����ļ������
    // ����ʹ���ⲿ�洢·��
    std::ofstream outfile("/storage/emulated/0/rdpm1hund_test.csv");
    if (!outfile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1; // Exit if file can't be opened
    }

    // д�� CSV �ļ��ı�ͷ
    outfile << "p,q,n,phi_n,e,d,m,c\n";

    // �������� p �� q����Χ�� 0 �� 100��
    std::vector<int> primes = generate_primes(50,100);

    // ��� p �� q
    for (int p : primes) {
        for (int q : primes) {
            if (p != q) {
                int n = p * q;  // n = p * q
                int phi_n = (p - 1) * (q - 1);  // ŷ������ ��(n)

                // Ѱ�ҺϷ��� e
                for (int e = 2; e < phi_n; ++e) {
                    if (gcd(e, phi_n) == 1) {
                        // Ѱ�� d
                        int d = mod_inverse(e, phi_n);  // �� e ��ģ��Ԫ�� d

                        // ��� m (����ǰ����Ϣ)
                        for (int m = 1; m < n; ++m) {
                            if (m < n) {
                                // ���ܹ��� c = m^e % n
                                int c = static_cast<int>(std::pow(m, e)) % n;
                                if (m == c) {
                                    // ��ӡ���������Ĳ���
                                    std::cout << "p=" << p << ", q=" << q << ", n=" << n
                                        << ", phi(n)=" << phi_n << ", e=" << e
                                        << ", d=" << d << ", m=" << m << ", c=" << c << std::endl;

                                    // д����������Ĳ����� CSV �ļ�
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
    std::cout << "�����ѳɹ�д�� RSA Disabled Parameter Matching Dataset �ļ���" << std::endl;
    return 0;
}
