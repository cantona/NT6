inherit ROOM;

void create()
{
        set("short", "龍騰武館");
        set("long", @LONG
龍騰武館是專為初出江湖的少年設立的。由于江湖叛師是十分為人不
齒的，初出道的少年可以在此學習一些基本的防身武功，一來不會光陰虛
度，二來也好為今後選定一個心慕的門派。
LONG);
        set("exits", ([
                  "north" : __DIR__"wroad2",
                  "south" : __DIR__"wuguan2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -7010);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}