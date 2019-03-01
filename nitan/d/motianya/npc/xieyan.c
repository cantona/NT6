// xieyan.c

#include <ansi.h>

inherit NPC;

mixed ask_me(); 
void greeting(object ob);

void create()
{
        seteuid(getuid());
        set_name("謝煙客", ({ "xie yanke", "xie" }));
        set("long", @LONG
摩天居士謝煙客乃天下第一奇人，武功高強，曾經散出
玄鐵令三枚，誓言可以滿足擁有此令的三人任何願望。
LONG );
        set("nickname", HIG "摩天居士" NOR);
        set("gender", "男性");
        set("age", 71);
        set("shen_type", 1);
        set("attitude", "friendly");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("qi", 5000);
        set("max_qi", 5000);
        set("jing", 2500);
        set("max_jing", 2500);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 150);

        set("combat_exp", 2500000);

        set_skill("force", 260);
        set_skill("unarmed", 250);
        set_skill("dodge", 250);
        set_skill("parry", 250);
        set_skill("strike", 260);
        set_skill("yijinjing", 260);
        set_skill("shexing-lifan", 250);
        set_skill("bizhen-qingzhang", 260);

        map_skill("force", "yijinjing");
        map_skill("dodge", "shexing-lifan");
        map_skill("strike", "bizhen-qingzhang");
        map_skill("parry", "bizhen-qingzhang");

        prepare_skill("strike", "bizhen-qingzhang");

        set("inquiry", ([
                "碧針清掌" : (: ask_me :),
                "絕招"     : (: ask_me :),
                "澎湃"     : (: ask_me :),
                "絕技"     : (: ask_me :),
                "玄鐵令"   : "兩枚玄鐵令我已經收回。",
                "石破天"   : "狗雜種那個白痴還沒死麼？",
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

int accept_object(object me, object ob)
{
        if( query("id", ob) != "xuantie ling" )
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        } else
        {
                command("say 很好，很好！");
                command("say 我這裡有一套碧針清掌，是我晚年創下的絕學，可以傳授予你。");
                set("can_learn/xieyanke/bizhen-qingzhang", 1, me);
                destruct(ob);
                return -1;
        }
}

int recognize_apprentice(object ob, string skill)
{
        if( !query("can_learn/xieyanke/bizhen-qingzhang", ob) )
        {
                command("say 你是什麼東西？給我滾開！\n");
                return -1; 

        }

        if (skill != "bizhen-qingzhang")
        {
                command("killair");
                command("say 我說過只傳授你這套掌法，你不學就算了。");
                return -1;
        }

        if (ob->query_skill("bizhen-qingzhang", 1) > 100)
        {
                command("say 夠了，剩下的自己去練。");
                return -1;
        }
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/bizhen-qingzhang/pengpai", me) )
                return "能教的已經教完了，還來找我幹嘛？";

        if( !query("can_learn/xieyanke/bizhen-qingzhang", me) )
                return "給我滾開，少在我面前羅嗦！";

        if (me->query_skill("bizhen-qingzhang", 1) < 180)
                return "你的碧針清掌練這個程度就來問絕招？";

        message_vision(HIW "$n" HIW "冷笑一聲，雙掌陡然揮舞"
                       "出一個大圈，橫推而出，頓時一股洶湧澎"
                       "湃的勁氣如波浪一般向" HIW "湧來。\n$N"
                       HIW "大駭，硬接了這一招，只感內息翻騰"
                       "，全身骨骼快要散架一般。突然目光一亮"
                       "，似乎明白了什麼。\n" NOR,
                       me, this_object());

        command("grin");
        command("say 我能教的已經教完了，以後大家各走各的路。");

        tell_object(me, HIC "你學會了碧針清掌「澎湃」這一招。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 300000);
        set("can_perform/bizhen-qingzhang/pengpai", 1, me);
        return 1;
}
