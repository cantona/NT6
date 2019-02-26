inherit ROOM;

void create()
{
        set("short", "捨身崖");
        set("long", @LONG
這是一處險峻的懸崖峭壁，相傳真武帝在此捨身得道。崖上立有
鐵柵欄，防止有人自殺步真武帝的後塵。
LONG );
        set("exits", ([
                "east" : __DIR__"nanyanfeng",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -320);
        set("coor/z", 110);
        setup();
        replace_program(ROOM);
}