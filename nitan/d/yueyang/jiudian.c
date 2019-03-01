// Room: /d/yueyang/jiudian.c 
// Last Modifyed by Winder on Dec. 4 2001
inherit ROOM;

void create()
{
        set("short", "洞賓樓");
        set("long", @LONG
呂洞賓三醉洞庭的故事無人不知，這個洞賓樓便是仰慕當年神跡而
建。現在生意好了，也變成一座岳陽城最大的大酒樓了。凡來到岳陽的
人，如果說沒有在洞賓樓喝過龜蛇酒，嘗過洞庭魚，也算是憾事了。
LONG );
        set("exits", ([
                "east"  : __DIR__"nanjie",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
	set("coor/x", -6210);
	set("coor/y", -3020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}