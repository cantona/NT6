// Room: /d/quanzhou/huruquan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "虎乳泉");
        set("long", @LONG
這是一塊斜臥著的石皮，有泉水從縫隙中迸出，流入一個尺余見方
的石孔中。它流了不知多少歲月了，但從來不涸。水清洌見底，甘甜似
乳，用它泡茶，香味沁人心脾。泉州及清源山得名「泉山」，皆源于此
泉。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown" : __DIR__"shanlu2",
                "northup"   : __DIR__"qingyuandong",
        ]));
	set("coor/x", -900);
	set("coor/y", -7540);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}