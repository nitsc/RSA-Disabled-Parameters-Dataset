import sympy
import csv
from colorama import init, Fore

# 初始化 colorama
init()

# 生成质数 p, q (在0到100之间)
primes = list(sympy.primerange(0, 101))

# 打开CSV文件用于写入
with open('C:\\Users\\admin\\Desktop\\rdpm1hund.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    # 写入表头
    writer.writerow(['p', 'q', 'n', 'phi(n)', 'e', 'd', 'm', 'c'])

    # 穷举 p 和 q
    for p in primes:
        for q in primes:
            if p != q:
                n = p * q  # n = p * q
                phi_n = (p - 1) * (q - 1)  # 欧拉函数 φ(n)
                
                # 寻找合法的 e
                for e in range(2, phi_n):
                    if sympy.gcd(e, phi_n) == 1:
                        # 寻找 d
                        d = sympy.mod_inverse(e, phi_n)  # 求 e 的模反元素 d
                        
                        # 穷举 m (加密前的消息)
                        for m in range(1, n):
                            if m < n:
                                # 加密过程 c = m^e % n
                                c = pow(m, e, n)
                                if m == c:
                                    # 打印符合条件的参数
                                    print(Fore.BLUE + f"p={p}, q={q}, n={n}, phi(n)={phi_n}, e={e}, d={d}, m={m}, c={c}")
                                
                                    # 写入符合条件的参数到 CSV 文件    
                                    writer.writerow([p, q, n, phi_n, e, d, m, c])
                                else:
                                    print(Fore.RED + f"Warning: m={m} does not match c={c}, it will be abandoned")

print(Fore.GREEN + "参数已成功写入 RSA Disabled Parameter Matching Dataset 文件！")
