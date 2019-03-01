inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。山路東西通向磨鏡台和天柱峰。
LONG );
        set("exits", ([
               "westup"    : __DIR__"tianzhu",
               "eastdown"  : __DIR__"mojingtai",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6960);
	set("coor/y", -5550);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}