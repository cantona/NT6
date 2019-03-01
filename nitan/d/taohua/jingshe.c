// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "精舍");
        set("long", @LONG
這座精舍全是以綠色大方竹搭成，屋外攀滿青籐，使人一見之下心中
頓生涼意。周圍環以奇花異草，聞之足可忘俗。精舍雖看似粗糙，但細觀
之下，卻發覺精舍竟與四周景物渾然天成，如同自然生成的一般，當真是
巧奪天工，好一片清涼洞天。西面有條小徑通向桃花深處，門前有一對白
雕(diao)。
LONG );
         set("exits", ([
                       "west"  : __DIR__"taolin",
                "south" : __DIR__"bibochi",
                "enter" : __DIR__"shuilong",
        ]));

        set("item_desc", ([
                "diao" : "一對白雕正展翅欲飛。如果是桃花島的弟子，\n"
                "騎上(mount)就可以飛到中原。\n",
        ]));
        
         set("objects", ([
                 "/d/taohua/npc/shagu" : 1,
                "/d/taohua/npc/shitong" : 1,
                CLASS_D("taohua") + "/first" : 1,
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
        "/clone/board/taohua_b"->foo();
}

int valid_leave(object me, string dir)
{

        if( (query("family/master_name", me) != "程英" )
         && (query("family/master_name", me) != "黃藥師" )
         && userp(me)
         && (!query_temp("shagu_pass", me) )
        && (dir == "enter")
        && present("sha gu", this_object()) )
        return notify_fail("\n傻姑傻笑了幾聲，伸開雙手一攔，說到：要進去先陪我玩一會兒吧，\n這裡人都不理我，悶死了！\n");
        return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_ride", "mount");
}
int do_ride(string arg)
{
        mapping myfam;
        object ob = this_player () ;
        
        myfam=query("family", ob);
/*
        if( !myfam || myfam["family_name"] != "桃花島" || !query("out_family", ob) )
        {
                message_vision("$N一躍身跨上了白雕。只見白雕仰天長唳，突然猛然一顛......\n" +
                               HIR "結果$N摔了個鼻青臉腫！\n" NOR +
                               "看來白雕對$N並不感興趣，它只認識桃花島的弟子。\n" , ob ) ;
                ob -> receive_damage ("qi", 50) ;
                ob -> receive_wound  ("qi", 50) ;
                return 1;
        }
*/
        if( (int)query("sb_ride") ) 
                return notify_fail("現在白雕正忙著,請過一會再乘坐!\n" ) ;
        addn("sb_ride", 1) ;
        message_vision("$N一躍身跨上了白雕。只見白雕仰天長唳，突然展翅高飛。\n\n"
                       "但看一雕一人身形漸漸縮小，終至不見。\n" , ob );
        ob->move("/d/taohua/lantian") ;
        tell_object(ob, CYN  "\n你不斷地飛呀飛，萬水千山身下飄過 ......\n\n" NOR ) ;
        call_out("taohua", 2 , ob );
        addn("sb_ride", -1) ;
        return 1 ;
}
void taohua( object ob )
{
        if (base_name(environment(ob)) != "/d/taohua/lantian")
                return;
        tell_object(ob, "你終于飛到了中原，白雕落了下來。\n\n"  ) ;
        ob -> move ("/d/guiyun/dayuan");
}
