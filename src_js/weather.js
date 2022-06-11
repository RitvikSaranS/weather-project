async function showdata (url){
    const response = await fetch(url);
    var data = await response.json();
    // console.log(data);
    var temperature = data["main"]["temp"] - 273.15;
    temperature = temperature.toFixed(2);
    var feelslike = data["main"]["feels_like"] - 273.15;
    feelslike = feelslike.toFixed(2);
    var name = data["name"];
    var country = data["sys"]["country"];
    var humidity = data["main"]["humidity"];
    var windspeed = data["wind"]["speed"];
    var pressure = data["main"]["pressure"];
    var windeg = data["wind"]["deg"];
    document.getElementById('display').innerHTML = 
    " Location : " + name + "(" + data["coord"]["lat"] + ", " + data["coord"]["lon"] + "), " + country +"<br>"+
    " Temperature : " + temperature + "°C (feels like " + feelslike + "°C ) <br>" +
    " Humidity : " + humidity + "% <br>" +
    " Pressure : " + pressure + " hPa <br>" +
    " Wind Speed : " + windspeed + " m/s | Deg : " + windeg + "° <br>" +
    " Visibility : " + data["visibility"] + " m";
}


document.getElementById('getreport').addEventListener('click', function() {
    let city = document.getElementById('input').value;
    let words = city.split(" ");
    for (let i = 0; i< words.length; i++){
        words[i] = words[i][0].toUpperCase() + words[i].substring(1); 
    }
    city = words.join(" ");
    console.log(city);
    let api_key = "7bca121c81148244b333fb5aebf4225b";
    let url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + api_key;
    // console.log(url);
    showdata(url);
}
);
