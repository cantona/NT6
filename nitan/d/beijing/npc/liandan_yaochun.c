#include <ansi.h>
inherit NPC;

int do_liandan();
string ask_me();
string ask_yinzhen();

void create()
{
        set_name("姚春", ({"yao chun", "yao", "chun"}));
        set("gender", "男性");
        set("age", 56);
        set("title", HIG "回春堂" NOR);
        set("nickname",HIR "跌打名醫" NOR);
        set("long",
                "這便是京城回春堂藥舖的跌打名醫姚春，身材幹\n"
                "瘦，其貌不揚。當年天地會徐天川受了傷，便由\n"
                "他醫治，此人既是名醫，擒拿短打也是一絕。\n");
        set("attitude", "heroism");
        set("shen_type",1);
        set("str", 32);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 20000);
        set("max_qi", 20000);
        set("jing", 1600);
        set("max_jing", 1600);
        set("neili", 20000);
        set("max_neili", 20000);

        set("combat_exp", 10000000);
        set("score", 300000);

        set_skill("medical", 150);
        set_skill("zhenjiu-shu", 150);
        set_skill("liandan-shu", 150);
        set_skill("literate", 150);

        map_skill("medical", "bencao-shuli");

        set("inquiry", ([
                "徐天川"  :  "那老猴兒便是我給醫治的，怎麼你也知道。\n",
                "煉丹"    : (:do_liandan:),
                "liandan" : (:do_liandan:),
                "quest"   :  "在我這裡可以幫著我「" HIR "煉丹" NOR + CYN
                             "」，如果願意可以想我詢問。\n",
                "job"     :  "在我這裡可以幫著我「" HIR "煉丹" NOR + CYN
                             "」，如果願意可以想我詢問。\n",
                "藥材"    :  "去找我的小童，他會幫你處理。\n",
                "原料"    :  "去找我的小童，他會幫你處理。\n",
                "yaocai"  :  "去找我的小童，他會幫你處理。\n",
                "藥"      :  "去找我的小童，他會幫你處理。\n",
                "醫術"    : (: ask_me :),
                "學醫術"  : (: ask_me :),
                "學習醫術": (: ask_me :),
                "煉丹術"  : (: ask_me :),
                "針灸術"  : (: ask_me :),
                "本草術理": (: ask_me :),
                "基本醫術": (: ask_me :),
                "學習"    : (: ask_me :),
                "學技"    : (: ask_me :),
                "銀針"    : (: ask_yinzhen :),
                "針"      : (: ask_yinzhen :),
                "針灸"    : (: ask_yinzhen :),
        ]) );

        setup();

}

void init()
{
        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, this_player());
}

int do_liandan()
{
        int exp, pot;
        object ob;
        object me = this_player();

        if( query_temp("liandan", me) )
        {
                if( query_temp("liandan", me)<4 )
                {
                        command("say 不是要去煉丹嗎，怎麼還在這呆著？\n");
                        return 1;
                }
                message_vision(CYN "姚春對$N" CYN "微笑道：煉丹是個修身養性的"
                               "過程，你能成功，很不錯！\n" NOR, me);

                exp = 100 + random(140);
                pot = exp / 3;

                GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : pot ]));

                delete_temp("liandan", me);
                addn("over_quest/liandan_quest", 1, me);
                if (! query("zhufu_mod/waist", me) && random(10) == 1) 
                {
                        message_vision("$n對$N嘿嘿一笑，道：幹得不賴，有點" 
                                       "意思，這個神之祝福束帶就算是我送給你的禮物吧。\n",
                                       me, this_object());
                        ob = new("/clone/goods/zhufu_waist"); 
                        ob->move(me, 1); 
                        tell_object(me, HIM "\n你獲得了一個" + ob->name() + HIM "！\n" NOR);
                        set("zhufu_mod/waist", 1, me); 
                }
                return 1;
        } else
        {
                message_vision(CYN "姚春對$N" CYN "點了點頭，說道：煉丹是考驗"
                               "人的定力修為，心不靜則事不成，你去向童子詢問「"
                               HIG "藥材" NOR + CYN "」吧。\n", me);
                set_temp("liandan", 1, me);
                return 1;
        }
}

string ask_me() 
{
        object me;

        me = this_player();

        if( query("can_learn_medical/yaochun", me) == 1 )
                return "我不是答應教你了嗎，你這人怎麼那麼羅嗦？";

        if( query("shen", me)<-10000 )
                return "你這種魔頭，不去殺人都算是武林大幸了。";

        if( query("over_quest/liandan_quest", me)<100 )
                return "這樣吧，你先幫我煉丹百次，心誠之時我自然會傳授給你。";

        if( query("shen", me)<0 )
                return "你俠義正事做得不夠，多多行善之後我自然會傳授給你。";

        set("can_learn_medical/yaochun", 1, me);
               return "既然你欲誠心鑽研學醫之道，我就成全成全你吧。"; 
}

int recognize_apprentice(object me, string skill)
{
        if( query("shen", me)<-10000 )
        {
                command("say 給我滾開！我不會傳授任何技能給你這種魔頭！");
                return -1;
        }

        if( !query("can_learn_medical/yaochun", me) )
        {
                command("say 我的醫術向來是不輕易傳授的。");
                return -1;
        }

        if (skill == "literate")
        {
                command("say 讀書寫字自己去找教書先生學去。");
                return -1;
        }

        if (skill != "medical" &&
            skill != "zhenjiu-shu")
        {
                command("say 我只能傳授基本醫術和針灸術。");
                return -1;
        }

        return 1;
}

string ask_yinzhen()
{
        mapping fam; 
        object ob;
        object me = this_player();

        if( query("shen", me)<-0 )
                return "你走吧，我的神針可不會給你這樣的人。";

        if ((int)me->query_skill("zhenjiu-shu", 1) < 60)
                return "你針灸術還不嫻熟，隨便用針會弄出人命來的。";

        if (present("yin zhen", this_player()))
                return "你身上不是還有一根嗎？";

        ob = new("/d/beijing/obj/yinzhen");
        ob->move(me);

        message_vision(HIW "\n姚春從針盒裡輕輕拈出一根銀針，遞給了$N" HIW "。\n" NOR, me);
                return "這針可是用來救命的，好好的利用它為人治病吧。";
}
