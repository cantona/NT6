// Room: /d/yueyang/zhongxin.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "中心菜市");
        set("long", @LONG
這裏是岳陽城的中心菜市。每天早上，東門來的時菜，西門來的活
魚，米店挑出來的陳米，屠場扛出來的生豬，全在這裏貨買，一片吆喝
不止。集散人空後，滿地的魚腥糞臭，過往行人往往掩鼻急行。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"dongjie",
                "west"  : __DIR__"xijie",
                "north" : __DIR__"beijie",
                "south" : __DIR__"nanjie",
        ]));
        set("objects", ([
                __DIR__"npc/xingren" : 1,
                __DIR__"npc/liumang" : 1,
                __DIR__"npc/xiaofan" : 1,
                CLASS_D("gaibang")+"/bangzhong" : 1,
                CLASS_D("gaibang")+"/wu-changfeng" : 1,
        ]));
	set("coor/x", -6200);
	set("coor/y", -3010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}