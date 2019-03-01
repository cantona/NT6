// Room: /d/huanggong/donghuamen.c

inherit ROOM;

void create()
{
        set("short", "東華門");
        set("long", @LONG
東華門是朝臣和內官員們平時進出皇宮之門. 門外設有下馬碑石,
碑刻: 官員人等至此下馬. 文武百官到達此地, 文官必須下轎, 武官必
須下馬, 不得違背.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 4 */
                "west"  : __DIR__"wenhua",
                "south" : __DIR__"dao2",
                "north" : __DIR__"dao3",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2780);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}