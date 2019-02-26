//Room: baodian.c

inherit ROOM;

void create ()
{
        set ("short", "大雄寶殿");
        set("long", @LONG
大雄寶殿內，金壁輝煌，雕樑畫棟，殿兩側共安放了六尊古佛，
古佛之後有釋伽與天龍諸部的壁畫。大雄寶殿為歷朝皇帝招見僧侶、
讀經唸佛的所在，是以陳設與其餘諸殿大不相同，倒像是莊嚴肅穆的
佛堂一般。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "north" : "/d/changan/baoxiangsi",
                "west" : "/d/changan/piandian",
                "east" : "/d/changan/fangzhangshi",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/xiangke" : 2,
        ]));
        
        set("coor/x", -10730);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}