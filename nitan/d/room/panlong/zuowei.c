// zuowei.c 左衛舍

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
//**    object ob;

        set("short", "左衛舍");             /* EXAMPLE */
//**    set("short", "ROOM_NAME左衛舍");
        set("long", @LONG
這裡是左衛舍，是看護大門的家丁放哨的地方。當然現在是空空
盪盪，沒有一個人。
LONG );

        set("default_long", "這裡是左衛舍，是看護ROOM_NAME大門的家丁放" /* EXAMPLE */
                            "哨的地方。");                              /* EXAMPLE */
                                                                        /* EXAMPLE */

        set("exits", ([
                "west"   : __DIR__"qianting",
        ]));

//**    set("objects", ([
//**            "/d/room/roomnpc/shouwei" : 2,
//**    ]));

        set("no_sleep_room", 1);
        setup();

//**    ob = present("shou wei", this_object());
//**    ob->set("coagents", ({
//**            ([ "startroom" : __DIR__"zuowei",
//**               "id"        : "shou wei 1" ]),
//**            ([ "startroom" : __DIR__"zuowei",
//**               "id"        : "shou wei 2" ]),
//**            ([ "startroom" : __DIR__"youwei",
//**               "id"        : "shou wei 2" ]),
//**            ([ "startroom" : __DIR__"youwei",
//**               "id"        : "shou wei 1" ]),
//**    }));

//**    ob = present("shou wei 2", this_object());
//**    ob->set("coagents", ({
//**            ([ "startroom" : __DIR__"zuowei",
//**               "id"        : "shou wei 1" ]),
//**            ([ "startroom" : __DIR__"zuowei",
//**               "id"        : "shou wei 2" ]),
//**            ([ "startroom" : __DIR__"youwei",
//**               "id"        : "shou wei 2" ]),
//**            ([ "startroom" : __DIR__"youwei",
//**               "id"        : "shou wei 1" ]),
//**    }));

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}