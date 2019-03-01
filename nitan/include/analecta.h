// analecta.h

#ifndef ANALECTA_D
#define ANALECTA_D      "/adm/daemons/analectad"
#endif

//#define ANALECTA_DIR            DATA_DIR + "analecta/"
#define ANALECTA_DIR            DATA_DIR + "wenxuan/"
#define HEAD_LINES              8
#define MAX_CONTENT_LINES       4000

// 文選排序
int sort_analectas(mapping a1, mapping a2) { return (a1["add_time"] - a2["add_time"]); }

// 篩選文選
int filter_analectas(mapping analecta, int time) { return (analecta["add_time"] > time); }

