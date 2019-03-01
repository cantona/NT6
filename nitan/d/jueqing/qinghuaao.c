#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "情花坳");
        set("long", @LONG
前方是一片徑長兩丈的園形草地(caodi)，一陣醉人心魄的
花香撲鼻而來，外邊密密層層的圍滿了情花。不論從那個方位
出來，都有八九丈地面生滿情花。任你武功再強，也決不能一
躍而出，縱然躍至半路也是難能。
        ====此處等待補充。。。。。====
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "westdown" : __DIR__"shanyao",
        ]));

        set("objects", ([
                __DIR__"npc/dizi1" : 1,
                __DIR__"npc/dizi2" : 1,
        ]));  

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}

