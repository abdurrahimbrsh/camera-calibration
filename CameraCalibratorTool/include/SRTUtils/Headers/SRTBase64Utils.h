#pragma once

//class to handle all base64 stuff...
class CSRTBase64Utils
{
private:
  int ErrorCode;
public:
  int GetLastError() {return ErrorCode;};
	CSRTBase64Utils();
	~CSRTBase64Utils();
  char* Decode(char *input, int *bufsize); //caller must free the result, bufsize holds the decoded length
  char* Encode(char *input, int bufsize); //caller must free the result, bufsize is the length of the input buffer
  
  unsigned char* Decode(unsigned char *input, int *bufsize); //caller must free the result, bufsize holds the decoded length
  unsigned char* Encode(unsigned char *input, int bufsize); //caller must free the result, bufsize is the length of the input buffer
};
