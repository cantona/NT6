inherit ROOM;

void create()
{
        set("short", "靜室");
        set("long", @LONG
這是一個昏暗的房間，除了幾張牀之外什麼都沒有。室內光線昏
暗，你不由的打了一個哈欠。
LONG);
        set("sleep_room", 1);
        set("no_fight", 1);

        set("exits", ([
                "north" : __DIR__"dating",
        ]));

        setup();
        replace_program(ROOM);
}