#include<iostream>
#include<string>
#include<curl/curl.h>
#include<nlohmann/json.hpp>

static size_t WriteCallback (void *contents, size_t size, size_t nmemb, void *userp){
  ((std::string*)userp)->append((char*)contents,size * nmemb);
  return size * nmemb;
}

char* url_generator(void){
  char f_url[150] = "https://api.openweathermap.org/data/2.5/weather?q=";
  char appid[150] = "&appid=7bca121c81148244b333fb5aebf4225b"; // Replace with your own API key
  std::string acity;
  std::cout<< "Enter the city name: ";
  std::getline(std::cin, acity);
  char city[50];
  for(int i=0;i<acity.length();i++){
    if(acity[i]!= ' '){
      city[i] = acity[i];
    }else{city[i] = '+';}
  }
  std::strcat(f_url,city);
  std::strcat(f_url,appid);
  char *url;
  url = (char*)malloc(strlen(f_url)+1);
  std::strcpy(url, f_url);
  return url;
}


int main(){
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  char *f_url = url_generator();
  curl = curl_easy_init();
  if( curl ){
    curl_easy_setopt(curl, CURLOPT_URL, f_url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    nlohmann::json data = nlohmann::json::parse(readBuffer);
    if (data["cod"] == 200) {
    std::cout<< "\n~~~~ Weather Report ~~~~\n" << std::endl;
    std::cout<< "Location\t:\t" << data["name"] << "(" << data["coord"]["lat"] << ", " << data["coord"]["lon"] << "), Country: " << data["sys"]["country"] <<std::endl;
    float tempjson = data["main"]["temp"]; tempjson -= 273.15;
    float feeljson = data["main"]["feels_like"]; feeljson -= 273.15;
    std::cout<< "Temperature\t:\t" << tempjson << " °C " << "(feels like " << feeljson << " °C)" <<std::endl;
    std::cout<< "Humidity\t:\t" << data["main"]["humidity"] << "%" << std::endl;
    std::cout<< "Pressure\t:\t" << data["main"]["pressure"] << " hPa" << std::endl;
    std::cout<< "Visibility\t:\t" << data["visibility"] << " m" << std::endl;
    std::cout<< "Wind Speed\t:\t" << data["wind"]["speed"] << " m/s | Deg\t:" << data["wind"]["deg"] << std::endl;
    std::cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
    }else {
      // Invalid City
      std::cout<< "Please enter a valid city name" << end;
    }
  }
  return 0;
}
