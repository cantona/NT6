inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是一條通往萬安寺後殿的木制走廊，走廊裡靜悄悄的，沒什麼人走動。後
方是萬安寺的大殿了。
LONG );
        set("exits", ([
                "north" : "/d/tulong/yitian/was_houdian",
                "south" : "/d/tulong/yitian/was_dadian",
        ]));

        setup();
}
