struct Mypair
{
  int x = 0;
  int y = 0;
  constexpr Mypair(int tx, int ty) : x(tx), y(ty) {}
  constexpr Mypair() {}
  constexpr auto operator<=>(const Mypair &) const = default;

  constexpr Mypair operator+=(Mypair r) noexcept
  {
    *this = (*this) + r;
    return *this;
  }
  friend constexpr Mypair operator+(Mypair l, Mypair r) noexcept
  {
    Mypair t(l);
    t.x += r.x;
    t.y += r.y;
    return t;
  }
};