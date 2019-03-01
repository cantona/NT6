inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是個長廊，通向西練武場，人們急沖沖的走過，不時有
人被抬出來，看樣子是練功脫力昏倒的。
LONG);
        set("no_fight", 1);
        set("exits", ([
               "west" : __DIR__"guofu_wuchang1",
               "east" : __DIR__"guofu_dayuan",
        ]));
        setup();
        replace_program(ROOM);
}