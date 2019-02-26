//Room: nanan-daokou.c

inherit ROOM;

void create ()
{
        set ("short", "南安道口");
        set("long", @LONG
長安城自古是繁華勝地，為數代皇朝建都之地，又為鹽商大賈所
聚集，殷富甲於天下。南安道口是一個四通八達的路口，東西方向通
往華瑞街，南面是長安南城門，北方有一條大路通到故皇宮的金水橋。
 
LONG );
        set("exits",([//sizeof() == 4
                "south" : "/d/changan/nan-chengmen",
                "north" : "/d/changan/nanan-dadao",
                "west" : "/d/changan/huarui3",
                "east" : "/d/changan/huarui4",
                "northeast" : "/d/changan/bingying4",
                "northwest" : "/d/changan/bingying5",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        