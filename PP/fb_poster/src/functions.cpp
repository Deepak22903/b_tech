#include "../include/header.h"
#include <cstddef>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

string get_date() {
  auto now = chrono::system_clock::now();
  time_t now_time = chrono::system_clock::to_time_t(now);
  tm local_time = *localtime(&now_time);
  ostringstream oss;
  oss << put_time(&local_time, "%B %d,%Y");
  string date = oss.str();
  return date;
}

// Callback function to store response
size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                     string *output) {
  size_t totalSize = size * nmemb;
  output->append((char *)contents, totalSize);
  return totalSize;
}

string generatePrompt() {
  CURL *curl = curl_easy_init();
  if (!curl) {
    cerr << "Failed to initialize cURL" << endl;
    return "";
  }

  string response_data;

  // Cloudflare API endpoint
  string url = "https://api.cloudflare.com/client/v4/accounts/" +
               CLOUDFLARE_ACCOUNT_ID +
               "/ai/run/@cf/meta/llama-3.1-70b-instruct";

  // Bearer token for authentication
  string auth_header = "Authorization: Bearer " + CLOUDFLARE_AUTH_TOKEN;

  // JSON payload
  json payload = {
      {"messages",
       {{{"role", "system"}, {"content", "You are a friendly assistant"}},
        {{"role", "user"},
         {"content",
          "Suggest a single prompt, don't output anything other than the "
          "prompt. The prompt will be given to a text-to-image generation AI. "
          "dont include and single or double quotes in the response "
          "The image is about Family Island game and free energy, which is an "
          "item inside the game. Here is some context about the game: "
          "Immerse yourself in an unforgettable world of adventure with a "
          "modern "
          "Stone Age family! Imagine what your life would be without modern "
          "technology—what would you do? Perhaps you would explore "
          "territories, build houses or even entire villages; farm, harvest, "
          "or maybe you would conquer new lands. You have an opportunity to "
          "be on a desert island together with the heroes of the Family "
          "Island game and try yourself in different roles: farmer, cook, "
          "explorer, trader, and many others."
          "Interested? Here are some more features of our game:"
          "★ Explore wild territories, solve puzzles, find hidden objects, and "
          "embark on thrilling adventures."
          "★ Build and improve your little city in the middle of the ocean."
          "★ Start your own family farm! Harvest, grow crops, and craft useful "
          "goods to trade with others."
          "★ Cook healthy and tasty food using ingredients found on the "
          "island."
          "★ Customize your village with beautiful decorations! Choose flowers "
          "and plants to match the unique landscapes."
          "★ Meet unusual animals: island hamsters, wild goats, and even a "
          "dinosaur are waiting for you!"
          "★ Help a family survive on a desert island."
          "And that is not all! Family Island is a farm game full of "
          "unexpected twists and captivating adventures!"}}}}};
  string jsonData = payload.dump();

  // Set cURL options
  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "Content-Type: application/json");
  headers = curl_slist_append(headers, auth_header.c_str());

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_POST, 1L);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
  curl_easy_setopt(curl, CURLOPT_CAINFO, "/etc/ssl/certs/ca-certificates.crt");

  // Perform request
  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    cerr << "cURL request failed: " << curl_easy_strerror(res) << endl;
  } else {
    try {
      // Parse JSON response
      json jsonResponse = json::parse(response_data);

      // Extract the "response" field
      if (jsonResponse.contains("result") &&
          jsonResponse["result"].contains("response")) {
        string extracted_response =
            jsonResponse["result"]["response"].get<string>();
        // Remove surrounding quotes if they exist
        if (!extracted_response.empty() && extracted_response.front() == '"' &&
            extracted_response.back() == '"') {
          extracted_response =
              extracted_response.substr(1, extracted_response.size() - 2);
        }
        return extracted_response;
      } else {
        cout << "Response field not found in JSON!" << endl;
        cout << jsonResponse << endl;
      }
    } catch (json::parse_error &e) {
      cerr << "JSON parsing error: " << e.what() << endl;
    }
  }

  // Cleanup
  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);
  return "";
}

