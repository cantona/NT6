// /d/npc/renzhi.c 人質
//modified by sega 1/10/99
//修改了獎勵的上限
#include <ansi.h>
#define lay_exp 20
#define lay_pot 5
#define lay_score 10
#define price_exp 300
#define price_pot 80
#define price_score 100
#define total_appear 10
#define killer_appear 2
#define total_cmd 10
#define rz_cmd 3
#define A_TIME 60
#define B_TIME 5

inherit NPC;
string * des_str=({
        "這是一位黑紗蒙面的人，看不出有多大歲數。\n",
        "他整個人都被裹在一件長大的黑衣裏，默默站在那裏一言不發。\n",
        "一位微微發胖的人，滿臉堆着笑。\n",
        "他的眉頭都鎖在一起，似乎對什麼事很擔心的樣子。\n",
        "這個人猥猥瑣瑣地站在那裏，好像有什麼話又不敢説似的。\n",
        "一位看起來神神祕祕的人，可是總讓人覺得有點怪異的樣子。\n",
        "這個人站在那裏好像不停地在發抖，也許是害怕什麼。\n",
        "他滿臉的皺紋，看起來好像歲數很大，不過仔細一看，又好象並沒有實際那麼大。\n",
        "他穿着一件本來質地很好的衣服，可是現在衣服上沾滿了塵土和血跡。\n",
});

string * random_act = ({
        "fear",
        "dazuo 40",
        "dazuo 60",
        "dazuo 100",
        "dazuo 120",
        "sigh",
        "sigh1",
        "say 你要把我帶到哪裏去啊？",
        "remove all",
        "remove all",
        "remove all",
        "drop all",
});

string * escape_msg = ({
        "$N突然驚恐地道：“哎呀，殺手來了，我從這條路先跑了。”\n",
        "$N突然驚恐地指着你，歇斯底里地大喊起來：“殺手！你就是殺手！你就是派來殺我的殺手！”沒等誰反應過來，$N轉身大跑起來。\n",
        "$N怯怯地四處看了看，突然叫了起來：“這地方如此偏僻，怎麼能多呆呢，我先走吧。”\n",
        "$N一回頭，似乎看見遠處有什麼東西掠過，驚得轉身就跑。\n",
        "忽然聽到$N一聲慘叫，好像被踩住了尾巴的兔子一樣轉身逃了開去。\n",
        "$N突然恍然般道：“哦，這地方我以前來過，該從這條路走。説罷，轉身就走。”\n"
,
        "$N驀地撒腿就跑，怎麼喊他也不回頭，一溜煙地消失了。\n",
});

string status_color(int current, int max);

void create()
{
        mapping name;
        if (random(2) == 0)
        {
                name = NAMES_D->random_name(1);
                set("gender", "女性");
        }
        else
        {
                name = NAMES_D->random_name(0);
                set("gender", "男性");
        }
        set_name(name["name"],({"ren zhi", "rz"}));

        set("age", 17 + random(60) );
        set("long", des_str[random(sizeof(des_str))]);

        set("combat_exp", 500 + random(5000));
        set("attitude", "friendly");
        set("inquiry", ([
                "name" : "我的姓名是不能對人亂講的。\n",
        ]));

        set("env/wimpy",50);
        set("no_get",1);
        set("no_beg",1);
        set("no_steal",1);
        set("no_kill",1);
        set("max_neili",150 + random(150) );
        set("neili",query("max_neili") );

        set_skill("unarmed",20);
        set_skill("sword",20);
        set_skill("blade",20);
        set_skill("dodge",20);
        set_skill("force",20);
        set_skill("huntian-qigong",20);
        map_skill("force","huntian-qigong");
        
        set( "max_qi", 350 + random(200) );
        set( "max_jing", 200 + random(300) );

        set("leader_name","");
        set("dest_add","");
        set("combat_num",0);
        set("total_steps",0);
        set("total_tired",0);

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_baohu","baohu");
        add_action("do_order","order");
        add_action("do_steal","steal");
        add_action("do_hit","hit");
        add_action("do_kill","kill");
        add_action("do_give","give");
        add_action("do_hp","hp");
        add_action("do_touxi","touxi");
        remove_call_out("do_check");
        call_out("do_check",A_TIME);
        remove_call_out("do_check1");
        call_out("do_check1",B_TIME);
}


