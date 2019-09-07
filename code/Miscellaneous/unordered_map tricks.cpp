// pair<int, int> hash function
struct HASH{
  size_t operator()(const pair<int,int>&x)const{
    return (size_t) x.first * 37U + (size_t) x.second;
  }
};


unordered_map<int,int>mp;
mp.reserve(1024);
mp.max_load_factor(0.25);
