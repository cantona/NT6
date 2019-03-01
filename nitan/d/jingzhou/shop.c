inherit ROOM;

void create()
{
        set("short", "廢園");
        set("long", @LONG
你看到四周芳草萋萋，這裡是一座廢棄了多年的園子，到處都是
老鼠和灰塵，使人不由得黯然神傷。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                  "south" : __DIR__"dongdajie2",
        ]));
        set("objects", ([
                "/d/jingzhou/npc/qigai" : 1,
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7080);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
 