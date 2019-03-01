// Room: /d/xingxiu/xianrenya.c
// Last Modified by winder on Apr. 25 2001

inherit ROOM;

void create()
{
        set("short", "仙人崖");
        set("long", @LONG
這裡以傳說有神仙出沒而得名，每到盛夏夜，火光從崖面飛出，名
曰仙人送燈。面山帶水，群峰環峙，野草蒙茸，奇花異樹，清幽險峻，
令人絕俗。
LONG);
        set("outdoors", "silu");
        set("exits", ([
                "northwest" : __DIR__"shuiliandong",
                "northeast" : __DIR__"silk1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20000);
        set("coor/y", 300);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}

#include "/d/xingxiu/job2.h";