//Room: /d/dali/wumeng.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","村外草坡");
        set("long", @LONG
一大片山坡長滿青草，正是放牧牛羊的好地方。這裏地勢甚高，
天空呈深藍色，附近山嶺樹木已經甚少，基本上都是低矮灌木或草地。
不少附近的村民在此放牧。
LONG );
        set("objects",([
            "/d/dali/npc/muyangren": 1,
            "/d/dali/npc/muyangnu": 1,
        ]));
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "west"      : "/d/dali/wumeng",
        ]));
	set("coor/x", -19160);
	set("coor/y", -6780);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}