#include <room.h>
inherit ROOM;

void create()
{
        set("short", "學堂");
        set("long", @LONG
這裡是武館內的一個小學堂，堂內陣陣朗朗讀書聲，一個
先生在這裡認真的教著，這裡放滿了桌子和椅子，靠先生那邊
牆上寫了幾個大字少壯不努力，老大徒傷悲。
LONG);
        set("no_fight", 1);
        set("exits", ([
                "south" : __DIR__"guofu_shilu-1",
        ]));
        set("objects", ([
                __DIR__"npc/zhuziliu" : 1,
        ]) );
        setup();
        replace_program(ROOM);
}