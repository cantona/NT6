inherit ROOM;

void create()
{
        set("short", "衡陽茶館");
        set("long", @LONG
你一進來，就聞到一股茶香沁入心脾，精神為之一爽。幾張八仙
桌一字排開，四周坐滿了客人，或高聲談笑，或交頭接耳。你要想打
聽江湖掌故和謠言，這裡是個好所在。
LONG );
        set("resource/water", 1);

        set("exits", ([
               "north" : __DIR__"hengyang",
        ]));

        set("objects", ([
                __DIR__"npc/chaboshi" : 1,
        ]));

	set("coor/x", -6890);
	set("coor/y", -5710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}