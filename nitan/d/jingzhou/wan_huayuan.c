// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "花園");
        set ("long", @LONG
這是萬家的後園，堆置了篩子、鋤頭、石臼、風扇之類雜物。在一
張小几放着一座香爐，香爐中插着三枝點燃了的線香。幾前有個人跪着
向天磕頭，不知祈着什麼願心。
LONG);
        set("outdoors", "jingzhou");
        set("region", "jingzhou");
        set("exits", ([
                "south" : __DIR__"wan_ketang",
                "east"  : __DIR__"wan_citang",
        ]));
        set("objects", ([
                __DIR__"npc/kongxincai"    : 1,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}