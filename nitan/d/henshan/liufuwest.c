inherit ROOM;

void create()
{
        set("short", "劉府西廂房");
        set("long", @LONG
這兒是西廂房，這兒整理得幹幹凈凈，窗外露出點綠綠的枝葉，
家具上一塵不染，地上舖著很大塊的青磚，一點灰塵也不沾。劉府的
小孩們不知在這裡悄悄說著什麼。
LONG );
        set("exits", ([
               "east"   : __DIR__"liufudating",
        ]));

        set("objects", ([
                __DIR__"npc/liujing" : 1,
                __DIR__"npc/liuqin"  : 1,
        ]));

        setup();
        replace_program(ROOM);
}