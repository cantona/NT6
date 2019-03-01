inherit ROOM;

void create()
{
        set("short", "衡陽西街");
        set("long", @LONG
你走在碎石舖就的狹小街道上。只見街上時常有人持劍疾行，似
乎這裡出了啥事了。南邊是一家小店，北面一座大宇巍峨，重檐疊瓦，
 門口彩燈高懸，管家家丁好象都是武林中人。
LONG );
        set("outdoors", "henshan");

        set("exits", ([
               "east"   : __DIR__"hengyang",
               "west"   : __DIR__"hengyang11",
               "south"  : __DIR__"shop",
               "north"  : __DIR__"liufugate",
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6900);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}