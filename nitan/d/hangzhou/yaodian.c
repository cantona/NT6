// yaodian.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "胡慶餘堂");
        set("long", @LONG
這是一家明淨寬敞的藥堂，後牆上是一個大藥櫃。幾個夥計正忙
着爬上爬下地從小抽屜裏抓藥。藥櫃前擺着一張桌子，桌旁一位老者
正在為人把脈。他就是名醫胡慶餘。
    櫃枱上方高掛一個大牌子(paizi).
LONG);
        set("exits", ([
            "west"      : __DIR__"road14",
        ]));
        set("no_beg","1");
        set("objects", ([
            __DIR__"npc/huqingyu" : 1,
        ]));
        set("item_desc", ([
            "paizi" :
@TEXT
        本店提供下列服務:
    先給胡大夫五百兩黃金, 然後:
    改名:          name 新名
TEXT]));
        set("no_clean_up", 0);
	set("coor/x", 830);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
