inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
你的眼前是一條用漢白玉舖成的台階，一直向下延伸，兩邊的牆
壁都是花崗巖，牆上隔十來步就有一盞油燈，使你能看清周圍。
LONG );
        set("exits", ([
                "up" : __DIR__"huayuan",
                "northdown": __DIR__"midao2",
        ]));
        set("objects",([
                __DIR__"npc/nvlang" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (  (dir == "northdown")
            && (query("family/family_name", me) != "靈鷲宮" )
           && objectp(present("nv lang", environment(me))) )
         return notify_fail
                ("蒙面女郎伸手攔住你，說道：“對不起，本門重地，請回！”\n");
        return ::valid_leave(me, dir);
}