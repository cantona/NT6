inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峯錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。這裏已經隱隱看到祝融峯了。 
LONG );
        set("exits", ([ 
                "eastdown" : __DIR__"shanlu003",
                "westup"   : __DIR__"zhurongfeng",         
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5490);
	set("coor/z", 60);
	setup();
        replace_program(ROOM);
}