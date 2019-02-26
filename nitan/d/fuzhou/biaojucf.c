// Room: /city/biaojucf.c

inherit ROOM;

void create()
{
        set("short", "鏢局廚房");
        set("long", @LONG
福威鏢局對夥計們十分款待，不但每月有薪金，而且還包吃住。這
裏就是夥計們一日三餐的地方。廚房的牆上掛滿了鍋碗瓢盆，還有一些
風乾的滷味兒。房中放着一張長台，長台的周圍擺着幾條長凳。
LONG
        );
        set("exits", ([
                "south" : __DIR__"biaojuhy",
        ]));
        set("objects", ([
                __DIR__"npc/hua" : 1,
        ]));
	set("coor/x", -101);
	set("coor/y", -6141);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}