int do_baohu(string arg)
{
        object me = this_player();

        if( query("leader_name") != query("id", me) )
                return notify_fail("你沒有負責保護該人質的義務！\n"); 
        set("gurader_name",query("id", me));
        tell_object(me,HIR"注意：你現在開始對人質進行保衞，任何針對人質的攻擊都將自動轉移到你身上！\n"NOR);
        return 1;
}

int do_hp(string arg)
{
        object ob = this_object();
        object me = this_player();
        string msg;
        mapping my;

        if( !arg || (arg != query("id", ob) && arg != "rz") )
                return 0;
        my = ob->query_entire_dbase();

        if( query("id", me) == query("leader_name")){
                tell_object(me,sprintf("%s的健康情況如下：\n",my["name"]));
                msg = sprintf(" 精  ： %s%4d/ %4d %s(%3d%%)\n" NOR ,
                        status_color(my["jing"], my["eff_jing"]), my["jing"], my["eff_jing"],
                        status_color(my["eff_jing"], my["max_jing"]), my["eff_jing"] * 100 / my["max_jing"]);
                tell_object(me,msg);
                msg = sprintf(" 氣  ： %s%4d/ %4d %s(%3d%%)\n" NOR ,
status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"],
status_color(my["eff_qi"], my["max_qi"]), my["eff_qi"] * 100 / my["max_qi"]);
                tell_object(me,msg);
                return 1;
        }
        else
                return 0;
}

int do_hit(string arg)
{
        object ob = this_object();
        object me = this_player();
        object gurad_ob;

        if( !arg || (arg != query("id", ob) && arg != "rz") )
                return 0;
        if (!query("gurader_name") || !gurad_ob = present(query("gurader_name"),environment(ob)) )
        {
                if (userp(me) )
                {
                        tell_object(me,HIW"玩家不能攻擊無保護的人質！\n"NOR);
                        return 1;
                }
                else
                        return 0;
        }
        if (me == gurad_ob)
        {
                tell_object(me,HIR"咦？你不是他的保護者嗎?\n"NOR);
                return 1;
        }
        else
        {
                tell_object(me,HIR"人質正受到"+query("name", gurad_ob)+"的保護，人家加入戰鬥對你發起攻擊！\n"NOR);
                tell_object(gurad_ob,HIR"人質受到"+query("name", me)+"攻擊，你挺身加入戰鬥！\n"NOR);
                me -> fight_ob(gurad_ob);                
                gurad_ob -> fight_ob(me);
                return 1;
        }
}

int do_kill(string arg)
{
        object ob = this_object();
        object me = this_player();
        object gurad_ob;

        if( !arg || (arg != query("id", ob) && arg != "rz"))return 0;
        if (!query("gurader_name") || !gurad_ob = present(query("gurader_name"),
environment()) )
        {
                if (userp(me) )
                {
                        tell_object(me,HIW"玩家不能攻擊無保護的人質！\n"NOR);
                        return 1;
                }
                else return 0;
        }

        if (!gurad_ob = present(query("gurader_name"),environment(ob) ) )
                return 0;
        if (me == gurad_ob)
        {
                tell_object(me,HIR"你不想完成你的任務了嗎？\n"NOR);
                return 1;
        }
        else
        {
                tell_object(me,HIR"人質正受到"+query("name", gurad_ob)+"的保護，人家加入戰鬥抵禦你的攻擊！\n"NOR);
                tell_object(gurad_ob,HIR+query("name", me)+"準備殺死人質，你挺身加入戰鬥！\n"NOR);
                me -> kill_ob(gurad_ob);                
                gurad_ob -> fight_ob(me);
                return 1;
        }
}

