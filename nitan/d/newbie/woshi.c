#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "卧室" NOR);
        set("long", @LONG
這是村長家卧房，因門窗常閉着，光線很昏暗。卧室裏別無他物，
只有中間放着一張收拾得舒舒服服的大牀，看着就讓人想睡覺（輸入
指令 sleep）。
LONG);
        set("exits", ([
                "south" : __DIR__"cunzhangjia",
        ]));

        set("xinshoucun", 1);
        set("no_clean_up", 0);
        set("sleep_room", 1);
        set("no_fight", 1);

        setup();

        replace_program(ROOM);
}