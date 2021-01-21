void setupDestSenzor(const int pin_pro_dest);
bool isPrsi(const int pin_pro_dest);

extern int tlak;

bool setupBMP280();
float readValueBMP280();

void setupCCS811();
int readValueCCS811();