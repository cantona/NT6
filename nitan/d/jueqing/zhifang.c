#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "芝房");
        set("long", @LONG
這裏是絕情谷儲藏各類藥材的地方，只見牆角放着一個藥
櫃(chest)，陣陣藥味從中散發出來。

         =====未完待續。。。。=====
LONG);

        set("item_desc",([
               "chest" : HIC "這是儲藏藥物的櫃子，想必裏面定是藏着許多珍貴的藥材。\n" NOR,
        ]));

        set("exits", ([
               "east"   : __DIR__"houtang",
        ]));

        set("no_clean_up", 0);

        setup();
}

void init()
{       
        add_action("do_open", ({ "open" }));
}

int do_open(string arg)
{
        object me = this_player();
        object ob;

        if (! arg || arg != "chest")
                return notify_fail("你要做什麼？\n");


       return 1;
}

