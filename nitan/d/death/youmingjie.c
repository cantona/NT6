// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM; 

int num_of_killer;
string call_killer();

void create() 
{ 
        set("short", HIB "幽冥界" NOR);
        set("long", HIB @LONG
幽冥界，你疑心怎麼從酆都走到這裡來了的。四處彌漫著濃厚的煙
霧，你什麼也看不清楚，空中浮動著若隱若現的鬼火，周圍似乎有一雙
雙眼睛盯著你看，你走了幾步，看見地上斜插著一塊石碑(shibei)，你
連忙俯身下去看上面的字。

LONG NOR);
        set("no_clean_up", 0);
        set("item_desc", ([
                "shibei" : (: call_killer :),
        ]));

        set("objects", ([
        ]));
        
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"youmingdian",
                "south" : "/d/death/qiao2",
        ]));
       
        set("no_magic", 1);
        setup();
        reset();
}

void reset()
{
        ::reset();
        num_of_killer = 5;
}

string call_killer()
{
        object ob;
        if (num_of_killer == 0) 
        return "石碑上寫著幾個血紅的大字：
"HIR"        酆 都 鬼 域 幽 冥 地 府 ！！"NOR"
忽然你覺得背後似乎有腳步聲，于是猛然回頭一看。。。
什麼也沒發現，原來是虛驚一場。\n";
        num_of_killer --;
        if (num_of_killer == 1)
        ob = new(__DIR__"npc/qinguangwang");
        else
        ob = new(__DIR__"npc/ghost");
        ob->move("/d/death/youmingjie");
        return "石碑上寫著幾個血紅的大字：
"HIR"        酆 都 鬼 域 幽 冥 地 府 ！！"NOR"
忽然你覺得背後似乎有腳步聲，于是猛然回頭一看。。。\n";
}

