inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是一條通往萬安寺大殿的木制走廊，走廊裡靜悄悄的，沒什麼人走動。前
面便是萬安寺的大殿了。大廳上燈火通明，非常的寬敞明亮。
LONG );
        set("exits", ([
                "north" : "/d/tulong/yitian/was_dadian",
                "south" : "/d/tulong/yitian/was_zoulang1",
        ]));

        setup();
}
