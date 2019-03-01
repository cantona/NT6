//Room: /d/dali/road1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","官道");
        set("long", @LONG
這是一條蜿蜒崎嶇的山間土路，是由中原通向大理的官道。此處
屬川南，向西南去的盤山路通上雲貴山區，繼而可達南昭大理國，此
去向北不遠就是蜀中名川--峨嵋山。
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : "/d/emei/qsjie2",
            "southwest"  : "/d/dali/road2",
            "east"  : "/d/kunming/xroad2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19140);
	set("coor/y", -6800);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}