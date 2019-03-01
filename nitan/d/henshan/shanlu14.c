inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。山路轉過芙蓉峰，西面遠遠看到藏經閣，東南
方向通往南天門。
LONG );
        set("exits", ([ 
               "west"       : __DIR__"cangjingdian",
               "southeast"  : __DIR__"nantian",
               "north"      : __DIR__"conglin-1",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5510);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}