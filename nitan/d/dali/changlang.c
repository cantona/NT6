//Room: /d/dali/changlang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","長廊");
        set("long", @LONG
這裏是鎮南王府的長廊，兩邊都是大圓柱。邊上假山小湖應有盡
有，顯得十分秀麗。北面是一座大建築，南邊是一個小庭院。
LONG );
        set("objects",([
            "/d/dali/npc/duanwuwei" : 1,
        ]));
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/tingfang",
            "south"  : "/d/dali/tingyuan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19101);
	set("coor/y", -6851);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}