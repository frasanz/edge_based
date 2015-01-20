/*
 * =====================================================================================
 *
 *       Filename:  helper.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/01/15 18:18:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __HELPER_H_
#define __HELPER_H_

#include <string.h>
#include <strings.h>
#include <stdbool.h>


#ifndef STRNCASECMP
#define STRNCASECMP strncasecmp
#endif

  inline int stringRemoveDelimiter(char delimiter, const char * string){
    int string_start=0;

    while (string[string_start] == delimiter){
      string_start++;
    }

    if(string_start >= (int)strlen(string)-1){
      return 0;
    }
    return string_start;
  }

  inline bool checkCmdLineFlag(const int argc, const char **argv, 
                               const char *string_ref){

    int i;
    bool bFound = false;

    if(argc >=1){
      for(i=1; i< argc; i++){
        int string_start = stringRemoveDelimiter('-', argv[i]);
        const char *string_argv = &argv[i][string_start];

        const char *equal_pos = strchr(string_argv, '=');
        int argv_length = (int)(equal_pos == 0 ? strlen(string_argv) :
          equal_pos - string_argv);

        int length = (int)strlen(string_ref);

        if (length == argv_length &&
            !STRNCASECMP(string_argv, string_ref, length)){
          bFound = true;
          continue;
      }
    }
  }
  return bFound;
}

#endif

