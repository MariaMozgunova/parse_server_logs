#define __STDC_FORMAT_MACROS 1
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#pragma once

const int DATE_LENGTH = 21;
const int LOG_LENGTH = 300;
uint64_t count_5xx = 0;

time_t time_since_the_epoch(char str_time[]) {
    int year, month, day, hour, min, sec;
    day = strtol(str_time, 0, 10);

    char smonth[4];
    strncpy(smonth, str_time + 3, 3);

    if (!strcmp(smonth, "Jan")) {month = 0;}
    if (!strcmp(smonth, "Feb")) {month = 1;}
    if (!strcmp(smonth, "Mar")) {month = 2;}
    if (!strcmp(smonth, "Apr")) {month = 3;}
    if (!strcmp(smonth, "May")) {month = 4;}
    if (!strcmp(smonth, "Jun")) {month = 5;}
    if (!strcmp(smonth, "Jul")) {month = 6;}
    if (!strcmp(smonth, "Aug")) {month = 7;}
    if (!strcmp(smonth, "Sep")) {month = 8;}
    if (!strcmp(smonth, "Oct")) {month = 9;}
    if (!strcmp(smonth, "Nov")) {month = 10;}
    if (!strcmp(smonth, "Dec")) {month = 11;}
    
    year = strtol(str_time + 7, 0, 10);
    hour = strtol(str_time + 12, 0, 10);
    min = strtol(str_time + 15, 0, 10);
    sec = strtol(str_time + 18, 0, 10);

    struct tm breakdown;
    breakdown.tm_year = year - 1900;
    breakdown.tm_mon = month;
    breakdown.tm_mday = day;
    breakdown.tm_hour = hour;
    breakdown.tm_min = min;
    breakdown.tm_sec = sec;

    time_t res = mktime(&breakdown);
    
    return res;
}

void getline(FILE * file, char line[], char date_str[], uint8_t is_end_file) {
    char c = '\0';

    if ((c = fgetc(file)) == EOF) {
        line[0] = '\0';
        return;
    }
    
    line[0] = c;
    int i = 1;
    int j = 0;
    uint8_t is_date = 0;
    uint8_t is_5xx = 0;

    while ((c = fgetc(file)) != '\n' && c != EOF) {
        line[i] = c;
        i++;

        if (i > 2 && c == '5' && line[i - 2] == ' ' && line[i - 3] == '"') {is_5xx = 1;}

        if (is_date && c == ' ') {is_date = 0;}

        if (is_date) {date_str[j] = c; j++;}

        if (c == '[') {is_date = 1;}

    }

    line[i] = '\0';
    date_str[j] = '\0';

    if (is_end_file && is_5xx) {
        printf("%s\n", line);
        count_5xx++;
    }
}

void solve(int argc, char* argv[], uint64_t* c5, uint64_t* ml) {
    time_t time_interval = atoi(argv[1]);

    const char* file_name = argv[2];
    FILE * start_date_file = fopen(file_name, "r");
    FILE * end_date_file = fopen(file_name, "r");

    uint64_t cur_logs = 0;
    uint64_t max_logs = 0;

    char end_date_line[LOG_LENGTH];
    char start_date_line[LOG_LENGTH];

    char end_date_str[DATE_LENGTH];
    char start_date_str[DATE_LENGTH];
    char buffer_date_str[DATE_LENGTH];

    char max_end_date_str[DATE_LENGTH];
    char max_start_date_str[DATE_LENGTH];
    
    getline(end_date_file, end_date_line, end_date_str, 1);
    getline(start_date_file, start_date_line, start_date_str, 0);

    while (end_date_line[0] != '\0') {
        time_t start_date = time_since_the_epoch(start_date_str);
        time_t end_date = time_since_the_epoch(end_date_str);
        time_t future_limit = start_date + time_interval;

        while (end_date_line[0] && end_date < future_limit) {
            strcpy(buffer_date_str, end_date_str);        
            getline(end_date_file, end_date_line, end_date_str, 1);
            end_date = time_since_the_epoch(end_date_str);
            cur_logs++;
        }
        
        if (cur_logs > max_logs) {
            max_logs = cur_logs;
            strcpy(max_start_date_str, start_date_str);
            strcpy(max_end_date_str, buffer_date_str);
        }

        strcpy(buffer_date_str, start_date_str);        

        while (end_date_line[0] && !strcmp(buffer_date_str, start_date_str)) {
            getline(start_date_file, start_date_line, start_date_str, 0);
            cur_logs--;
        }
    }
    
    printf("# of logs with 5xx status: %" PRIu64 "\n", count_5xx);
    printf(
        "The maximum number of request (%" PRIu64 ") was between %s and %s\n",
        max_logs,
        max_start_date_str,
        max_end_date_str
    );

    *c5 = count_5xx;
    *ml = max_logs;
}

