// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "墓室");
        set("long", @LONG
墓室正中是一道香案，案上供著黃藥師夫人馮氏靈位，靈前有兩盞琉
璃燈，昏黃的燈光映著黃藥師手繪的夫人遺像(portrait)。墓室中壁間案
頭盡是古物珍玩，名畫書法，無一不是價值連城的精品。黃藥師當年縱橫
湖海，搜羅的奇珍異寶不計其數，這時都供在亡妻墓室之中；只見珍寶中
那些明珠美玉、翡翠瑪瑙之屬在燈光下發出淡淡光芒。靈案後一道氈帷，
後面是馮氏的玉棺。
LONG );
        
        set("item_desc", ([
                "portrait" : 
"\n黃夫人馮氏面目栩栩如生；當真是天妒紅顏，一代佳人竟爾早夭。\n"
        ]));

        set("exits", ([
                "out" : __DIR__"didao",
        ]));

        set("objects", ([
                "/d/taohua/obj/coffin" : 1,
        ]));
        
        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        object ob;
        
        ob = present("coffin", environment(me));
        delete("opened", ob);
        set("long", "這是一具由整塊白玉雕成的石棺，晶瑩光潔，實是曠世難尋的珍物。\n", ob);
          
        return ::valid_leave(me, dir);
}

int is_container() { return query("opened"); }
