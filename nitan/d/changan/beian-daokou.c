//Room: beian-daokou.c

inherit ROOM;

void create ()
{
        set ("short", "北安道口");
        set("long", @LONG
長安城自古是繁華勝地，為數代皇朝建都之地，又為鹽商大賈所
聚集，殷富甲於天下。北安道口是一個四通八達的路口，東西方向通
往麒祥街，北面是長安北城門，南方有一條大路通到故皇宮的金水橋。
 
LONG );
        set("exits",([//sizeof() == 4
                "south" : "/d/changan/beian-dadao",
                "north" : "/d/changan/bei-chengmen",
                "west" : "/d/changan/qixiang3",
                "east" : "/d/changan/qixiang4",
                "southeast" : "/d/changan/bingying1",
                "southwest" : "/d/changan/bingying2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}