// Code of JHSH
// baituo python 白駝山蛇谷的大蛇、蟒蛇
// by maco
#include <ansi.h>

inherit SNAKE;

int auto_perform_duwu();
int auto_perform_chan();

void create()
{
        int s, p;

        s = random(40);
        p = random(3);
        set_weight(12000);

        switch( p )
        {
        case 0:
                set_name("巨蟒", ({ "ju mang", "she", "mang", "python" }) );
                set("long", "一條碗口粗細的三角頭巨蟒，有兩丈多長。\n");
                set("chat_msg_combat", ({
                        (: auto_perform_chan :),
                }));
                break;
        case 1:
                set_name("大蛇", ({ "da she", "she", "snake", "dashe" }) );
                set("long", "一條身長兩丈，粗如人臂的大蛇，全身斑斕五色，一顆頭作三角形，比人的拳頭還大。\n"
                "尋常大蛇無毒，此蛇如此巨大，卻是毒蛇，實在罕見。\n");
/*
        set("snake_poison", ([
                "level"  : 200,
                "perhit" : 60,
                "remain" : 100,
                "maximum": 100,
                "supply" : 5,
        ]));
*/

                set("chat_msg_combat", ({
                        (: auto_perform_duwu :),
                }));
                break;
        case 2:
                set_name("毒蟒", ({ "du mang", "she", "mang", "snake", "python"}) );
                set("long", "一條白身黑章的大蟒蛇，蟒頭作三角形，頭頂上高高生了一個\n"
                "凹凹凸凸的肉瘤，身長二丈，粗逾手臂。\n"
                "蟒蛇本來無毒，這條大蟒卻生的如此異狀，又具劇毒，實是希罕。\n");
/*
        set("snake_poison", ([
                "level"  : 200,
                "perhit" : 60,
                "remain" : 100,
                "maximum": 100,
                "supply" : 5,
        ]));
*/

                set("chat_msg_combat", ({
                        (: auto_perform_chan :),
                        (: auto_perform_duwu :),
                }));
                break;
        }

        set("age", 100);
        set("attitude", "peaceful");

        set("str", 30 + p );
        set("con", 40 + p );
        set("int", 10);
        set("dex", 30 + p );

        set("max_jing", 4000);
        set("max_qi", 4000);
        set("max_jingli", 2000);

        set("combat_exp", p*100000 + 500000);
        set("chat_chance_combat", 30);

        set_temp("apply/attack", 300 + s);
        set_temp("apply/damage", 200 + s);
        set_temp("apply/armor", 400 + s);
        set_temp("apply/parry", 300 + s);
        set_temp("apply/dodge", 260 + s);
        set("bt_snake", 1);

        setup();
}

void init()
{
        object me;
        ::init();
        me = this_object();
        add_action("convert","bian");
        add_action("do_struggle","struggle");
        add_action("do_struggle","zhengza");

        if (!me->is_fighting() && living(me) && !me->is_busy()
         && !query("no_fight", environment(me))){
                remove_call_out("hunting");
                call_out("hunting", 1, me, this_player());
        }
}

void hunting(object me, object ob)
{
    if (! objectp(me) || ! objectp(ob))
        return;

        if(random(4) != 0 && !me->is_fighting() && living(me) && !me->is_busy()
         && !query("no_fight", environment(me)) )
                set_temp("hunting",query("id", ob));

        if (present(ob, environment(me))) {
                if( !ob->is_character() && query("my_killer", ob) != query("id", me)){
                        message_vision("$N在$n旁邊繞了幾圈，嘶地一吐信，慢慢蜿蜒遊開，似乎不感興趣。\n", me, ob);
                        return;
                }
                else if( query_temp("hunting") && !me->is_fighting() && living(me)
                 && !me->is_busy() && !query("no_fight", environment(me))){

                        if(random(2) == 0) {
                        message("vision", HIR"你忽然聞得一陣腥風，猛見"+me->name()+"張開大口，露出獠牙，疾向"+ob->name()+"咬去！\n"NOR, environment(ob), ob);
                        tell_object(ob,HIR"你耳中忽聞嘶嘶聲響，一遲疑間，驀地腥臭迎面，"+me->name()+"猛然向你張口撲來！\n"NOR);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        kill_ob(ob);
                        delete_temp("hunting");
                        }
                        else {
                        remove_call_out("hunting");
                        call_out("hunting", 2, me, ob);
                        }
                        return;
                }

                else message_vision("$N聽到$n過來的聲息，立時盤曲成團，昂起了頭，伸出血紅的舌頭，嘶嘶作聲。\n", me, ob);
        }
        return;
}


