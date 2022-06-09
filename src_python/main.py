import requests

def kelvintoC(temp):
    return round(temp - 273.15,2)

if __name__ == "__main__":
    city = str(input("Enter the city name: "))
    api_key = "7bca121c81148244b333fb5aebf4225b" # check apikey.md file
    openweatherurl = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + api_key
    report = requests.get(openweatherurl)
    report_json = report.json() # Uses a json decoder, returns json decode error if not possible.
    temp = report_json['main']
    print("\n~~~~ PRIMARY WEATHER REPORT ~~~~\n")
    print(f"Location: {report_json['name']} {report_json['coord']}, {report_json['sys']['country']}")
    print(f"Temperature : {kelvintoC(temp['temp'])}° C (feels like {(kelvintoC(temp['feels_like']))}° C)")
    print(f"Humidity : {temp['humidity']}%")
    print(f"Pressure : {temp['pressure']} hPa")
    print(f"Wind : {report_json['wind']['speed']} m/s | Deg : {report_json['wind']['deg']}")
    print(f"Visibility: {report_json['visibility']} m")
    print("\n~~~~~~~~~~~\n")
