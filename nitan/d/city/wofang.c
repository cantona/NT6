inherit ROOM;
void create()
{
         set("short","鐵匠臥房");
        set("long", @LONG
這裡是鐵匠的臥房，如果你累了，也可以在這裡休息一下。
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