inherit ROOM;

void create()
{
        set("short", "荊州北門" );
        set("long", @LONG
這裏是荊州的北門，由於荊州歷來都是軍事要地，因此城牆堅實
無比，城樓高高聳立，由於北門以外，人煙稀少，來往的人不多，所
以官兵的防衞也就不十分嚴密。
LONG );
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/clone/npc/xunbu" : 1,
                "/d/beijing/npc/ducha" : 1,
        ]));
        set("exits", ([
                "northup" :"/d/wudang/wdroad5",
                "south" :__DIR__"beidajie2",
  
        ]));
        set("outdoors", "jingzhou");
        set("coor/x", -7100);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}