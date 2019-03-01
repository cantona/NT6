//Room: /d/dali/road5.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","黃土路");
        set("long",@LONG
這裡是大理境內，你走在一條黃土大路上，行人多是本地的擺
夷族人。也間或有些中原打扮的人事走動，此路北面通向官道，向
西北有路通往大理城的南門，東行可達廣東佛山。
LONG);
        set("objects", ([
           __DIR__"npc/yetu": 2,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "northwest"  : __DIR__"shuangheqiao",
	    "northeast"  : "/d/foshan/road1",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}