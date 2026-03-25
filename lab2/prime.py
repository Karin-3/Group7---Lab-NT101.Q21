import random
import sympy
import math

def generate_prime(bits):
    while True:
        num = random.getrandbits(bits)
        num |= (1 << bits-1) | 1   # đảm bảo đúng số bit và là số lẻ
        if sympy.isprime(num):
            return num

def mersenne_prime_10():
    # Mersenne thứ 10: 2^89 - 1
    M = 2**89 - 1

    primes = []
    n = M - 1

    while len(primes) < 10:
        if sympy.isprime(n):
            primes.append(n)
        n -= 1

    return primes

def check_prime(n):
    return sympy.isprime(n)


def gcd_large(a, b):
    return math.gcd(a, b)


def mod_exp(a, x, p):
    return pow(a, x, p)


print("Prime number generation")

prime8 = generate_prime(8)
prime16 = generate_prime(16)
prime64 = generate_prime(64)

print("8-bit prime :", prime8)
print("16-bit prime:", prime16)
print("64-bit prime:", prime64)


print("10 primes below mersenne prime")

mersenne_primes = mersenne_prime_10()
for i, p in enumerate(mersenne_primes):
    print(f"{i+1}: {p}")


print("prime number check")
num = int(input("Enter a number (< 2^89 -1): "))
if check_prime(num):
    print("This is a prime number")
else:
    print("This is not a prime number")


print("GCD of two large numbers")
a = int(input("Enter first number: "))
b = int(input("Enter second number: "))

print("GCD =", gcd_large(a, b))


print("Modular exponentiation")
a = int(input("Enter a: "))
x = int(input("Enter exponent x: "))
p = int(input("Enter modulo p: "))

print("Result:", mod_exp(a, x, p))

print("Example: 7^40 mod 19 =", mod_exp(7,40,19))