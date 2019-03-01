inherit ROOM;

void create()
{
        set("short", "登高台");
        set("long", @LONG
這裡是南天門登高望遠的好去處。你站在這裡，俯視諸峰，丘垤
如泥丸。遙看湘江北去，九向九背，時隱時現。周圍煙霞，碧羅，紫
蓋，天柱諸峰環抱，氣象萬千。
LONG );
        set("exits", ([
               "northwest"  : __DIR__"nantian",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 4,
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6930);
	set("coor/y", -5530);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}