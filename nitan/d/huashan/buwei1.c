inherit ROOM;

void create()
{
        set("short", "有所不為軒");
        set("long", @LONG
這就是華山掌門嶽不羣的居所「有所不為軒」，此處乃是前廳，
廳上掛着「正氣堂」三字匾額。廳中很寬敞，卻沒什麼擺設，靠牆放
着兩把交椅。這裏乃是嶽不羣議事及授徒的地方後面是寢室。
LONG );
        set("exits", ([
                    "north" : __DIR__"buwei2",
                    "south" : __DIR__"qunxianguan",
                    "west"  : __DIR__"garden",
                    "east"  : __DIR__"buwei3",
        ]));
        set("objects", ([
                     __DIR__"npc/dayou" : 1,
                "/clone/quarry/hou" : 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object guard;

        if (dir == "south" ||
            ! objectp(guard = present("lu dayou", this_object())))
                return ::valid_leave(me, dir);

        return guard->permit_pass(me, dir);
}