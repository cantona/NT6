inherit ROOM;

void create()
{
        set("short", "居室");
        set("long", @LONG
一間頗為精致的小屋，似乎是女子的居所。房間的中央擺
著一支香爐，緩緩散發著清香。門前還懸掛著一籠白鸚鵡，雕
花檀香木的床上整齊的疊放著錦緞綢被。
LONG);
        set("exits", ([
                  "south" : __DIR__"miaojia_zoulang1",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                CLASS_D("miao") + "/lan" : 1,
        ]));
        set("coor/x", -9000);
	set("coor/y", -950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}