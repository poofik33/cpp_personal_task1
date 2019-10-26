/*
 Условие ИЗ№1:
 Создать структуру для хранения записей блога: названия, содержимого, тегов,
 комментариев к записи, ее оценок и даты. Составить с ее использованием
 программу поиска записей блога, набравших наибольшее количество комментариев и
 оценок в первый месяц после их публикации.
 */

#include "post.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main() {
    post *posts = NULL;
    const post **popular_posts = NULL;
    printf("Введите количество постов\n");
    size_t array_size = input_number();
    bool success = create_posts_array(&posts, array_size);

    if (!success)
        return EXIT_FAILURE;

    size_t popular_posts_size = 0;
    popular_posts = get_popular_posts(posts, array_size, &popular_posts_size);
    printf("Названия самых популярных постов\n");
    for (int i = 0; i < popular_posts_size; i++) {
      printf("%s", popular_posts[i]->name);
    }
    free(popular_posts);

    delete_posts(posts, array_size);
    return EXIT_SUCCESS;
}
