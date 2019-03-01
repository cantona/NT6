//Room: /d/dali/zhulin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","竹林小路");
        set("long",@LONG
一條小路穿竹林而過，西南方竹林深處是一大片台夷人聚居的村
鎮，東北可遙遙望見喜州城的城牆。道路兩邊竹林茂密，時有台夷人
來砍伐。
LONG);
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "southwest"  : __DIR__"wuding",
            "northeast"  : __DIR__"xizhou",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19140);
	set("coor/y", -6960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}