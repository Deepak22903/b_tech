#ifndef HEADER_H
#define HEADER_H
#include <Poco/Base64Encoder.h>
#include <chrono>
#include <cppcodec/base64_rfc4648.hpp>
#include <cstddef>
#include <ctime>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

using json = nlohmann::json;
using namespace std;
using namespace cppcodec;

// Base64 encoding table
const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz"
                                 "0123456789+/";

// ✅ Use `const string` instead of `#define`
const string CLOUDFLARE_ACCOUNT_ID = "d03ba4adab44b19322eed9dd5a40de7d";
const string CLOUDFLARE_AUTH_TOKEN = "MkPwb3osbvgKuSWn8XR43dnk3vAs2VW-EgXZ_pek";
const string FB_PAGE_ID_FAMILY_ISLAND = "555233441009283";
const string FB_ACCESS_TOKEN =
    "EAANZBEY9KdLkBOZCDRYjSg7RqdTZC9f1i4uPI4RnKS0fFz26pw9c2huvOH6GuSFXQ9FZAPK"
    "ZBm832w5CaJkj8or93AJzZB9dnk"
    "WZCAAYBiWJUyXJJIuAZBIpZAsZCLDZB6f2KI3wcXN3nR14D0HVRL1jbLCrPsZCtkIXGAAbGQ"
    "LWZCndJqhcfk0Yb994fhDx980ZA3xlbw";

// Function Declarations
std::string image_to_base64(const std::string &image_path);
string generatePrompt(string prompt_input);
string generateImage(string prompt);
size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *output);
string post_to_fb(string generated_img, string page_id);
string get_date();
string generateImageFromImage(string img, string prompt);
void family_island();
void coin_tales();

#endif // HEADER_H
