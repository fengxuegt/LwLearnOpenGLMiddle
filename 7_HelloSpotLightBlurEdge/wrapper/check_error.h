#pragma once
#ifdef DEBUG
#define GL_LW_CALL(func) func;checkError()
#else
#define GL_LW_CALL(func) func
#endif
void checkError();