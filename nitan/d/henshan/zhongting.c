inherit ROOM;

void create()
{
        set("short", "鍾亭");
        set("long", @LONG
鍾亭內設鐵鐘一口，重九千斤。每逢山洪暴發，鳴鐘鎮洪，亦以
示警，聲聞二十里外。 
LONG );
        set("exits", ([
               "west"   : __DIR__"kuixingge",
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6880);
	set("coor/y", -5680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}