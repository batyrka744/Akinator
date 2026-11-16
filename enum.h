#pragma once

enum errors {ERR_OK = 0, ERR_NULL_PTR = 1, ERR_NULL_DATA = 2,
             ERR_WRONG_CAPACITY = 3, ERR_WRONG_SIZE = 4,
             ERR_OVERFLOW = 5, ERR_NO_MEMORY = 6, ERR_ARR_CANARY = 7, ERR_STK_CANARY = 8,
             ERR_NO_PARENT = 9}; 

const char* ErrCode(errors err); 