// zhulin.c 盤龍居竹林

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "竹林");
        set("long", @LONG
這裏種着好大一片竹林，非常幽靜。風一起就聽竹葉沙沙的響。
LONG );

        set("default_long", "這裏種着好大一片竹林，非常幽靜。風一起就" /* EXAMPLE */
                            "聽竹葉沙沙的響，有時ROOM_OWNER就去聽濤閣" /* EXAMPLE */
                            "默聽竹浪濤聲，參悟武功。");               /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "west" : __DIR__"huayuan",
                "east" : __DIR__"tingtao",
        ]));

        set("outdoors", "OUTDOORS");
        set("sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}