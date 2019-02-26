// /guanwai/milin3.c

inherit ROOM;

void create()
{
        set("short", "密林");
        set("long", @LONG
這是一片茂密的松林，雜亂的生長在傾斜的山坡上。每棵松樹都有三四
抱粗細，高達十幾丈。樹冠枝多葉密，將天空完全遮住，因此林內顯得有些
昏暗。樹木之間長着很多灌木雜草，使行走很艱難，據説人蔘就生長在這些
雜草之中。
LONG );
        set("exits", ([
                "northdown"  : __DIR__"milin2",
                "eastup"     : __DIR__"heifengkou",
        ]));
        // 可打獵標誌
        set("can_hunting", 1);
        set("quarry", ([
             "hu"        :  10,
             "hu2"       :  6,
             "hu2"       :  6,  
             "lang"      :  70,
             "lang2"     :  80,
             "lang3"     :  25,
             "xiong"     :  8,
             "xiong2"    :  8,
             "diao"      :  10,
             "jizi"      :  50,
             "laohu"     :  20,
             "laohu2"    :  10,
             "lu"        :  20,
             "lu2"       :  15,
             "pao"       :  40,
                 "bao"       :  3,
         "song"      :  90,
        ]));

        set("no_clean_up", 0);
        set("outdoors", "changbai");
        setup();
        replace_program(ROOM);
}
