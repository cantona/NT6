//hcfdian.c

#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "藥舖");
        set("long",
"這是回春堂在唐門鎮的藥舖，一股濃濃的藥味讓你幾欲窒息，由此可\n"
"知這兒的藥是絕對正宗。但唐門人為什麼沒有開個藥店呢，原因很簡單：\n"
"唐門的藥是不賣的，只有唐門弟子才能亨用的。伙計站在櫃台後招呼著顧客。\n"
);
        set("objects", ([
                "/d/city/npc/huoji" : 1,
        ]));
        set("exits", ([
                 "east" : __DIR__"ndajie",
        ]));
        set("no_clean_up", 0);
        setup();
}
