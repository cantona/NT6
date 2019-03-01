inherit ROOM;

void create()
{
        set("short", "郭府大院");
        set("long", @LONG
這是個大院子，東西兩邊都是練武場，不少人在這裡習武
強身，這裡很吵，亂哄哄的，你看見不時有扛著東西的，挑著
水的匆匆而過。
LONG);
        set("no_fight", 1);
        set("exits", ([
                "south" : __DIR__"guofu_gate",
                "north" : __DIR__"guofu_dayuan2",
                "east" : __DIR__"guofu_lang2",
                "west" : __DIR__"guofu_lang1",
        ]));
        set("valid_startroom", 1);
        setup();
        replace_program(ROOM);
}
