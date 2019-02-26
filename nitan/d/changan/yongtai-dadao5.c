//Room: yongtai-dadao5.c

inherit ROOM;

void create ()
{
        set ("short", "永泰大道");
        set("long", @LONG
城內街道，與南北三條並行的大街，和東西的二條主街互相交錯
而成。五條大街在這清朗的夜初，卻見人來車往，燈火通明，別有一
番熱鬧。其他小街橫巷，則依這些主街交錯佈置，井然有序。
LONG );
        set("exits",([//sizeof() == 2
                "south" : "/d/changan/yongtai-nankou",
                "north" : "/d/changan/yongtai-dadao4",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10760);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        