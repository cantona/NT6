//Room: /d/dali/zhulin2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","竹林深處");
        set("long",@LONG
這是一大片茂密的竹林，向南上山則是更茂密的闊葉林，鳥獸眾
多。有經驗的台夷獵人擅在竹林中下套、陷肼，捕捉兔、鹿等小獸，
或結夥持利刃上深山捕捉大些的猛獸。
LONG);
        set("objects", ([
                __DIR__"npc/lieshou": 2,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
                "north"      : __DIR__"hexi",
                "west"       : "/d/wudu/cun8",
        ]));
	set("coor/x", -19130);
	set("coor/y", -6990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}