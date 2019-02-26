//Cracked by Kafei
// /d/city/npc/obj/biaoche.c 鏢車
// sdong,12/05/98 created

#include <ansi.h>
#include <room.h>
inherit ITEM;

string *Robber_Name = ({
                                         "土匪","山大王","路霸","山賊","毛賊","寨主","幫匪"

});





mapping default_dirs = ([
                  "north":        "北",
                  "south":        "南",
                  "east":         "東",
                  "west":         "西",
                  "northup":      "北邊",
                  "southup":      "南邊",
                  "eastup":       "東邊",
                  "westup":       "西邊",
                  "northdown":    "北邊",
                  "southdown":    "南邊",
                  "eastdown":     "東邊",
                  "westdown":     "西邊",
                  "northeast":    "東北",
                  "northwest":    "西北",
                  "southeast":    "東南",
                  "southwest":    "西南",
                  "up":           "上",
                  "down":         "下",
                  "out":          "外",
                  "enter":        "裏",
]);



void set_owner(object owner,object owner2);
int do_drive(string arg);
int do_open();
int do_check();
int do_unride(string arg);
int do_ride(string arg);
int do_attack(string arg);
int do_rob();
void host_appear();
void destroy_cart(object cart);
void greeting(object ob);
void destroy_it(object ob);
void do_leave(object ob);
void robber_rob(object me);

void create()
{
        seteuid(getuid());
        set_name(HIW"鏢車"NOR, ({"biao che", "che"}));
        set("long",
                "這是一輛非常結實的鏢車，由兩匹大騾子拉着，不知裝着什麼東西。鏢車上豎着一面大旗，上書“福威鏢局”四個大字。\n");
        set("unit", "輛");
        set_weight(10000);
        set_max_encumbrance(5000);

        set("value", 1000000);
        set("material", "steel");

        set("no_get",1);

        set("no_refresh", 1);

        remove_call_out("auto_check");
        call_out("auto_check", 30+random(30) );
}

