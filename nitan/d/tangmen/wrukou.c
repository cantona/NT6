//wrukou.c  by winder

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "西較武場入口");
        set("long",
"這是唐門的西較武場入口。門口上面塊一金漆牌匾，“西較武場”幾\n"
"個大字寫得孔武有力，氣勢逼人，彷彿是幾件隨時可以橫空而出的暗器，\n"
"記載了唐門戰史的輝煌。這裏的西面，是西較武場的看台，東面是一條青\n"
"石小路。\n"
);        
        set("no_steal", "1");
        set("no_fight", "1");
        set("exits", ([
                "east" : __DIR__"nzlangn1",
                "west" : __DIR__"wkantai2",
        ]));
        setup();
        replace_program(ROOM);
}