// Room: /d/xiangyang/tiejiangpu.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "兵器鋪");
        set("long", @LONG
這裏原來是一家極其簡陋的鐵匠鋪。近年來蒙古大軍屢次進犯襄
陽，這家鐵匠鋪被官府徵用，作為官辦作坊。目前規模很大，一般用
來為襄陽守軍打造鎧甲、兵器等，近來因襄陽需籌備守城物資，奉郭
夫人之命也生產一些鐵釺、鐵錘、伐木斧頭等。只見幾十個鐵匠正叮
叮噹當地忙個不停。
LONG );
        set("exits", ([
                "west" : __DIR__"southjie3",
        ]));
        set("objects", ([
                "/d/city/npc/smith" : 1,
        ]));
        set("coor/x", -7810);
	set("coor/y", -800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}