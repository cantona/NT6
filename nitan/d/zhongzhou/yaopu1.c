inherit ROOM;

void create()
{
        set("short", "藥鋪內院");
        set("long", @LONG
這裏就是藥鋪內院，你一走進來就覺得一股熱浪。只見十
幾隻爐子都在熬藥，有幾個藥鋪的夥計在忙碌着。你要熬藥的
話就要依着藥方把放進藥罐裏。
LONG);
        set("exits", ([
                "north" : __DIR__"yaopu",
                
        ]));

        set("coor/x", -9030);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}