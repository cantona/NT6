inherit ROOM;

void create()
{
        set("short", "存儲室");
        set("long", @LONG
這裡是當舖的存儲室，用于存儲一些已被典當，但還可能被物主贖回
的東西，當然這只是暫時的，只要一過了可贖回的期限，當舖老板會毫不
猶豫的將其高價出售，要知道商人除了錢是什麼也不會認的。這裡陰森黑
暗潮濕，而且空氣中還充斥著一股霉味。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "up" : __DIR__"dangpu",
        ]));

	set("coor/x", -7000);
	set("coor/y", 2170);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}