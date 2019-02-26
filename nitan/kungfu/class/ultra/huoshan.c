// huoshan 霍山

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

mixed ask_opinion();

#define ULTRA_OPINION   "宗師"
#define OPINION_TYPE    HIY "內家功夫" NOR
#define MY_OPINION      "force"

string  *my_opinions = ({ "force" });

// 該頭文件必須在這裏嵌入
#include <ultra.h>

void create()
{
        set_name("霍山", ({ "huo shan", "huo", "shan" }) );
        set("title", HIW "大宗師" NOR);
        set("gender", "男性");
        set("age", 91);
        set("long", "他身着奇裝異服，相貌平平，便似一般的西域人士。\n");
        set("attitude", "peaceful");
        set("class", "fighter");
        set("str", 30);
        set("int", 37);
        set("con", 39);
        set("dex", 33);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 100);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "乾坤大挪移" : "嘿，這東西乃是我中年時所創，算不得什麼。",
                "評價"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "武學修養" : "好好提高自己的武學修養(martial-cognize)，到時候什麼武功都如小兒科！",
        ]));

        set_skill("unarmed", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("sword", 500);
        set_skill("jiuyang-shengong", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 220);

        map_skill("parry", "qiankun-danuoyi");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "qiankun-danuoyi");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("sword", "jiuyang-shengong");

        prepare_skill("unarmed", "jiuyang-shengong");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "本座");

        setup();
        carry_object("/clone/cloth/cloth")->wear();

        set("startroom", "/d/mingjiao/xuantianshi");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        delete_temp("want_opinion", me);
        if (ultrap(me))
                message_vision(CYN "$N" CYN "眉頭一皺，哼了一聲。\n"
                               NOR, this_object(), me);
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if( query("combat_exp", me)<200000 )
                return "哼！你這點武功也出來丟人現眼？";

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
                return "不必了，你內功方面的修為已經稱得上是宗師了！";

        if (is_fighting(me))
                return "哈哈，廢什麼話，打贏了我，你自己給自己評價吧！";

        if (me->is_fighting())
                return "你等會兒吧！待我趕走他們。";

        if (objectp(ob = query_temp("opinion")))
        {
                if (ob == me)
                {
                        command("say 你着什麼急？不要煩我。");
                        return 1;
                }

                message_vision(CYN "$N" CYN "頗為惱怒的對$n" CYN
                               "道：“沒看我正忙着嗎？”\n" NOR,
                               this_object(), me);
                return 1;
        }

        switch(query_temp("want_opinion/shenni", me) )
        {
        case 0:
                command("say 好吧，咱們過一招，比拚一下內力。");
                break;
        case 1:
                command("say 你準備好沒有？好了就來吧。");
                break;
        case 2:
                message_vision(CYN "$N" CYN "皺眉對$n" CYN
                               "道：“我看你這人是夠羅嗦的。”\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say 快給我閉上你的鳥嘴！");
                return 1;
        }

        addn_temp("want_opinion/shenni", 1, me);
        return 1;
}

int calc_level(object me, string skill)
{
        int lvl;
        string sp;

        lvl = me->query_skill(skill, 1) / 2;
        sp = me->query_skill_mapped(skill);
        if (! sp) return lvl;

        lvl += me->query_skill(sp, 1);
        if( query("max_neili", me)>4000)lvl+=20;
        return lvl;
}

void do_congration(object me)
{
        command("chat 不錯，不錯，真是不錯。");
}

int accept_hit(object me)
{
        command("sneer");
        command("say 好你個" + RANK_D->query_rude(me) + "，你找死找到這來了！");
        kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        object weapon;

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
        {
                message_vision(CYN "$N" CYN "對$n" CYN "道：“很"
                               "好，你也算是宗師高手了，來吧！咱"
                               "們比劃一下！”\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( !query_temp("want_opinion/shenni", me) )
        {
                command("say 你幹什麼要和我動手？");
                return 0;
        }

        command("look"+query("id", me));

        COMBAT_D->do_attack(this_object(), me, 0);

        if( query("qi", me) <= 0 )
        {
                message_vision(CYN "\n$N" CYN "搖搖頭對$n" CYN
                               "道：“你現在的武功還差得遠，連"
                               "我一招都接不住！”\n" NOR,
                               this_object(), me);
                return notify_fail("看來要好好的修煉功夫了。\n");
        }

        message_combatd(HIC "$N" HIC "右掌伸出，正和$n" HIC "手"
                        "掌相對，兩人同時運起內力，不一會兒只見"
                        "二人頭上生起騰騰霧氣。\n忽然$N" HIC "手"
                        "掌一撤、收回功力，沒有一點阻滯，不禁讓"
                        "$n" HIC "大為愕然。\n" NOR, this_object(),
                        me);
        if( query("neili", me)<3000 )
        {
                message_vision(CYN "\n$N" CYN "搖搖頭對$n" CYN
                               "道：“適才你內力不足，我難以衡"
                               "量，待你將內力修煉好了再來吧！"
                               "”\n" NOR, this_object(), me);
                return notify_fail("看來還是回去鍛鍊一下內力吧！\n");
        }
        set("neili", 0, me);


        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        delete_temp("want_opinion", me);
        message_vision(CYN "\n$N" CYN "一擺手道：“好了，待我想"
                       "想。”\n" NOR, this_object(), me);
        return notify_fail("看來不能心急，還得等一會兒。\n");
}

int accept_kill(object me)
{
        if( query("combat_exp", me)<500000 )
        {
                message_vision(CYN "$N" CYN "大怒道：“無名小輩搗"
                               "什麼亂？給我滾！”説罷一掌把$n" CYN
                               "劈倒在地。\n" NOR, this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say 很好！近年還真沒有遇到什麼敢和我較量的高手！");
        return 1;
}

void unconcious()
{
        message("vision", "\n"HIR + name() + "臉色一變，吐了一口鮮"
                "血，身形一閃，消逝不見。\n\n" NOR, environment());
        command("chat 罷！罷！罷！本座去也！");
        destruct(this_object());
}

void die()
{
        message("vision", "\n"HIR + name() + "大叫一聲，狂吐了一口鮮"
                "血，身形一閃，就此不見。\n\n" NOR, environment());
        command("chat 本座去也！");
        destruct(this_object());
}
