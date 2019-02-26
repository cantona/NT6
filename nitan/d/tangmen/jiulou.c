// jiulou.c

#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "唐門酒樓");
        set("long",
"這是唐家鎮有名的酒樓可以説是無人不知，無人不曉。所有人到此，\n"
"都要來這兒一醉方休，不醉不歸。據説對人的身體某些方面有好處，不過\n"
"沒有確定是不是的，因為醉過的人都是笑而不答。但你可以試一試啊。樓\n"
"下佈置簡易，樓上是雅座。老闆就在上面啊。不知有沒有福氣見見她啊！\n"
"見到她，説不定有什麼好處啊！\n"
);
        set("exits", ([
                "south" : __DIR__"xdajie",
                // "up"    : __DIR__"jiulou2",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
        set("no_fight", 1);
        set("resource/water", 1);
        set("no_steal", 1);
        setup();
}
