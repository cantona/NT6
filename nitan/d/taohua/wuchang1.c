inherit ROOM;

void create()
{
        set("short", "修行場");
        set("long", @LONG
這裡是桃花島彈指山莊修行的場所，大部分的桃花島弟子
武功有了一定的根基以後就在這裡苦修，領悟上乘武學。
LONG);
        set("exits", ([
                "northwest" : __DIR__"houyuan",
        ]));

        set("for_family", "桃花島");
        set("outdoors", "taohua");
        setup();
        replace_program(ROOM);
}