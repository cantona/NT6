// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
#include <ansi.h>

inherit ROOM;

int do_pigua();

void create()
{
        set("short", "清音洞");
        set("long", @LONG
此洞面南背北，加之洞口狹小，是以終年不見陽光。但奇怪的是洞內
十分幹燥，也沒有什麼蟲豸。洞壁(wall)上有一些模模糊糊的人形，作撲
擊格鬥之狀，像是桃花島的一些基本武學圖解。
LONG );
        set("item_desc", ([
                "wall" : " 壁上有十數個人形，或縱高伏低，或儲勢待發，每一個都捏著不同指訣，甚為靈動，\n"
                         "似乎是桃花島的一套奇門武學打根基的招式。\n",
        ]));
         set("exits", ([
                "out" : __DIR__"tzfeng",
        ]));

        set("coor/x", 9030);
        set("coor/y", -2970);
        set("coor/z", 20);
        setup();
//        replace_program(ROOM);
}

void init()
{
        add_action("do_tanzhi", "tanzhi");
        add_action("do_use", "use");
}

int do_use(string arg)
{
        object me = this_player();

        if (! arg || arg == "") 
                return 0;
        if (! present("fire", me))  
                return 0;
        if (arg == "fire") 
        {
                tell_object(me, "借著火光映照，你向洞中深處走去。\n");
                     me->move(__DIR__"neidong");
        }
        return 1;
}

int do_tanzhi()                
{
        object me, ob, *inv; 
        int check, i;

        me = this_player();

        ob = present("tie bagua", me);
        if( (ob) && (query("tanzhi", ob)<1) )
        {
                message_vision(CYN "你伸指向鐵八卦上的卦象彈去。\n" NOR, me);
                message_vision(HIW "鐵八卦“咯哧”一聲壞掉了！\n" NOR, me);
                if (ob->query_amount() > 1) 
                {
                        ob->add_amount(-1);
                        set("tanzhi", 200, ob);
                } else    
                        destruct(ob);
                return 1;
        }

        if ((int)me->query_skill("finger", 1) >= 30
        &&  (int)me->query_skill("finger", 1) <= 100 
        &&  present("bagua", me))
        {
                check = (int)me->query_skill("finger", 1) *
                        (int)me->query_skill("finger", 1) *
                        (int)me->query_skill("finger", 1);
                        
                if( check<query("combat_exp", me)*10 && query("jing", me)>50 )
                {
                             me->receive_damage("jing", random(40));
                              me->improve_skill("finger",query("int", me)*2);
                              tell_object(me, CYN "你伸指向鐵八卦上的卦象彈去。\n" NOR);
                        tell_object(me, "你領悟了基本指法方面的幾個疑難。\n");
                             addn("tanzhi", -1, ob);
                } else 
                if( check<query("combat_exp", me)*10 && query("jing", me)<30 )
                {
                              tell_object(me, "你精神無法集中。\n");
                } else 
                {
                        tell_object(me, "你實戰經驗不足，無法領悟基本指法。\n");
                }        
        } else 
        if ((int)me->query_skill("finger", 1) > 120) 
        {
                tell_object(me, HIC "只聽“錚”的一聲，鐵八卦發出一聲清響\n" NOR);
        } else 
        {
                tell_object(me, "什麼？\n");
        } 
         
        return 1;
}    
