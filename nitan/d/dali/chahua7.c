//Room: /d/dali/chahua7.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花園");
        set("long", @LONG
大理茶花冠絕天下，鎮南王府的茶花自然更非凡品。你站在茶花
園中，北面是一座小山，山上栽滿了常青喬木。地上長草委地，密密
層層的。東面有一個小小庭院，西邊望去仍是一片萬紫千紅。
LONG );
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "south"   : "/d/dali/chahua6",
            "northup" : "/d/dali/chahua9",
            "east"    : "/d/dali/chahua10",
            "west"    : "/d/dali/chahua8",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19071);
	set("coor/y", -6821);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}