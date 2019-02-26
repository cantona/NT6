// /d/tangmen/qianzhuang.c

#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "唐氏錢莊");
        set("long",
"蜀中唐門的錢莊，已有三多百年的歷史了，信譽是一流的。老闆也是\n"
"唐門中比較有威信的人擔任，不是一般的人所能勝任的。而且這裏的銀票\n"
"全國通用，是不可多有的老字號了。\n"
);
        set("exits", ([
                "north" : __DIR__"edajie",
        ]));
        set("objects", ([
               "/d/tangmen/npc/tangq" : 1
        ]));
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        setup();
}

