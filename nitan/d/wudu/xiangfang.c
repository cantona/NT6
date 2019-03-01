#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "廂房");
        set("long", @LONG
這是一間亂糟糟的廂房，裡面到處都是各種大大小小的籠子、瓦
罐之類的東西。不時還能看到有毒蟲在籠子裡面上竄下跳，四處遊走。
一個赤著膀子的白胡子老者正在手忙腳亂的給毒蟲們挨個喂食，忙得
手忙腳亂。
LONG);
        set("exits", ([
                "east" : __DIR__"nanyuan",
        ]));
        set("objects", ([
                __DIR__"npc/oldman": 1,
        ]));
        setup();
}