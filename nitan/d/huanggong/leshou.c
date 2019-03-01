// Room: /d/huanggong/leshou.c

inherit ROOM;

void create()
{
        set("short", "樂壽堂");
        set("long", @LONG
這裡是太上皇賦詩, 祝壽的地方. 後來, 慈禧曾居住在此, 並在這
慶祝她的六十大壽, 下令用籌建海軍的軍費興建頤和園, 耗銀高達數千
萬兩.
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                 "north" : __DIR__"yihexuan",
                 "south" : __DIR__"yangxin2",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2810);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}