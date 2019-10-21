//
// Created by poofik on 12.10.2019.
//

#ifndef PERSTASK1_POST_H
#define PERSTASK1_POST_H

#include <stdbool.h>
#include <time.h>

#define POPULAR_POSTS_COUNT 2

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

bool create_posts_array(post **posts, size_t array_size);
bool create_post(post *new_post_p);
bool create_comments_array(struct comment **array_p, size_t *array_size, const struct tm *publication_date_p);
bool create_ratings_array(struct rating **array_p, size_t *array_size, const struct tm *publication_date_p);


int time_difference(const struct tm *a, const struct tm *b);

const post** get_popular_posts(const post *posts, size_t array_size, size_t *return_array_size);
bool get_popularity(struct data *post_with_content);

void delete_posts(post *posts, size_t array_size);

#endif //PERSTASK1_POST_H
