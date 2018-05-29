uint32_t icbrt(uint64_t x) {
  int32_t s;
  uint32_t y;
  uint64_t b;
  y = 0;
  for (s = 63; s >= 0; s -= 3) {
    y += y;
    b = 3*y*((uint64_t) y + 1) + 1;
    if ((x >> s) >= b) {
      x -= b << s;
      y++;
    }
  }
  return y;
}
