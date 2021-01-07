## Příklad posílání dat na VPS
```
curl -X POST -H "Content-Type: application/json" -d '{"CAS":"2020-12-13 9:00:00", "TEPLOTA":"20", "VLHKOST":"60", "TLAK":"1000", "CO2":"5"}' http://207.180.232.51:8888/novaData
```

# Zdroje:
https://www.js-tutorials.com/nodejs-tutorial/node-js-rest-api-add-edit-delete-record-mysql-using-express/

https://nodejs.dev/learn/the-package-json-guide



Vyčkání na mysql
https://www.datanovia.com/en/lessons/docker-compose-wait-for-container-using-wait-tool/docker-compose-wait-for-mysql-container-to-be-ready/


[Getting Date and Time in Node.js](https://usefulangle.com/post/187/nodejs-get-date-time)

[How to format a UTC date as a `YYYY-MM-DD hh:mm:ss` string using NodeJS?](https://stackoverflow.com/questions/10645994/how-to-format-a-utc-date-as-a-yyyy-mm-dd-hhmmss-string-using-nodejs)