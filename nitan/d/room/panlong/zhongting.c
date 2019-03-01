// zhongting.c 盤龍居中庭

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
//**    object ob;

        set("short", "中庭");             /* EXAMPLE */
//**    set("short", "ROOM_NAME中庭");
        set("long", @LONG
這是盤龍居之腰：中庭，兩旁便是客人居住的廂房，後面通往後
花園和主人居所，前面則是議事廳，一直通往大院。
LONG );

        set("default_long", "這是ROOM_NAME之腰：中庭，兩旁便是客人居"  /* EXAMPLE */
                            "住的廂房，後面通往後花園和主人居所，前面" /* EXAMPLE */
                            "則是議事廳，一直通往大院。");             /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "north"  : __DIR__"houyuan",
                "south"  : __DIR__"yishiting",
                "east"   : __DIR__"zuoxiang",
                "west"   : __DIR__"youxiang",
        ]));

        set("outdoors", "OUTDOORS");

//**    set("objects", ([
//**            "/adm/npc/shouwei" : 1,
//**    ]));

        create_door("east", "木門", "west", DOOR_CLOSED);
        create_door("west", "木門", "east", DOOR_CLOSED);

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

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

int valid_leave(object me, string dir)
{
        object ob;

        ob = present("shou wei", this_object());
        if (dir != "north" || ! objectp(ob) || ! living(ob))
                return ::valid_leave(me, dir);

        if (ob->is_owner(me))
        {
                message_vision("$N彎腰對$n道：“請進！”\n", ob, me);
                return ::valid_leave(me, dir);
        }

        if (ob->is_owner_permit(me))
        {
                message_vision("$N對$n道：“即然是主人的朋友，但進無妨。”\n",
                               ob, me);
                return ::valid_leave(me, dir);
        }

        if (present(query("room_owner_id") + " pass", me))
        {
                message_vision("$N對$n道：“即然有主人的手諭，就請進吧。”\n",
                               ob, me);
                return ::valid_leave(me, dir);
        }

        message_vision("$N伸手攔住$n，道：“對不起，沒有" +
                       query("room_owner") + "的手諭，不可擅自闖入！”\n", ob, me);
        return 0;
}