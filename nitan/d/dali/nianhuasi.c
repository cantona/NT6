//Room: /d/dali/nianhuasi.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","拈花寺");
        set("long",@LONG
山路越走越荒僻，轉過四個山坳，來到一座小小的古廟前，廟門
上寫着‘拈花寺’三字。佛教是大理國教。大理京城內外，大寺數十，
小廟以百計，這座‘拈花寺’地處偏僻，無甚香火，即是世居大理之
人，多半也不知曉。
LONG);
        set("objects", ([
           __DIR__"npc/pochen": 1,
           __DIR__"npc/poyi": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "enter"      : __DIR__"nianhua1",
            "southdown"  : __DIR__"shanlu2",
        ]));
	set("coor/x", -19160);
	set("coor/y", -6880);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}