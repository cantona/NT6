inherit ROOM;

void create()
{
        set("short", "藥舖內院");
        set("long", @LONG
這裡就是藥舖內院，你一走進來就覺得一股熱浪。只見十
幾只爐子都在熬藥，有幾個藥舖的伙計在忙碌著。你要熬藥的
話就要依著藥方把放進藥罐裡。
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