//Room: /d/dali/chahua10.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花苑");
        set("long", @LONG
大理茶花冠絕天下，鎮南王府的茶花自然更非凡品。這裡是府中
的茶花苑，天下名品畢聚于此，你對著滿苑茶花，心花怒放，看了一
本，喜歡一本，實在不知道哪本茶花更好些。
LONG );
        set("objects", ([
           "/d/dali/obj/chahua2": 1,
           "/d/dali/obj/chahua3": 1,
           "/d/dali/obj/chahua6": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "west"  : "/d/dali/chahua7",
        ]));
	set("coor/x", -19061);
	set("coor/y", -6821);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}