// Room: /d/huanggong/yangxin2.c

inherit ROOM;

void create()
{
        set("short", "養性殿");
        set("long", @LONG
皇上退位後, 做了太上皇就居住在此. 太上皇不再來問朝政, 就在
此休息, 靜心養性. 直至壽終正寢.
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "north" : __DIR__"leshou",
                "east"  : __DIR__"changyinge",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2810);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}