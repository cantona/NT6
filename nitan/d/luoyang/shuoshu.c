inherit ROOM;

void create()
{
        set("short", "說書大廳");
        set("long", @LONG
這裡就是說書大廳，一位四十多歲的中年人正坐在大廳中央手拿折扇
，搖頭晃腦說個不停，三國演義，楚漢相爭，薛綱反唐，大隋唐，明英烈，
西遊記，水滸傳等等，這位說書先生是樣樣精通，正說的唾液橫飛。周圍
的人聽的是津津有味，不住的點頭稱道。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"chalou2",
        ]));
        set("objects", ([
                "/d/beijing/npc/chaboshi" : 1,
                "/d/beijing/npc/teahuoji" : 1,
                "/d/beijing/npc/chake" : 4,
        ]));
	set("coor/x", -7010);
	set("coor/y", 2160);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}