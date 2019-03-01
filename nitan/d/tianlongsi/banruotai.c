inherit ROOM;

void create()
{
        set("short", "般若台");
        set("long", @LONG
這是個普通的石台，相傳當年佛祖曾降臨此台傳法。再往南去就
是本寺重地──牟尼堂。江湖中傳言天龍寺的鎮寺之寶──六脈神劍
譜就藏于此中。
LONG );
        set("exits", ([
                "south" : __DIR__"munitang",
                "north" : __DIR__"doushuai",
        ]));
        setup();
}

string long()
{
        if (! stringp(query("exits/south")))
                return query("long") + "    奇怪的是大門緊"
                       "閉，不知道裡面怎麼回事。\n";

        return query("long");
}

int valid_leave(object me, string dir)
{
        if (me->query_condition("killer") && dir == "south")
                return notify_fail("那裡PKER不能進去。\n");

        return ::valid_leave(me, dir);
}