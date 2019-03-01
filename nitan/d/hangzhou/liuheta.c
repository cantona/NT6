// liuheta.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "六和塔底");
        set("long", @LONG
爬上月輪山，便來到了六和塔之前。六和塔亦名六合塔，“六和”
之名來之佛家的六種規約，“六合”就是“天，地，四方”的意思。
這座八角塔有十三層，在它的飛檐翹角上括有一百零四隻大鐵鈴。
LONG);
        set("outdoors", "xihu");
        set("exits", ([
            "eastdown" : __DIR__"qiantang",
            "enter"    : __DIR__"liuhe1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 760);
	set("coor/y", -2120);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}