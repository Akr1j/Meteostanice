# Meteostanice
Maturitní práce

## Připojení na VPS
```
ssh root@207.180.232.51 -p 2200
```

## Příklad posílání dat na VPS
```
curl -X POST -H "Content-Type: application/json" -d '{"CAS":"2020-12-13 9:00:00", "TEPLOTA":"20", "VLHKOST":"60", "TLAK":"1000", "CO2":"5"}' http://207.180.232.51:8888/novaData
```