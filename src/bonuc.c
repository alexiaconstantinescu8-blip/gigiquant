#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"

struct MemoryStruct {
    char *memory;
    size_t size;
};

// 1. Am adăugat 'const' aici:
static size_t WriteMemoryCallback(const void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) return 0;
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

double* get_open_prices(const char* symbol, const char* interval, const char* range, int *count_out) {
    CURL *curl_handle;
    struct MemoryStruct chunk = {malloc(1), 0};
    char url[256];
    double *prices = NULL;

    sprintf(url, "https://query1.finance.yahoo.com/v8/finance/chart/%s?interval=%s&range=%s", symbol, interval, range);
    curl_handle = curl_easy_init();
    
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    // 2. Am adăugat acest (cast) pentru a potrivi semnătura funcției cu ce așteaptă libcurl
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, (size_t (*)(void *, size_t, size_t, void *))WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    if (curl_easy_perform(curl_handle) == CURLE_OK) {
        cJSON *json = cJSON_Parse(chunk.memory);
        
        // 3. Am adăugat 'const' aici:
        const cJSON *result = cJSON_GetArrayItem(cJSON_GetObjectItem(cJSON_GetObjectItem(json, "chart"), "result"), 0);
        
        cJSON *quote = cJSON_GetArrayItem(cJSON_GetObjectItem(cJSON_GetObjectItem(result, "indicators"), "quote"), 0);
        
        // 4. Am adăugat 'const' aici:
        const cJSON *open_prices = cJSON_GetObjectItem(quote, "open");

        *count_out = cJSON_GetArraySize(open_prices);
        prices = malloc((*count_out) * sizeof(double));

        for (int i = 0; i < *count_out; i++) {
            cJSON *val = cJSON_GetArrayItem(open_prices, i);
            prices[i] = cJSON_IsNumber(val) ? val->valuedouble : -1.0;
        }
        cJSON_Delete(json);
    }
    
    curl_easy_cleanup(curl_handle);
    free(chunk.memory);
    return prices;
}