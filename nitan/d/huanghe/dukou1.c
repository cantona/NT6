#include <ansi.h>
inherit RIVER;

void create()
{
        set ("short", "黃河渡口");
        set ("long", @LONG
渡口前就是洶湧澎湃的黃河 (river)了。濁流滾滾，泥沙
俱下，聲震數裡。兩岸渡船來來往往，在波谷中穿行，甚為兇
險。過了黃河，就是華北了。
LONG);
        set("to", "/d/beijing/dukou2");
        set("exits", ([
                "south" : __DIR__"huanghe4",
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu",
        }));

        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        setup();
        replace_program(RIVER);
}
