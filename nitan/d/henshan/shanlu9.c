inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。南邊是南台寺，北邊通往福嚴寺。
LONG );
        set("exits", ([ 
               "southup"  : __DIR__"nantaisi",
               "northup"  : __DIR__"fuyansi",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6940);
	set("coor/y", -5580);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}