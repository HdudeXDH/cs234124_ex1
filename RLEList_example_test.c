#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RLEList.h"
#include "tests/test_utilities.h"

typedef bool (*testFunc)(void);

bool basicTest();
bool basicTest2();

#define TESTS_NAMES             \
    X(basicTest)                \
    X(basicTest2)                \

testFunc tests[] = {
#define X(name) name,
    TESTS_NAMES
#undef X
};

const char *tests_names[] = {
#define X(name) #name,
    TESTS_NAMES
#undef X
};

static int number_of_tests = sizeof(tests) / sizeof(tests[0]);

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        for (int test_idx = 0; test_idx < number_of_tests; test_idx++)
        {
            RUN_TEST(tests[test_idx], tests_names[test_idx]);
        }
        return 0;
    }
    if (argc != 2)
    {
        fprintf(stdout, "Usage: tests <test index>\n");
        return 0;
    }

    int test_idx = strtol(argv[1], NULL, 10);
    if (test_idx < 1 || test_idx > number_of_tests)
    {
        fprintf(stderr, "Invalid test index %d\n", test_idx);
        return 0;
    }

    RUN_TEST(tests[test_idx - 1], tests_names[test_idx - 1]);
    return 0;
}

bool basicTest(){
    RLEList list = RLEListCreate();
    bool result=true;
    ASSERT_TEST(list != NULL, destroy);

    //adding elements to the list
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // a
    ASSERT_TEST(RLEListAppend(list, 'c') == RLE_LIST_SUCCESS, destroy);    // ac
    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // acb
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acba
    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // acbab
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acbaba
    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // acbabab
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acbababa
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acbababaa
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acbababaaa

    ASSERT_TEST(RLEListRemove(list, 1) == RLE_LIST_SUCCESS, destroy); // abababaaa

    // check if the represented string is "abababaaa"
    const char *s = "abababaaa";
    char it;
    for(int i=0; i<RLEListSize(list); i++)
    {
        it=RLEListGet(list, i, NULL);
        ASSERT_TEST(it == s[i++], destroy);
    }
    //check if the length's are equal
    ASSERT_TEST(RLEListSize(list)==strlen(s), destroy);
    
    destroy:
    RLEListDestroy(list);
    return result;
}

bool basicTest2(){
    RLEList list = RLEListCreate();
    bool result=true;
    ASSERT_TEST(list != NULL, destroy);
    ASSERT_TEST(RLEListSize(list) == 0, destroy);
    RLEListResult func_result;
    //adding elements to the list
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // a
    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // ac
    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // acb
    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // acba
    ASSERT_TEST(RLEListSize(list) == 4, destroy);

    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // acbab
    ASSERT_TEST(RLEListAppend(list, 'c') == RLE_LIST_SUCCESS, destroy);    // acbab

    ASSERT_TEST(RLEListGet(list, 5, &func_result) == 'c', destroy);    // acbab
    ASSERT_TEST(func_result == RLE_LIST_SUCCESS, destroy);    // acbab
    ASSERT_TEST(RLEListGet(list, 6, &func_result) == 0, destroy);    // acbab
    ASSERT_TEST(func_result == RLE_LIST_INDEX_OUT_OF_BOUNDS, destroy);    // acbab
    ASSERT_TEST(RLEListGet(NULL, 6, &func_result) == 0, destroy);    // acbab
    ASSERT_TEST(func_result == RLE_LIST_NULL_ARGUMENT, destroy);    // acbab

    ASSERT_TEST(RLEListRemove(list, 1) == RLE_LIST_SUCCESS, destroy);
    ASSERT_TEST(RLEListRemove(list, 8) == RLE_LIST_INDEX_OUT_OF_BOUNDS, destroy);
    ASSERT_TEST(RLEListRemove(list, 4) == RLE_LIST_SUCCESS, destroy);
    ASSERT_TEST(RLEListAppend(NULL, 'A') == RLE_LIST_NULL_ARGUMENT, destroy);
    ASSERT_TEST(RLEListAppend(list, '\0') == RLE_LIST_NULL_ARGUMENT, destroy);
    ASSERT_TEST(RLEListExportToString(NULL, NULL) == NULL, destroy);


    const char *s = "abbb";
    const char *test_string = "a1\nb3\n";
    ASSERT_TEST(strcmp(RLEListExportToString(list,NULL), test_string)==0, destroy);
    char it;
    for(int i=0; i<RLEListSize(list); i++)
    {
        it=RLEListGet(list, i, NULL);
        ASSERT_TEST(it == s[i++], destroy);
    }
    //check if the length's are equal
    ASSERT_TEST(RLEListSize(list)==strlen(s), destroy);

    destroy:
    RLEListDestroy(list);
    return result;
}