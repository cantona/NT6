//Room: /d/dali/hexi.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","河西鎮");
        set("long",@LONG
此鎮正處妃麗湖南，住的是阿藜蠻的休獵部。阿藜蠻屬台夷，村
民除了耕種沿湖的田地外，主要以捕魚為生。臨湖風光格外秀麗，北
邊不遠就是漁船出入的小碼頭。南邊山中有不少野獸，休獵部的男子
經常前去狩獵。
LONG);
        set("objects", ([
           __DIR__"npc/tshangfan": 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : __DIR__"feilihueast",
            "west"       : __DIR__"yujia",
            "north"      : __DIR__"feilihusouth",
            "south"      : __DIR__"zhulin2",
        ]));
	set("coor/x", -19130);
	set("coor/y", -6980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}