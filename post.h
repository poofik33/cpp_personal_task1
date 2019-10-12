//
// Created by poofik on 12.10.2019.
//

#ifndef PERSTASK1_POST_H
#define PERSTASK1_POST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define BUFFER_SIZE 512
#define CHUNK_SIZE 64
#define POPULAR_POSTS_COUNT 2

#define DATE__FORMAT_SIZE 10
#define DAY_FORMAT 2
#define MONTH_FORMAT 2
#define YEAR_FORMAT 4

#define MIN_DAY_VALUE 1
#define MAX_DAY_VALUE 31
#define MIN_MONTH_VALUE 1
#define MAX_MONTH_VALUE 12
#define MIN_YEAR_VALUE 1900

#define SEC_IN_DAY 86400

struct comment {
    char* content;
    struct tm *date;
};

struct rating {
    bool rank; // 0 - dislike, 1 - like
    struct tm *date;
};

struct blog_post {
    char *name;
    char *content;
    char *tags;
    struct comment *comments;
    unsigned comments_count;
    struct rating *ratings;
    unsigned ratings_count;
    struct tm *publication_date;
};

typedef struct blog_post post;

struct data {
    unsigned relevant_comments_count;
    unsigned relevant_ratings_count;
    const post *p_post;
};

bool create(post **posts, size_t array_size);
bool create_post(post **new_post_p);

int time_difference(const struct tm *a, const struct tm *b);

const post** get_popular_posts(const post *posts, size_t array_size, size_t *return_array_size);
bool get_popularity(struct data *post_with_content);

char* input_string();
struct tm * input_date();
int input_number();

void delete_content(post *posts, size_t array_size);

#endif //PERSTASK1_POST_H
