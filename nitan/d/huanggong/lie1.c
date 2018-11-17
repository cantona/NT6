// Room: /d/huanggong/lie1.c

inherit ROOM;

void create()
{
        set("short", "上林囿");
        set("long", @LONG
這是西苑的一片廣袤的大獵場, 疾風吹勁草, 大有草枯鷹眼疾的非
凡氣派.
LONG
        );

        set("outdoors", "huanggong");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"dadao",
                "west"  : __FILE__,
                "north" : __DIR__"lie2",
                "south" : __FILE__,
        ]));
	set("coor/x", -2870);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}