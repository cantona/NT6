//Room: /d/dali/chahua2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花園");
        set("long", @LONG
大理茶花冠絕天下，鎮南王府的茶花自然更非凡品。你站在茶花
園中，看萬紫千紅，爭奇鬥妍，心胸大爽。靠東一座小石凳，凳後柳
樹成行，拖曳水面，把湖面點成一個個漣漪。
LONG );
        set("objects", ([
           "/d/dali/obj/chahua1": 1,
           "/d/dali/npc/huanu": 1,
        ]));
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "west"  : "/d/dali/chahua1",
            "northeast"  : "/d/dali/chahua3",
            "southeast"  : "/d/dali/chahua4",
        ]));
	set("coor/x", -19081);
	set("coor/y", -6861);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}