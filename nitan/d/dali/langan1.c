//Room: /d/dali/langan1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","桿欄");
        set("long",@LONG
擺夷族大多依樹積木以居其上，就是桿欄，在夷語裡叫做榔盤。
其構造大致略似樓，側面開門，有梯可上下，上閣如車蓋狀，中層住
人，這裡是下層，一般為牛羊圈。
LONG);
        set("objects",([
            __DIR__"npc/shanyang" : 2,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "north"   : __DIR__"nongtian2",
            "up"      : __DIR__"langan2",
        ]));
	set("coor/x", -19060);
	set("coor/y", -6880);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}