//Room: xian-daokou.c

inherit ROOM;
void create ()
{
        set ("short", "西安道口");
        set("long", @LONG
長安城自古是繁華勝地，為數代皇朝建都之地，又為鹽商大賈所
聚集，殷富甲于天下。西安道口是一個四通八達的路口，東方有一條
大路通往扶風道，西面是長安西城門，南北方向是永泰大道。 
LONG );
        set("exits",([//sizeof() == 5
                "south" : "/d/changan/yongtai-dadao4",
                "north" : "/d/changan/yongtai-dadao3",
                "west" : "/d/changan/xi-chengmen",
                "east" : "/d/changan/xian-dadao",
                "southeast" : "/d/changan/bingying3",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10760);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        