inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是衙門大堂後面的走廊，走廊西面有一小石拱門，裏面
是一個小花園，花叢中有兩個花匠正在修剪花草。北面走廊的
盡頭的門開着，不知是不是就是師爺處.
LONG);

        set("exits", ([
                "west" : __DIR__"huayuan",
                "north" : __DIR__"zoulang1",
                "east"  : __DIR__"yamen",

        ]));

        set("coor/x", -9060);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}