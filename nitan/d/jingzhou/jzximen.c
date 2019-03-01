inherit ROOM;

void create()
{
        set("short", "荊州西門" );
        set("long", @LONG
你來到荊州的西門，荊州歷來都是軍事要地，因此城牆堅實無比，
城樓高高聳立，出了西門，就踏上了艱險的蜀道，一直向天俯之國而
去，路上多有險阻，如果你要去的話，務必多加小心。入了城門，進
入荊州，你就等于到了中原了。
LONG );
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/clone/npc/xunbu" : 1,
                "/d/beijing/npc/ducha" : 1,
        ]));

        set("exits", ([  
               "east" : __DIR__"xidajie2",
        ]));
        set("outdoors", "jingzhou");

        set("coor/x", -7130);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}