// 花圃 huapu4.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "花圃");
        set("long", @LONG
這裏是蝴蝶谷的花圃，是『見死不救』胡青牛用來種各種各樣藥
材的，裏面種滿了諸般花草。
LONG );

        set("no_clean_up", 0);
        set("outdoors", "蝴蝶谷");

        set("exits", ([
            "north" : __DIR__"houshan",
            "south" : __DIR__"chufang",
        ]));

        setup();
}