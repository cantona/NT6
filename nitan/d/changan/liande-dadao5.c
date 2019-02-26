//Room: liande-dadao5.c

inherit ROOM;

void create ()
{
        set ("short", "連德大道");
        set("long", @LONG
城內街道，與南北三條並行的大街，和東西的二條主街互相交錯
而成。五條大街在這清朗的夜初，卻見人來車往，燈火通明，別有一
番熱鬧。其他小街橫巷，則依這些主街交錯佈置，井然有序。
LONG );
        set("exits",([//sizeof() == 3
                "south" : "/d/changan/liande-nankou",
                "north" : "/d/changan/liande-dadao4",
                "east" : "/d/changan/xiaojia-qianyuan",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10680);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        