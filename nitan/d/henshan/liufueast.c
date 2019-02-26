inherit ROOM;

int do_knock(string arg);

void create()
{
        set("short", "劉府東廂房");
        set("long", @LONG
這兒是東廂房，這兒整理得乾乾淨淨，窗外露出點綠綠的枝葉，
傢俱上一塵不染，地上鋪着很大塊的青磚，一點灰塵也不沾。
LONG );
        set("exits", ([
               "west"   : __DIR__"liufudating",
        ]));

        set("objects", ([
                __DIR__"npc/liufuren" : 1,
        ]));

        setup();
        replace_program(ROOM);
}