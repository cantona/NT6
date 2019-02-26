// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;
 
int do_pick(string arg);

void create()
{
        set("short", "山洞");
        set("long", @LONG
你正處在一個小山洞中。這裏光線很暗，只能隱隱約約看出地上有一
堆乾草。乾草上好像放着一個石匣(xia)。你突然聞到一股難聞的氣味，
顯然是有人長期住在這裏卻不打掃的緣故。
LONG );   
        set("item_desc", ([
                "xia" : @TEXT
你仔細看了一下石匣，發現裏面似乎放着一本書，似乎可以試着拿出來
(pick book)。
TEXT
        ]) );
        set("exits", ([
                "out"  : __DIR__"road4",
        ]));
        set("objects", ([
                // __DIR__"npc/zhou" : 1,
        ]) );    
        set("coor/x", 8990);
        set("coor/y", -2930);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_pick","pick");
}
void reset()
{
        ::reset();
        set("get_available" , 1);
}
int do_pick(string arg)
{
        object me,obj;
        me = this_player();
        
        if( !arg || arg!="book" )
              return notify_fail("你要拿什麼?\n");
              
        obj = present("zhou botong",environment(me));
        if (obj && living(obj))        
        {
                message_vision(YEL "周伯通兩眼一瞪，哼了一聲道：別在我這裏偷偷摸摸！"
                               "我周伯通還沒死哪！\n" NOR,me) ;
                return 1 ;
        }
        if ( query("get_available") )  
        {
                obj = new ("/clone/book/jiuyin1");
                obj->move(me);
                addn("get_available", -1);
                message_vision("$N從石匣中取出一本書。\n",me );
        } else
                return notify_fail("你要拿起那本書，卻發現你看花了眼，其實那裏什麼都沒有。\n");
        return 1;
}