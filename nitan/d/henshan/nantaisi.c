inherit ROOM;

void create()
{
        set("short", "南台寺");
        set("long", @LONG
南台寺為禪宗七祖懷讓的弟子石頭希遷的道場，寺下紫雲峯上是
石頭和尚墓。寺周林蔭夾道，曲徑通幽，泉流叮咚，蜂蝶紛飛，山風
吹過時萬葉悉索，真好去處。
LONG );
        set("exits", ([
                "northdown"  : __DIR__"shanlu9",
        ]));

        set("objects", ([
                __DIR__"npc/xiangke" : 4,
        ]));                    

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6940);
	set("coor/y", -5590);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}