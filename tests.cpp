#include "utils.c"

#include <gtest/gtest.h>

TEST(ParseLogs, No5xxError) {
    FILE* in = fopen("some_name.txt", "w+");
    char contents[] = 
        "burger.letters.com - - [01/Jul/1995:00:00:12 -0400] \"GET /images/NASA-logosmall.gif HTTP/1.0\" 304 0\n"
        "burger.letters.com - - [01/Jul/1995:00:00:12 -0400] \"GET /shuttle/countdown/video/livevideo.gif HTTP/1.0\" 200 0\n"
        "205.212.115.106 - - [01/Jul/1995:00:00:12 -0400] \"GET /shuttle/countdown/countdown.html HTTP/1.0\" 200 3985\n"
        "d104.aa.net - - [01/Jul/1995:00:00:13 -0400] \"GET /shuttle/countdown/ HTTP/1.0\" 200 3985\n"
        "129.94.144.152 - - [01/Jul/1995:00:00:13 -0400] \"GET / HTTP/1.0\" 200 7074\n";
    fprintf(in, contents);
    rewind(in);
    uint64_t count_5xx;
    uint64_t max_logs;
    char* argv[] = {"", "2", "some_name.txt"};
    
    solve(3, argv, &count_5xx, &max_logs);
    ASSERT_EQ(count_5xx, 0) << "Wrong number of count_5xx No5xxError";
    ASSERT_EQ(max_logs, 5) << "Wrong number of max_logs No5xxError";

    fclose(in);
    remove("some_name.txt");
}

TEST(ParseLogs, Include5xxError) {
    FILE* in = fopen("some_name.txt", "w+");
    char contents[] = 
        "tallyho.facs.bellcore.com - - [03/Jul/1995:09:07:05 -0400] \"GET /shuttle/missions/sts-71/images/KSC-95EC-0917.jpg HTTP/1.0\" 200 52491\n"
        "134.83.184.18 - - [03/Jul/1995:09:07:06 -0400] \"GET /shuttle/countdown/video/livevideo.gif HTTP/1.0\" 200 50073\n"
        "amherst-ts-12.nstn.ca - - [03/Jul/1995:09:07:06 -0400] \"GET /icons/blank.xbm HTTP/1.0\" 500 509\n"
        "ereapp.erenj.com - - [03/Jul/1995:09:07:08 -0400] \"GET /history/mercury/ma-9/ma-9-patch-small.gif HTTP/1.0\" 500 21214\n"
        "ereapp.erenj.com - - [03/Jul/1995:09:07:09 -0400] \"GET /history/apollo/images/APOLLO-logosmall.gif HTTP/1.0\" 200 1173\n";
    fprintf(in, contents);
    rewind(in);
    uint64_t count_5xx;
    uint64_t max_logs;
    char* argv[] = {"", "2", "some_name.txt"};
    
    solve(3, argv, &count_5xx, &max_logs);
    ASSERT_EQ(count_5xx, 2) << "Wrong number of count_5xx Include5xxError";
    ASSERT_EQ(max_logs, 3) << "Wrong number of max_logs Include5xxError";

    fclose(in);
    remove("some_name.txt");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}