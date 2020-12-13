import requests
import json

### base url is http://{{node}}:{{port}}/OASREST/v2/
url = 'http://207.180.232.51:8888/novaData'
data = '''{"CAS":"2020-12-13 03:00:00", "TEPLOTA":"3", "VLHKOST":"90", "TLAK":"1400", "CO2":"1"}'''
headers = {'Content-Type':'application/json'}

### Authentication is completed via a POST request
response = requests.request("POST", url, data=data,
                             headers=headers)

print(response.text)

