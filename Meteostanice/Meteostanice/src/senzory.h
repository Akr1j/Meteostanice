void setupDestSenzor(const int pin_pro_dest);
bool isPrsi(const int pin_pro_dest);

extern int tlak;
extern int tlak2;
extern int vlhkost;

bool setupBMP280();
float readValueBMP280();

void setupCCS811();
int readValueCCS811();

bool setupBME280();
float readValueBME280();