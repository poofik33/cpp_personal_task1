//
// Created by poofik on 12.10.2019.
//
#include "post.h"

// функция создания массива постов через консольный ввод/вывод
bool create(post **posts, size_t array_size) {
    if (!posts) {
        return false;
    }
    *posts = (post*)malloc(sizeof(post) * array_size);
    post *posts_array = *posts;
    if (!posts_array)
        return false;
    for (unsigned i = 0; i < array_size; i++) {
        post *new_post = NULL;
        bool success = create_post(&new_post);
        if (!success)
            return false;
        memcpy(&posts_array[i], new_post, sizeof(post));
        free(new_post);
    }
    return true;
}

// функция создания поста через консольный ввод/вывод
bool create_post(post **new_post_p) {
    if (!new_post_p) {
        return false;
    }
    *new_post_p = (post*)malloc(sizeof(post));
    post *new_post = *new_post_p;
    if (!new_post) {
        return false;
    }
    new_post->name = NULL;
    new_post->content = NULL;
    new_post->comments = NULL;
    new_post->comments_count = 0;
    new_post->ratings = NULL;
    new_post->ratings_count = 0;
    new_post->tags = NULL;
    new_post->publication_date = NULL;
    printf("Введите название поста\n");
    char *string = input_string();
    if (!string)
        return false;
    new_post->name = string;
    printf("Введите содержание поста\n");
    string = input_string();
    if (!string)
        return false;
    new_post->content = string;
    printf("Введите теги\n");
    string = input_string();
    if (!string)
        return false;
    new_post->tags = string;
    printf("Введите дату публикации поста (формат: DD-MM-YYYY)\n");
    struct tm * date = input_date();
    if (!date) {
        return false;
    }
    new_post->publication_date = date;
    printf("Введите количество комментариев\n");
    size_t tmp = input_number();
    new_post->comments_count = tmp;
    struct comment *comment_array = (struct comment *)malloc(sizeof(struct comment) * tmp);
    new_post->comments = comment_array;
    for (unsigned i = 0; i < tmp; i++) {
        printf("Введите комментарий\n");
        string = input_string();
        if (!string)
            return false;
        comment_array[i].content = string;
        int diff_time = -1;
        while (diff_time < 0) {
            printf("Введите дату публикации комментария (формат: DD-MM-YYYY)\n");
            printf("Дата комментария не должна быть раньше даты публикации поста\n");
            date = input_date();
            if (!date) {
                return false;
            }
            diff_time = time_difference(date, new_post->publication_date);
            if (diff_time < 0)
                free(date);
        }
        comment_array[i].date = date;
    }

    printf("Введите количество оценок\n");
    tmp = input_number();
    new_post->ratings_count = tmp;
    struct rating *ratings_array = (struct rating *)malloc(sizeof(struct rating) * tmp);
    new_post->ratings = ratings_array;
    for (unsigned i = 0; i < tmp; i++) {
        int rank = -1;
        while(rank != 0 && rank != 1) {
            printf("Введите оценку (0 - dislike, 1 - like)\n");
            rank = input_number();
        }
        ratings_array[i].rank = rank;
        int diff_time = -1;
        while (diff_time < 0) {
            printf("Введите дату выставления оценки (формат: DD-MM-YYYY)\n");
            printf("Дата оценки не должна быть раньше даты публикации поста\n");
            date = input_date();
            if (!date) {
                return false;
            }
            diff_time = time_difference(date, new_post->publication_date);
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
    if (!posts || !return_array_size)
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

char* input_string() {
    int buffer_capacity = BUFFER_SIZE;
    char *buffer = (char *)malloc(sizeof(char) * buffer_capacity);
    if (!buffer)
        return NULL;
    char *chunk = (char *)malloc(sizeof(char) * CHUNK_SIZE);
    if (!chunk) {
        free(buffer);
        return NULL;
    }
    char *buffer_p = buffer;
    unsigned int buffer_real_size = 0;
    unsigned int chunk_size = 1;
    chunk[0] = '\0';
    while(chunk[chunk_size - 1] != '\n' && fgets(chunk, CHUNK_SIZE, stdin)) {
        chunk_size = strlen(chunk);
        if (buffer_real_size + chunk_size >= buffer_capacity) {
            buffer_capacity *= 2;
            char *new_buffer_p = (char *)realloc(buffer ,sizeof(char) * buffer_capacity);
            if(!new_buffer_p) {
                free(chunk);
                free(buffer);
                return NULL;
            }
            buffer = new_buffer_p;
            buffer_p = buffer + buffer_real_size;
        }
        buffer_real_size += chunk_size;
        memcpy(buffer_p, chunk, chunk_size);
        buffer_p += chunk_size;
    }
    free(chunk);
    char *new_string = (char *)realloc(buffer, sizeof(char) * (buffer_real_size + 1));
    if (!new_string) {
        free(buffer);
        return 0;
    }
    if (!buffer_real_size)
        new_string[buffer_real_size] = '\n';
    else
        new_string[buffer_real_size] = '\0';
    return new_string;
}

struct tm * input_date() {
    char* date_string_p = NULL;
    char* tmp = input_string();
    if (!tmp)
        return NULL;
    date_string_p = (char *)realloc(tmp, sizeof(char) * DATE__FORMAT_SIZE + 1);
    date_string_p[DATE__FORMAT_SIZE] = '\0';
    if(strlen(date_string_p) != DATE__FORMAT_SIZE) {
        free(date_string_p);
        return NULL;
    }
    tmp = date_string_p;
    bool correct_date_input = 1;
    char* str_int = (char *)malloc(sizeof(char) * (DAY_FORMAT + 1));
    if (!str_int) {
        free(date_string_p);
        return NULL;
    }
    memcpy(str_int, tmp, 2);
    str_int[DAY_FORMAT] = '\0';
    int day = atoi(str_int);
    correct_date_input = correct_date_input && (day <= MAX_DAY_VALUE || day >= MIN_DAY_VALUE);
    tmp += DAY_FORMAT + 1;
    memcpy(str_int, tmp, 2);
    str_int[MONTH_FORMAT] = '\0';
    int month = atoi(str_int);
    correct_date_input = correct_date_input && (month <= MAX_MONTH_VALUE || month >= MIN_MONTH_VALUE);
    tmp += MONTH_FORMAT + 1;
    char* str_year = realloc(str_int, sizeof(char) * (YEAR_FORMAT + 1));
    if (!str_year) {
        free(date_string_p);
        free(str_int);
        return NULL;
    }
    str_int = str_year;
    memcpy(str_int, tmp, 4);
    str_int[YEAR_FORMAT] = '\0';
    int year = atoi(str_int);
    correct_date_input = correct_date_input && (year >= MIN_YEAR_VALUE);
    if (!correct_date_input) {
        free(str_int);
        free(date_string_p);
        return NULL;
    }
    struct tm *date = (struct tm *)malloc(sizeof(struct tm));
    if (!date) {
        free(str_int);
        free(date_string_p);
        return NULL;
    }
    struct tm tmp_date = {
            .tm_year = year - 1900,
            .tm_mon = month - 1,
            .tm_mday = day
    };
    *date = tmp_date;
    free(str_int);
    free(date_string_p);
    return date;
}

int input_number() {
    char* string = input_string();
    char *end;
    if (!string)
        return 0;
    int return_number = strtol(string, &end, 0);
    free(string);
    return return_number;
}

void delete_content(post *posts, size_t array_size) {
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


