// Room: /huanghe/shulin2.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "樹林");
        set("long", @LONG
樹林裏光線暗淡，只能聽見頭頂上傳來一些鳥兒的啼鳴。偶爾從茂
密的葉間透過的一線光伴着落葉在飛舞。朽木腐爛的氣味和身後傳來野
獸的嘯聲使人不覺猶豫了前進的腳步。
LONG );
        set("exits", ([
                "east"  : __DIR__"shulin1",
                "north" : __DIR__"shulin4",
        ]));
        set("objects", ([
                "/d/baituo/npc/wolf" : 1,
        ]));
        set("quarrys", ([
                "tu"        : 100000,
                "ji"        : 80000,
                "pao"       : 50000,
                "caihuashe" : 50000,
                "dushe"     : 20000,
                "hu"        : 5000,
                "bao"       : 2000,
                "laohu"     : 2000,
        ]));
        set("outdoors", "huanghe");
        set("coor/x", -220);
        set("coor/y", 100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
