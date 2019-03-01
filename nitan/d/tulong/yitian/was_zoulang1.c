inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是一條通往萬安寺後廳的木制走廊，走廊裡靜悄悄的，沒什麼人走動。左
右兩旁是兩個側廳。
LONG );
        set("exits", ([
                "north" : "/d/tulong/yitian/was_zoulang2",
                "south" : "/d/tulong/yitian/was_dayuan",
                "east" : "/d/tulong/yitian/was_tinge",
                "west" : "/d/tulong/yitian/was_tingw",
        ]));

        setup();
}
