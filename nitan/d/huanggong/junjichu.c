// Room: /d/huanggong/junjichu.c

inherit ROOM;

void create()
{
        set("short", "軍機處");
        set("long", @LONG
這是一排不起眼的房舍. 但這排又矮又小的房子其實非同尋常, 
這是輔佐皇帝的最高政務機構, 以處理西北軍務為名的設軍機房, 又
名辦理軍機處.
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "southeast" : __DIR__"qianqingmen",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2820);
	set("coor/y", 7751);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}