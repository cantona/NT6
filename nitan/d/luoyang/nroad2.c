inherit ROOM;

void create()
{
        set("short", "淳熙路");
        set("long", @LONG
淳熙大路是洛陽最整潔的一條大路，街道寬敞而幹凈，漢白玉砌的路
面被雨水沖得光明如鏡，大路兩側的瓦房高大而宏偉，分明便是巨富宅院。
雙人合抱的楊樹十步一株，整齊的排在兩邊。東邊是衙門所在，西邊是則
一家糧舖。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"yamendoor",
                  "north" : __DIR__"nroad3",
                  "south" : __DIR__"nroad1",
                  "west" : __DIR__"liangpu",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy1" : 1,
                "/d/beijing/npc/old2" : 1,
        ]));
	set("coor/x", -6990);
	set("coor/y", 2200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}