inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是衙門大堂後面的走廊，走廊西面有一小石拱門，裡面
是一個小花園，花叢中有兩個花匠正在修剪花草。北面走廊的
盡頭的門開著，不知是不是就是師爺處。
LONG);
        set("exits", ([
                "south" : __DIR__"zoulang",
                "north" : __DIR__"shiye",
                 
        ]));

        set("coor/x", -9060);
	set("coor/y", -960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}