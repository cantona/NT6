// Room: /d/xiangyang/jiangjunyuan.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "將軍府大院");
        set("long", @LONG
這裏是將軍府的大院，只見大理石鋪就的地面一塵不染，兩個衣
着光鮮的小丫鬟認真的在擦洗兩邊的欄杆和柱子，不時有值班的衞士
走過來。向裏望去，可以看到將軍府的大堂。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"jiangjungate",
                "north" : __DIR__"jiangjuntang",
        ]));
        set("coor/x", -7810);
	set("coor/y", -750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}