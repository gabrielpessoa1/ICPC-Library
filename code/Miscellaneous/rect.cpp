namespace {
  struct safe_hash {
    static uint64_t splitmix64(uint64_t x) {
      // http://xorshift.di.unimi.it/splitmix64.c
      x += 0x9e3779b97f4a7c15;
      x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
      x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
      return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
      static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
      return splitmix64(x + FIXED_RANDOM);
    }
  };
}

struct rect {
  int x1, y1, x2, y2; // x1 < x2, y1 < y2
  rect () {};
  rect (int x1, int y1, int x2, int y2) : x1(x1), x2(x2), y1(y1), y2(y2) {};
  
  rect inter (rect other) {
    int x3 = max(x1, other.x1);
    int y3 = max(y1, other.y1);
    int x4 = min(x2, other.x2);
    int y4 = min(y2, other.y2);
    return rect(x3, y3, x4, y4);
  }
  
  uint64_t get_hash() {
    safe_hash sh;
    uint64_t ret = sh(x1);
    ret ^= sh(ret ^ y1);
    ret ^= sh(ret ^ x2);
    ret ^= sh(ret ^ y2);
    return ret;
  }
};
