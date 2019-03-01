// Room: /yixing/shulin5.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
樹林裡光線暗淡，只能聽見頭頂上傳來一些鳥兒的啼鳴。偶爾從茂
密的葉間透過的一線光伴著落葉在飛舞。朽木腐爛的氣味和身後傳來野
獸的嘯聲使人不覺猶豫了前進的腳步。
LONG );
        set("outdoors", "yixing");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : __DIR__"tiandi",
                "east"      : __DIR__"shulin2",
        ]));
        set("coor/x", 250);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}