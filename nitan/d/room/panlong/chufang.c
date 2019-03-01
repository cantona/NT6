// chufang.c 盤龍居廚房

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

string *names = ({
        "/d/shaolin/obj/mala-doufu",
        "/d/shaolin/obj/bocai-fentiao",
        "/d/shaolin/obj/shanhu-baicai",
        "/d/shaolin/obj/liuli-qiezi",
        "/d/shaolin/obj/mizhi-tianou",
        "/d/shaolin/obj/jiaxin-biji",
        "/d/shaolin/obj/basi-shanyao",
        "/d/shaolin/obj/furong-huagu",
});

void create()
{
        set("short", "廚房");
        set("long", @LONG
此處便是盤龍居的廚房，武功再高終究也不能辟谷，飯總是要吃的。
LONG );

        set("default_long", "此處便是ROOM_NAME的廚房，只間幾個僕人忙來"/* EXAMPLE */
                            "忙去，不得歇息。");                       /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "east" : __DIR__"houyuan",
        ]));

//**    set("objects", ([
//**            names[random(sizeof(names))] : 1,
//**            names[random(sizeof(names))] : 1,
//**            names[random(sizeof(names))] : 1,
//**            "/d/room/roomobj/rice"  : 2,
//**            "/d/room/roomobj/soup"  : 2,
//**            "/d/room/roomobj/mantou": 3,
//**            "/d/room/roomnpc/puren" : 2 + random(3),
//**    ]));

//**    set("resource/water", 1);
        set("no_sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}