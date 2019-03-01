// zeng.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_job();

int  working(object me);
int  halt_working(object me);

void create()
{
        set_name("曾柔", ({ "zeng rou", "zeng", "rou" }));
        set("gender", "女性");
        set("age", 16);
        set("per", 25);
        set("con", 25);
        set("int", 25);
        set("dex", 25);
        set("str", 25);
        set("long",
"她是韋爵爺不知道第幾房的小妾，在這裡開個成衣舖，賣些不知道
哪來的衣服。有人說那都是韋爵爺從宮中弄出來的禁品。話這麼說，
生意照樣紅活。\n");
        set_skill("unarmed", 60);
        set_skill("changquan", 60);
        map_skill("unarmed", "changquan");
        set_temp("apply/damage", 15);

        set("combat_exp", 50000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                __DIR__"cloth/belt",
                __DIR__"cloth/boots",
                __DIR__"cloth/bu-shoes",
                __DIR__"cloth/cloth",
                __DIR__"cloth/color-dress",
                __DIR__"cloth/fu-cloth",
                __DIR__"cloth/gui-dress",
                __DIR__"cloth/hat",
                __DIR__"cloth/jade-belt",
                __DIR__"cloth/liu-dress",
                __DIR__"cloth/marry-dress",
                __DIR__"cloth/mini-dress",
                __DIR__"cloth/moon-dress",
                __DIR__"cloth/pink-dress",
                __DIR__"cloth/qi-dress",
                __DIR__"cloth/red-dress",
                __DIR__"cloth/scarf",
                __DIR__"cloth/sha-dress",
                __DIR__"cloth/shoes",
                __DIR__"cloth/xian-cloth",
                __DIR__"cloth/xiu-cloth",
                __DIR__"cloth/xiu-scarf",
                __DIR__"cloth/yan-dress",
                __DIR__"cloth/zi-dress",
        }));

        set("inquiry", ([
            "工作" : (: ask_job :),
            "job"  : (: ask_job :),
        ]));

        setup();
        carry_object(__DIR__"cloth/feature")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_sew", "sew");
}

string ask_job()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/sew", me) )
                return "讓你做的衣服你弄好了麼？";

        if( query("gender", me) != "女性" )
                return "這女孩子家的活你也來幹？";

        if( query("combat_exp", me)<3000 )
                return "讓你在我這兒幹活我還真有點不放心。";

        if( query("combat_exp", me)>300000 )
                return "大俠您好，您還是看見什麼好的自己選件吧，讓您幹活也太委屈了！";

        if( query("qi", me)<30 )
                return "你臉色這麼差，還是先歇會兒吧。";

        if( query("jing", me)<30 )
                return "你精神頭不行啊，別把我得料子糟踏了！";

        if (me->query_int() < 20)
                return "嘻嘻...你這麼笨手笨腳的，也會做衣服？";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/sew", $1) && 
                              query_ip_number($1) == query_ip_number($(me)) :));

        if (sizeof(obs) > 0)
                return "現在已經有" + obs[0]->name() + "在幫我啦，不勞你了。";

        set_temp("job/sew", 1, me);
        return "好，你就幫我做點裁縫(sew)的小活吧！喏，東西都在這兒。";
}

int do_sew(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("你正忙著呢，別著急。\n");

        if( !query_temp("job/sew", me) )
        {
                message_vision("$N偷偷的拿起一個頂針，$n一聲嬌吒道："
                               "你給我放下，有什麼好玩的？\n",
                               me, this_object());
                return 1;
        }

        set_temp("job/step", 1, me);
        me->start_busy(bind((: call_other, __FILE__, "working" :), me),
                       bind((: call_other, __FILE__, "halt_working" :), me));
        tell_object(me, "你開始縫紉。\n");
        return 1;
}

int working(object me)
{
        string msg;
        object ob;
        int finish;
        int b;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/sew", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        me->receive_damage("jing", 1);
        me->receive_damage("qi", 2);
        switch(query_temp("job/step", me) )
        {
        case 1:
                msg = "$N戴上一個頂針，摸出針線。";
                break;
        case 2:
                msg = "$N展開布料，對著樣子比劃了半天。";
                break;
        case 3:
                msg = "$N輕輕的折了折料子，留下幾條痕印。";
                break;
        case 4:
        case 6:
                msg = "$N專心致志的一針一線的縫紉。";
                break;
        case 5:
                msg = "$N凝眉看了看樣子，若有所思。";
        case 7:
                msg = "$N輕動纖纖細指，縫針上下穿梭，衣服的模樣漸漸的出來了。";
                break;
        default:
                msg = "$N把衣服縫好，燙熨完畢，疊好遞給$n。";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                msg += "$n看了$N縫出來的衣服，點頭道：不錯，有點意思。\n";
                delete_temp("job/sew", me);
                delete_temp("job/step", me);

                b = 900 + random(100);
                GIFT_D->delay_work_bonus(me, ([ "exp" : b, "pot" : b / 3 ]));

                ob = new("/clone/money/silver");
                ob->set_amount(6);
                ob->move(me, 1);
        }

        msg = replace_string(msg, "$N", "你");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);

        if (finish)
        {
                if (! query("zhufu_mod/cloth", me) && random(10) == 1) 
                {
                        message_vision("$n對$N微微一笑，道：幹得不賴，有點" 
                                       "意思，這個神之祝福戰衣就算是我送給你的禮物吧。\n",
                                       me, this_object());
                        ob = new("/clone/goods/zhufu_cloth"); 
                        ob->move(me, 1); 
                        tell_object(me, HIM "\n你獲得了一個" + ob->name() + HIM "！\n" NOR);
                        set("zhufu_mod/cloth", 1, me); 
                }
                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_working(object me)
{
        message_vision("$N把手中的針線一扔，嘀咕道："
                       "沒勁，本姑娘不幹了！\n", me);
        delete_temp("job/sew", me);
        delete_temp("job/step", me);
        return 1;
}
