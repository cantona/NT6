//Room: /d/dali/hongsheng4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","宏聖寺塔");
        set("long", @LONG
這裡是宏聖寺塔內部，四面牆壁上都辟有佛龕，龕內置佛像。西
面塔壁由模印磚所砌，上面用梵，漢文刻了陰形文的『阿眾佛滅正保
咒』。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "down"     : "/d/dali/hongsheng3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19151);
	set("coor/y", -6821);
	set("coor/z", 49);
	setup();
        replace_program(ROOM);
}