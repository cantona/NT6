inherit ROOM;

void create()
{
        set("short", "荒道");
        set("long", @LONG
這裡的地上是一種黃褐色，紅褐色的石礫鑲嵌在細細的黃
沙之中，給人以極其怪異的感覺。這裡就是西域與中原的中間
地帶，再往西就是邊塞。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                "west" : __DIR__"guandao2",
                "east" : "/d/lanzhou/road",
        ]));
        setup();
        replace_program(ROOM);
}
