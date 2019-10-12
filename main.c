/*
 Условие ИЗ№1:
 Создать структуру для хранения записей блога: названия, содержимого, тегов, комментариев к записи, ее оценок и даты.
 Составить с ее использованием программу поиска записей блога, набравших наибольшее количество комментариев и оценок
 в первый месяц после их публикации.
 */

#include "post.h"

int main() {
    post *posts = NULL;
    const post **popular_posts = NULL;
    printf("Введите количество постов\n");
    size_t array_size = input_number();
    bool success = create(&posts, array_size);
    if (success) {
        size_t popular_posts_size = 0;
        popular_posts = get_popular_posts(posts, array_size, &popular_posts_size);
        printf("Названия самых популярных постов\n");
        for (int i = 0; i < popular_posts_size; i++) {
            printf("%s", popular_posts[i]->name);
        }
        free(popular_posts);
    }
    delete_content(posts, array_size);
    return 0;
}