int do_touxi(string arg)
{
        object ob = this_object();
        object me = this_player();
        object gurad_ob;

        if( !arg || (arg != query("id", ob) && arg != "rz") )
                return 0;
        if (!query("gurader_name") || !gurad_ob = present(query("gurader_name"),environment(ob)) )
        {
                if (userp(me) )
                {
                        tell_object(me,HIW"玩家不能攻擊無保護的人質！\n"NOR);
                        return 1;
                }
                else return 0;
        }

        if (!gurad_ob = present(query("gurader_name"),environment() ) )
                return 0;
        if (me == gurad_ob)
        {
                command("papa"+query("id", me));
                tell_object(me,HIR"你不能偷襲人質。\n"NOR);
                return 1;
        }
        else
        {
                tell_object(me,HIR"人質正受到"+query("name", gurad_ob)+"的保護，人家加入戰鬥抵禦你的攻擊！\n"NOR);
                tell_object(gurad_ob,HIR+query("name", me)+"準備對人質進行偷襲，你挺身加入戰鬥！\n"NOR);
                me -> kill_ob(gurad_ob);
                gurad_ob -> fight_ob(me);
                return 1;
        }
}

int do_steal(string arg)
{
        object ob = this_object();
        object me = this_player();
        string who;

        sscanf(arg,"%*s %*s %s",who);

        if( who == query("id", ob) || who == "rz" )
        {
                message("vision",HIW"玩家不能偷人質身上的東西！\n"NOR,me);
                return 1;
        }
        return 0;
}

int do_order(string arg)
{
        object me = this_player();
        object ml;
        string act,sth,dest,dest_add;
        int give_exp,give_pot,give_score;
        int i;
        object room,shashou,anshazhe;
        string ss_name;

        if( query("leader_name") != query("id", me) )
                return notify_fail("由於你不是該任務的接收者，人質不會聽你的指揮！\n");
        if (!arg || sscanf(arg, "%s %s",act,sth) != 2)
                return notify_fail("指令格式：order <動作詞> <具體動作描述>\n");

        if (query("qi") < 50)
                return notify_fail("目前人質沒有力氣執行該項動作！\n");

        if ( act!="go" && act!="ask chuanfu about 出海" && act!="get" && act!="give" && act!="drink" && act!="wear" && act!="remove" && act!="zou" && act!="wield" && act!="unwield" && act!="enter" && act!="eat" )
                return notify_fail("目前暫時不支持該項動作指令！\n");

        if ( me->is_busy() || me->is_fighting())
                    return notify_fail("你正忙着呢。\n");

        if (act == "go")
        {
                if (this_object()->is_busy() )
                        return notify_fail(HIY"人質要休息一會兒再上路。\n"NOR);
                dest = sprintf( "exits/%s",sth);
                if( !dest_add=query(dest, environment()) )
                        return notify_fail("這個方向沒有出路。\n");
                if( !query("no_fight", environment(this_object())) )
                        addn("total_steps",1);
                if (dest_add == query("dest_add") )
                {
                //目的地到達
                        message_vision(YEL"$N長出了一口氣道：哎，終於到了。不知道從哪裏冒出來一輛馬車將$N接上了車，然後揚塵而去。\n"NOR,this_object(),me);
                        tell_object(me,HIW"恭喜你成功將人質送到目的地，完成了這項任務！\n"NOR);
                        message("channel:chat",HIM"【謠言】聽説"+query("name", me)+"成功將人質護送到目的地了！\n"NOR,users());
             
                        i = 0;
                        give_exp = lay_exp * query("total_steps");
                        give_pot = lay_pot * query("total_steps");
                        give_score = lay_score * query("total_steps");
                        while ( i < query("combat_num") )
                        {
                                give_exp += (price_exp/2 + random(price_exp/2));
                                give_pot += (price_pot/2 + random(price_pot/2));
                                give_score += (price_score/2 + random(price_score/2));
                                i++;
                        }
                        if(give_exp > 8000) give_exp = 6000 + random(2000);
                        if(give_pot > 2000 ) give_pot = 1800 + random(400);
                        if(give_score > 1500 ) give_score = 1000 + random(500);
                        log_file("mission/ms_renzhi",sprintf("%20s做保護人質任務，得到：%4i點EXP和%4i點潛能。\n",
       query("name", me)+"("+getuid(me)+")",give_exp,give_pot));
                        tell_object(me,HIW + sprintf("你被獎勵了！得到%s點經驗和%s點潛能，%s點江湖閲歷。\n", chinese_number(give_exp), chinese_number(give_pot), chinese_number(give_score) ) + NOR);
                        addn("combat_exp", give_exp, me);
                        addn("potential", give_pot, me);
                        addn("score", give_score, me);
                        if ( ml = present("mi ling",me) ) destruct(ml);
                        destruct(this_object());
                        return 1;
                }
                else
                {
                        if (random(total_appear) < killer_appear)
                        {
                                if (random(2)>0) ss_name=__DIR__"shashou";
                                else ss_name=__DIR__"anshazhe";
                                if ( !room=find_object(dest_add) )
                                        room=load_object(dest_add);
                                shashou = new(ss_name);
                                shashou->move(room);
                                shashou->set_leader(this_object());
                                command(arg);
                                this_object()->start_busy(1);
                        }
                        else
                        {
                                command(arg);
                                this_object()->start_busy(random(2));
                        }
                }
        }
        else command(arg);
        return 1;

}

