// Room: /yixing/shulin4.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
樹林裏光線暗淡，只能聽見頭頂上傳來一些鳥兒的啼鳴。偶爾從茂
密的葉間透過的一線光伴着落葉在飛舞。朽木腐爛的氣味和身後傳來野
獸的嘯聲使人不覺猶豫了前進的腳步。
LONG );
        set("outdoors", "yixing");
        set("exits", ([
                "west"  : __DIR__"shulin3",
                "south" : __DIR__"shanlu1",
                "north" : __DIR__"cldamen",
        ]));
        set("objects", ([
                __DIR__"npc/dabei" : 1,
        ]));
        set("coor/x", 280);
	set("coor/y", -1020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}