// 花圃 huapu2.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "花圃");
        set("long", @LONG
這裡是蝴蝶谷的花圃，是『見死不救』胡青牛用來種各種各樣藥
材的，裡面種滿了諸般花草。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([
            "west" : __DIR__"xfang1",
        ]));

        setup();
}