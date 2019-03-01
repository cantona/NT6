//Room: biaoju-dayuan.c

inherit ROOM;

void create()
{
        set("short", "河洛鏢局大院");
        set("long", @LONG
院子裡面堆放著十幾輛用草席蓋著的空鏢車，草席上積滿了雪，
東面的屋檐下，斜插著一面醬色鑲金邊的鏢旗，被風吹得蠟蠟作響，
使人幾乎分辨不出用金線繡在那上面的是老虎，還是獅子。大院裡不
時鏢師進出。
LONG );
        set("exits", ([
                "north" : "/d/changan/biaoju-damen",
                "south" : "/d/changan/biaoju-dating",
        ]));
        set("objects", ([
                "/d/changan/npc/biaotou" : 1,
                "/d/changan/npc/tang" : 2,
        ]) );
    
        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
}