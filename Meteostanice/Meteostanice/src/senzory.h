void setupDestSenzor(const int pin_pro_dest);
bool isPrsi(const int pin_pro_dest);

void setupCCS811();
int readValueCCS811();

bool setupBME280();
double * readValueBME280();