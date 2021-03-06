#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_job();

int  do_cook(string arg);
int  cooking(object me);
int  halt_cooking(object me);

void create()
{
        set_name("廚娘", ({"chu niang", "chu", "niang"}));
        set("long", @LONG
她是一個看上去普普通通的廚娘，常年累月的在廚房燒菜作飯，一雙
粗糙的大手，油膩的圍裙，貌不驚人，可是她做的飯菜深得卻是川中
一絕，為人似乎十分傲慢，看來不是一般的人物。
LONG );
        set("gender", "女性");
        set("age", 35);
        set("no_get", 0);
        set("attitude", "friendly");

        set("inquiry",([
                "job" : (: ask_job :),
                "工作" : (: ask_job :),
        ]));

        set("age", 30);

        set("str", 21);
        set("int", 22);
        set("con", 30);
        set("dex", 21);

        set("max_qi", 450);
        set("max_jing", 200);
        set("neili", 350);
        set("max_neili", 350);
        set("jiali", 30);
        set("combat_exp", 5000);
        set("score", 100);

        set_skill("force", 30);
        set_skill("dodge", 50);
        set_skill("cooking", 200);
        set_skill("chuancai-jiyi", 200);
        set_skill("unarmed", 50);

        set("vendor_goods", ({
                "/clone/misc/cailiao",
        }));

        setup();
}

void init()
{
        add_action("do_cook", "cooking");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

string ask_job()
{
        object *uob;
        object me;
        me = this_player();
        if( query("gender", me) != "女性" )
                return "你一個大老爺們，來炒什麼菜啊？";

        if( query("combat_exp", me)<100 )
                return "呦，你這點本事啊，端得動盤子麼？";

        if( query("jing", me)<100 )
                return "你還是休息會兒吧，小心把身子累垮了！";

        if( query("combat_exp", me)>180000 )
                return "這位女俠，你這不是折殺小的嗎！你還是去前面用餐吧！飯菜馬上就好！";

        if (me->query_skill("cooking") < 30)
                return "你的炒菜手藝那麼差，那裏能幫我？";

        if (me->query_skill_mapped("cooking") != "chuancai-jiyi")
                return "我説你知不知道來的客人可都是吃川菜的，亮出你川菜的活兒再説！";

        if (random(30) == 0)
        {
        uob = filter_array(users(), (: query_ip_name($1) == $(query_ip_name(me)) :));
        uob=filter_array(uob,(:objectp($1) && query_temp("job/cook", $1):));

        if (sizeof(uob) > 5)
        {
                me->start_busy(180);
                return "對不起，您這個IP做炒菜工作的ID太多了！";
        }
        }

        set_temp("job/cook", 1, me);
        return "好吧,你就幫我炒菜(cooking)吧！菜在這兒，灶台在那邊。";
}

int recognize_apprentice(object ob, string skill)
{
        if( query_temp("mark/廚娘", ob)<1 )
                return 0;

        if (skill != "cooking" && skill != "chuancai-jiyi")
        {
                command("say 你打住...我可只會做菜燒飯。");
                return -1;
        }

        addn_temp("mark/廚娘", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object me = this_player();

        if( query_temp("mark/廚娘", who)<1 )
                set_temp("mark/廚娘", 0, who);

        if( query("money_id", ob) && ob->value() >= 2000 )
        {
                message_vision("廚娘同意指點$N一些關於炒菜的常識和技巧。\n", who);
                addn_temp("mark/廚娘", ob->value()/50, who);
                destruct(ob);
                return 1;
        }

        command("say 雖説炒菜對闖蕩江湖沒什麼用，我也不能白白教你"
                "啊！拿來，辛苦費紋銀二十兩，童叟無欺！");
        return 0;
}

int do_cook(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("你正忙着呢，彆着急。\n");

        if( !query_temp("job/cook", me) )
        {
                tell_object(me, "廚娘喝道：你要幹什麼？不要來搗亂，我忙着呢！\n");
                return 1;
        }

        set_temp("job/step", 1, me);
        me->start_busy((: cooking :), (: halt_cooking :));
        tell_object(me, "你拿起蔬菜，走到一邊坐下，開始揀菜。\n");
        return 1;
}

int cooking(object me)
{
        string msg;
        int finish;
        int gain_exp, gain_pot, gain_money;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/cook", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        me->receive_damage("jing", 10);
        switch(query_temp("job/step", me) )
        {
        case 1:
                msg = "$N看看菜差不多夠了，站起身來走到水盆邊開始洗菜。";
                break;
        case 2:
                msg = "譁----，$N將水盆中的污水倒掉，菜也洗乾淨了。";
                break;
        case 3:
                msg = "$N走到灶台前開始切菜，嚓----嚓-----。";
                break;
        case 4:
        case 6:
                msg = "$N將油到入鍋中，繼續切菜。";
                break;
        case 5:
                msg = "油熱了，冒出陣陣清煙，$N將切好的菜到入鍋中！滋------";
                break;
        case 7:
                msg = "$N不斷翻動鍋中的菜，慢慢的，一陣香味散發出來。";
                break;
        default:
                msg = "$N在鍋中加入調料，又翻動了幾下，將炒好的菜鏟到盤中，拿給$n。";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                object ob;
                msg += "$n看了$N炒的菜，又夾了兩片嚐了嚐，滿意的點點頭"
                       "這是給你的報酬！你可以在我這裏學點炒菜技術。\n";
                delete_temp("job/cook", me);
                delete_temp("job/step", me);
                gain_money = 60 + random(60);
                addn_temp("mark/廚娘", random(30), me);
                me->improve_skill("cooking", 10 + random(10));

                // 獎勵的經驗為10加20的隨機數（較多）， money為100加炒菜技
                // 術的等級取隨機數（較多），潛能為不超過3點，主要還是以加
                // silver為主。

                /*
                if( query("potential", me)>me->query_potential_limit() )
                        set("potential", me->query_potential_limit(), me);
                */
                ob = new("/clone/money/coin");
                ob->set_amount(gain_money);
                ob->move(this_object());

        }

        msg = replace_string(msg, "$N", "你");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);

        if (finish)
        {
                if( query("combat_exp", me) >= 50000 )
                {
                        write(MAG "你隱隱約約的發現炒菜居然和武功有一些相通之處，真是奇妙。\n" NOR);
                        gain_exp = 5 + random(15);
                        gain_pot = gain_exp / 3;
                        /*
                        if( query("potential", me) >= me->query_potential_limit() )
                                gain_pot = 0;
                        */
                        addn("combat_exp", gain_exp, me);
                        addn("potential", gain_pot, me);
                        msg = HIC "你獲得了" + chinese_number(gain_exp) +
                              "點經驗";
                        if (gain_pot)
                                msg += "和" + chinese_number(gain_pot) +
                                       "點潛能。\n" NOR;
                        else
                                msg += "。\n" NOR;
                        tell_object(me,  msg);
                }
                command("givecointo"+query("id", me));
                command("drop coin");
                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_cooking(object me)
{
        message_vision("$N揉揉腰部，又扭了扭，歎到："
                       "這也太難了，我還是去闖蕩江湖吧！\n", me);
        delete_temp("job/cook", me);
        delete_temp("job/step", me);
        return 1;
}
