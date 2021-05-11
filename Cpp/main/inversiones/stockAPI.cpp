#include <curl/curl.h>
#include "../../../lib/rapidjson/document.h"
#include "stockAPI.h"
#include <iostream>
#include <string>

using namespace stockAPI;
using namespace std;

//CURL Write Callback
size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

//Symbol
Symbol::Symbol(const char *description, const char *displaySymbol, const char *symbol, const char *type)
{
    this->description = description;
    this->displaySymbol = displaySymbol;
    this->symbol = symbol;
    this->type = type;
}

Symbol::~Symbol()
{
    delete this->description;
    delete this->displaySymbol;
    delete this->symbol;
    delete this->type;
}

const char *Symbol::getDescription() const
{
    return this->description;
}
const char *Symbol::getDisplaySymbol() const
{
    return this->displaySymbol;
}
const char *Symbol::getSymbol() const
{
    return this->symbol;
}
const char *Symbol::getType() const
{
    return this->type;
}

float Symbol::getCurrentValue() const
{
    float currentValue = 0;
    CURL *curl = curl_easy_init();
    if (curl)
    {
        string readBuffer;

        string url = "https://finnhub.io/api/v1/quote?symbol=";
        url.append(this->symbol);
        url.append("&token=c29u97aad3ifmap92ah0");

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK)
        {
            rapidjson::Document document;
            document.Parse(readBuffer.c_str());
            currentValue = document["c"].GetFloat();
        }

        curl_easy_cleanup(curl);
    }
    return currentValue;
}
//Search
Search::Search(const char *query)
{
    this->query = query;
    performSearch();
}
Search::~Search()
{
    //delete query; ERROR pointer being freed was not allocated
    delete results;
}
void Search::performSearch()
{
    CURL *curl = curl_easy_init();
    if (curl)
    {
        string readBuffer;

        string url = "https://finnhub.io/api/v1/search?q=";
        url.append(this->query);
        url.append("&token=c29u97aad3ifmap92ah0");

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK)
        {
            rapidjson::Document document;
            document.Parse(readBuffer.c_str());

            int tempSize = document["count"].GetInt();
            Symbol **tempResults = new Symbol *[tempSize];

            int finalSize = 0;
            for (int i = 0; i < tempSize; i++)
            {
                string sy = document["result"].GetArray()[i]["symbol"].GetString();
                if (sy.find(".") == string::npos)
                {
                    Symbol *s = new Symbol(document["result"].GetArray()[i]["description"].GetString(), document["result"].GetArray()[i]["displaySymbol"].GetString(), document["result"].GetArray()[i]["symbol"].GetString(), document["result"].GetArray()[i]["type"].GetString());
                    *(tempResults + finalSize) = s;
                    finalSize++;
                }
            }
            this->count = finalSize;
            this->results = new Symbol *[finalSize];
            for (int i = 0; i < finalSize; i++)
            {
                this->results[i] = *(tempResults + i);
            }
        }
        curl_easy_cleanup(curl);
    }
}
int Search::getCount() const
{
    return this->count;
}
Symbol **Search::getResults() const
{
    return this->results;
}