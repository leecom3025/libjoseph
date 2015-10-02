#include <arpa/inet.h>

#define FREQ_LEVEL 12

struct freq_str {
  int32_t seq;
  int32_t id;
  int32_t time;
  int32_t last;
} freq_str;

struct jcpu {
	int32_t online;
	int32_t id;
	int32_t temp;
	int32_t util;
#if _PRODUCT == _hima
  struct freq_str freq_a[FREQ_LEVEL];
  char *stat_path;
  int32_t max_freq;
#endif
	int32_t freq;
} jcpu;

#if _PRODUCT == _hima
struct jfreq {
  struct freq_str freq[FREQ_LEVEL];
} jfreq;
#endif
/*
struct Jsocket {
	struct sockaddr_in si;
	size_t si_len;
	// struct sockaddr_rc sr;
	union {
		int socket;
		int client;
	};
	int port;
	int type;
	int role;
} Jsocket;*/
