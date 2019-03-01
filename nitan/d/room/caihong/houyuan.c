// houyuan.c 彩虹居後院

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "後院");             /* EXAMPLE */
//**    set("short", "ROOM_NAME後院");
        set("long", @LONG
這是彩虹居的後院，種著一些花草，大部分是都不知名的野生花草。
不過花兒開起來也看上去也非常漂亮。主人如果讀書練武疲倦了，就可
以到這裡稍作休息，院角放著一張籐椅。
LONG );

        set("default_long", "這是ROOM_NAME的後院，種著一些花草，大"  /* EXAMPLE */
                            "部分是都不知名的野生花草。不過花兒開起" /* EXAMPLE */
                            "來也看上去也非常漂亮。有時ROOM_OWNER讀" /* EXAMPLE */
                            "書練武疲倦了，就到這裡稍作片刻以休息，" /* EXAMPLE */
                            "也有時友人來到這裡，大家在這裡切磋一下" /* EXAMPLE */
                            "武藝。");                               /* EXAMPLE */
                                                                     /* EXAMPLE */
        setup();

        set("exits", ([
                "south"  : __DIR__"dating",
        ]));

        set("outdoors", "OUTDOORS");
        set("sleep_room", 1);

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
        add_action("do_sit", "sit");
        delete_temp("has_sit", this_player());
}

int do_sit(string arg)
{
        object me;

        me = this_player();
        if( query_temp("has_sit", me) )
        {
                message_vision("$N坐在那裡搖啊搖，好不愜意。\n", me);
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