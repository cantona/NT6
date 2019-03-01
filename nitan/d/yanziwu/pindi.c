//ROOM: /d/yanziwu/pindi.c

inherit ROOM;

void create()
{
        set("short", "品笛庭");
        set("long", @LONG
只見牆上掛有蕭管之類的樂器，桌上放有一沓樂譜，想是慕容世
家演練樂曲的所在了。在向西就到了太湖岸邊，向東則是慕容世家接
待賓客的龍鳳廳了。
LONG );
        set("exits", ([
            "east"  : __DIR__"longfeng",
            "west"  : __DIR__"bozhou",
        ]));

        set("objects", ([
                 __DIR__"npc/gongye"  : 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir != "east")
                return 1;

        if (guarder = present("gongye qian", this_object()))
                return guarder->permit_pass(me, dir);

        return 1;
}