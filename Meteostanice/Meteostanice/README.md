# Zabezpečení krádeže
```
static uint64_t sleep_start_us = 0;
struct timeval tv_now;

void timeChecker() {
  sleep_start_us = gettimeofday(&tv_now,NULL);
  time_t now;
  time(&now);
  printf(ctime(&now));
}
```

# Zdroje
[System Time](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html)
[[C/C++] Converting time structure to date format](https://ubuntuforums.org/archive/index.php/t-1114250.html)


# Pokud se nejde dostat na port
sudo chmod a+rw /dev/ttyUSB0