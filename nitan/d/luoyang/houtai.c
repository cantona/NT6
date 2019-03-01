inherit ROOM;

void create()
{
        set("short", "後台");
        set("long", @LONG
這裡是戲院的後台，地方不大，除了化妝台，就沒有什麼了，到處都
堆滿了服裝和道具，顯得很緊湊，人人都緊張的忙碌著，化妝的化妝，卸
妝的卸妝，修道具的修道具，理服裝的理服裝，大家都在為前台的表演做
著準備。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"xiyuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/xizi1" : 2,
        ]));
	set("coor/x", -6970);
	set("coor/y", 2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}