string generateImage(string prompt) {
  CURL *curl = curl_easy_init();
  string response_data;
  if (!curl)
    cerr << "Failed to initialize cURL" << endl;

  string url = "https://api.cloudflare.com/client/v4/accounts/" +
               CLOUDFLARE_ACCOUNT_ID +
               "/ai/run/@cf/black-forest-labs/flux-1-schnell";

  string auth_hdr = "Authorization: Bearer " + CLOUDFLARE_AUTH_TOKEN;

  string content_type_header = "Content-Type: application/json";

  prompt = "{ \"prompt\": \"" + prompt + "\" }";

  struct curl_slist *headers = NULL;

  headers = curl_slist_append(headers, content_type_header.c_str());
  headers = curl_slist_append(headers, auth_hdr.c_str());

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_POST, 1L);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, prompt.c_str());
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

  CURLcode res = curl_easy_perform(curl);
  string extracted_image;
  if (res != CURLE_OK)
    cerr << "cURL request failed: " << curl_easy_strerror(res) << endl;
  else {

    try {
      // Parse JSON response
      json jsonResponse = json::parse(response_data);

      // Extract the "response" field
      if (jsonResponse.contains("result") &&
          jsonResponse["result"].contains("image")) {
        extracted_image = jsonResponse["result"]["image"].get<string>();
        // Remove surrounding quotes if they exist
        if (!extracted_image.empty() && extracted_image.front() == '"' &&
            extracted_image.back() == '"') {
          extracted_image =
              extracted_image.substr(1, extracted_image.size() - 2);
        }
      } else {
        cout << "Response field not found in JSON!" << endl;
        cout << jsonResponse << endl;
      }
    } catch (json::parse_error &e) {
      cerr << "JSON parsing error: " << e.what() << endl;
    }
  }
  curl_easy_cleanup(curl);
  curl_slist_free_all(headers);

  vector<unsigned char> decoded = base64_rfc4648::decode(extracted_image);
  std::string baseName = "./output/result";
  std::string extension = ".jpg";
  int count = 1;

  // Find the next available filename
  std::string filename;
  do {
    std::ostringstream oss;
    oss << baseName << count << extension;
    filename = oss.str();
    count++;
  } while (std::filesystem::exists(filename));

  if (!decoded.empty()) {
    ofstream file(filename, ios::binary);
    file.write(reinterpret_cast<const char *>(decoded.data()), decoded.size());
  } else {
    cerr << "Failed to decode Base64" << endl;
  }
  return filename;
}

string post_to_fb(string generated_img) {
  CURL *curl = curl_easy_init();
  if (!curl) {
    cerr << "Failed to initialize cURL" << endl;
    return "";
  }

  string date = "(" + get_date() + ")";
  string response_data;
  string url = "https://graph.facebook.com/v22.0/" + FB_PAGE_ID + "/photos";
  string caption =
      "Family Island Free Energy ⚡🎁\n" + date + "\nhttps://gogl.to/3GEF ✅";

  curl_mime *form = curl_mime_init(curl);
  curl_mimepart *field;

  // Add access token - FIXED: Don't include "access_token=" prefix
  field = curl_mime_addpart(form);
  curl_mime_name(field, "access_token");
  curl_mime_data(field, FB_ACCESS_TOKEN.c_str(), CURL_ZERO_TERMINATED);

  // Add image file
  field = curl_mime_addpart(form);
  curl_mime_name(field, "source");
  curl_mime_filedata(field, generated_img.c_str());

  // Add caption
  field = curl_mime_addpart(form);
  curl_mime_name(field, "caption");
  curl_mime_data(field, caption.c_str(), CURL_ZERO_TERMINATED);

  // Set up the request
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

  string post_id;
  CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK) {
    cerr << "cURL request failed: " << curl_easy_strerror(res) << endl;
  } else {
    try {
      json jsonData = json::parse(response_data);
      if (jsonData.contains("id")) { // Changed from "post_id" to "id"
        post_id = jsonData["id"];
      } else if (jsonData.contains("error")) {
        cerr << "Facebook API error: " << jsonData["error"]["message"] << endl;
      }
    } catch (json::parse_error &e) {
      cerr << "JSON parsing error: " << e.what() << endl;
    }
  }

  curl_mime_free(form);
  curl_easy_cleanup(curl);
  return post_id;
}
