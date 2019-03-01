// /d/yixing/obj/caili.c  彩禮
// Last Modified by winder on Jul. 12 2002


#include  <ansi.h>
#include <command.h>
#include <changle.h>
inherit ITEM;
#include D_BANG

void create()
{
        set_name(RED"彩禮"NOR, ({ "caili" }));
        set("weight", 20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
"這是一份包裝精制的彩禮，裡面一定裝著貴重的東西。\n");
                set("unit", "份");
                set("value", 30);
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");            
        }

        setup();

        call_out("do_check", 1 + random(20));
}


// to avoid players from cheating
// like go by da che or let other players carry them
// like go by following another player or driven by another player

// i still think, it is better to change follow.c and sing.c files
// then will save source

void do_check()
{
        object owner, room;

        if( !(owner = query("owner")) ) {
                destruct(this_object());
                return;
        }

        if( !living(owner)
        ||  owner->query_leader() 
         || query_temp("cursed", owner)){
                tell_object(owner, HIR"\n你忽然有一種不祥的感覺。\n"NOR);
                destruct(this_object());
                return;
        }

        call_out("do_check", 1 + random(20));
}

void init()
{
        add_action("do_go", "go");
        add_action("do_visit", "visit");
        add_action("do_giveup", "giveup");
}

int do_go(string arg)
{
        object me = this_player(), ob, room;
        string *bangs;
        int ap, dp;

        if( me->is_busy() ) {
                write("你正忙著。\n");
                return 1;
        } 

        room = environment(me);

        if( ob = present("bang zhong", room) ) {
                if( living(ob) ) {
                        ap=query("combat_exp", me);
                        dp=3*query("combat_exp", ob);
     // leave a trick here for smarter players
                        if( random(ap + dp) > dp )
                                return 0;

                        me->start_busy(1);
                        message_vision("$N對$n喝道：" + RANK_D->query_rude(me) + "把東西留下！！！\n", ob, me);
                        if( !ob->is_fighting(me) )
                                ob->kill_ob(me);
                        return 1;
                }
        }

        if( random(4) ) {
                me->receive_damage("jing", 30 + random(30), 1,"力盡而死");
                me->receive_damage("qi", 30 + random(30), 1,"力盡而死");
                tell_object(me,"你走了一會兒，有點累了。\n");
                return 0;
        }

        ob = new(BANGZHONG2);
        bangs = keys(info_bang);
        bangs-=({query("party/party_name", me)});
        set("title", bangs[random(sizeof(bangs))], ob);

        ob->move(room);
        message("vision",
                query("title", ob)+ob->name()+"走了過來。\n",
                environment(ob), ({ob}));
        message_vision(HIR"\n"+query("title", ob)+ob->name()+"對$N喝道："+RANK_D->query_rude(me)+"把東西留下！！！\n"NOR,me);
        ob->kill_ob(me);
        me->start_busy(1);
        return 1; 
}

int do_visit(string arg)
{
        object room, ob, me = this_player(), obj;
        int bonus, record;
        mapping job;

        if( me->is_busy() || me->is_fighting() ) {
                write("你正忙著。\n");
                return 1;
        }

        if( !arg ) {
                write("你要拜訪誰？\n");
                return 1;
        }

        if( !mapp(job = query("job")) ) {
                destruct(this_object());
                return 1;
        }

   // the following is very important to avoid players cheating
        room = environment(me);
        if( base_name(room) != job["file"] ) {
                write("你還沒到目的地呢。\n");
                return 1;
        }

        if( !(ob = present(arg, room)) ) {
                write("這兒沒有你要拜訪的人。\n");
                return 1;
        }

        if( query("name", ob) != job["name"]){
                write("你拜訪錯人了。\n");
                return 1;
        }

        if( !living(ob) ) {
                write("你還是等此人醒來再說吧。\n");
                return 1;
        }

        if( ob->is_busy() || ob->is_fighting() ) { 
                write("此人正忙著。\n");
                return 1;
        }

        message_vision("$N向$n躬身作了個揖，郎聲說道：弊幫幫主差" + RANK_D->query_self_rude(me) + "送一份大禮給" + RANK_D->query_respect(ob) + "。\n", me, ob);
        message_vision("$N將" + name() + "雙手奉給$n。\n", me, ob);
        move(ob);
        remove_call_out("do_destroy");
        call_out("do_destroy", 1, this_object());

        message_vision("$N還了一個禮，說道：" + RANK_D->query_respect(me) + "辛苦了。回去後代我向你幫主問個安。\n", ob);

        bonus=job["bonus"]*400000/(200000+query("combat_exp", me));
        record = bonus + random(bonus);
        addn("combat_exp", record, me);
        write_file("/log/test/BangJob",sprintf("%-10s于%-20s時因送禮得%-5s經驗點\n",query("name", me),ctime(time()),chinese_number(record)));

        bonus /= 4;
        addn("shen", -bonus, me);

        if( obj = present("bang ling", me) ) {
                if( query("owner", obj) == query("id", me) )
                        addn("score", bonus, obj);
                        delete("job", obj);
        }

        return 1;
}

void do_destroy(object ob)
{
        if(ob) destruct(ob);
}

int do_giveup()
{
        object ob;

        if( ob = present("bang zhong", environment(this_player())) ) {
                if( base_name(ob) == BANGZHONG2 && living(ob) ) {
                message_vision("$N滿含失望地長嘆一聲，說道：既然如此，也就罷了！\n", this_player());
                message_vision("$N將彩禮送給$n。\n", this_player(), ob);
                message("vision",
                ob->name() + "說道：算你識時務，我就饒你一命。說完便揚長而去。\n",
                environment(ob), ({ob}));
                destruct(ob);
                destruct(this_object());
                return 1;
                }
        }
        return notify_fail("又沒人搶劫，你幹嘛？\n");
}
