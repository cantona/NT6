//Room: /d/dali/shanlu6.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","山路");
        set("long", @LONG
一條山路，兩邊是茂密的樹林，西面是延綿不絕的大山，南面是
一望無際的西雙版納大森林，傳説有邪教教眾在其中活動。道路兩旁
間或可見一些夷族的村鎮。山路轉向東蜿蜒着。
LONG );
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "northwest"  : "/d/dali/shanlu5",
            "east"       : "/d/dali/gudao",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19160);
	set("coor/y", -6920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}