void setupDestSenzor(const int pinSenzoruDeste);
bool isPrsi(const int pinSenzoruDeste);

bool setupCCS811();
int readValueCCS811();

bool setupBME280();
double * readValueBME280();