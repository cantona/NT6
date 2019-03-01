// hupaoquan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "虎跑泉");
        set("long", @LONG
只見泉水從沙巖中滲流而出，清澈見底。相傳有位名叫性空的和
尚深愛此山風景靈秀，便住了下來。後因水源奇缺，準備遷走。一夜，
夢神告訴他說“南岳衡山童子泉，當遣二虎移來。”第二天，果然看
見兩只老虎跑地作穴，湧出泉水，所以定名為“虎跑泉”。
LONG);
        set("exits", ([
            "east"    : __DIR__"road17",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 760);
	set("coor/y", -2110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}