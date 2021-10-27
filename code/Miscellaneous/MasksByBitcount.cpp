for(int k = n-1; k >= 0; k--) {
  unsigned int i = (1 << k) -1;
  while(i < (1 << n)) {
    // do what you want
    unsigned int t = (i | (i - 1)) + 1;  
    if(i == 0) break;
    i = t | ((((t & -t) / (i & -i)) >> 1) - 1);
  }
}