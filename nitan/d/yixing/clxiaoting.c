// /d/yixing/clxiaoting.c
// Last Modified by winder on Jul. 12 2002

#include <changle.h>
#define WOSHI   BANGS"clwoshi"
#define THE_BANGZHU BANGS"npc/cl_situ"
inherit ROOM;
#include "/d/yixing/doc/info_beauty.h" 

void create()
{
        set("short", "小廳");
        set("long", @LONG
這是幫主及總管商討機密大事的所在，正中是一張太師椅，門上吊
著半舊的紅綢軟簾。牆上附庸風雅地掛著幾張山水字畫，一望可知均是
俗手之作。窗前幾盆菊花倒是十分繁茂。
LONG );
        set("exits", ([
                "south" : __DIR__"clzoulang2",
                "north" : __DIR__"clwoshi",
        ]));
        set("objects",([
                __DIR__"npc/cl_situ" : 1,
        ]));
        set("coor/x", 279);
	set("coor/y", -981);
	set("coor/z", -1);
	setup();
}

int valid_leave(object me, string dir)
{
        string beauty;
        object ob, leader, ling, *inv;
        int bonus, record;

        if( dir != "north" )
                return ::valid_leave(me, dir);
        if( !(ob = present("situ heng", environment(me))) )
                return ::valid_leave(me, dir);
        if( !living(ob) )
                return ::valid_leave(me, dir);

        if( ob->is_fighting() || ob->is_busy() )
                return notify_fail(sprintf("%s攔在你面前，喝道：" + RANK_D->query_rude(me) + "不得無禮！沒見幫主正忙著？\n", ob->name()));

        if( stringp(beauty=query_temp("bangs/beauty", me)) )
        {
                inv = all_inventory(this_object());
                for(int i = 0; i < sizeof(inv); i++)
                {
                        if( query("name", inv[i]) == beauty && 
                                inv[i]->query_leader() == me )
                        {
                                message_vision("$N在$n的頭上彈了個清脆的腦崩兒，$n的腦門兒上立刻長出了個小臌包。\n", ob, me);
                                return ::valid_leave(me, dir);
                        }
                }
        }

        if( !userp(me) )
        {
                beauty=query("name", me);
                if( intp(bonus = info_beauty[beauty]) &&
                        leader = me->query_leader() )
                {
                        if( userp(leader) &&
                        query_temp("bangs/beauty", leader) == beauty )
                        {
                                tell_object(leader,ob->name()+"說道：好！好！好！"+query("party/party_name", ob)+"上上下下幾千人中數你最討幫主的歡心！\n");
                                delete_temp("bangs/beauty", leader);
                                bonus=bonus*25000/(100000+query("combat_exp", leader));
                                record = bonus + random(bonus);
                                addn("combat_exp", record, leader);
                                addn("shen", -record, leader);
                                write_file("/log/test/BangWomen",sprintf("%s于%s時上貢%s得%s經驗點\n",query("name", leader),ctime(time()),beauty,chinese_number(record)));
                                if( ling = present("bang ling", leader) )
                                {
                                        if( query("owner", ling) == 
                                                query("id", leader) )
                                                addn("score", bonus/2+random(bonus/2), ling);
                                }
                                me->set_leader(0);
                                remove_call_out("destroy_beauty");
                                call_out("destroy_beauty", 1, me, leader);
                                return ::valid_leave(me, dir);
                        }
                }
        }
        return notify_fail(sprintf("%s攔在你面前，喝道：" + RANK_D->query_rude(me) + "不得無禮！後面是幫主的臥房。\n", ob->name()));
}

void destroy_beauty(object me, object leader)
{
        object room, ob;

        if( !me ) return;

        if( !leader ) { destruct(me); return; } 

        room = environment(me);
        if( base_name(room) != WOSHI ) { destruct(me); return; }
        if( room != environment(leader) ) { destruct(me); return; }
        if( !(ob = present("shijian", room)) ) { destruct(me); return; }
        if( !living(ob) ) { destruct(me); return; }
        message_vision("$N對$n喝道：我要給這位小姐更衣，你快出去吧！\n", ob, leader);
        message_vision("$N飛起一腳將$n踢了出去。\n", ob, leader);
        leader->move(this_object());
        message("vision", leader->name() + "被人從臥房中踢了出來，狼狽不堪。\n", this_object(), ({leader}));

        destruct(me);
}