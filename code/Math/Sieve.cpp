bool notPrime[ms];
int primes[ms], qnt;

void sieve(int lim) {
  primes[qnt++] = 1 // se o 1 for valido na questao
  for(int i = 2; i < ms; i++) {
    if(notPrime[i]) continue;
    primes[qnt++] = i;
    for(int j = i + i; j < ms; j += i)
      notPrime[j] = true;
  }
}