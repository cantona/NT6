#include <ansi.h>

inherit NPC;
string ask_tianjidao();

void create()
{
        set_name(HIW "星君眼" NOR, ({ "xingjun yan", "xingjun", "yan"}));
        set("long", HIW "一個長相奇特的老者，看樣子不像是人界中人。\n" NOR);         
        set("title", HIY "天界守護者" NOR);
        set("gender", "男性");
        set("age", 999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);
        set("per", 35);

        set("max_qi", 9999999);
        set("max_jing", 9999999);
        set("max_neili", 999999);
        set("neili", 999999);
        set("jiali", 2500);
        set("combat_exp", 8000000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "blade.bafa" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

        set_skill("dodge", 420);
        set_skill("parry", 420);
        set_skill("hand", 440);
        set_skill("unarmed", 440);
        set_skill("shou-yin", 440);
        set_skill("wudu-shu", 420);
        set_skill("force", 400);
        set_skill("changsheng-jue", 400);
        set_skill("blade", 320);
        set_skill("jingzhong-bafa", 420);
        set_skill("literate", 400);
        set_skill("martial-cognize", 400);

        map_skill("force", "changsheng-jue");
        map_skill("blade", "jingzhong-bafa");
        map_skill("dodge", "wudu-shu");
        map_skill("parry", "jingzhong-bafa");
        map_skill("hand", "shou-yin");
        map_skill("unarmed", "shou-yin");
        set("inquiry", ([
                "天極道" : (: ask_tianjidao :),
                
        ]));
        prepare_skill("hand", "shou-yin");

        setup();

        carry_object(__DIR__"obj/cloth2")->wear();
}

string ask_tianjidao()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if (me->query("int") < 32 ||
            me->query("con") < 32 ||
            me->query("str") < 32 ||
            me->query("dex") < 32)
            return "你的先天屬性還不足以修煉天極道，我看你還是先回去吧。\n";


        if (! me->query("scborn/ok"))
                return "走開，走開，沒看我正忙嗎？\n";
        
        if (me->query_skill("yinyang-shiertian", 1) && ! me->query("thborn/ok"))
                return "閣下武功已經獨步天下，何必如此貪心?\n";

        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此貪心！\n";
                                        
        // 已經完成任務
        if (me->query("lunhui-sword_quest/tianjidao/finish"))
                return "呵呵，不錯不錯，上次那些天蠶絲解了老夫燃眉之急啊。\n";

        // 分配任務
        if (! me->query("lunhui-sword_quest/tianjidao/give_quest"))
        {
                command("shake");
                command("say 不久前，老夫將借來的一件天蠶寶甲給弄丟了，不知如何是好？");
                command("say 如果能搜集到30根天蠶絲，老夫倒是有辦法重新制作一。");
                command("不過……");
                command("tan");
                command("say 那天蠶絲並非凡物，只有天山頂峰的天蠶身才有，看來這次真是闖大禍了！");
                command("look " + me->query("id"));
                command("say 閣下如果能搜集到30根天蠶絲給老夫，老夫這裡倒是有一些厲害的武功可以傳授給你。");
                tell_object(me, this_object()->name() + HIG "讓你幫他搜集30根天蠶絲，趕快去吧！\n" NOR);
                me->set("lunhui-sword_quest/tianjidao/give_quest", 1);
                me->save();
                return "怎麼樣，考慮考慮？";
        }
        
        // 完成任務
        
        if (! objectp(ob_hlp = present("tiancan si", me)))
                return "怎麼樣，30根天蠶絲搜集夠了嗎？\n";
                
        if (base_name(ob_hlp) != "/clone/quarry/item/cansi2")
                return "怎麼樣，30根天蠶絲搜集夠了嗎？\n";
        
        if ("/adm/daemons/stored"->get_ob_amount(me, ob_hlp) >= 30)
        {
                for (i = 1; i <= 30; i++)
                {
                        destruct(ob_hlp);
                        ob_hlp = present("tiancan si", me);
                }
        }
        else
        {
                return "怎麼樣，30根天蠶絲搜集夠了嗎？\n";
        }
        
        command("hehe");
        command("nod");
        command("say 既然你幫我了這個忙，好！老夫也遵守諾言，傳你「天極道」……");
        
        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳邊悄悄說了幾句，然後又拿出一本書，指指點點，"
                     "$n" HIC "不住地點頭，忽而眉頭深鎖，忽而低頭沉思 ……\n良久，$n" HIC "大笑一聲，似乎"
                     "對剛才的疑慮有所頓悟。\n", this_object(), me);
                             
        tell_object(me, HIG "恭喜你領悟了「天極道」劍法，目前等級為10級。\n");
        me->set_skill("tianji-dao", 10);
        me->set("lunhui-sword_quest/tianjidao/finish", 1);
        
        return "多謝了！";
        
                
}
