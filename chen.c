/*
 * Copyright (c) 2017, Michel Martens <mail at soveran dot com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TEMP "mktemp /tmp/chen.XXXXXXXX"
#define LIST "ls -1 > %s"
#define EDIT "$EDITOR %s"

static void chomp(char *s) {
	s[strcspn(s, "\n")] = '\0';
}

static void run(char *fmt, char *str) {
	char cmd[255];
	sprintf(cmd, fmt, str);
	system(cmd);
}

static int line(char *l, FILE *fp) {
	if (fgets(l, 255, fp) == NULL) return 0;
	chomp(l);
	return 1;
}

static void tempfile(char *s) {
	FILE *output;

	output = popen(TEMP, "r");

	if (output == NULL) {
		printf("chen: Failed to run command\n" );
		exit(1);
	}

	fgets(s, 255, output);
	chomp(s);

	pclose(output);
}

int main(int argc, char **argv) {
	char old[255];
	char new[255];

	char old_name[255];
	char new_name[255];

	FILE *old_fp;
	FILE *new_fp;

	if (getenv("EDITOR") == NULL) {
		printf("chen: $EDITOR is not set\n");
		exit(1);
	}

	tempfile(old);
	tempfile(new);

	run(LIST, old);
	run(LIST, new);
	run(EDIT, new);

	old_fp = fopen(old, "r");

	if (old_fp == NULL) {
		printf("chen: Failed to open file %s\n", old);
		exit(1);
	}

	new_fp = fopen(new, "r");

	if (new_fp == NULL) {
		printf("chen: Failed to open file %s\n", new);
		exit(1);
	}

	while (line(old_name, old_fp) &&
		   line(new_name, new_fp)) {

		if (strcmp(old_name, new_name)) {
			printf("%s -> %s\n", old_name, new_name);
			rename(old_name, new_name);
		}
	}

	fclose(old_fp);
	fclose(new_fp);

	unlink(old);
	unlink(new);

	return 0;
}
