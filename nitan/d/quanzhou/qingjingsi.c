// Room: /d/quanzhou/qingjingsi.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "清淨寺");
        set("long", @LONG
這是一座依照敍利亞大馬士革伊斯蘭禮拜堂而建的教堂，全部用青
色和白色的花崗石建造。高大的穹形頂的尖拱大門使人們站在門內，大
有「天作穹廬地作氈」之感。寺內還有一「永樂上諭」石刻。寺門後的
西側是「奉天壇」，阿拉伯教徒在此面西朝拜。
    門楣上還刻有「可蘭經」。
LONG );
        set("exits", ([
                "south" : __DIR__"tumenji",
                "north" : __DIR__"alabo",
        ]));
        set("objects", ([
                __DIR__"npc/huihui" : 1,
        ]));
	set("coor/x", -890);
	set("coor/y", -7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}