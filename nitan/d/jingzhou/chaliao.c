inherit ROOM;

void create()
{
        set("short", "荊州茶僚");
        set("long", @LONG
這裡是荊州的茶僚，過往的路人多半都在這裡歇腳、補充幹糧，
水袋，屋裡正坐著些歇腳的人，或高聲談笑，或交頭接耳。你要想打
聽江湖掌故和謠言，這裡是個好所在。
LONG );
        set("resource/water", 1);
        set("exits", ([
                "east" : __DIR__"nandajie1",
        ]));
        set("objects", ([
                __DIR__"npc/afang" : 1,
        ]));
        set("coor/x", -7110);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}