//Room: /d/dali/zhenxiong.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","鎮雄");
        set("long",@LONG
這裡是烏撒部的聚居中心，烏撒是烏蠻族的大部，屬烏夷，領有
巴的甸、鎮雄、和附近的威寧。這是一座石砌小城，人口不多，居民
散居在鎮子附近，鎮子上主要是一些商舖和祭祀所。
LONG);
        set("objects", ([
           __DIR__"npc/muyangnu": 1,
           __DIR__"npc/wshangfan": 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "south"      : __DIR__"badidian",
            "north"      : __DIR__"gelucheng",
            "northeast"  : __DIR__"minadian",
            "east"       : __DIR__"titian1",
            "west"       : __DIR__"wuyiminju3",
        ]));
	set("coor/x", -19210);
	set("coor/y", -6860);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}