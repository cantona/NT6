inherit ROOM;

void create()
{
        set("short", "中院");
        set("long", @LONG
中院分為前後兩部分，院子的正中有座鐵制浮屠，高七層。雕刻
精美花紋。前邊部分除中間的行道外，兩邊是花圃，各種一棵高大的
菩提樹。後邊舖著青石，通向大雄寶殿。南邊是天王殿，東邊是素齋
廚，西面是浴室。
LONG );
        set("objects", ([
                  __DIR__"npc/obj/tiefutu" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"tianwang",
                  "north" : __DIR__"daxiong",
                  "east" : __DIR__"chufang",
                  "west" : __DIR__"yushi",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5040);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}