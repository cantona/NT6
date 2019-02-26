inherit ROOM;
void create()
{
         set("short","鐵匠卧房");
        set("long", @LONG
這裏是鐵匠的卧房，如果你累了，也可以在這裏休息一下。
LONG );
         set("exits",([
         "north":"/d/city/datiepu",
]));
       set("sleep_room", 1);
	set("coor/x", 20);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
}