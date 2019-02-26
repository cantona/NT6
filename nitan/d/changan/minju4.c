//Room: minju4.c

inherit ROOM;

void create ()
{
        set ("short", "民居");
        set("long", @LONG
這裏是一家民居住房，窗台上放着大大小的小陶盆瓷罐，裏面種
着花草之類的東西，兩扇窗子大開，飄出一股花草的清香味。民居里
十分熱鬧，一張大木桌子，周圍放着幾把椅子，幾個鄰里湊在一起，
不知在談什麼。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/huarui4",
        ]));

        set("coor/x", -10710);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}