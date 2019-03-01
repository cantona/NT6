// fu-mishi.c 密室
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
這裡是一間密室，四周散布著幾條帶血的鞭子，還有一些各
種各樣的刑具。看來傳說果然不虛，這侯員外果真是個魚肉鄉裡
的惡霸。
LONG
        );
        set("exits", ([
                "northwest" : __DIR__"fu-midao",
                "up" : __DIR__"fu-woshi",
        ]));
        set("objects", ([
                "/clone/medicine/vegetable/xuejie" : 1,
        ]));
        set("coor/x", -3130);
        set("coor/y", -60);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}