// Room: /huanghe/shulin1.c
// Java. Sep 21 1998

#include <room.h>
#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "樹林");
        set("long", @LONG
樹林裏光線暗淡，只能聽見頭頂上傳來一些鳥兒的啼鳴。偶爾從茂
密的葉間透過的一線光伴着落葉在飛舞。朽木腐爛的氣味和身後傳來野
獸的嘯聲使人不覺猶豫了前進的腳步。林中立着一塊牌子(paizi)。
LONG );
        set("exits", ([
                "west"  : __DIR__"shulin2",
                "east"  : __DIR__"caodi2",
                "north" : __DIR__"shulin3",
        ]));
        set("item_desc", ([
                "paizi" : HIR"\n非黃河幫眾者    擅入格殺勿論\n\n"NOR,
        ]));
        set("objects", ([
                "/d/shenlong/npc/dushe" : 1,
                "/d/hangzhou/obj/shuzhi" : 1,
        ]));
        set("outdoors", "huanghe");
        set("coor/x", -210);
        set("coor/y", 100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}