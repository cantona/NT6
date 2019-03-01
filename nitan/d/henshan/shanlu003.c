inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。一直往西不遠便是衡山五峰中最高的祝融峰了。
 
LONG );
        set("exits", ([ 
                "eastdown" : __DIR__"zhurongdian",
                "westup"   : __DIR__"shanlu004",         
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6940);
	set("coor/y", -5490);
	set("coor/z", 50);
	setup();
        replace_program(ROOM);
}