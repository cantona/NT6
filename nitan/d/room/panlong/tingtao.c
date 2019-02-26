// tingtao.c 盤龍居聽濤閣

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "聽濤閣");
        set("long", @LONG
這是竹林一角的聽濤閣，在這裏風吹竹葉的陣陣濤聲聽的非常真
切，真是讓人心曠神怡。實在是一個參悟武功的好去處。
LONG );

        set("default_long", "這是竹林一角的聽濤閣，在這裏風吹竹葉的陣" /* EXAMPLE */
                            "陣濤聲聽的非常真切，真是讓人心曠神怡。實" /* EXAMPLE */
                            "在是一個參悟武功的好去處。");             /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "west" : __DIR__"zhulin",
        ]));

        set("sleep_room", 1);
        setup();

//**    set("research_improve", 15);  //15% improved
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}