void chaning(object me, object ob)
{
        int ap, dp, pp, jingli, damage;

        string *chan_msg = ({
                HIR"\n$n暗運勁力，想將纏在身上的$N崩斷。但$N身子可伸可縮，只略加延伸，並不會斷。\n"NOR,
                HIR"\n$N猛力纏緊，只箍得$n腰骨幾欲折斷。\n"NOR,
                HIR"\n$N身子一卷到$n，越收越緊，再也不放，$n漸漸給$N纏得喘不過氣來。\n"NOR,
                HIR"\n$n被$N纏住，除了呻吟怒罵，再無反抗的能為。\n"NOR,
        });
        string *chan_beast_msg = ({
                HIR"\n$N猛力纏緊，不讓$n有機會逃脫。\n"NOR,
                HIR"\n$N身子一卷到$n，越收越緊，再也不放，$n漸漸給$N纏得喘不過氣來。\n"NOR,
                HIR"\n$n被$N纏住，慢慢失了抗拒之力，氣息越來越是微弱。\n"NOR,
        });

        string *chan_snake_msg = ({
                HIR"\n$N猛力纏緊，牢牢箍住$n的七寸。\n"NOR,
                HIR"\n$N身子一卷到$n，越收越緊，再也不放，$n漸漸給$N纏得喘不過氣來。\n"NOR,
                HIR"\n$N將$n緊緊纏住，慢慢施力，$n雖然不斷扭動蛇身，卻也無法脫困。\n"NOR,
        });
        string *chan_bird_msg = ({
                HIR"\n$N猛力纏緊，只箍得$n雙翅幾欲折斷。\n"NOR,
                HIR"\n$n被$N纏住，吱吱亂叫，翅膀不停撲打。\n"NOR,
                HIR"\n$N癒盤癒緊，$n毛羽賁張，竭力相抗，眼見不支。\n"NOR,
        });

        string chan;
        switch(query("race", ob)){
        case "人類" :        chan = chan_msg[random(sizeof(chan_msg))];        break;
        case "飛禽" :        chan = chan_bird_msg[random(sizeof(chan_bird_msg))];        break;
        case "蛇類" :        chan = chan_snake_msg[random(sizeof(chan_snake_msg))];        break;
        case "野獸" :
        case "家畜" :        chan = chan_beast_msg[random(sizeof(chan_beast_msg))];        break;
        default:        return 0;
        }


        jingli=query("jingli", me);
        ap = jingli + random(jingli);
        pp=query("jiali", ob)+ob->query_str()*random(10)+ob->query_skill("force");
        damage = (ap - pp)/3;

        if(damage > 1000 ) damage = 1000;
        if(damage < 100 ) damage = 100;

        if(wizardp(ob))
        tell_object(ob,sprintf("ap：%d ,pp：%d ,damage：%d \n" ,ap,pp,damage));

        if(!ob) {
                delete_temp("chaning", me);
                return;
        }
        if (present(ob, environment(me))) {

                if( !query_temp("chaning", me) || !query_temp("snake_chan", ob)){
                delete_temp("chaning", me);
                delete_temp("snake_chan", ob);
                return;
        }

                if (!living(ob) ) {  //獵物昏了就咬死
                        if( query("race", ob) == "人類" )
                                message_vision(HIR"這時$n已給$N纏得奄奄一息，$N張開大口，咬住了$n，腿腳先入蛇口，慢慢的給吞至腰間，又吞至胸口。\n"NOR, me, ob);
                        else message_vision(HIR"這時$n已給$N纏得奄奄一息，$N張開大口，一口便將$n咬死。\n"NOR, me, ob);
                        ob->receive_wound("qi",(query("qi", ob)+100),"被"+me->name()+"咬死了");
                        ob->receive_damage("qi",(query("qi", ob)+100),"被"+me->name()+"咬死了");
                        delete_temp("snake_chan", ob);
                        delete_temp("chaning", me);

                        return;
                }

                else if (!ob->is_character() ) {  //獵物死了就放開
                        message_vision("$N鬆開身子，放開了$n，四下蜿蜒遊走。\n", me, ob);
                        delete_temp("snake_chan", ob);
                        delete_temp("chaning", me);
                        return;
                }
                else {

                        if(ap < random(pp) || jingli < 500 ) {
                        message_vision("$N似乎敵不過$n的勁力，慢慢鬆開身子，放開了$n，四下蜿蜒遊走。\n", me, ob);
                        delete_temp("snake_chan", ob);
                        delete_temp("chaning", me);
                        }
                        else {
                        message_vision(chan , me, ob);
                        ob->start_busy(3);
                        me->start_busy(2);
                        addn("jingli", -(pp/20), me);

                        addn("jingli", -damage/4, ob);
                        ob->receive_wound("qi", random(damage/10), "被"+me->name()+"纏死了");
                        ob->receive_damage("qi", damage/2, "被"+me->name()+"纏死了");

                        remove_call_out("chaning");
                        call_out("chaning", 1, me, ob);
                        }
                        return;
                }
        }

        return;
}


int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she") return 0;
        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你不能化蛇為杖。\n");

        return notify_fail(this_object()->name()+"身子太過粗大，無法化為蛇杖。\n");
}

int do_struggle(string arg)
{
        object me, snake;
        int ap, jingli, jiali;

        me = this_player();
        snake = this_object();

        if( query_temp("chaning", snake) != query("id", me) )
                return 0;
        if( !query_temp("snake_chan", me) || !me->is_busy() )
                return 0;

        jingli=query("jingli", snake);
        jiali=query("jiali", me);
        ap = jingli + random(jingli);

        if( query_temp("struggle_snake", me)>4){
                message_vision(HIW"\n$N用力掙了一掙，想擺脫纏住身子的$n.....\n"NOR, me, snake);
                message_vision(HIR"\n不料$N身子動得太厲害，激怒了纏住了$P的$n，一口便咬住$P的嚥喉！\n"NOR, me, snake);
                me->receive_wound("qi", random(ap/2), "被"+me->name()+"咬死了");
                me->receive_damage("qi", ap/2, "被"+me->name()+"咬死了");
                me->unconcious();
        }
        else {
                message_vision(HIW"\n$N用力掙了一掙，想擺脫纏住身子的$n.....\n"NOR, me, snake);
                addn("neili", -jiali, me);
                addn("jingli", -jiali*2, snake);
                addn_temp("struggle_snake", 1, me);
                remove_call_out("remove_effect");
                call_out("remove_effect", 1, me);
        }

        return 1;
}

void remove_effect(object me)
{
        delete_temp("struggle_snake", me);
}

#include "snake_perform.h"