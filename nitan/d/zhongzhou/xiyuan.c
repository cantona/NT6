inherit ROOM;

void create()
{
        set("short", "戲院");
        set("long", @LONG
這是戲院的大廳，裡面台上唱戲正唱的歡呢。你剛站定就
有兩三個彪行大漢來勢兇兇上前，不知要發生什麼事。
LONG);
        set("exits", ([
                "east" : __DIR__"wendingbei2",
                "south" : __DIR__"liangongfang",
                "west" : __DIR__"xiyuan1",
                "north" : __DIR__"sushe",
        ]));

        set("objects",([
                "/d/beijing/npc/guanzhong" : 3,
        ]));

        set("coor/x", -9050);
	set("coor/y", -980);
	set("coor/z", 0);
	setup();
}