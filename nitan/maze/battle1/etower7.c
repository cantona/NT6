// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","炮台");

        set("long",@LONG
這裏居然是一座高高的炮台，真是令人難以置信。從這裏可以看到試劍山莊
的每一個角落，但見紅磚青瓦，風光無限。可是其中掩藏的殺機，卻令人不寒而
慄。眾武林高手，一聲不坑地嚴陣以待。
LONG);

        set("exits",([
                "down" : __DIR__"etower6",
        ]));

        set("objects", ([
                __DIR__"obj/pao"     : 1,
                __DIR__"obj/huoyao"     : 2,
                __DIR__"obj/dantou"     : 5,
        ]));

        set("outdoors", "battle");
        setup();
}
