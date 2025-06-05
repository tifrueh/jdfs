// Copyright (C) 2024 Timo Früh
// See main.c for the full notice.

#include "path.h"

struct jd_path parse_jd_path(const char path_descriptor[]) {
    struct jd_path retval = {-1, -1, -1};

    int descriptor_length = strlen(path_descriptor);

    if (descriptor_length < 1 || descriptor_length > 5) {
        return retval;
    }

    if (descriptor_length == 1 && isdigit(path_descriptor[0]) != 0) {
        retval.area = path_descriptor[0] - '0';
    }

    if (descriptor_length == 2 && isdigit(path_descriptor[1]) != 0) {
        retval.area = path_descriptor[0] - '0';
        retval.category = path_descriptor[1] - '0';
    }

    if (
            descriptor_length == 5 &&
            path_descriptor[2] == '.' &&
            isdigit(path_descriptor[3]) != 0 &&
            isdigit(path_descriptor[4]) != 0)
    {
        retval.area = path_descriptor[0] - '0';
        retval.category = path_descriptor[1] - '0';
        retval.id = atoi(path_descriptor + 3);
    }

    return retval;
};

int get_fs_path(char* fs_path, int fs_path_bufsize, const struct jd_path jd_path, const char jdfs_root[]) {

    if (jdfs_root == NULL || strcmp(jdfs_root, "") == 0) {

        snprintf(error_str, ERROR_STR_BUFSIZE, "%s", E_NO_JDFS_ROOT);
        return ERROR;
    }

    if (jd_path.area == -1) {
        snprintf(error_str, ERROR_STR_BUFSIZE, "invalid jd path descriptor");
        return INPUT_ERROR;
    }

    DIR* dir = opendir(jdfs_root);

    enum return_value retval = NOT_FOUND;
    char area_name[MAX_FNLEN] = "";

    if (dir == NULL) {
        snprintf(error_str, ERROR_STR_BUFSIZE, "error opening directory %s: %s", jdfs_root, strerror(errno));
        return ERROR;
    }

    struct dirent* dp;
    while ((dp = readdir(dir)) != NULL) {

        if (strlen(dp->d_name) > 0 && dp->d_name[0] == jd_path.area + '0') {
            snprintf(area_name, MAX_FNLEN, "%s", dp->d_name);
            snprintf(fs_path, fs_path_bufsize, "%s/%s", jdfs_root, area_name);
            retval = SUCCESS;
            break;
        }

    }

    if (retval != SUCCESS) {
        snprintf(error_str, ERROR_STR_BUFSIZE, "unable to find area %i", jd_path.area);
        goto exit_get_fs_path;
    }

    if (jd_path.category == -1) {
        goto exit_get_fs_path;
    }

    closedir(dir);
    dir = opendir(fs_path);
    retval = NOT_FOUND;
    char category_name[MAX_FNLEN] = "";

    if (dir == NULL) {
        snprintf(error_str, ERROR_STR_BUFSIZE, "error opening directory %s: %s", jdfs_root, strerror(errno));
        retval = ERROR;
        goto exit_get_fs_path;
    }

    while ((dp = readdir(dir)) != NULL) {

        if (strlen(dp->d_name) > 1 && dp->d_name[1] == jd_path.category + '0') {
            snprintf(category_name, MAX_FNLEN, "%s", dp->d_name);
            snprintf(fs_path, fs_path_bufsize, "%s/%s/%s", jdfs_root, area_name, category_name);
            retval = SUCCESS;
            break;
        }
    }

    if (retval != SUCCESS) {
        snprintf(error_str, ERROR_STR_BUFSIZE, "unable to find category %i%i", jd_path.area, jd_path.category);
        goto exit_get_fs_path;
    }

    if (jd_path.id == -1) {
        goto exit_get_fs_path;
    }

    closedir(dir);
    dir = opendir(fs_path);
    retval = NOT_FOUND;
    char id_name[MAX_FNLEN] = "";

    if (dir == NULL) {
        snprintf(error_str, ERROR_STR_BUFSIZE, "error opening directory %s: %s", jdfs_root, strerror(errno));
        retval = ERROR;
        goto exit_get_fs_path;
    }

    while ((dp = readdir(dir)) != NULL) {

        if (dp->d_name[2] != '.') {
            continue;
        }

        char id_chars[2] = { (jd_path.id / 10) + '0', (jd_path.id % 10) + '0' };

        if (dp->d_name[3] == id_chars[0] && dp->d_name[4] == id_chars[1]) {
            snprintf(id_name, MAX_FNLEN, "%s", dp->d_name);
            snprintf(fs_path, fs_path_bufsize, "%s/%s/%s/%s", jdfs_root, area_name, category_name, id_name);
            retval = SUCCESS;
            break;
        }

    }

    if (retval != SUCCESS) {
        snprintf(error_str, ERROR_STR_BUFSIZE, "unable to find id %i%i.%.2i", jd_path.area, jd_path.category, jd_path.id);
        goto exit_get_fs_path;
    }

    exit_get_fs_path:
    closedir(dir);
    return retval;
};
