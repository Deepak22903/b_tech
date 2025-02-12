#ifndef HEADER_H
#define HEADER_H

#include <chrono>
#include <cppcodec/base64_rfc4648.hpp>
#include <ctime>
#include <curl/curl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
using namespace std;
using namespace cppcodec;

// ✅ Use `const std::string` instead of `#define`
const std::string CLOUDFLARE_ACCOUNT_ID = "d03ba4adab44b19322eed9dd5a40de7d";
const std::string CLOUDFLARE_AUTH_TOKEN =
    "MkPwb3osbvgKuSWn8XR43dnk3vAs2VW-EgXZ_pek";
const std::string FB_PAGE_ID = "555233441009283";
const std::string FB_ACCESS_TOKEN =
    "EAANZBEY9KdLkBOZCDRYjSg7RqdTZC9f1i4uPI4RnKS0fFz26pw9c2huvOH6GuSFXQ9FZAPK"
    "ZBm832w5CaJkj8or93AJzZB9dnk"
    "WZCAAYBiWJUyXJJIuAZBIpZAsZCLDZB6f2KI3wcXN3nR14D0HVRL1jbLCrPsZCtkIXGAAbGQ"
    "LWZCndJqhcfk0Yb994fhDx980ZA3xlbw";

// Function Declarations
std::string generatePrompt();
void generateImage(std::string prompt);
size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                     std::string *output);

#endif // HEADER_H
