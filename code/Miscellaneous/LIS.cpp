int arr[ms], lisArr[ms], n;
// int bef[ms], pos[ms];

int lis() {
  int len = 1;
  lisArr[0] = arr[0];
  // bef[0] = -1;
  for(int i = 1; i < n; i++) {
    // upper_bound se non-decreasing
    int x = lower_bound(lisArr, lisArr + len, arr[i]) - lisArr; 
    len = max(len, x + 1);
    lisArr[x] = arr[i];
    // pos[x] = i;
    // bef[i] = x ? pos[x-1] : -1;
  }
  return len;
}

vi getLis() {
  int len = lis();
  vi ans;
  for(int i = pos[lisArr[len - 1]]; i >= 0; i = bef[i]) {
    ans.push_back(arr[i]);
  }
  reverse(ans.begin(), ans.end());
  return ans;
}