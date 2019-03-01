// Room: /d/huanggong/qinghedian.c
inherit ROOM;

void create()
{
        set("short", "清和殿");
        set("long", @LONG
清和殿, 這是康熙爺與納蘭皇後用膳的地方. 皇後不喜歡吵鬧, 
所以你們不得大聲說話. 長長的檀香桌上已為聖上準備好了一席滿漢
全席. 真香啊!
LONG
        );

        set("exits", ([
                "east" : __DIR__"yushanfang",
        ]));
        set("objects", ([
                __DIR__"obj/nverhong" : 2,
                __DIR__"npc/taijian" :1,
        ]));

	set("coor/x", -2800);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}