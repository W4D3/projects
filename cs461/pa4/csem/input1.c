double m[6];

scale(double x, double y, int k) {
  int i;
  double t;
  double s;
  
  if (x == 0)
    return 0;
  for (i = 0; i < 6; i += 1)
    m[i] *= x;
  return 1;
}
