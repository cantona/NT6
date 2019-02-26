// 花圃 huapu3.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "花圃");
        set("long", @LONG
這裏是蝴蝶谷的花圃，是『見死不救』胡青牛用來種各種各樣藥
材的，裏面種滿了諸般花草。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([
            "east" : __DIR__"maopeng",
        ]));

        setup();
}