int do_give(string arg)
{
        object me = this_player();
        object ob ;
        string o_name,p_name;

        if( query("id", me) != query("leader_name"))return 0;
        if (!arg) return 0;
        if ( sscanf(arg,"%s %s",p_name,o_name) != 2) return 0;
        if ( sscanf(arg,"%s to %s",o_name,p_name) !=2 ) return 0;
        if ( p_name != "rz") return 0;
        if (! ob = present(o_name,me))
                return notify_fail("你身上沒有這樣東西。\n");
        if( query("no_drop", ob) )
                return notify_fail("這樣東西不能隨便給人。\n");

        ob -> move(this_object());
        message("vision",sprintf("%s給%s一%s%s。\n",me->name(),
                this_object()->name(),query("unit", ob),ob->name()),me);
        return 1;

}

int active_died()
{
        object me;
        object ml;

        if (! me = find_player(query("leader_name")) ) return 1;
        else {
                tell_object(me,HIB"人質死了，你的任務失敗了！\n"NOR);
                if (ml = present("mi ling",me) )
                        destruct(ml);
                return 1;
        }
}

void do_check()
{
        object me,shashou;
        string ss_name;
        int i;
        mapping exits;
        string * dirs;
        object ob = this_object();
        object where = environment(ob);

        add ("total_tired",1);

        if (! living(ob) || ob->is_fighting())
        {
                remove_call_out("do_check");
                call_out("do_check",A_TIME);
        }
        else
        {
                if (! me = find_player(query("leader_name") ))
                {
                        remove_call_out("do_check");
                        call_out("do_check",A_TIME);
                }
                else
                {
                        if (random(total_appear) < killer_appear)
                        {
                                if (random(2)>0) ss_name=__DIR__"shashou";
                                else ss_name=__DIR__"anshazhe";
                                shashou = new(ss_name);
                                shashou->move(where);
                                ob -> start_busy(1);
                                shashou->set_leader(ob);
                        }
                        else
                        {
                                if (random(total_cmd) < rz_cmd )
                                {
                                        if (! ob->is_busy() )
                                        {
                                                if (random(2) >0 ) command(random_act[random(sizeof(random_act))]);
                                                else
                                                {
                                                        if( mapp(exits=query("exits", where)) )
                                                        {
                                                                message_vision(HIY+escape_msg[random(sizeof(escape_msg))]+NOR,ob);
                                                                dirs = keys(exits);
                                                                command("go "+dirs[random(sizeof(dirs))]);
                                                        }
                                                }
                                        }
                                }
                        }
                        remove_call_out("do_check");
                        call_out("do_check",A_TIME);
                }
        }
}

void do_check1()
{
        object ob = this_object();

        if( query("qi", ob)<10 )
        {
                message_vision(HIR"$N一聲慘叫，轟地一聲倒在地上。\n"NOR,ob);
                ob -> receive_damage("qi",100);
                ob -> receive_wound("qi",100);
                ob -> die();
        }
        else
        {
                if (living(ob) )
                {
                        remove_call_out("do_check1");
                        call_out("do_check1",B_TIME);
                }
                else
                {
                        message_vision(HIR"$N在昏迷中突然急促地呻吟了一聲，然後就再沒有聲音了。\n"NOR,ob);
                        ob -> die();
                }
        }
}

string status_color(int current, int max)
{
        int percent;

        if( max>0 ) percent = current * 100 / max;
        else percent = 100;
        if( percent > 100 ) return HIC;
        if( percent >= 90 ) return HIG;
        if( percent >= 60 ) return HIY;
        if( percent >= 30 ) return YEL;
        if( percent >= 10 ) return HIR;
        return RED;
}
