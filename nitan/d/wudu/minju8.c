inherit ROOM;

void create()
{
        set("short", "灶房");
        set("long", @LONG
這是一個簡陋的灶房，四壁都被煙火薰的黑糊糊的，灶台旁的牆
上貼着一張發黃的黃裱紙，旁邊掛着一些風乾的獸肉。灶台鐵鍋旁的
水缸上擺着幾隻粗瓷大碗，屋的一角堆着一大堆麥秸。 
LONG);

        set("exits", ([
                "east" : __DIR__"minju3",
        ]));
        set("objects", ([
                  __DIR__"obj/qhcwan": 2,
                  __DIR__"obj/shourou2": 1,
                  __DIR__"obj/shourou1": 1,
        ]));
        setup();
        replace_program(ROOM);
}