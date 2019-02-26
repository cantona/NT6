inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峯錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。南邊就是福嚴寺。
LONG );
        set("exits", ([ 
               "southup"  : __DIR__"sansheng",
               "northup"  : __DIR__"mojingtai",
        ]));

        set("objects", ([
                __DIR__"npc/xiangke"  : 2,
                __DIR__"npc/youke"    : 3,
        ]));    

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5560);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}