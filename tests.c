#include "tests.h"

struct tm date01012019 = {
        .tm_mday = 1,
        .tm_mon = 0,
        .tm_year = 119
};

struct tm date01022019 = {
        .tm_mday = 1,
        .tm_mon = 1,
        .tm_year = 119
};

struct tm date02012019 = {
        .tm_mday = 2,
        .tm_mon = 0,
        .tm_year = 119
};

struct tm date10102019 = {
        .tm_mday = 10,
        .tm_mon = 9,
        .tm_year = 119
};

struct tm date31012019 = {
        .tm_mday = 31,
        .tm_mon = 0,
        .tm_year = 119
};

struct comment comment1 = {
        .content = "some_content",
        .date = &date01012019
};

struct comment comment2 = {
        .content = "some_content",
        .date = &date01022019
};

struct comment comment3 = {
        .content = "some_content",
        .date = &date10102019
};

struct comment comment4 = {
        .content = "some_content",
        .date = &date31012019
};

struct comment comment5 = {
        .content = "some_content",
        .date = &date02012019
};

struct rating rating1 = {
        .rank = 1,
        .date = &date01012019
};

struct rating rating2 = {
        .rank = 1,
        .date = &date02012019
};

struct rating rating3 = {
        .rank = 0,
        .date = &date31012019
};

struct rating rating4 = {
        .rank = 0,
        .date = &date01022019
};

struct rating rating5 = {
        .rank = 1,
        .date = &date10102019
};

post test = {
        .name = "test",
        .content = "some content",
        .tags = "some tags",
        .publication_date = &date01012019
};

size_t com_size = 0;
size_t rating_size = 0;

bool initialize_test_bad_input1() {
    post_size = 1;
    test_array = (post *)malloc(sizeof(post) * post_size);
    if (!test_array)
        return false;
    *test_array = test;

    result_array = (post *)malloc(sizeof(post) * post_size);
    *result_array = test;

    return true;
}

bool initialize_test1() {
    post_size = 3;
    test_array = (post *)malloc(sizeof(post) * post_size);
    if (!test_array)
        return false;
    com_size = 5;
    struct comment *com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    com_array[0] = comment1;
    com_array[1] = comment5;
    com_array[2] = comment4;
    com_array[3] = comment1;
    com_array[4] = comment1;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 5;
    struct rating *ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    ratings_array[0] = rating1;
    ratings_array[1] = rating2;
    ratings_array[2] = rating3;
    ratings_array[3] = rating2;
    ratings_array[4] = rating3;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post1";
    test_array[2] = test; //post1 - популярность 10

    com_size = 3;
    com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    com_array[0] = comment1;
    com_array[1] = comment5;
    com_array[2] = comment4;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 3;
    ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    ratings_array[0] = rating1;
    ratings_array[1] = rating2;
    ratings_array[2] = rating3;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post2";
    test_array[1] = test; //post2 - популярность 6

    com_size = 0;
    com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 0;
    ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post3";
    test_array[0] = test; //post3 - популярность 0

    result_array = (post *)malloc(sizeof(post) * POPULAR_POSTS_COUNT);
    result_array[0] = test_array[2];
    result_array[1] = test_array[1];

    return true;
}

bool initialize_test2() {
    post_size = 3;
    test_array = (post *)malloc(sizeof(post) * post_size);
    if (!test_array)
        return false;
    com_size = 5;
    struct comment *com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    com_array[0] = comment1;
    com_array[1] = comment2;
    com_array[2] = comment2;
    com_array[3] = comment3;
    com_array[4] = comment3;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 5;
    struct rating *ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    ratings_array[0] = rating1;
    ratings_array[1] = rating2;
    ratings_array[2] = rating4;
    ratings_array[3] = rating5;
    ratings_array[4] = rating5;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post1";
    test_array[2] = test; //post1 - популярность 3

    com_size = 3;
    com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    com_array[0] = comment1;
    com_array[1] = comment5;
    com_array[2] = comment4;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 3;
    ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    ratings_array[0] = rating1;
    ratings_array[1] = rating2;
    ratings_array[2] = rating3;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post2";
    test_array[1] = test; //post2 - популярность 6

    com_size = 2;
    com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    com_array[0] = comment1;
    com_array[1] = comment4;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 4;
    ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    ratings_array[0] = rating1;
    ratings_array[1] = rating2;
    ratings_array[2] = rating3;
    ratings_array[3] = rating5;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post3";
    test_array[0] = test; //post3 - популярность 5

    result_array = (post *)malloc(sizeof(post) * POPULAR_POSTS_COUNT);
    result_array[0] = test_array[1];
    result_array[1] = test_array[0];

    return true;
}

bool initialize_test3() {
    post_size = 3;
    test_array = (post *)malloc(sizeof(post) * post_size);
    if (!test_array)
        return false;
    com_size = 5;
    struct comment *com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    com_array[0] = comment3;
    com_array[1] = comment3;
    com_array[2] = comment3;
    com_array[3] = comment2;
    com_array[4] = comment2;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 5;
    struct rating *ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    ratings_array[0] = rating4;
    ratings_array[1] = rating4;
    ratings_array[2] = rating4;
    ratings_array[3] = rating5;
    ratings_array[4] = rating5;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post1";
    test_array[2] = test; //post1 - популярность 0

    com_size = 1;
    com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    com_array[0] = comment1;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 3;
    ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    ratings_array[0] = rating1;
    ratings_array[1] = rating2;
    ratings_array[2] = rating3;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post2";
    test_array[1] = test; //post2 - популярность 4

    com_size = 0;
    com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 2;
    ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    ratings_array[0] = rating1;
    ratings_array[1] = rating2;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post3";
    test_array[0] = test; //post3 - популярность 2

    result_array = (post *)malloc(sizeof(post) * POPULAR_POSTS_COUNT);
    result_array[0] = test_array[1];
    result_array[1] = test_array[0];

    return true;
}

bool initialize_test4() {
    post_size = 3;
    test_array = (post *)malloc(sizeof(post) * post_size);
    if (!test_array)
        return false;
    com_size = 0;
    struct comment *com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 0;
    struct rating *ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post1";
    test_array[2] = test; //post1 - популярность 0

    com_size = 0;
    com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 0;
    ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post2";
    test_array[1] = test; //post2 - популярность 0

    com_size = 0;
    com_array = (struct comment *)malloc(sizeof(struct comment) * com_size);
    if (!com_array)
        return false;
    test.comments_count = com_size;
    test.comments = com_array;
    rating_size = 0;
    ratings_array = (struct rating *)malloc(sizeof(struct rating) * rating_size);
    if (!ratings_array)
        return false;
    test.ratings = ratings_array;
    test.ratings_count = rating_size;

    test.name = "post3";
    test_array[0] = test; //post3 - популярность 0

    result_array = (post *)malloc(sizeof(post) * POPULAR_POSTS_COUNT);
    result_array[0] = test_array[0];
    result_array[1] = test_array[1];

    return true;
}

void destruct_test() {
    if (test_array) {
        for (int i = 0; i < post_size; i++) {
            if (test_array[i].comments)
                free(test_array[i].comments);
            if (test_array[i].ratings)
                free(test_array[i].ratings);
        }
        free(test_array);
    }
    if (result_array)
        free(result_array);
}



