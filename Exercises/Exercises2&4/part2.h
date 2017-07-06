double binding_energy (int Z, int N);
int ceiling_binding_energy (double be);
int ceiling_binding_energy (int Z, int N);

void get_limits (int &Z_low, int &Z_high, int &N_low, int &N_high);
void plot (int Z_low, int Z_high, int N_low, int N_high);
void find_dripline(int Z_low, int Z_high, int N_low, int N_high);
void calc_single();