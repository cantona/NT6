// houyuan.c 盤龍居後院

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "後院");
        set("long", @LONG
這是盤龍居的後院，正中一個假山，傲然而立、非常雄偉。下有
一水池，環山而走，悠然不息。東面乃是練武之處，西面是傭人們準
備食物的廚房。
LONG );

        set("default_long", "這是ROOM_NAME的後院，正中一個假山，傲然而"/* EXAMPLE */
                            "立、非常雄偉。下有一水池，環山而走，悠然" /* EXAMPLE */
                            "不息。東面乃是練武之處，西面是廚房。");   /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "south" : __DIR__"zhongting",
                "north" : __DIR__"huayuan",
                "east"  : __DIR__"lianwu",
                "west"  : __DIR__"chufang",
        ]));

        set("outdoors", "OUTDOORS");
        set("no_sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}