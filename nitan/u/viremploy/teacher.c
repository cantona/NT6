#include <ansi.h>
inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIY "【新手導師工作室】" NOR);
        set("long", @LONG
這裏是新手導師工作的地方，地上散落着各種紙片，留言版上
寫滿着工作記錄。
請將工作情況post到留言版，巫師會定期查詢。
LONG
);

        set("exits", ([
                "out" : "/d/city/kedian",
        ]));

        set("valid_startroom", 1);
        set("sleep_room", 1);
        set("no_fight", 1);

        setup();
        "/clone/board/teacher_b"->foo();
}

