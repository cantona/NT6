// /d/city/npc/oldman.c
// Last Modified by winder on Aug. 5 2001

#include <ansi.h>
inherit NPC;
inherit F_DEALER;

string *classes = ({
        "dragon","phenix","kylin","elephant","lion","tiger","panther","bear","fox","wolf","dog",
        "pig","deer","marten","cat","mouse","monkey","eagle","vulture","chicken","duck","snake",
        "tortoise","crocodile","horse","donkey","cattle","rabbit"
});
string *title = ({
        HIY"龍",HIC"鳳凰",YEL"麒麟","象","獅","虎","豹","熊","狐","狼","狗","豬","鹿","貂","貓",
        "鼠","猴","鷹","雕","雞","鴨","蛇","龜","鱷","馬","驢","牛","兔"
});
int *petstr=({30,20,25,30,25,25,20,25,12,15,12,15,10, 5, 5, 5,12,10,18, 5, 5,15, 5,18,20,18,22,10});
int *petdex=({30,30,25,10,20,20,25,12,20,20,20,10,22,20,20,18,30,25,25,20,20,15, 5,10,20,22,12,18});
int *petcon=({30,30,30,25,25,25,20,25,13,15,18,15,15,18,20,18,15,20,20,12,12,20,22,20,15,18,20,12});
int *petint=({30,30,30,12,15,15,12,12,20,12,20,10,10, 5,12,11,30,10,12,10,10, 5, 5, 8,12,10,10,12});
int *petper=({25,25,25,20,20,20,20,12,15,15,15,12,22,25,22,11,22,20,18,15,13, 8,10, 5,15,15,15,18});
int *petkar=({30,30,30,12,15,18,20,12,18,15,20,18,15,20,25,23,28,20,22,18,15,10,10, 8,12,15,15,12});
int *petcor=({30,30,30,15,20,25,25,20,12,20,18,12, 5,10,20,18,15,25,28,10,10,12,15,20,12,13,15, 5});
int *petcps=({30,30,30,25,20,20,15,20,25,12,18,15, 5, 8,10, 9,15,10,20,10,10,12,20,20,13,12,15, 5});
int *weight=({90,10,50,80,60,60,40,70,15,20,20,40,18,10,10, 8,15,20,35,10,10,18,10,30,40,30,45, 5});
int *value =({99,99,99,49,49,49,49,39,39,39,39,19,29,19, 9, 9,29,29,49, 9, 9,19, 9,39,39,29,29, 9});