void init()
{
        object ob;

        add_action("do_check", "check");
        add_action("do_drive", "gan");
        add_action("do_drive", "g");
        add_action("do_ride", "ride");
        add_action("do_ride", "shang");
        add_action("do_unride", "leave");
        add_action("do_attack", "attack");
        add_action("do_attack", "att");
        add_action("do_rob", "jiebiao");

        if( interactive(ob = this_player()) ) {
                 call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        int bonus,old_pot;

        object target,robber;
        object here = environment(this_object());
        object owner;
        string sO;

        if( !ob || environment(ob) != environment() ) return;


        sO = query("owner");

        if(sO)
         owner = present( sO,here);

        if( !owner || owner != ob )
        {
                sO = query("owner2");

                if(sO)
                 owner = present( sO,here);
        }

        if( !owner || owner != ob)return;


        if( !owner && here && (robber = present("robber",here)) )
        {
                robber->command("open");
        }
        else if( query_temp("biao/dest2") && here && (base_name(here) == query_temp("biao/dest2") )&& owner && userp( owner ) )
        {
                message_vision(HIG"\n$N"+HIG"累得半死，總算趕到目的地！\n\n",owner);

                if( (target = present( query_temp("biao/dest"),here)  ) )
                {
                        call_out("award",1,target,ob );
                }
                else
                {
                        message_vision(RED"可是$N"+RED"卻找不到主人，把$P急得直冒汗！\n\n"NOR,owner);
                        remove_call_out("host_appear");
                        call_out("host_appear", 2 + random(3) );
                }
        }
        else if( query_temp("biao/dest") && here && (target = present( query_temp("biao/dest"),here)  ) )
        {
                        message_vision("$N急急忙忙離開了！\n",target);
                        target->move( query_temp("biao/dest2")+".c" );
                        message_vision("$N急急忙忙走了過來！\n",target);
        }
}

void host_appear()
{
        object target;
        string host = query_temp("biao/dest");

        if(!host)return;

        target = find_object( host );
        if(!target)target = find_player(host);
        if(!target )target = find_living(host);


        if( !target )
        {
                seteuid(geteuid());
                if ( query_temp("biao/dest") == "dao baifeng" ) target = new ("/kungfu/class/dali/daobaifeng.c");
                else if ( query_temp("biao/dest") == "hu laoye" ) target = new ("/d/xingxiu/npc/bayi.c");
                else if ( query_temp("biao/dest") == "ye erniang" ) target = new ("/kungfu/class/xixia/ye.c");
                else if ( query_temp("biao/dest") == "feng yiming" ) target = new ("/d/foshan/npc/yiming.c");
                else if ( query_temp("biao/dest") == "wang tongzhi" ) target = new ("/d/quanzhou/npc/wang.c");
        }
        else
        {
                if( target && environment( target) )
                        message_vision("$N急急忙忙離開了！\n",target);
        }

        if(target)
        {
                target->move( query_temp("biao/dest2")+".c" );
                message_vision("$N急急忙忙走了過來！\n",target);
        }

}

void award2(object dest,object owner)
{
        object wage;
        object here = environment(dest);
        int nGold;

        if( userp(owner) && query("biao/dest2", owner) )
        {
                nGold=2+random(2+query("combat_exp", owner)/100000);

                if (MONEY_D->player_job_pay(owner, dest, nGold * 10000))
                        message_vision(HIY"$N"+HIY"遞給$n幾錠黃金，説：“一點小意思，"+RANK_D->query_respect(owner)+"請笑納！”\n"NOR,dest,owner);

                delete("biao/dest", owner);
                delete("biao/dest2", owner);
                delete_temp("riding", owner);
                set("biao/bonus", 660+random(500), owner);
        }
}

void award(object dest,object owner)
{
        object *obj,here = environment(dest);
        object cart=this_object();
        int i;

        if(userp(owner))
        {
                message_vision(HIY"$N"+HIY"跳下了鏢車！\n"NOR,owner);
                delete_temp("riding", owner);
                message_vision("$N上前對着$n抱拳道：“這位"+RANK_D->query_respect(dest)+"請了。"+RANK_D->query_self(owner)+"總算不負所托，現將鏢貨原物奉上。請您清點！”\n",owner,dest);
                message_vision("$N滿臉堆笑的説：“這位福威鏢局的"+RANK_D->query_respect(owner)+"果然英雄了得。"+RANK_D->query_self(dest)+"多謝了！”\n",dest);
                call_out("award2",1,dest,owner);
                remove_call_out("killer_show");
                remove_call_out("auto_check");
                if(owner->query_condition("biaoju"))
                        owner->clear_one_condition("biaoju");


                obj = all_inventory(here);

                 for(i=0;i<sizeof(obj);i++)
                {

                        if( living(obj[i]) && (query_temp("biao/owner", obj[i]) == query("id", owner )

                                 || query_temp("biao/owner2", obj[i]) == query("id", owner) )

                         && obj[i] != owner )

                        {

                                call_out("destroy_cart",2,obj[i]);

                        }

                        if( query("id", obj[i]) == "robber" && !userp(obj[i]) )

                                do_leave(obj[i]);

                }



                call_out("destroy_cart",5,cart);

        }

}

void destroy_cart(object cart)
{
        if( !objectp(cart) )return;
        if( query("race", cart) != "人類" )
                message_vision("僕人上前把$N拉走了。\n",cart);
        else message_vision("丫環上前把$N請進去了。\n",cart);

        destruct(cart);
}

void set_owner(object owner,object owner2)
{
        object ob = this_object();
        set("owner",query("id", owner));
        if(owner2)
                set("owner2",query("id", owner2));
        set_temp("biao/dest",query("biao/dest", owner));
        set_temp("biao/dest2",query("biao/dest2", owner));

        call_out("destroy_it", 1200,ob);
}



int do_ride(string arg)
{
        object me = this_player();
        object cart = this_object();


        if (!arg) return notify_fail("你要上什麼？\n");

        if( query_temp("riding", me))return notify_fail("你已經在鏢車上！\n");

        if( cart = present("biao che",environment()) );

        if( query("owner") != query("id", me) && query("owner2") != query("id", me))return notify_fail("不是你的車。\n");

        message_vision(HIY"$N"+HIY"神氣地跳上了鏢車，一手拿起鞭子，一手握住韁繩，吆喝了起來！\n"NOR,me);
        me->set_leader( cart );
        set_temp("riding", 1, me);
        return 1;
}

int do_unride(string arg)
{
        object me = this_player();

        if( !query_temp("riding", me))return notify_fail("你已經不在鏢車上！\n");

        message_vision(HIY"$N"+HIY"跳下了鏢車！\n"NOR,me);
        delete_temp("riding", me);
        return 1;
}



int auto_check()
{
        object me = this_object();
        object here,owner;
        if( !me )return 0;
        here = environment(me);
        if(!here) return 0;
        call_out("auto_check", 45+random(30) );

        //if( !(owner = present(query("owner"),here) ) && query("owner2") && !(owner = present(query("owner2"),here) )  )
                if( !(owner = find_player(query("owner")) ) &&  query("owner2") && !(owner = find_player(query("owner2")) ) )
                {
                        call_out("auto_check", 1+random(3) );
                        call_out( "destroy_it",1, me );
                        return 1;
                }


  if( !owner || !query("biao/dest2", owner) )
  {
                call_out( "destroy_me",1, me );
                return 0;
  }


        if( strsrch(base_name(here), "/d/city") == -1 &&
                strsrch(base_name(here), "/d/") != -1 &&
                strsrch(base_name(here), "duchuan") == -1   )
        {
                                call_out( "killer_show",1+random(5),owner );
                                if( query("owner2") && query("owner2") != query("owner") )
                                {
                                        owner = find_player( query("owner2") );
                                        if( owner && random(2) ==0 ) call_out( "killer_show",1+random(5),owner );
                                }
        }

        return 1;
}


void do_leave(object ob)
{
                if( objectp(ob) )
                {
                        if( ob->is_busy() || ob->is_fighting())
                        {
                                message_vision("$N向後一跳，跳出戰圈！\n",ob);
                                if( random(2)==0 )
                                        message_vision("$N説道：沒想到福威鏢局的還真有兩下子。"+RANK_D->query_self(ob)+"今天暫且饒你一條狗命！\n",ob);
                                else
                                        message_vision("$N説道：今天老子手氣不好，算你狠，改日再來陪你玩！\n",ob);
                        }

                        if(!living(ob))ob->revive(0);
                        message_vision("$N急急忙忙離開了。\n",ob);
                        destruct(ob);
                }
}



void run_away()

{
        object obj, ob=this_object(), me,partner;

        object here = environment(ob);

        string *dirs,dir,dest,target_dir;

        mapping exit;



        if(!ob)return;

        if(!here || !objectp(here) )return;



        if(random(16) != 0) call_out("run_away",0);



        exit=query("exits", here);

        if( !exit ) return;

        dirs = keys(exit);

        dir = dirs[random(sizeof(dirs))];

        if(!dir)return;

        dest = exit[dir];

        if( !dest )return;



        if( !(obj = find_object(dest)) )

                call_other(dest, "???");

        if( !(obj = find_object(dest)) )

                return;

        if( !wizardp(ob) && query("short", obj) == "巫師休息室" )

                return;



        if( query("short", obj) == "大沙漠" || query("short", obj) == "沙漠" || query("short", obj) == "茶亭" )

                return;



        if( !undefinedp(default_dirs[dir]) )

                                         target_dir = default_dirs[dir];

                  else

                                         target_dir = dir;



        message( "vision", HIY"騾子受驚，四蹄發力，瘋狂地拉了鏢車就跑。\n"NOR,environment(ob), ({ob}));



        if( ob->move(obj) ) {

                        message( "vision", HIY "只見一輛"

                                +ob->name()+HIY"轟隆隆沉重的駛了過來。\n" NOR, environment(ob), ({ob}));



                        if( query("owner", ob) )

                        {

                                if( (me=present(query("owner", ob),here)) && query_temp("riding", me) )

                                {

                                        me->move(obj);

                                        all_inventory(here)->follow_me(me,dir);

                                }

                        }



                        if( query("owner2", ob) )

                        {

                                 if( (partner=present(query("owner2", ob),here)) && query_temp("riding", partner) )

                                 {

                                        partner->move(obj);

                                        all_inventory(here)->follow_me(partner,dir);

                                 }

                        }

        }



}


void action(object me, object ob)
{
        object here = environment();


        if( !ob || !objectp(ob) )return;

        if( !(me=present( query("owner"), here ) ) )
        {
                if( query("owner2") )
                {
                  if( !(me=present( query("owner2"), here )) )
                        {
                                if( here == environment(ob) )
                                {
                                        robber_rob(ob);
                                        return;
                                }
                        }
                } else
                {
                        if( here == environment(ob) )
                        {
                                 robber_rob(ob);
                                 return;
                        }
                }
        }


        if( !living(ob) )
        {
                 call_out("action",random(10),me,ob);
                 return;
        }

        if( !ob->is_busy() && !ob->is_fighting() )
        {
          if(random(3)) message_vision(HIR"\n$N"+HIR"喝道：此樹是我栽，此路是我開，要從此處過，留下買路錢。相好的，識趣點交出寶貝，就饒你一條狗命！\n"NOR, ob);

          else if( random(3) ) message_vision(HIR"\n$N"+HIR"喝道："+RANK_D->query_self(ob)+"我正好缺幾個錢花。相好的，趕快交出寶貝受死，就饒你一條全屍！\n"NOR, ob);
          else message_vision(HIR"\n$N"+HIR"喝道："+RANK_D->query_self(ob)+"我替天行道，劫富濟貧，狗腿子，識趣點交出寶貝，就饒你不死！\n"NOR, ob);
          ob->kill_ob(me);
        }



        if( random(60) == 1 )

        {

          message_vision(HIR"\n$N"+HIR"突然飛起一腳，向騾子踢去，結果正好踢在騾子的屁股上。\n"NOR, ob);

          call_out("run_away",0);

        }

        call_out("action",random(10),me,ob);
}

void robber_rob(object me)
{
        object here, target;

        if(random(3)) message_vision(HIR"\n$N"+HIR"喝道：此樹是我栽，此路是我開，要從此處過，留下買路錢。相好的，識趣點交出寶貝，就饒你一條狗命！\n"NOR, me);
        else if( random(3) ) message_vision(HIR"\n$N"+HIR"喝道："+RANK_D->query_self(me)+"我正好缺幾個錢花。相好的，趕快交出寶貝受死，就饒你一條全屍！\n"NOR, me);
        else message_vision(HIR"\n$N"+HIR"喝道："+RANK_D->query_self(me)+"我替天行道，劫富濟貧，狗腿子，識趣點交出寶貝，就饒你不死！\n"NOR, me);

        target = find_player( query("owner") );
        remove_call_out("destroy_it");

        message_vision(HIY"$N打開鏢車，取出一大包鏢貨。\n",me);

        if(target)

        {

                         target->remove_all_killer();

                         target->remove_enemy(me);

                         CHANNEL_D->do_channel(this_object(), "rumor","聽説"+me->name()+"洗劫了"+target->name()+"的鏢車！" );

                         delete("biao", target);

                         target->set("biao/fail");

        }

        else

         CHANNEL_D->do_channel(this_object(), "rumor","聽説"+me->name()+"洗劫了"+ query("owner")+"的鏢車！" );

  call_out("do_leave",1,me);
  call_out("destroy_me",3,this_object() );
  return ;

}



private int is_suitable(object victim, object killer)
{
                  string *no_kill_list = ({

                                         "mu ren",

                                         "huang zhen",

                                         "juexin dashi",

                                         "fighter dummy",

                                         "xie yanke",

                                         "ren woxing",

                                         "zuo lengchan",

                                         "ouyang zhan",

                                         "seng bing",

                                         "ding chunqiu",

                                         "ouyang feng",

                                         "ye erniang",

                                         "ouyang ke",

                                         "jiumozhi",

                                         "mengmian ren",

                                         "black gargoyle",

                                         "white gargoyle",

                                         "zhen xibei",

                                         "xie xun",

                                         "biao shi",

                                         "bangzhong",

                                         "yin li",

                                         "lao denuo",

                                         "robber",

                                         "yue buqun",

                                         "mao zei",

                                          "zhou zhiruo",

                                        "jinlun fawang",
                                        
                                        "sangtu gong",
                                        "dongfang bubai",
                  });



                  if(  !victim || !clonep(victim) || !living(victim) || userp(victim)

                         || query("race", victim) != "人類"

                         || query("shen", victim) >= 0

                         || query("winner", victim )

                        || strsrch(base_name(victim), "/kunfu/skill/") != -1

                        || strsrch(base_name(victim), "/clone/") != -1

                        || strsrch(base_name(victim), "/u/") != -1

                        || strsrch(base_name(victim), "/d/xiakedao/") != -1

                         || query("combat_exp", victim)<query("combat_exp", killer)*1/10

                         || query("combat_exp", victim)>query("combat_exp", killer)*7/4

                         || query("family/family_name", victim) == query("family/family_name", killer )

                         || query("family/family_name", victim) == "桃花島"

                         || member_array(query("id", victim),no_kill_list) != -1 || random(2) == 0 )

                  {

                                         return 0;

                  }

                  return 1;

}

void setup_skill(object me,object obj)
{
        mapping skills;
        string *names;
        int level,i;

        if(!objectp(me) || !objectp(obj) )return;


        if( query("combat_exp", obj)<query("combat_exp", me) )

        {

                set("combat_exp",query("combat_exp",  me)/100*(100+random(80)), obj);

        }



        level=pow(query("combat_exp", obj)*10.,0.33333);

        if(level < 10) level = 10;



        if( query("combat_exp", obj)<300000 )

        {

                level = level/2 + random(level*2/3);

        }

        else if( query("combat_exp", obj)<500000 )

        {

                level = level/2 + random(level/2);

        }

        else if( query("combat_exp", obj)<800000 )

        {

                level = level/2 + random(level/3);

        }

        else if( query("combat_exp", obj)<2000000 )

        {

                level = level/2 + random(level/3);

        }
        else
                level = level/2  + random(level*2/3);

        if( query("family/family_name", me) == "峨嵋派")//theirqishort,solowerrobber'sskillabit

        {

                level = level*2/3 ;

        }

        
        skills = obj->query_skills();

        names = keys(skills);

        for (i=0; i<sizeof(names); i++) {
          obj->set_skill(names[i], level);
        }

        delete("title", obj);
        delete("nickname", obj);
        delete("long", obj);
        delete("family", obj);
        delete("name", obj);
        delete("short", obj);
        obj->set_name(Robber_Name[random(7)], ({ "robber", "zei" }));
        set("owner",query("id",  me), obj);
        set_temp("biao/dest",query("biao/dest",  me), obj);

        if( query("owner2") )
                set("owner2", query("owner2"), obj);

        call_out("do_leave",20+random(15),obj);

}

void killer_show(object me)
{
  object ob,here,owner;
  object *target_list;

  int i;

  if( !me || !(here=environment()) || strsrch(base_name(here),"/d/") == -1 || query("no_fight", here) )
  {

                if( query("owner2") )

                {
                        owner = find_player( query("owner2") );
                        if( owner ) call_out( "killer_show",1,owner );
                }
                return;

 }


  if( !query("biao", me) )

  {

                call_out( "destroy_me",1, this_object() );

                return;

  }



  target_list = filter_array(livings(), "is_suitable", this_object(), me);

  if( sizeof(target_list) == 0 ) {

                  // try again in 5 secs.

                 call_out("killer_show", 5, me);

                 return;

  }

  do
  {
          i = random(sizeof(target_list));
          if( !environment(target_list[i]) )
                {
                        destruct(target_list[i]);
                        continue;
                }
          if( !target_list[i] || !objectp(target_list[i]) )continue;
          ob=new( base_name(target_list[i]) + ".c" );

  }
  while( !ob || !living(ob) );



  ob->move(here);
  setup_skill(me,ob);
  message_vision("\n$N突然跳了出來!\n", ob);

  ob->set_leader(me);
  call_out("action",random(3),me,ob);

  if( random(3) == 1)
  {
          remove_call_out("killer_show");
          call_out( "killer_show",1+random(2),me );
  }
}


int do_attack(string arg)
{
        object here, *obj, me = this_player(),target;
        string victim;
        int i;

        if (!arg) return notify_fail("你要攻擊誰？\n");

        victim = arg;
        if( victim == query("id", me))return notify_fail("你發瘋啦？\n");
        here = environment(me);

        target = present(victim, here);
        if (!target) return notify_fail("這裏並無此人！\n");

        if( query("race", target) != "人類" )
        {
                return notify_fail("你發瘋啦？\n");
        }

        obj = all_inventory(here);

        message_vision(HIR "$N對着$n"+HIR"喝道："+RANK_D->query_rude(target)+HIR"也想劫鏢？弟兄們，給我狠狠地教訓$p！\n\n" NOR, me, target);

        if( query("biao/dest", me) )
        {
                for(i=0;i<sizeof(obj);i++)
                {

                        if( living(obj[i]) &&

                                (query("biao/dest", obj[i]) == query("biao/dest", me )

                                         || query_temp("biao/owner", obj[i]) == query("id", me )

                                         || query_temp("biao/owner2", obj[i]) == query("id", me )

                                ) && obj[i] != me && query("id", obj[i]) != "robber" && query("id", target) != query("id", obj[i]) )

                        {

                                if( query("combat_exp", obj[i])<query("combat_exp", target) )

                                {

                                        message_vision(HIY "只見$N應聲衝着$n撲了過去！喝道："+RANK_D->query_rude(target)+HIY"拿命來吧！\n" NOR, obj[i], target);

                                        obj[i]->kill_ob(target);

                                }

                                else

                                {

                                        message_vision(HIG "只見$N對着$n不屑地哼了一聲：這個不知天高地厚的"+RANK_D->query_rude(target)+HIG"就交給你們去收拾了！\n" NOR, obj[i], target);

                                }

                        }

                }

        }



        if( living(target) )

        {

                if(random(2)==0)

                        message_vision( HIR "\n$N對着$n"+HIR"冷笑一聲：狗腿子便是全上，俺又有何懼，看招！\n\n" NOR, target,me );
                else message_vision( HIR "\n$N對着$n"+HIR"冷笑一聲：想倚多為勝？看招！\n\n" NOR, target,me );
                target->kill_ob(me);
        }

        return 1;
}


int do_check()
{
        object ppl = this_player();
        object obj = this_object();

        if( query_temp("biao/dest", obj) == "daobaifeng")write("這是由"+query("owner", obj)+"壓運的大理王妃刀白鳳的鏢貨。\n");
        else if( query_temp("biao/dest", obj) == "hulaoye")write("這是由"+query("owner", obj)+"壓運的北疆小鎮巴依託送的重鏢，要儘快送到。\n");
        else if( query_temp("biao/dest", obj) == "yeerniang")write("這是西夏葉二孃託送的重鏢，由"+query("owner", obj)+"壓運，要儘快送到。\n");
        else if( query_temp("biao/dest", obj) == "fengyiming")write("這是佛山英雄會館鳳一鳴的重鏢，由"+query("owner", obj)+"壓運。\n");
        else if( query_temp("biao/dest", obj) == "wangtongzhi")write("這是泉州濟世堂老店的重鏢，由"+query("owner", obj)+"壓運，務必交到藥鋪掌櫃王通治手裏。\n");

        return 1;
}

void destroy_it( object obj)
{
        object ppl;
        if(!objectp(obj))return;

        remove_call_out("killer_show");
        remove_call_out("auto_check");

        if( !query("owner", obj) && !query("owner2", obj))return ;
        if( query("owner", obj))ppl=find_player(query("owner", obj));
        if( userp(ppl) )
        {
                delete_temp("apply/short", ppl);
                delete("biao", ppl);
                set("biao/fail", 1, ppl);
        }


        if( query("owner2", obj))ppl=find_player(query("owner2", obj));
        if( userp(ppl) )
        {
                delete_temp("apply/short", ppl);
                delete("biao", ppl);
                set("biao/fail", 1, ppl);
        }


        if( objectp(obj) )
        {
                if( userp(ppl) && query_temp("riding", ppl) )
                {
                        message_vision( HIR"騾子突然發瘋似的拉着$N"+HIR"就跑，把$n"+HIR"一屁股甩在地上，轉眼就跑沒影了。！\n",obj,ppl);
                }
                else
                        message_vision( HIR"騾子突然發瘋似的拉着$N"+HIR"跑，轉眼就跑沒影了。！\n",obj );
                destruct(obj);
        }
}

void destroy_me(object me)
{
  remove_call_out("killer_show");
  remove_call_out("auto_check");
  destruct(me);
}


int do_rob()
{
        object here, *obj, me = this_player(),target,biaohuo;
        int i,bGuarded = 0;

        here = environment(me);

        if(!here)return 1;

        if( !query("xbiao/owner", me) || 
                (query("owner") != query("xbiao/owner", me) && query("owner2") != query("xbiao/owner", me) || 
                  query_temp("biao/dest") != query("xbiao/dest", me )
                )
        )
                return notify_fail("沒事亂劫鏢？當心你的小命！\n");

        obj = all_inventory(here);


        if(random(3)) message_vision(HIR"\n$N"+HIR"喝道：此樹是我栽，此路是我開，要從此處過，留下買路錢。相好的，識趣點交出寶貝，就饒你一條狗命！\n"NOR, me);
        else if( random(3) ) message_vision(HIR"\n$N"+HIR"喝道："+RANK_D->query_self(me)+"我正好缺幾個錢花。相好的，趕快交出寶貝受死，就饒你一條全屍！\n"NOR, me);
        else message_vision(HIR"\n$N"+HIR"喝道："+RANK_D->query_self(me)+"我替天行道，劫富濟貧，狗腿子，識趣點交出寶貝，就饒你不死！\n"NOR, me);

         for(i=0;i<sizeof(obj);i++)
         {

                        if( living(obj[i]) &&

                                        (query("id", obj[i]) == query("xbiao/owner", me )

                                                || ( query("owner2") && obj[i] == present( query("owner2"), here ) )

                                                 || query_temp("biao/owner", obj[i]) == query("xbiao/owner", me )

                                                 || query_temp("biao/owner2", obj[i]) == query("xbiao/owner", me )

                                        ) && obj[i] != me && query("id", obj[i]) != "robber"

                                )

                        {

                                obj[i]->kill_ob(me);

                                me->kill_ob(obj[i]);

                                bGuarded = 1;

                        }

         }



         target=find_player(query("xbiao/owner", me));



         if( !bGuarded )

         {

                 remove_call_out("destroy_it");

                 biaohuo = new ("/clone/npc/obj/biaohuo.c");

                 if(biaohuo)biaohuo->move(me);

                 message_vision(HIY"$N打開鏢車，取出一大包鏢貨。\n",me);

                 set("owner",query("id",  me), biaohuo);

                 me->remove_all_killer();

                 delete("xbiao/owner", me);

                 if(target)

                 {

                         me->remove_enemy(target);

                         target->remove_all_killer();

                         target->remove_enemy(me);

                         CHANNEL_D->do_channel(this_object(), "rumor","聽説"+me->name()+"洗劫了"+target->name()+"的鏢車！" );

                         delete("biao", target);

                         target->set("biao/fail");

                 }

                 else

                         CHANNEL_D->do_channel(this_object(),"rumor","聽説"+me->name()+"洗劫了"+query("xbiao/owner", me)+"的鏢車！");
                 call_out("destroy_me",1,this_object() );
         }



        return 1;

}


int do_drive(string arg)
{
        object env, obj, ob, me = this_player(), partner;
        string target_dir, dir, dest, victim;
        mapping exit;
        object here = environment(me),robber = present("robber",here);
        int busy_time;

        if (!arg) return notify_fail("你要驅趕什麼？\n");

        if( sscanf(arg, "%s %s", victim, dir) != 2 ) return notify_fail("指令錯誤！\n");

        if( victim == query("id", me))return notify_fail("何必多此一舉？\n");

        if( !query_temp("riding", me))return notify_fail("你又不在鏢車上！怎麼趕車？\n");

        if ( victim != "che" && victim != "da che" ) return notify_fail("你要驅趕什麼？\n");

        ob = present(victim, environment(me));

        if (!ob) return notify_fail("這裏並無此人！\n");

        if ( me->is_busy() ) return notify_fail("你在忙着呢！\n");

        env = environment(me);
        if( !mapp(exit=query("exits", env)) || undefinedp(exit[dir]) )
                return notify_fail("無此方向可去！\n");

        dest = exit[dir];

        if( !(obj = find_object(dest)) )
                                         call_other(dest, "???");
                  if( !(obj = find_object(dest)) )
                                         return notify_fail("無法走！\n");
        if( !wizardp(ob) && query("short", obj) == "巫師休息室" )
                return notify_fail("無法走！\n");

        if( !undefinedp(default_dirs[dir]) )
                                         target_dir = default_dirs[dir];
                  else
                                         target_dir = dir;

        message_vision( HIG"$N"+HIG"揚了揚鞭子，高聲驅趕騾子駕着$n"+HIG"朝"+target_dir+"駛去。\n" , me, ob);

        if( robber && (query("owner", robber) == query("id", me) || query("owner2", robber) == query("id", me)) )
        {
                message_vision( HIR"$N喝道：想溜？沒門！\n"NOR,robber);
                return 1;
        }

        if( query("owner", ob) != query("id", me) && query("owner2", ob) != query("id", me) )
        {
                message_vision( HIW"可是騾子理都不理$N。\n" NOR,me);
                return 1;
        }

        message("vision", HIY "只見"+ob->name()+HIY"轟隆隆沉重的向"+target_dir+"駛過去。\n" NOR, environment(ob), ({ob}));

        if( ob->move(obj) ) {
                        message( "vision", HIY "只見一輛"+ob->name()+HIY"轟隆隆沉重的駛了過來。\n" NOR, environment(ob), ({ob}));

                        busy_time = 4 + random(4);

                        if( query("owner", ob) )
                        {
                                if( (me=present(query("owner", ob),env)) && query_temp("riding", me) )
                                {
                                        message_vision( HIG"$N坐在鏢車上向"+target_dir+"駛過去。\n" NOR,me);
                                        me->move(obj);
                                        message_vision( HIG"$N坐在鏢車上駛過來。\n" NOR,me);
                                        me->start_busy( busy_time );
                                        all_inventory(env)->follow_me(me,dir);
                                }
                                else if( (me=present(query("owner", ob),environment(ob))) )
                                        me->start_busy( busy_time );
                        }

                        if( query("owner2", ob) )
                        {
                                 if( (partner=present(query("owner2", ob),env)) && query_temp("riding", partner) )
                                 {
                                        message_vision( HIG"$N坐在鏢車上向"+target_dir+"駛過去。\n" NOR,partner);
                                        partner->move(obj);
                                        message_vision( HIG"$N坐在鏢車上駛過來。\n" NOR,partner);
                                        partner->start_busy( busy_time );
                                        all_inventory(env)->follow_me(partner,dir);
                                 }
                                 else if( (partner=present(query("owner2", ob),environment(ob))) )
                                {
                                        partner->start_busy( busy_time );
                                }
                        }
        }

        return 1;
}