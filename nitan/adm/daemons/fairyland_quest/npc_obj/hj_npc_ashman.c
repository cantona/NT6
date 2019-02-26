//                標準描述長度示例                                   |
// 清道夫，四處揀取垃圾
// by naihe  2002-10-23  於茂名

#include <ansi.h>

inherit NPC;

#include "hj_settings/room_amount_hj.h"

int begin=1,move_time=3,temp=1;
string out_msg="$N忽地從旁邊的樹木林中鑽去，不見了。\n";
string help_msg=CYN"$N"NOR+CYN"歇斯底里般叫道：“來人啦！救命啦！有人要殺人啦！”\n"NOR;
string xixi_msg=CYN"$N"NOR+CYN"「嘻嘻嘻」傻笑了幾聲。\n"NOR;

int steal_times;

void create()
{
    set_name("小矮人",({"ai ren","ren"}));
    set("long","這是一個小矮人，模樣醜陋。\n");
    set("gender","男性");
    set("age",55);
    set("per",14);
    set("attitude","friendly");
    set("no_refresh",1);

    set("hj_game/npc","ashman");
    set("msg","只聽得一陣樹葉撥拉之聲，一個"+query("name", this_object())+"從旁邊林子裏鑽了出來。\n");

    set_temp("hj_hp_max",100+random(101));
    set_temp("hj_hp",query_temp("hj_hp_max"));

    setup();
}

void init()
{
    add_action("do_do","dodo");
    if(begin==1)
    {
        begin=2;
        call_out("get_all",1,this_object());
        call_out("random_move",5,this_object());
        call_out("delete_me",120+random(60),this_object());
    }
}

// 受到攻擊時引發一些行為
void hj_get_attack( object attacker )
{
    remove_call_out("checking");
    call_out("checking",1,this_object());
}

void checking()
{
    object *inv, ob;
    int i;

    if( query("is_die") )
        return;
    ob = this_object();
    if(query_temp("hj_hp") < 1)
    {
        remove_call_out("delete_me");
        inv = all_inventory(ob);
        out_msg="$N慘叫一聲，整個身體誇張地扭曲起來，隨即消失不見了。\n";
        if(inv || sizeof(inv) > 0)
        {
            for(i=0;i<sizeof(inv);i++)
            {
                inv[i]->move(environment(ob));
                message_vision(sprintf("$N身上忽地掉下了一%s%s！\n",query("unit", inv[i]),query("name", inv[i])),ob);
            }
        }
        call_out("delete_me",1,ob);
        set("is_die",1);
        return;
    }

    if(query("killme_by") && temp == 1)
    {
        message_vision( help_msg, ob );
        move_time=1;
        temp=2;
        remove_call_out("normal");
        call_out("normal",30,ob);
    }

    if(temp == 2)
    {
        remove_call_out("checking");
        call_out("checking",1,ob);
    }
}

void normal()
{
    move_time=3;
    temp=1;
    delete("killme_by");
    message_vision("$N神色緊張地四處張望着，一副驚魂未定的樣子。\n",this_object());
}

void delete_me()
{
    object *inv, t, env, ob = this_object();
    if( objectp( (env=environment(ob)) ) )
    {
        message_vision(out_msg, ob );
        // naihe 05-9-7 9:29 矮人偷東西偶爾可能掉些回來。也算是給點機會給玩家！
        if( sizeof( (inv=all_inventory( ob )) ) > 0 )
        {
            foreach( t in inv )
            {
                if( !random(5) && query("hj_game/obj", t) )
                {
                    message_vision("$N身上忽地掉下一"+query("unit", t)+"$n。\n",ob,t);
                    t->move( env );
                }
            }
        }
    }
    destruct(this_object());
}

// naihe 05-8-29 10:13 加入真正清垃圾的函數……
// 以前腦子發暈，搞個 get all 還要全部 hj obj 配合，靠。
void do_real_get_all()
{
    object *inv, ob, env;
    if( !(env = environment(this_object()))
      || !sizeof( (inv=all_inventory(env)) )
    )
        return;
    foreach( ob in inv )
    {
        if( !userp(ob)
           && !query("hj_game", ob )
        )
            destruct( ob );
    }
}

void get_all()      // 加入隨機偷取玩家東西的函數 by naihe 10:52 02-10-30
{
    object *all_here,*inv, env, ob = this_object();
    int i,iii,amount;
    string steal="no";

    if( !(env=environment(ob)) || query_temp("hj_hp") < 1 ) return;
    // 準備去死了的矮人不能再偷東西   fix by naihe 03-01-22

    if(random(2) == 1)
    {
        do_real_get_all();
        if(random(move_time) == 0 )
        {
            if(temp==1)
                message_vision( xixi_msg, ob );
            if(temp==2)
                message_vision( help_msg, ob );
        }
    }

    // 或者其在忙時中，不得偷東西
    if( is_busy() || steal_times >= 3 )  // 每個 小矮人 最多也就偷取 3 個物品
    {
        remove_call_out("get_all");
        call_out("get_all",5,ob);
        return;
    }
    all_here = all_inventory(env);

    for(i=0;i<sizeof(all_here);i++)
    {
        if( query("hj_game/npc", all_here[i] )
         || !query_temp("hj_hp", all_here[i] )
         || query_temp("huanjing", all_here[i]) != "start"
        || present( "hj temp leave obj", all_here[i] )      // 臨時離開遊戲者，不偷取
        )
            continue;

        amount=0;
        inv=all_inventory(all_here[i]);

        for(iii=0;iii<sizeof(inv);iii++)
        {
            if( query("hj_game/obj", inv[iii]))amount++;
        }
        if( amount > 20 )  // 當玩家攜帶了的幻境內物品超過此數字，將會被隨機偷取掉一件。
        {
            for(iii=0;iii<sizeof(inv);iii++)
            {
                if( random(10) == 1 && query("id", inv[iii]) != "qixing deng" && 
                   query("hj_game/obj", inv[iii]) )
                {
                    message_vision(sprintf("$N身上帶着的一%s%s似乎被誰偷偷摸走了！\n",query("unit", inv[iii]),query("name", inv[iii])),all_here[i]);
                    inv[iii]->move(ob);
                    steal="yes";
                    steal_times++;
                    break;
                }
            }
        }
        if(steal == "yes") break;
    }
    remove_call_out("get_all");
    call_out("get_all",5,ob);
}

int do_do(string arg)
{
    if(!arg || !wizardp(this_player())) return 0;
    command(arg);
    write("do la.\n");
    return 1;
}

int random_move()
{
    string *dirs=({
        "east","west","south","north",
        "northeast","northwest","southeast","southwest"
    });
    if( query_temp("hj_hp") < 1)
        return 1;
    if(random(5) == 1 && living(this_object()))
        command( "go " + dirs[random(sizeof(dirs))] );
    remove_call_out("random_move");
    call_out("random_move",move_time,this_object());
    return 1;
}
