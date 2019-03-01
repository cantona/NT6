inherit ROOM;

void create()
{
        set("short", "玉皇閣");
        set("long", @LONG
玉皇閣高十三米坐北朝南，採用仿木結構均用磚砌成。外觀下閣
上亭。下圓下方，造型奇特，是一座集蒙古包與閣樓巧妙結合，具有
元代風格的建築。閣內供有真武銅像一尊。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"sanqing",
                  "up" : __DIR__"yuhuang2",
        ]));

	set("coor/x", -5100);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}