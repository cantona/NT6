inherit ROOM;

void create()
{
        set("short", "天王殿");
        set("long", @LONG
這是天王殿，四大天王手握法器，高據于法壇之上，兩邊有紅色
柵欄與中間的通道隔開。每個法像的身前各有一個蒲團供善男信女們
膜拜，以求風調雨順。
LONG );
        set("objects", ([
                  __DIR__"npc/hufa" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"qianyuan",
                  "north" : __DIR__"zhongyuan",
        ]));

	set("coor/x", -5040);
	set("coor/y", 2190);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}