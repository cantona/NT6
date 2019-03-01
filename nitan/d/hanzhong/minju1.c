// minju1.c 民居
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
這好象是一家相對殷實的小康人家，屋內舖著青磚，擺著一套紅
木桌椅。牆上掛著幾幅山水畫(hua)， 主人不在家裡。
LONG
        );
        set("exits", ([
                "east" : __DIR__"beijie",
        ]));
        set("item_desc", ([
        "hua": "這不是北宋范寬的‘溪山行旅圖’嗎？你大吃一驚。揉了揉眼睛仔細一看，原來是副贗品。\n"
        ]) );
        set("no_clean_up", 0);
        set("coor/x", -12260);
	set("coor/y", 820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}