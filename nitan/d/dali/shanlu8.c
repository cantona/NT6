//Room: /d/dali/shanlu8.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","山路");
        set("long",@LONG
道路在山林中蜿蜒繼續，從西面的山嶺通向東面的低窪地帶。這
裡山勢較為平緩，山叢中偶有人煙，透過叢林的縫隙中向東望去，隱
約可見一汪碧水和些許人煙。
LONG);
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "eastdown"  : __DIR__"yangzong",
            "westdown"  : __DIR__"shanlu7",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19030);
	set("coor/y", -6880);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}