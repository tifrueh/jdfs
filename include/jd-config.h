#ifndef JDCONF_H
#define JDCONF_H

#include <stdio.h>

#include "configuration.h"
#include "retval.h"

int jd_config(int argc, char* argv[], const struct conf_data* configuration);

#endif
