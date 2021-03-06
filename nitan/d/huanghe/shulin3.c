// Room: /huanghe/shulin3.c
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
                "west"  : __DIR__"shulin4",
                "south" : __DIR__"shulin1",
                "north" : __DIR__"tiandi1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -210);
        set("coor/y", 300);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}