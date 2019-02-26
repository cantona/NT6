//lianyunge.c                四川唐門—蓮雲閣

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "蓮雲閣");
        set("long",
"這裏是蓮雲閣。這裏是一個極大、至廣闊的建築，共有七十二道柱樑\n"
"每個樑柱上都栩栩如生的雕着麒麟、龍鳳、犀、饕餮等七十二種不同的奇\n"
"珍異獸。天花板中央雕了個遒勁萬鈞的“唐”字，令人讚歎的是地板上竟\n"
"也十分逼真的刻有齊天大聖鬧天宮，而正中廳堂則是太上老君將孫悟空放\n"
"在丹爐裏熬煉的雕畫手工，堪稱絕世精品，可是更令人驚詫的是，地板並\n"
"不因為這些雕刻而有絲毫凹凸不平，反而還十分平滑，似走在堅冰上一般！\n"
);
        set("exits", ([        
                        "east"  : __DIR__"eting",
                        "west"  : __DIR__"wting",
                        "north" : __DIR__"nzlang1",
                        "south" : __DIR__"shuige2",]));
        set("objects", ([
                CLASS_D("tangmen") + "/tangtian" : 1,
                CLASS_D("tangmen") + "/first" : 1,
        ]));
//        set("length",20);
        set("valid_startroom",1);
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}
