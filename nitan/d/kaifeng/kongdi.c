inherit ROOM;

void create()
{
        set("short", "空地");
        set("long", @LONG
在滿園的菜地中間的一片空地，估計是因為原來的菜地被踩平後，
僧人不耐煩再種而留下來的。場地的中間一住老槐樹枝葉顫顫的，上
面的老鴉不時驚叫。南邊是個小糞窖，東面有間小堂間。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"caidi5",
                  "south" : __DIR__"fenjiao",
                  "east" : __DIR__"tangjian",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -4980);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}