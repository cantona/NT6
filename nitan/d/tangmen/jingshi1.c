//jingshi1.c                四川唐門—靜室

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "靜室");
        set("long",
"這是一間靜室。這裏是唐門弟子吐納、打坐的地方，這裏非常安靜，\n"
"沒有一絲聲音。屋中沒有任何擺設，只是在地上扔着十幾個蒲團有幾名弟\n"
"子正盤坐在上面用心練功。\n"
);
        set("no_steal", "1");
        set("no_fight", "1");
        set("exits", ([
                "south" : __DIR__"nzlangw2",
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}