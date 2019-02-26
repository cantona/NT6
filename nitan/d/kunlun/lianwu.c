// Room: /d/kunlun/lianwuchang.c
// Last Modified by winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "練武場");
        set ("long", @long
這裏是練武場，崑崙派的很多弟子在這裏練習武功，在練武場的一
角，有一個專門用來練武的梅花樁(zhuang)，許多弟子都圍在這裏練習
腿功。
long);
        set("exits",([
                "west" : __DIR__"huayuan1",
        ]));
        set("item_desc", ([
                "zhuang" : "這是一片梅花樁，跳上去可以練習腿功，許多弟子在上面扎馬(zhama)。\n",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -119980);
        set("coor/y", 40080);
        set("coor/z", 90);
        setup();
}
int init()
{
        add_action("do_zhama","zhama");
}

int do_zhama(string arg)
{
        object me;
        me = this_player();
        if ( !living(this_player()) || arg != "zhuang" )
                return notify_fail("你要在哪扎馬？\n");
        if ((int)me->query_skill("leg", 1) > 100)
                return notify_fail("你的腿功已經很高了,這種練習對你沒什麼作用。\n");
        if( query("qi", me)<30 )
        {
                me->receive_damage("qi", 10);
                write("你的腿已經酸了,還是先休息一會吧！\n");
                return 1;
        }
        me->receive_damage("qi", random(25));
        message_vision("$N正在梅花樁上扎着馬步。\n", me);
        write("你全神貫注的在梅花樁上紮了一柱香時間的馬步，感覺基本腿法又進了一步。\n");
        me->improve_skill("leg", me->query_int());
        return 1;
} 