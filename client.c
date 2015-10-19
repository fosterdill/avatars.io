#include "client.h"

size_t callbackfunction(void *ptr, size_t size, size_t nmemb, void* userdata)
{
  return send(*(int*)userdata , ptr , nmemb, 0);
}

int download_jpeg(char* url, int sock)
{
    FILE* fp = fopen("out.jpg", "wb");
    if (!fp)
    {
        return 0;
    }

    CURL* curlCtx = curl_easy_init();
    curl_easy_setopt(curlCtx, CURLOPT_URL, url);
    curl_easy_setopt(curlCtx, CURLOPT_WRITEDATA, &sock);
    curl_easy_setopt(curlCtx, CURLOPT_WRITEFUNCTION, callbackfunction);
    curl_easy_setopt(curlCtx, CURLOPT_FOLLOWLOCATION, 1);

    CURLcode rc = curl_easy_perform(curlCtx);
    if (rc)
    {
        return 0;
    }

    long res_code = 0;
    curl_easy_getinfo(curlCtx, CURLINFO_RESPONSE_CODE, &res_code);
    if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK))
    {
        return 0;
    }

    curl_easy_cleanup(curlCtx);

    fclose(fp);

    return 1;
}
