// fangjian3.c
// Modified by Winder June.25 2000

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "房間");
        set("long", @LONG
你只覺得眼前陡然一亮，一個宮裝的美女，正拿著一把長劍，對準
了你的胸膛！。。。。一場虛驚之後，你才發現原來只是個白玉雕成的
玉像，但是看上去卻與真人一般無異。玉像的一雙眸子瑩然有光，神採
飛揚。你此時只覺得神馳目眩，竟如著魔中邪，眼光再也離不開玉像。
。。。
LONG );
        set("exits", ([
                "east"    : __DIR__"tongmen",
                "northup" : __DIR__"shiji4",
        ]));
        set("objects",([
                __DIR__"obj/putuan" : 1,
        ]));
//        set("no_clean_up", 0);
        set("book_count",1);
        set("coor/x", -50010);
        set("coor/y", -21020);
        set("coor/z", -40);
        setup();
}

void init()
{
        set_temp("ketou_times", 50, this_player());
        add_action("do_kneel", "kneel");
        add_action("do_ketou", "ketou");
}

int do_kneel(string arg)
{
        object me,room,weapon;
        me = this_player();
        if ( !arg || arg == "") return 0;
        if ( arg != "putuan") return 0;
        if (!present("putuan",environment(me))) return 0;
        if( query_temp("marks/kneel", me) == 1 )
                return notify_fail("你已經跪下來了。\n");
        message_vision("$N雙膝一屈，跪了下來。\n", me);
        addn_temp("marks/kneel", 1, me);
        return 1;
}

int do_ketou()
{
        object me, ob;

        me = this_player();
        if( !query_temp("marks/kneel", me))return 0;
        if (!present("putuan",environment(me))) return 0;
        if( query_temp("ketou_times", me) == 0 )
        {
                message_vision("$N磕頭太拼命了。\n", me);
                set_temp("ketou_times", random(50), me);
                me->unconcious();
                return 1;
        }

        addn_temp("ketou_times", -1, me);

        message_vision("$N恭恭敬敬地給玉像磕頭。咚、咚、咚。。。。\n", me);

        if ( random(100) == 37 
        && !present("bojuan", me)
        && query("book_count") >= 1)
        {
                addn("book_count", -1);
                ob=new("/clone/book/bojuan");
                if (ob->violate_unique()) {destruct(ob);return 1;}
                ob->move(me);
message("channel:rumor",MAG"【謠言】某人："+query("name", this_player())+"取到了北冥神功帛卷啦。\n"NOR,users());
                tell_object(me, "突然，你發現小蒲團面上的一層薄薄的蒲草已然破裂，露出下面有物！\n");
                tell_object(me, "你急忙把它拿了出來。\n");
        }

        return 1;

}

int valid_leave(object me, string dir)
{
        if( query_temp("ketou_times", me) >= 0)delete_temp("ketou_times", me);
        if( query_temp("marks/kneel", me))delete_temp("marks/kneel", me);
        return ::valid_leave();
}