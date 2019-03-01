inherit ROOM;

#include "langqun.h"

void create()
{
        set("short", "小徑");
        set("long", @LONG
這條道路不知已有多少年無人行走，有些地方長草比人還
高，有些地方又全被沙堆阻塞，四下如死一般的寂靜，只有風
吹過草梢的沙沙之聲。偶爾一兩聲狼嚎隨著腥風飄至耳際。
LONG);
        set("exits", ([ 
                "south" : __DIR__"bridge2",
                "north" : __DIR__"shibi",
        ]));

        set("quarrys", ([
                "lang2" : 200000,
                "lang"  : 100000,
        ]));

        setup();
}