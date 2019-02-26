// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "大廳");
        set ("long", @LONG
這是萬家為慶祝老爺子五十大壽佈置的大廳，前來拜壽的客人已陸
續就座，幾個丫鬟僕人正忙着端茶送水，大廳上一個身形魁梧的老者正
在和眾賓客周旋。
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "south"  : __DIR__"wan_damen",
                "north"  : __DIR__"wan_zoulang",
                "east"   : __DIR__"wan_donglou",
                "west"   : __DIR__"wan_xilou",
        ]));
        set("objects", ([
                __DIR__"npc/wanzhenshan" : 1,
                __DIR__"npc/lvtong"      : 1,
                __DIR__"npc/lukun"       : 1,
                __DIR__"npc/zhouqi"      : 1,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}