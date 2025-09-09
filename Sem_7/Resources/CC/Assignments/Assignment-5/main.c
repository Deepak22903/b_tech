#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_TAGS 10
#define MAX_VALUES 10
#define MAX_VALUE_LENGTH 100

typedef struct {
    char tag[MAX_TAGS][20];
    char values[MAX_TAGS][MAX_VALUES][MAX_VALUE_LENGTH];
    int count[MAX_TAGS];
    int unique_tag_count;
} TagData;

void trim_whitespace(char *str) {
    int start = 0;
    while (isspace((unsigned char)str[start])) {
        start++;
    }

    if (start > 0) {
        int i = 0;
        while (str[start + i]) {
            str[i] = str[start + i];
            i++;
        }
        str[i] = '\0';
    }

    int end = strlen(str) - 1;
    while (end >= 0 && isspace((unsigned char)str[end])) {
        str[end] = '\0';
        end--;
    }
}

// Function to escape special characters for JSON
void escape_json(const char *src, char *dest) {
    while (*src) {
        if (*src == '\"' || *src == '\\') {
            *dest++ = '\\';
        }
        *dest++ = *src++;
    }
    *dest = '\0';
}

int find_tag_index(TagData *tag_data, const char *tag) {
    for (int i = 0; i < tag_data->unique_tag_count; i++) {
        if (strcmp(tag_data->tag[i], tag) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to parse HTML and write tag-data pairs into a JSON file
void parse_html_to_json(const char *html, const char *json_filename) {
    FILE *json_file = fopen(json_filename, "w");
    if (json_file == NULL) {
        printf("Failed to open the JSON file.\n");
        return;
    }

    TagData tag_data;
    tag_data.unique_tag_count = 0; 

    const char *ptr = html;
    char tag[100];
    char data[1000];
    int tag_index = 0;
    int data_index = 0;
    bool inside_tag = false;

    while (*ptr != '\0') {
        if (*ptr == '<') {
            inside_tag = true;
            tag_index = 0;
            ptr++;

            if (*ptr == '/') {
                while (*ptr != '>' && *ptr != '\0') {
                    ptr++;
                }
                if (*ptr == '>') {
                    ptr++; 
                }
                inside_tag = false;
                continue;
            }

            while (*ptr != '>' && *ptr != '\0' && !isspace(*ptr)) {
                tag[tag_index++] = *ptr;
                ptr++;
            }
            tag[tag_index] = '\0';

            while (*ptr != '>' && *ptr != '\0') {
                ptr++;
            }
            if (*ptr == '>') {
                ptr++; 
            }
            inside_tag = false;

            data_index = 0;
            while (*ptr != '<' && *ptr != '\0') {
                data[data_index++] = *ptr;
                ptr++;
            }
            data[data_index] = '\0';

            trim_whitespace(data);

            int tag_idx = find_tag_index(&tag_data, tag);
            if (tag_idx == -1) {
                if (tag_data.unique_tag_count < MAX_TAGS) {
                    strcpy(tag_data.tag[tag_data.unique_tag_count], tag);
                    tag_data.count[tag_data.unique_tag_count] = 0; // Initialize count
                    tag_idx = tag_data.unique_tag_count; // Get the index of the newly added tag
                    tag_data.unique_tag_count++;
                } else {
                    fprintf(stderr, "Exceeded maximum unique tags limit.\n");
                    break;
                }
            }

            if (strlen(data) > 0 && tag_idx != -1) {
                if (tag_data.count[tag_idx] < MAX_VALUES) {
                    strcpy(tag_data.values[tag_idx][tag_data.count[tag_idx]], data);
                    tag_data.count[tag_idx]++;
                } else {
                    fprintf(stderr, "Exceeded maximum values for tag %s.\n", tag);
                }
            }

        } else {
            ptr++;
        }
    }

    fprintf(json_file, "{\n");
    for (int i = 0; i < tag_data.unique_tag_count; i++) {
        fprintf(json_file, "  \"%s\": [\n", tag_data.tag[i]);
        for (int j = 0; j < tag_data.count[i]; j++) {
            char escaped_data[2000];
            escape_json(tag_data.values[i][j], escaped_data);
            fprintf(json_file, "    \"%s\"%s\n", escaped_data, (j < tag_data.count[i] - 1) ? "," : "");
        }
        fprintf(json_file, "  ]%s\n", (i < tag_data.unique_tag_count - 1) ? "," : "");
    }
    fprintf(json_file, "}\n");

    fclose(json_file);
    printf("HTML parsed and saved to %s\n", json_filename);
}

int main() {
    const char *html_data = "<html><head><title>Test Page</title></head>"
                            "<body><h1>Welcome!</h1><h1>Welcome!</h1><h1>Welcome!<p>This is a simple HTML parser in C.</p></body></html>";

    parse_html_to_json(html_data, "output.json");

    return 0;
}
