//shufang.c

inherit ROOM;

#include <ansi.h>

void create()
{
        set("short","華山書房");
        set("long", @LONG
這裡是華山派的書房，靠牆是一排書架，裡面堆著亂七八糟的一
大堆書，最近老有人上山尋事，都很久沒人整理書房了，要找啥書都
很麻煩。右側有張書桌，桌上四寶俱備。
LONG );
        set("exits",([
                "north" : __DIR__"garden",
        ]));
        set("objects",([
                "/clone/book/zhengqi_book" : 1,
        ]));

        set("book_count", 1);
        setup();
}

void init()
{
        add_action("do_zhengli", "zhengli");
}

int do_zhengli()
{
        object ob, me=this_player();
        addn("qi", -5, me);
        if ((query("book_count") > 0) && (random(5) == 3))
        {
                message_vision(HIY "$N" HIY "辛辛苦苦整理了好半天，居然在"
                               "破雜物堆裡發現了一本書。\n"NOR,me);
                ob=new("/clone/book/sword_book2");
                ob->move(me);
                addn("book_count", -1);
        } else
                message_vision(HIY "$N" HIY "辛辛苦苦整理了好半天，啥都沒"
                               "找到，真是白忙了。\n"NOR,me);
        return 1;
}

void reset()
{
        ::reset();
        set("book_count", 1);
}
