// hhuayuan.c 盤龍居花園

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "後花園");
        set("long", @LONG
這是盤龍居的後花園，種着一些採自五湖四海，名山大川的奇花
異草，美麗非常。主人有時讀書練武疲倦了，就到這裏稍作休息，觀
賞花草以怡情自樂，或許能突發靈感，有所領悟。西面就是通往主人
居所的鐵門，東面則是一片竹林。
LONG );

        set("default_long", "這是ROOM_NAME的後花園，種着一些ROOM_OWNER"/* EXAMPLE */
                            "採自五湖四海、名山大川的奇花異草，美麗非" /* EXAMPLE */
                            "常。ROOM_OWNER有時讀書練武疲倦了，就到這" /* EXAMPLE */
                            "裏稍作休息，觀賞花草以怡情自樂，或許能突" /* EXAMPLE */
                            "發靈感，有所領悟。西面就是通往主人居所的" /* EXAMPLE */
                            "鐵門，東面則是一片竹林。");               /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "south"  : __DIR__"houyuan",
                "east"   : __DIR__"zhulin",
                "west"   : __DIR__"jusuo",   /* EXAMPLE */
        ]));

        set("outdoors", "OUTDOORS");
        set("sleep_room", 1);
//**    set("room_key", "ROOM_KEY");
        setup();

//**    set("KEY_DOOR", ([
//**            "exit" : "west",
//**            "room" : __DIR__"jusuo",
//**    ]));
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
//**    ::init();
        add_action("do_sit", "sit");
        delete_temp("has_sit", this_player());
}

int do_sit(string arg)
{
        object me;

        me = this_player();
        if( query_temp("has_sit", me) )
        {
                message_vision("$N坐在那裏搖啊搖，好不愜意。\n", me);
                return 1;
        }

        message_vision("$N找了的地方作了下來，看上去輕鬆多了。\n", me);
        set_temp("has_sit", 1, me);
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query_temp("has_sit", me) )
        {
                message_vision("$N撣撣塵土，站了起來。\n", me);
                delete_temp("has_sit", me);
        }

        return ::valid_leave(me, dir);
}