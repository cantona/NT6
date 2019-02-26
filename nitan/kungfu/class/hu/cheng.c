// cheng.c

#include <ansi.h>;

inherit NPC;

#define SHENPIAN    "/clone/book/yaowang"

mixed ask_shenpian();

void create()
{
        set_name("程靈素", ({ "cheng lingsu", "cheng" }));
        set("gender", "女性");
        set("age", 24);
        set("long", @long
她看上去雙眉緊縮，不知道有什麼心事，長得相貌平平，並不出眾。
身材瘦小，穿着粗布衣衫。
long);
        set("attitude", "peaceful");
        set("str", 22);
        set("int", 35);
        set("con", 31);
        set("dex", 27);
        set("chat_chance", 10);
        set("chat_msg", ({
                "程靈素哀哀的歎了口氣。\n",
        }));

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 1200);
        set("max_jing", 1200);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 40);
        set("combat_exp", 400000);
     
        set_skill("force", 300);
        set_skill("poison", 600);
        set_skill("dispel-poison", 600);
        set_skill("medical", 600);
        set_skill("baicao-jue", 600);
        set_skill("yaowang-miaoshu", 600);

        set("inquiry",([
                "胡斐":     "他...他...\n",
                "袁紫衣":   "我...你提他幹什麼？\n",
                "藥王神篇" : (: ask_shenpian :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

int recognize_apprentice(object me, string skill)
{
        if( query("family/family_name", me) != "關外胡家" )
        {
                command("say 你是誰？來幹什麼？");
                return -1;
        }

        if (skill != "poison" && skill != "dispel-poison" &&
            skill != "medical" && skill != "yaowang-miaoshu")
        {
                command("say 我只會毒功和醫術，別的我就沒法子教你啦！");
                return -1;
        }

        if( query("shen", me)<0 )
        {
                command("sigh");
                command("say 你怎能走上邪路？我可不能教你毒技。");
                return -1;
        }

        if( !query_temp("can_learn/cheng/poison", me) )
        {
                set_temp("can_learn/cheng/poison", 1, me);
                command("say 看在胡斐你面子上，我就叫你一點本事吧，你可要好自為之！");
                return 1;
        }

        return 1;
}

mixed ask_shenpian()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "關外胡家" )
                        message_vision(CYN "$N" CYN "冷哼一聲，對$n" CYN "道："
                                       "“你難道忘記了你師傅是怎麼教你的嗎？現在居"
                                       "然和那三個傢伙一樣走上了邪道，我如何能"
                                       "將《藥王神篇》交予你？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一聲，對$n" CYN "説道"
                                       "：“好一個邪派妖徒，竟敢貪圖本派寶物！"
                                       "”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "關外胡家" )
                return "你不是關外胡家的，打聽它幹什麼？";

        if( query("shen", me)<100000 )
                return "你俠義正事做得還不夠，《藥王神篇》我不能給你。";

        if (me->query_skill("medical", 1) < 100)
                return "你基本醫術尚未學好，給了你你也讀不懂。";

        ob = find_object(SHENPIAN);
        if (! ob) ob = load_object(SHENPIAN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "我這《藥王神篇》現在不就在你手裏嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你來晚了一步，我已經把《藥王神篇》借給你同門師兄弟了。";

                if( query("family/master_id", owner) == query("id") )
                        return "嗯，《藥王神篇》現在在你同門師兄弟"+query("name", owner)+
                               "手裏，你去找他吧。";
                else
                        return "本門的《藥王神篇》現在落入了"+query("name", owner)+
                               "之手，你去把它取回來吧！";
        }

        ob->move(this_object());
        message_vision(HIC "$N" HIC "微微一笑，道：“這本《藥王神篇》現在"
                       "給你，記住，千萬不可用它為非作歹！”\n" NOR,
                       this_object(), me);
        command("give yaowang shenpian to "+query("id", me));
        return 1;
}
