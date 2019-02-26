#include <ansi.h>
#include "honghua.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("常赫志", ({ "chang hezhi", "chang", "hezhi" }));
        set("title", "紅花會五當家");
        set("nickname", HIB "黑無常" NOR);
        set("long", "他身材又高又瘦，臉色蠟黃，眼睛凹進，眼\n"
                    "角上有一粒黑痣，眉毛斜斜的倒垂下來，形\n"
                    "相甚是可怖。他是青城派慧侶道人的徒弟。\n"
                    "黑沙掌的功夫，江湖上無人能敵。黑白無常\n"
                    "兩兄弟是川江上著名的俠盜，一向劫富濟貧，\n"
                    "不過心狠手辣，因此得了這難聽的外號。\n");
        set("gender", "男性");
        set("age", 32);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 3000);
        set("max_qi", 3000);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jiali", 120);
        set("combat_exp", 1000000);
        set("score", 10000);

        set_skill("force", 140);
        set_skill("honghua-xinfa", 140);
        set_skill("qingcheng-neigong", 140);
        set_skill("strike", 160);
        set_skill("heisha-zhang", 160);
        set_skill("dodge", 160);
        set_skill("yanzi-chuanyun", 160);
        set_skill("sword", 140);
        set_skill("songfeng-jian", 140);
        set_skill("parry", 160);
        set_skill("martial-cognize", 120);
        set_skill("literate", 140);

        map_skill("force"  , "qingcheng-neigong");
        map_skill("sword"  , "songfeng-jian");
        map_skill("strike" , "heisha-zhang");
        map_skill("dodge"  , "yanzi-chuanyun");
        map_skill("parry"  , "heisha-zhang");

        prepare_skill("strike", "heisha-zhang");

        set("no_teach", ([
                "qingcheng-neigong" : "這內功沒得啥子用，你給老子好生練掌法就行了。",
        ]));

        create_family("紅花會", 4, "當家");

        set("inquiry", ([
                "催魂掌" : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "strike.cui" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        setup();

        carry_object("/d/wudang/obj/greyrobe")->wear();
    
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("shen", me)<5000 )
        {
                command("say 你非我俠義中人，我不能收你。");
                return;
        }

        if ((int)me->query_skill("honghua-xinfa", 1) < 50)
        {
                command("say 你把本門的心法練好了再來。");
                return;
        }

        command("heihei");
        command("say 以後你就跟着老子吧。");
        command("recruit "+query("id", me));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/heisha-zhang/cui", me) )
                return "老子把啥子都給你説完了，你龜兒咋那麼煩哦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你龜兒子是哪兒來的？老子認不到你。";

        if (me->query_skill("heisha-zhang", 1) < 1)
                return "你龜兒黑砂掌都沒學，還説啥子催魂掌哦！";

          if( query("family/gongji", me)<150 )
                return "你龜兒貢獻都做得不夠，喊我咋個傳你嘛？";

        if( query("shen", me)<5000 )
                return "你連行俠仗義都搞忘了，我還敢傳你啥子嘛？";

        if (me->query_skill("force") < 150)
                return "你龜兒內功都沒學好，學啥子這招哦！";

        if (me->query_skill("heisha-zhang", 1) < 100)
                return "你黑砂掌學成這副龜兒子德性，咋個練催魂掌嘛？";

        message_vision(HIY "$n" HIY "看了看$N" HIY "，哈哈一笑，説道"
                       "：“要得，要得！看你娃學得還\n可以，今天我就"
                       "教你催魂掌。”$n" HIY "説罷，便輕輕拍出一掌，"
                       "看\n似不着半點力道。正當$N" HIY "納悶間，聽得"
                       "“噗”的一聲，隨即塵沙滾\n滾，飄然四起，身前"
                       "沙地豁然留下一個烏黑的掌印，煞是驚人。\n" NOR,
                       me, this_object());

        command("heihei");
        command("say 剛才老子説的你都要記好了好，自己下去練。");
        tell_object(me, HIC "你學會了「催魂掌」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("heisha-zhang"))
                me->improve_skill("heisha-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/heisha-zhang/cui", 1, me);
          addn("family/gongji", -150, me);

        return 1;
}
