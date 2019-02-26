inherit ROOM;

void create()
{
        set("short", "淳熙路");
        set("long", @LONG
淳熙大路是洛陽最整潔的一條大路，街道寬敞而乾淨，漢白玉砌的路
面被雨水衝得光明如鏡，大路兩側的瓦房高大而宏偉，分明便是鉅富宅院。
雙人合抱的楊樹十步一株，整齊的排在兩邊。東邊是舉子秀才常去之地文
廟，而西邊則是科考試場 。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"wenmiao",
                  "north" : __DIR__"nroad4",
                  "west" : __DIR__"kaoshi",
                  "south" : __DIR__"nroad2",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng2" : 1,
        ]));
	set("coor/x", -6990);
	set("coor/y", 2210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}