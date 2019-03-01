inherit ROOM;

void create()
{
        set("short", "戲院後台");
        set("long", @LONG
這裡是長安戲院的後台，後台不大，卻打掃得很幹凈。幾個戲子
正在後台化妝，看見你來了，都用很奇怪的眼神盯著你。
LONG );
        set("exits", ([
                "south" : "/d/beijing/xiyuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/q" : 10,
        ]));

        setup();
        replace_program(ROOM);
}

