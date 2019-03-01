// biaotou.c
// 此代碼有重大消耗cpu的bug
inherit NPC;
#include <ansi.h>

#define lay_exp 20
#define lay_pot 5
#define price_exp 300
#define price_pot 80
#define total_appear 10
#define killer_appear 3
#define delay_appear 2
#define total_cmd 10
#define bt_cmd 3
#define A_TIME 60
#define B_TIME 1

string * random_act = ({
        "fear",
        "dazuo 40",
        "dazuo 60",
        "dazuo 100",
        "dazuo 120",
        "sigh",
        "sigh1",
        "say 你要把鏢車運到哪裡去？",
        "remove all",
        "remove all",
        "remove all",
        "drop all",
});

string * inroad_msg = ({
        "$N突然恍然般道：“哦，這地方我以前來過，該從這走。”說罷，轉身就走。\n",
        "$N突然驚恐地道：“哎呀，劫匪來了，我從這條路先走了。”\n",
        "$N奇怪地瞪著$n：“哎，你不認識路吧？去北京走這邊！”說著自顧走了。\n",
        "$N向$n擺擺手：“那邊現在路不平靜，江湖人物多。走僻靜的吧！”一邊說一邊扭頭就走。\n",
        "$N悄悄對$n說道：“江湖有言道：『小心天下去得，莽撞寸步難行』。”拋下$n就走了。\n",
        "$N對$n說道：“『忍得一時之氣，可免百日之災。』上次在這吃過虧，這次往那邊閃吧。”\n",
        "$N說道：“江湖上有言道：『寧可不識字，不可不識人。』”理也不理$n，拔步就走。\n",
        "$N說道：“江湖上有言道：『晴天不肯走，等到雨淋頭。』”腳下絲毫不停，一路小跑而去。\n",
        "$N說道：“江湖上有言道：『念念當如臨敵日，心心便似過橋時。』$n，我先行一步。”\n",
        "$N說道：“江湖上有言道：『路逢險處須當避，不是才子莫吟詩。』”雙腿一拔，回身狂奔。\n",
        "$N說道：“江湖上有言道：『若要精，聽一聽；站得遠，望得清。』你往那邊去，我往這邊走。”\n",
        "$N說道：“江湖上有言道：『真人不露相，露相不真人。』你先探探那邊路，我到這邊躲躲再走。”\n",
        "$N對$n說道：“『你去你的陽關道，我走我的獨木橋。』回見回見。”\n",
        "$N滿臉堆笑，對$n說道：“『光棍不吃眼前虧，伸手不打笑臉人。』在下到那邊方便方便。”\n",
});

string *xing=({"趙","錢","孫","李","周","吳","鄭","王","馮","陳","褚","衛","蔣","沈","韓","楊","朱","秦","尤","許","何","呂","施","張","孔","曹","嚴","華","金","魏","陶","姜","戚","謝","鄒","喻","柏","水","竇","章","雲","蘇","潘","葛","奚","范","彭","郎","魯","韋","昌","馬","苗","鳳","花","方","俞","任","袁","柳","酆","鮑","史","唐","費","廉","岑","薛","雷","賀","倪","湯","滕","殷","羅","畢","郝","鄔","安","常","樂","于","時","傅","皮","卞","齊","康","伍","余","元","卜","顧","孟","平","黃","和","穆","蕭","尹","姚","邵"});

string status_color(int current, int max);

void create()
{
        object ob;
        string name = xing[random(sizeof(xing))]+"鏢頭";
        set_name(name, ({"biao tou", "bt" }));
        set("title", HIR"福"HIC"威"YEL"鏢局"HIY"鏢頭"NOR);
        set("gender", "男性" );
        set("age", 20+random(10));
        set("max_qi",300+random(200));
        set("combat_exp", 100000);
        set("attitude", "friendly");
        set("vendetta_mark", "authority");
        set("env/wimpy",50);
        set("per",2);
        set("chat_chance", 15);
        set("chat_msg",({
                name+"喝道：“閒雜人等閃開了。”\n",
                name+"喝道：“快走快走，別偷懶！”\n",
                name+"說道：“江湖上有言道：『容情不動手，動手不容情。』”\n",
                name+"說道：“江湖上有言道：『只要人手多，牌樓抬過河。』諸位和我同保此鏢，還怕誰來！”\n",
                name+"說道：“江湖上有言道：『行家一伸手，便知有沒有。』”\n",
                name+"說道：“江湖上有言道：『做賊的心虛，放屁的臉紅。』你們可得定下神，別讓人瞧出了破綻。”\n",
                name+"說道：“江湖上有言道：『手穩口也穩，到處好藏身。』待回到鏢局，咱們再痛痛快快的大醉一場。”\n",
                name+"說道：“江湖上有言道：『有緣千裡來相會，無緣對面不相逢。』此次同往保鏢，真是幸會哪！幸會！”\n",
        }) );
        set("chat_chance_combat",80);
        set("chat_msg_combat", ({
                name+"大喊道：“不好了，有人劫鏢了。”\n",
        }) );

        set_skill("sword",50);
        set_skill("force",40);
        set_skill("parry",50);
        set_skill("dodge",50);
        set_skill("bixie-sword",50);
        map_skill("sword","bixie-sword");
        map_skill("parry","bixie-sword");
        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/cloth/cloth");
}

