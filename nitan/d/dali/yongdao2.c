//Room: /d/dali/yongdao2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","甬道");
        set("long", @LONG
這是鎮南王府的甬道。兩邊是密密的參天喬木，天光透過樹葉，
在地上洒下星星斑點。石砌的甬道路面兩側，是如茵的綠草，點綴著
一星半點的小花，周圍十分安靜，偶爾蟲鳴悠揚。
LONG );
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/neitang",
            "east"       : "/d/dali/chahua8",
            "southwest"  : "/d/dali/yongdao1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6821);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}