// Room: /d/quanzhou/mituoyan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "彌陀巖");
        set("long", @LONG
這裏古木參天，巨石峭立。多雨時節，有飛瀑如練，從巖上垂掛下
來，濺起千堆細沫，詩云：虹雨千層吹不斷，琉璃萬盅湧還多。瀑邊兩
大巨石夾峙，巖壁小松攀生，仰望天空細如一線，即為「一線天」之所
在。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southeast" : __DIR__"liandanshi",
                "northwest" : __DIR__"qianshouyan",
        ]));
	set("coor/x", -920);
	set("coor/y", -7540);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}