int do_goumai(string arg);
void addaction(object pet);
void addaction(object pet)
{
        switch(query("class", pet) )
        {
                case "dragon"   :     //龍
                        set("verbs", ({"angel","bite","claw","rope","tail"}), pet);break;
                case "phenix"   :     //鳳凰
                        set("verbs", ({"claw","poke","wind"}), pet);break;
                case "kylin"    :     //麒麟
                        set("verbs", ({"angel","bite","hoof","knock"}), pet);break;
                case "elephant" :     //象
                        set("verbs", ({"hoof","knock","snoot"}), pet);break;
                case "lion"     :     //獅
                        set("verbs", ({"bite","claw","hoof","snap"}), pet);break;
                case "tiger"    :     //虎
                        set("verbs", ({"bite","claw","hoof","snap","tail"}), pet);break;
                case "panther"  :     //豹
                        set("verbs", ({"bite","claw","hoof","snap"}), pet);break;
                case "bear"     :     //熊
                case "fox"      :     //狐
                        set("verbs", ({"bite","claw","hoof"}), pet);break;
                case "wolf"     :     //狼
                case "dog"      :     //狗
                        set("verbs", ({"bite","claw","hoof","snap"}), pet);break;
                case "pig"      :     //豬
                        set("verbs", ({"bite","hoof","knock"}), pet);break;
                case "deer"     :     //鹿
                case "cattle"   :     //牛
                        set("verbs", ({"angel","hoof","knock"}), pet);break;
                case "marten"   :     //貂
                case "cat"      :     //貓
                case "monkey"   :     //猴
                case "rabbit"   :     //兔
                case "mouse"    :     //鼠
                        set("verbs", ({"bite","claw","hoof"}), pet);break;
                case "eagle"    :     //鷹
                case "vulture"  :     //雕
                case "chicken"  :     //雞
                case "duck"     :     //鴨
                        set("verbs", ({"claw","poke","wind"}), pet);break;
                case "snake"    :     //蛇
                        set("verbs", ({"bite","rope","tail"}), pet);break;
                case "tortise"  :     //龜
                        set("verbs", ({"bite"}), pet);break;
                case "crocodile":     //鱷
                        set("verbs", ({"bite","claw","tail"}), pet);break;
                case "horse"    :     //馬
                case "donkey"   :     //驢
                        set("verbs", ({"bite","hoof","knock"}), pet);break;
                default:
                        set("verbs", ({"bite","claw"}), pet);break;
        }
}
void create()
{
        set_name("白髯老頭", ({ "lao tou", "laotou", "oldman"}) );
        set("gender", "男性" );
        set("age", 64);
        set("long","一個鬚髮皆白的老者，精神矍鑠，滿面紅光。如果你有興趣，可以向他要只寵物養來玩玩。\n");
        set("max_qi", 2000);
        set("max_jing", 2000);
        set("max_neili", 2000);
        set("jiali", 50);
        set("combat_exp", 400000);
        set("attitude", "friendly");
        set_skill("dodge", 120);
        set_skill("unarmed",120);
        set_skill("parry", 120);
        set_skill("force",120);
        set("inquiry", ([
                "寵物"  : "你要購買(goumai)什麼寵物？請看本店招牌。\n",
        ]) );
        set("vendor_goods", ({
                FODDER_DIR+"siliao",
                FODDER_DIR+"fantuan",
                FODDER_DIR+"miantuan",
                FODDER_DIR+"roukuai",
                FODDER_DIR+"routuan",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",30);
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_goumai","goumai");
        add_action("do_return","return");
        add_action("do_lingqu","lingqu");
        add_action("do_zancun","zancun");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query("Pet", ob) )
        {
                say("白髯老者掀髯笑道：“這位"+RANK_D->query_respect(ob)+"，你的寵物養得如何了啊？”\n");
        }
        else
        {
                say("白髯老者掀髯笑道：“這位"+RANK_D->query_respect(ob)+"，來買寵物啊？”\n");
        }
}
int do_goumai(string arg)
{
        object pet, gold, me = this_player(), ob = this_object();
        int num;

        if(!arg)
                return notify_fail("老頭笑道：“別急，你想購買什麼寵物，請先看清楚招牌。”\n");
        if( query("Pet", me) && !wizardp(me) )
        {
                command("say 這位"+RANK_D->query_respect(me)+"，寵物只能豢養一隻，如果想買新的，得把舊的先還(return)給我。”\n");
                return 1;
        }
        if ( member_array(arg, classes) == -1)
                return notify_fail("老頭歉然笑道：“暫時沒有這種寵物可買，請看清楚招牌。”\n");
        if( !wizardp(me) && query("combat_exp", me)<2000000 && 
                (arg == "dragon" || arg == "phenix" || arg == "kylin"))
                return notify_fail("老頭呵呵一通，笑道：“你的經驗還不足養這些寵物。”\n");

        num = member_array(arg, classes);
        gold = present("gold", me);
        if(!gold) return notify_fail("老頭笑了笑：“你沒帶金子來？”\n");
        if((int) gold->query_amount() < value[num])
                return notify_fail("老頭看了你一眼：“你身上黃金沒帶夠。”\n");
        pet = new("/clone/misc/pet");
        set("class", classes[num], pet);
        set("id", classes[num], pet);
        set("title", title[num]+NOR, pet);
        set("name", "寵物", pet);
        set("race", "野獸", pet);
        pet->set_name("寵物", ({classes[num], "pet"}));
        set("long", "這是一隻寵物"+title[num]+"。\n"NOR, pet);
        set("level", 1, pet);
        set("owner",query("id",  me), pet);
        set_temp("owner",query("id",  me), pet);
        set_temp("ownername",query("name",  me), pet);
        set("Pet/id", classes[num], me);
        set("Pet/name", "寵物", me);

        set("str", petstr[num]+random(10), pet);
        set("dex", petdex[num]+random(10), pet);
        set("con", petcon[num]+random(10), pet);
        set("int", petint[num]+random(10), pet);
        set("per", petper[num]+random(10), pet);
        set("kar", petkar[num]+random(10), pet);
        set("cor", petcor[num]+random(10), pet);
        set("cps", petcps[num]+random(10), pet);
        set("obe", 1, pet);//初始馴服度
        set("age", 1, pet);//年齡
// 重量決定食量
        set("weight", weight[num]*1000, pet);
        pet->set_weight(weight[num]*1000);
        if( random(10)>4)set("gender", "雌性", pet);
        else set("gender", "雄性", pet);
        gold->add_amount(-value[num]);

        addaction(pet);
        pet->move(environment(me));
        message_vision("$N掏出"HIR+chinese_number(value[num])+NOR"兩"HIY"黃金"NOR"，往櫃面一砸：“給我來一隻"+title[num]+NOR"。”\n", me);
        message_vision("$N看了一眼"HIY"黃金"NOR"成色，伸手一捋，把它捋到抽屜裏。然後從身後籠子裏取出一隻"+title[num]+NOR"放在地上。\n", ob);
        set("Pet/class",query("class",  pet), me);
        set("Pet/exp",query("combat_exp",  pet), me);
        set("Pet/id",query("id",  pet), me);
        set("Pet/title",query("title",  pet), me);
        set("Pet/name",query("name",  pet), me);
        set("Pet/nickname",query("nickname",  pet), me);
        set("Pet/long",query("long",  pet), me);
        set("Pet/level",query("level",  pet), me);
        set("Pet/max_jing",query("max_jing",  pet), me);
        set("Pet/eff_jing",query("eff_jing",  pet), me);
        set("Pet/jing",query("jing",  pet), me);
        set("Pet/max_qi",query("max_qi",  pet), me);
        set("Pet/eff_qi",query("eff_qi",  pet), me);
        set("Pet/qi",query("qi",  pet), me);
        set("Pet/food",query("food",  pet), me);
        set("Pet/water",query("water",  pet), me);

        set("Pet/str",query("str",  pet), me);
        set("Pet/dex",query("dex",  pet), me);
        set("Pet/con",query("con",  pet), me);
        set("Pet/int",query("int",  pet), me);
        set("Pet/per",query("per",  pet), me);
        set("Pet/kar",query("kar",  pet), me);
        set("Pet/cor",query("cor",  pet), me);
        set("Pet/cps",query("cps",  pet), me);
        set("Pet/obe",query("obe",  pet), me);

        if( query("last_age_set", pet) )
                addn("mud_age", time()-query("last_age_set", pet), pet);
        else addn("mud_age", 1, pet);
        set("Pet/mud_age",query("mud_age",  pet), me);
        set("Pet/weight",query("weight",  pet), me);
        set("Pet/gender",query("gender",  pet), me);
        set("Pet/wimpy",query("env/wimpy",  pet), me);

        set("Pet/unarmed", pet->query_skill("unarmed",1), me);
        set("Pet/dodge", pet->query_skill("dodge",1), me);
        set("Pet/parry", pet->query_skill("parry",1), me);

        return 1;
}

int do_return()
{
        object me = this_player(), *ob;
        string file, id;
        int i;

        if( !query("Pet", me) )
                return notify_fail("老頭呵呵樂了：“你就沒養寵物，來這湊啥熱鬧來着？”\n");
        if(me->is_busy())
                return notify_fail("你上一個動作還沒有完成。\n");
        id=query("id", me);
        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if( query("owner", ob[i]) == id && query("curiousness", ob[i]) )
                {
                        break;
                }
        }
        if( i == sizeof(ob) )
                return notify_fail("老頭奇怪地看了你一眼：“你的寵物沒帶來，那你怎麼還給我啊？”\n");
        message_vision("$N一把抱起地上的$n，遞過櫃枱還給老頭。\n", me, ob[i]);
        delete("Pet", me);
        destruct(ob[i]);
        me->start_busy(1);
        return 1;
}
int do_lingqu()
{
        object pet, me = this_player(), ob = this_object(), *obj;
        int i;

        if(me->is_busy())
                return notify_fail("你上一個動作還沒有完成。\n");
        if( !query("Pet", me) )
        {
                command("say 這位"+RANK_D->query_respect(me)+"，你沒暫存(zancun)過寵物，這裏哪有東西可領取？”\n");
                return 1;
        }

        obj = objects();
        for (i=0; i<sizeof(obj); i++)
        {
                if( query("owner", obj[i]) == query("id", me) && //奸細也有owner
                        query("curiousness", obj[i]) )
                {
                        if(environment(obj[i]) == me )
                                return notify_fail(ob->name()+ "説道：你不是正騎在你的寵物身上麼？\n");
                        else
                                if(environment(obj[i]) != environment(me) )
                                        return notify_fail(ob->name()+"説道：你的寵物在"+(query("outdoors",environment(obj[i])) ? to_chinese(query("outdoors",environment(obj[i]))) : "哪裏")+"的"+query("short",environment(obj[i]))+"，趕快去找吧。\n");
                                else
                                        return notify_fail(ob->name()+ "説道：你的寵物不是就在你旁邊麼？\n");
                        return 1;
                }
        }
        pet = new("/clone/misc/pet");

        set("owner",query("id",  me), pet);
        set_temp("owner",query("id",  me), pet);
        set_temp("ownername",query("name",  me), pet);

        set("class",query("Pet/class",  me), pet);
        set("id",query("Pet/id",  me), pet);
        set("title",query("Pet/title",  me), pet);
        set("name",query("Pet/name",  me), pet);
        set("nickname",query("Pet/nickname",  me), pet);
        set("race", "野獸", pet);
        pet->set_name(query("Pet/name", me),({query("Pet/id", me),"pet"}));
        set("long",query("Pet/long",  me), pet);
        set("level",query("Pet/level",  me), pet);

        set("str",query("Pet/str",  me), pet);
        set("dex",query("Pet/dex",  me), pet);
        set("con",query("Pet/con",  me), pet);
        set("int",query("Pet/int",  me), pet);
        set("per",query("Pet/per",  me), pet);
        set("kar",query("Pet/kar",  me), pet);
        set("cor",query("Pet/cor",  me), pet);
        set("cps",query("Pet/cps",  me), pet);
        set("obe",query("Pet/obe",  me), pet);

        set("combat_exp",query("Pet/exp",  me), pet);
        set("mud_age",query("Pet/mud_age",  me), pet);
        set("age", 1+query("Pet/mud_age", me)/86400, pet);
        set("weight",query("Pet/weight",  me), pet);
        pet->set_weight(query("Pet/weight", me));
        set("gender",query("Pet/gender",  me), pet);
        set("env/wimpy",query("Pet/wimpy",  me), pet);

        set("max_jing",query("Pet/max_jing",  me), pet);
        set("eff_jing",query("Pet/eff_jing",  me), pet);
        set("jing",query("Pet/jing",  me), pet);
        set("max_qi",query("Pet/max_qi",  me), pet);
        set("eff_qi",query("Pet/eff_qi",  me), pet);
        set("qi",query("Pet/qi",  me), pet);
        set("food",query("Pet/food",  me), pet);
        set("water",query("Pet/water",  me), pet);

        set("curiousness", 1, pet);
        set("last_age_set", time(), pet);

        pet->set_skill("unarmed",query("Pet/unarmed", me));
        pet->set_skill("dodge",query("Pet/dodge", me));
        pet->set_skill("parry",query("Pet/parry", me));

        addaction(pet);

        pet->move(environment(me));
        message_vision("$N從身後籠子裏取出一隻"+pet->name()+"放在地上。\n", ob);
        me->start_busy(1);
        return 1;
}

int do_zancun()
{
        object me = this_player(), *ob;
        string file, id;
        int i;

        if( !query("Pet", me) )
                return notify_fail("老頭呵呵樂了：“你就沒養寵物，來這湊啥熱鬧來着？”\n");
        if(me->is_busy())
                return notify_fail("你上一個動作還沒有完成。\n");
        id=query("id", me);
        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if( query("owner", ob[i]) == id && query("curiousness", ob[i]) )
                {
                        break;
                }
        }
        if( i == sizeof(ob) )
                return notify_fail("老頭奇怪地看了你一眼：“你的寵物沒帶來，暫存啥啊？”\n");
        if( query_temp("feeded", ob[i]) )
                return notify_fail(ob[i]->name()+"剛吃了東西，懶洋洋的不想理你。\n");

        set("Pet/class",query("class",  ob[i]), me);
        set("Pet/exp",query("combat_exp",  ob[i]), me);
        set("Pet/id",query("id",  ob[i]), me);
        set("Pet/title",query("title",  ob[i]), me);
        set("Pet/name",query("name",  ob[i]), me);
        set("Pet/nickname",query("nickname",  ob[i]), me);
        set("Pet/long",query("long",  ob[i]), me);
        set("Pet/level",query("level",  ob[i]), me);
        set("Pet/max_jing",query("max_jing",  ob[i]), me);
        set("Pet/eff_jing",query("eff_jing",  ob[i]), me);
        set("Pet/jing",query("jing",  ob[i]), me);
        set("Pet/max_qi",query("max_qi",  ob[i]), me);
        set("Pet/eff_qi",query("eff_qi",  ob[i]), me);
        set("Pet/qi",query("qi",  ob[i]), me);
        set("Pet/food",query("food",  ob[i]), me);
        set("Pet/water",query("water",  ob[i]), me);

        set("Pet/str",query("str",  ob[i]), me);
        set("Pet/dex",query("dex",  ob[i]), me);
        set("Pet/con",query("con",  ob[i]), me);
        set("Pet/int",query("int",  ob[i]), me);
        set("Pet/per",query("per",  ob[i]), me);
        set("Pet/kar",query("kar",  ob[i]), me);
        set("Pet/cor",query("cor",  ob[i]), me);
        set("Pet/cps",query("cps",  ob[i]), me);
        set("Pet/obe",query("obe",  ob[i]), me);

        if( query("last_age_set", ob[i]) )
                addn("mud_age", time()-query("last_age_set", ob[i]), ob[i]);
        else addn("mud_age", 1, ob[i]);
        set("Pet/mud_age",query("mud_age",  ob[i]), me);
        set("Pet/weight",query("weight",  ob[i]), me);
        set("Pet/gender",query("gender",  ob[i]), me);
        set("Pet/wimpy",query("env/wimpy",  ob[i]), me);

        set("Pet/unarmed", ob[i]->query_skill("unarmed",1), me);
        set("Pet/dodge", ob[i]->query_skill("dodge",1), me);
        set("Pet/parry", ob[i]->query_skill("parry",1), me);

// 取消跟隨狀態
        delete_temp("comedby", me);

        message_vision("$N一把抱起地上的$n，遞過櫃枱給老頭暫存。\n", me, ob[i]);
        destruct(ob[i]);
        me->start_busy(1);
        return 1;
}