/*
void init()
{
        add_action("do_baobiao","baobiao");
        add_action("do_baobiao","jiebiao");
        add_action("do_order","order");
        add_action("do_give","give");
        add_action("do_hp","hp");
        remove_call_out("do_check");
        call_out("do_check",A_TIME);
        remove_call_out("do_check1");
        call_out("do_check1",B_TIME);
}
*/

int do_baobiao(string arg)
{
        object me = this_player();

        if( !query_temp("fuwei_ready", me) )
                return notify_fail(query("name", this_object())+"說：“去去去，去帳房交錢去！”\n");
        if( query("leader_name") != query("id", me) )
                return notify_fail(query("name", this_object())+"說：“你沒有負責保護此鏢的義務！”\n");
        set("gurader_name",query("id", me));
        me->set_leader(this_object());
        tell_object(me,"你現在開始接管鏢隊了，命令(order)他們啟程，人鏢齊全送到"+query_temp("fuwei_dest", me)+"分局就成！\n");
        return 1;
}

int do_hp(string arg)
{
        object ob = this_object();
        object me = this_player();
        string msg;
        mapping my;

        if( !arg || (arg != query("id", ob) && arg != "bt") )
                return 0;
        my = ob->query_entire_dbase();

        if( query("id", me) == query("leader_name") )
        {
                tell_object(me,sprintf("%s的健康情況如下：\n",my["name"]));
                msg = sprintf(" 精  ： %s%4d/ %4d %s(%3d%%)\n" NOR ,
status_color(my["jing"], my["eff_jing"]), my["jing"], my["eff_jing"],
status_color(my["eff_jing"],my["max_jing"]),my["eff_jing"]*100/my["max_jing"]);
                tell_object(me,msg);
                msg = sprintf(" 氣  ： %s%4d/ %4d %s(%3d%%)\n" NOR ,
status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"],
status_color(my["eff_qi"], my["max_qi"]), my["eff_qi"] * 100 / my["max_qi"]);
                tell_object(me,msg);
                return 1;
        }
        else return 0;
}

int do_order(string arg)
{
        object me = this_player();
        string ss_name,act,sth,dest,dest_add, *dirs;
        int give_exp,give_pot,i,flag;
        object room,gaoshou,jiefei,fbiaotou,cart,ob = this_object();
        mapping exits;

        if( query("leader_name") != query("id", me) )
                return notify_fail("這不是你要接的鏢，鏢隊不會聽你指揮！\n");
        if( query("gurader_name") != query("id", me) )
                return notify_fail("由于你沒有接鏢(jiebiao)，鏢隊不會聽你指揮！\n");
        if (!arg || sscanf(arg, "%s %s",act,sth) != 2)
                return notify_fail("指令格式：order <動作詞> <具體動作描述>\n");

        if ( act!="go" && act!="give" && act!="wear" && act!="remove" && act!="zou" && act!="wield" && act!="unwield" && act!="enter" && act!="eat" )
                return notify_fail("目前暫時不支持該項動作指令！\n");

        if (act == "go")
        {
                if (! objectp(cart = present("cart", environment(me))))
                {
                        command(arg);
                        if (! objectp(cart = present("cart", environment(me))))
                        return notify_fail(HIR"鏢車沒跟著，找找吧。\n"NOR);
                }
                if (ob->is_busy() )
                        return notify_fail(HIG"鏢車輪陷泥裡了，等會吧。\n"NOR);
                dest = sprintf( "exits/%s",sth);
                if( !dest_add=query(dest, environment()) )
                        return notify_fail("這個方向沒有出路。\n");
                addn("total_steps",1);

                if (random(5) == 0)
                {
                        message_vision("鏢車隆隆駛了開去。\n",ob);
                        if( mapp(exits=query("exits", environment(me))) )
                                dirs = keys(exits);
                        message_vision(HIY+inroad_msg[random(sizeof(inroad_msg))]+NOR,ob,me);
                        command("go " + dirs[random(sizeof(dirs))]);
                        cart->move(environment());
                        message_vision("鏢車隆隆駛了過來。\n",ob);
                }
                else
                if (random(total_appear) < killer_appear)
                {
                        message_vision("鏢車隆隆駛了開去。\n",ob);
                        if ( !room=find_object(dest_add) )
                                room=load_object(dest_add);
                        if (random(2)>0)
                        {
                                ss_name=__DIR__"gaoshou";
                                gaoshou = new(ss_name);
                                gaoshou->move(room);
                        }
                        else
                        {
                                ss_name=__DIR__"fake-biaotou";
                                fbiaotou = new(ss_name);
                                fbiaotou->move(room);
                                set("name",query("name",  ob), fbiaotou);
//                                fbiaotou->set("id", ob->query("id"));
                                fbiaotou->set_leader(ob);
                                message_vision("\n$N走了過來。\n",fbiaotou);
                                message_vision("\n\n$N忽然發現有點不對勁。不過來不及啦！\n",me);
                        }
                        command(arg);
                        ob->start_busy(1);
                        cart->move(environment());
                        message_vision("鏢車隆隆駛了過來。\n",ob);
                }
                else
                if (random(total_appear) < delay_appear)
                {
                        command(arg);
                        ob->start_busy(1);
                        message_vision(HIR"鏢車沒跟著，找找吧。\n"NOR, ob);
                }
                else
                {
                        message_vision("鏢車隆隆駛了開去。\n",ob);
                        command(arg);
                        ob->start_busy(random(2));
                        cart->move(environment());
                        message_vision("鏢車隆隆駛了過來。\n",ob);
                }
        }
        else command(arg);
        return 1;
}
void die()
{
        object me, cart;
        object ob;

        ob = this_object();
        if ( objectp( cart = present("cart", environment(ob))) )
                destruct(cart);
        if( query("leader_name", ob) && objectp(me=find_player(query("leader_name", ob))) )
                tell_object(me,HIB"鏢師死了，鏢車丟了，你交不了差了！\n"NOR);
        return ::die();
}
int do_give(string arg)
{
        object me = this_player();
        object ob ;
        string o_name,p_name;

        if( query("id", me) != query("leader_name"))return 0;
        if ( sscanf(arg,"%s %s",p_name,o_name) == 2 ||
                sscanf(arg,"%s to %s",o_name,p_name) ==2 ) ;
        else return 0;
        if ( p_name != "bt") return 0;
        if (! ob = present(o_name,me))
                return notify_fail("你身上沒有這樣東西。\n");
        if( query("no_drop", ob) )
                return notify_fail("這樣東西不能隨便給人。\n");

        ob -> move(this_object());
        message("vision",sprintf("%s給%s一%s%s。\n",me->name(),
                this_object()->name(),query("unit", ob),ob->name()),me);
        return 1;
}

