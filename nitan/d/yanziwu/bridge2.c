// Room: /d/yanziwu/bridge2.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "瀉玉橋");
        set("long", @LONG
蓮韻塘水從蔓陀峰中流而下，從瀉玉橋下流入太湖中。水流過此橋
下，流速甚快，濺起無數水花，如飛瓊落玉一般，伴隨著古琴流音般的
水響。站在橋上，看著橋心“瀉玉”二字，仿佛橋下流走的不是清水，
而是你無悔的年華。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"path11",
                "west"  : __DIR__"path16",
        ]));
        set("coor/x", 1230);
        set("coor/y", -1220);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}