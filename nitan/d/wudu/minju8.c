inherit ROOM;

void create()
{
        set("short", "灶房");
        set("long", @LONG
這是一個簡陋的灶房，四壁都被煙火熏的黑糊糊的，灶台旁的牆
上貼著一張發黃的黃裱紙，旁邊掛著一些風幹的獸肉。灶台鐵鍋旁的
水缸上擺著幾只粗瓷大碗，屋的一角堆著一大堆麥秸。 
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