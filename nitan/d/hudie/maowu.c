// 茅屋 maowu.c
 
#include <ansi.h>

inherit ROOM;

void create() 
{ 
        set("short", "茅屋");
        set("long", @LONG
這裏是一間簡陋的茅屋，正中擺放着一張木桌，周圍整齊地放着
幾張凳子，一個小童正坐在那裏打瞌睡，看到有人來了，趕忙熱情地
迎了上來。西面很安靜，東面一陣藥氣傳了過來，北面一道簾子，不
知道是什麼地方。
LONG );

        set("exits", ([
            "north" : __DIR__"caotang",
            "west" : __DIR__"xfang2",
            "south" : __DIR__"caojing",
            "east" : __DIR__"yaofang",
        ]));

        setup();
}