//
// Created by poofik on 12.10.2019.
//
#include "post.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// функция создания массива постов через консольный ввод/вывод
bool create_posts_array(post **posts, size_t array_size) {
    if (!posts || array_size == 0) {
        return false;
    }
    post *posts_array = (post*)malloc(sizeof(post) * array_size);
    if (!posts_array)
        return false;
    *posts = posts_array;
    for (unsigned i = 0; i < array_size; i++) {
        bool success = create_post(&posts_array[i]);
        if (!success)
            return false;
    }
    return true;
}

// функция создания поста через консольный ввод/вывод
bool create_post(post *new_post_p) {
    new_post_p->name = NULL;
    new_post_p->content = NULL;
    new_post_p->comments = NULL;
    new_post_p->comments_count = 0;
    new_post_p->ratings = NULL;
    new_post_p->ratings_count = 0;
    new_post_p->tags = NULL;
    new_post_p->publication_date = NULL;

    printf("Введите название поста\n");
    char *string = input_string();
    if (!string)
        return false;
    new_post_p->name = string;

    printf("Введите содержание поста\n");
    string = input_string();
    if (!string)
        return false;
    new_post_p->content = string;

    printf("Введите теги\n");
    string = input_string();
    if (!string)
        return false;
    new_post_p->tags = string;

    printf("Введите дату публикации поста (формат: DD-MM-YYYY)\n");
    struct tm * date = input_date();
    if (!date) {
        return false;
    }
    new_post_p->publication_date = date;

    bool success = create_comments_array(&new_post_p->comments, &new_post_p->comments_count, new_post_p->publication_date);
    if (!success)
        return false;

    success = create_ratings_array(&new_post_p->ratings, &new_post_p->ratings_count, new_post_p->publication_date);
    if (!success)
        return false;

    return true;
}

bool create_comments_array(struct comment **array_p, size_t *array_size, const struct tm *publication_date_p) {
    if (!array_p || !array_size || !publication_date_p)
        return false;

    printf("Введите количество комментариев\n");
    *array_size = input_number();
    struct comment *comment_array = (struct comment *)malloc(sizeof(struct comment) * *array_size);
    *array_p = comment_array;
    for (unsigned i = 0; i < *array_size; i++) {
        printf("Введите комментарий\n");
        char *string = input_string();
        if (!string)
            return false;
        comment_array[i].content = string;
        int diff_time = -1;
        struct tm *date = NULL;
        while (diff_time < 0) {
            printf("Введите дату публикации комментария (формат: DD-MM-YYYY)\n");
            printf("Дата комментария не должна быть раньше даты публикации поста\n");
            date = input_date();
            if (!date) {
                return false;
            }
            diff_time = time_difference(date, publication_date_p);
            if (diff_time < 0)
                free(date);
        }
        comment_array[i].date = date;
    }
    return true;
}

bool create_ratings_array(struct rating **array_p, size_t *array_size, const struct tm *publication_date_p) {
    if (!array_p || !array_size || !publication_date_p)
        return false;

    printf("Введите количество оценок\n");
    *array_size = input_number();
    struct rating *ratings_array = (struct rating *)malloc(sizeof(struct rating) * *array_size);
    *array_p = ratings_array;
    for (unsigned i = 0; i < *array_size; i++) {
        int rank = -1;
        while(rank != 0 && rank != 1) {
            printf("Введите оценку (0 - dislike, 1 - like)\n");
            rank = input_number();
        }
        ratings_array[i].rank = rank;
        int diff_time = -1;
        struct tm *date = NULL;
        while (diff_time < 0) {
            printf("Введите дату выставления оценки (формат: DD-MM-YYYY)\n");
            printf("Дата оценки не должна быть раньше даты публикации поста\n");
            date = input_date();
            if (!date) {
                return false;
            }
            diff_time = time_difference(date, publication_date_p);
            if (diff_time < 0)
                free(date);
        }
        ratings_array[i].date = date;
    }
    return true;
}

