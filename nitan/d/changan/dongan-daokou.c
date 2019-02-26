//Room: dongan-daokou.c

inherit ROOM;
void create ()
{
        set ("short", "東安道口");
        set("long", @LONG
長安城自古是繁華勝地，為數代皇朝建都之地，又為鹽商大賈所
聚集，殷富甲於天下。東安道口是一個四通八達的路口，西方有一條
大路通往馮詡道，東面是長安東城門，南北方向是連德大道。 
LONG );
        set("exits",([//sizeof() == 5
                "south" : "/d/changan/liande-dadao4",
                "north" : "/d/changan/liande-dadao3",
                "west" : "/d/changan/dongan-dadao",
                "east" : "/d/changan/dong-chengmen",
                "southwest" : "/d/changan/bingying6",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10680);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        