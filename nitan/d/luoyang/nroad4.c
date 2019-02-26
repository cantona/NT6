inherit ROOM;

void create()
{
        set("short", "淳熙路");
        set("long", @LONG
淳熙大路是洛陽最整潔的一條大路，街道寬敞而乾淨，漢白玉砌的路
面被雨水衝得光明如鏡，大路兩側的瓦房高大而宏偉，分明便是鉅富宅院。
雙人合抱的楊樹十步一株，整齊的排在兩邊。西邊是一家皮貨店，東邊是
一條青石小巷，筆直通往一座新建蘭薪寺 。
LONG);
        set("outdoors", "luoyang");
        set("exits", ([
                  "east" : __DIR__"xiaoxiang",
                  "north" : __DIR__"beidoor",
                  "south" : __DIR__"nroad3",
                  "west" : __DIR__"pimao",
        ]));
        set("objects", ([
                "/d/beijing/npc/xianren" : 1,
        ]));
	set("coor/x", -6990);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}