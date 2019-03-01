// Room: /t/wanjiegu/left_room.c

inherit ROOM;

void create()
{
        set("short", "左廂房");
        set("long", @LONG
這是一間普通的房間，裏面放着一些日常用品。桌子上放着一壺
茶，還沒有冷掉。旁邊一個大櫃子，裏面放着許多衣服。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "north" : __DIR__"bed_room",
            "east" : __DIR__"hall",
        ]));

        set("objects", ([
            __DIR__"npc/xier" : 1,
        ]));
//        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}