void do_check()
{
        object me,gaoshou,jiefei;
        string ss_name;
        int i;
        mapping exits;
        string * dirs;
        object ob = this_object();
        object where = environment(ob);

        addn("total_tired",1);

        if (ob->is_fighting())
        {
                remove_call_out("do_check");
                call_out("do_check",A_TIME);
        }
        else
                if (! living(ob))
                {
                        ob->receive_damage("qi",1000);
                }
                else
                {
                        if (query("leader_name") && ! me = find_player(query("leader_name") ))
                        {
                                remove_call_out("do_check");
                                call_out("do_check",A_TIME);
                        }
                        else
                        {
                                if (random(total_appear) < killer_appear)
                                {
                                        if (random(2)>0) ss_name=__DIR__"gaoshou";
                                        else ss_name=__DIR__"fake-biaotou";
                                        gaoshou = new(ss_name);
                                        gaoshou->move(where);
                                        ob -> start_busy(1);
                                }
                                else
                                {
                                        if (random(total_cmd) < bt_cmd )
                                        {
                                                if (! ob->is_busy() )
                                                {
                                                        if (random(2) >0 )
                                                                command(random_act[random(sizeof(random_act))]);
                                                        else
                                                        {
                                                                if( mapp(exits=query("exits", where)) )
                                                                {
                                                                        message_vision(HIC+inroad_msg[random(sizeof(inroad_msg))]+NOR,ob);
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
        object cart;
        object ob = this_object();

        if( living(ob) && query("qi", ob)>0 )
        {
                remove_call_out("do_check1");
                call_out("do_check1",B_TIME);
        }
        else
        {
                message_vision(HIR"$N在昏迷中突然急促地呻吟了一聲，然後就再沒有聲音了。\n"NOR,ob);
             if (objectp(cart = present("cart", environment(ob)))) destruct(cart);

             ob -> receive_damage("qi",1000);
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

int accept_hit(object me)
{
        object ob = this_object();
        object gurad_ob;

        if (!query("gurader_name")) return 1;
        if (!gurad_ob = present(query("gurader_name"),environment(ob) ) )
  {
          if (userp(me))
                  return notify_fail(HIW"玩家不能劫鏢！\n"NOR);
                return 1;
        }
        if (me == gurad_ob)
                return notify_fail(HIR"你不想幹啦？早說嘛！\n"NOR);
        else
        {
                tell_object(me,HIR"當值鏢師正受到"+query("name", gurad_ob)+"的保護，你受到反撲！\n"NOR);
                tell_object(gurad_ob,HIR"當值鏢師受到"+query("name", me)+"攻擊，危險！護鏢要緊！你挺身就上！\n"NOR);
                me -> kill_ob(gurad_ob);
                gurad_ob -> fight_ob(me);
                return notify_fail("");
        }
}
int accept_fight(object who)        {return accept_hit(who);}
int accept_kill(object who)                {return accept_hit(who);}
int accept_touxi(object who)        {return accept_hit(who);}