// функция расчета разницы между двумя датами в днях
int time_difference(const struct tm *a, const struct tm *b) {
    int day_time_difference = 0;
    struct tm t1 = *a, t2 = *b;
    time_t time1 = mktime(&t1);
    time_t time2 = mktime(&t2);
    day_time_difference = (int)difftime(time1, time2) / SEC_IN_DAY;
    return day_time_difference;
}

/*
 * функция поиска популярных постов:
 * число постов зафиксировано в POPULAR_POSTS_COUNT
 * популярность расчитывается с учетом всех оценок(сумма + и -) и комментариев оставленных в первый месяц
 * популярность равна сумме актуальных оценок и комментариев
 * возвращается массив указателей на константные данные постов
 * */
const post** get_popular_posts(const post *posts, size_t array_size, size_t *return_array_size) {
    if (!posts || !return_array_size || array_size == 0)
        return NULL;
    const post **popular_posts = (const post **)malloc(sizeof(post *) * POPULAR_POSTS_COUNT);
    if (!popular_posts)
        return NULL;
    if (POPULAR_POSTS_COUNT >= array_size) {
        for (int i = 0; i < array_size; i++)
            popular_posts[i] = &posts[i];
        *return_array_size = array_size;
        return popular_posts;
    }
    *return_array_size = POPULAR_POSTS_COUNT;
    struct data *search_data = (struct data *)malloc(sizeof(struct data) * array_size);
    if (!search_data)
        return popular_posts;
    for (int i = 0; i < array_size; i++) {
        search_data[i].p_post = &posts[i];
        get_popularity(&search_data[i]);
    }
    for (int i = 0; i < POPULAR_POSTS_COUNT; i++) {
        struct data *max_data = &search_data[i];
        for (int j = i + 1; j < array_size; j++) {
            unsigned max_popularity = max_data->relevant_comments_count + max_data->relevant_ratings_count;
            unsigned current_popularity = search_data[j].relevant_comments_count + search_data[j].relevant_ratings_count;
            if (current_popularity > max_popularity)
                max_data = &search_data[j];
        }
        if (max_data != &search_data[i]) {
            struct data tmp = search_data[i];
            search_data[i] = *max_data;
            *max_data = tmp;
        }
        popular_posts[i] = search_data[i].p_post;
    }
    free(search_data);
    return popular_posts;
}

//функция расчета популярности для конкретного поста
bool get_popularity(struct data *post_with_content) {
    if (!post_with_content)
        return false;
    const post *tmp = post_with_content->p_post;
    int relevant_comments = 0;
    struct comment *tmp_comment = tmp->comments;
    for (int i = 0; i < tmp->comments_count; i++) {
        if (time_difference(tmp_comment[i].date, tmp->publication_date) <= 30)
            relevant_comments++;
    }
    post_with_content->relevant_comments_count = relevant_comments;
    int relevant_ratings = 0;
    struct rating *tmp_rating = tmp->ratings;
    for (int i = 0; i < tmp->ratings_count; i++) {
        if (time_difference(tmp_rating[i].date, tmp->publication_date) <= 30)
            relevant_ratings++;
    }
    post_with_content->relevant_ratings_count = relevant_ratings;
    return true;
}

void delete_posts(post *posts, size_t array_size) {
    if (!posts)
        return;
    for(unsigned i = 0; i < array_size; i++) {
        post *deleted_post = &posts[i];
        if (deleted_post->name)
            free(deleted_post->name);
        if (deleted_post->content)
            free(deleted_post->content);
        if (deleted_post->tags)
            free(deleted_post->tags);
        if (deleted_post->publication_date)
            free(deleted_post->publication_date);
        if (deleted_post->comments) {
            for (unsigned j = 0; j < deleted_post->comments_count; j++) {
                struct comment *deleted_comment = &deleted_post->comments[j];
                if (deleted_comment->content)
                    free(deleted_comment->content);
                if (deleted_comment->date)
                    free(deleted_comment->date);
            }
            free(deleted_post->comments);
        }
        if (deleted_post->ratings) {
            for (unsigned j = 0; j < deleted_post->ratings_count; j++) {
                struct rating *deleted_rating = &deleted_post->ratings[j];
                if (deleted_rating->date)
                    free(deleted_rating->date);
            }
            free(deleted_post->ratings);
        }
    }
    free(posts);
}


