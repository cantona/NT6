// Room: /d/huanggong/lie3.c

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
        set("exits", ([ /* sizeof() == 4 */
                "west"  : __DIR__"lie2",
                "east"  : __DIR__"lie3",
                "north" : __DIR__"lie3",
                "south" : __DIR__"lie4",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2860);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}