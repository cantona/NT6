inherit ROOM;

void create()
{
        set("short", "書房");
        set("long", @LONG
這是絕情谷的書房，但見四周整齊地擺放著各種書籍。書
房中央有一個雕有花紋的書桌和一張精致的木椅。
LONG);
        set("exits", ([
               "east"    : __DIR__"changlang1",
               "north"   : __DIR__"huohuanshi",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}