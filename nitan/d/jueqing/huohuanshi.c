inherit ROOM;

void create()
{
        set("short", "火浣室");
        set("long", @LONG
這裡便是絕情谷的火浣室。谷主規定每日有一個時辰焚燒
烈火。
LONG);
        set("exits", ([
               "south"   : __DIR__"shufang",
               "north"   : __DIR__"danfang",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}