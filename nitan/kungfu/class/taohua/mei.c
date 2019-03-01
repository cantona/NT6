// This program is a part of NT MudLIB
// mei.c 梅超風

#include <ansi.h>;
inherit NPC;

#define YINJIAO    "/clone/lonely/yinjiaobian"

mixed ask_skill();
mixed ask_skill1();

void create()
{
        object ob;
        set_name("梅超風", ({ "mei chaofeng", "mei", "chaofeng" }));
        set("title", "黑風雙煞");
        set("nickname", WHT "鐵屍" NOR);
        set("gender", "女性");
        set("age", 32);
        set("long", "梅超風是黃藥師唯一的女弟子，本來極受黃藥師疼愛，可\n"
                    "惜她與師兄陳玄風暗生情愫，他們偷了「九陰真經」私奔。\n"
                    "她面色大概因為久居海島顯得黝黑，模樣卻頗為俏麗。她\n"
                    "在桃花弟子中尤精通鞭法。\n");
        set("attitude", "aggressive");
        set("str", 29);
        set("int", 32);
        set("con", 35);
        set("dex", 31);
        set("max_qi", 4500);
        set("max_jing",3000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 200);
        set("level", 20);
        set("combat_exp", 1800000);

        set_skill("claw", 200);
        set_skill("strike", 200);
        set_skill("force", 200);
        set_skill("parry", 220);
        set_skill("dodge", 220);
        set_skill("cuixin-zhang", 200);
          set_skill("jiuyin-baiguzhao", 200);
        set_skill("luoying-shenfa", 200);
        set_skill("whip", 220);
        set_skill("canglang-bian", 220);
        set_skill("martial-cognize", 200);

        map_skill("force", "luoying-xinfa");
        map_skill("whip", "canglang-bian");
        map_skill("parry", "yinlong-bian");
        map_skill("dodge", "luoying-shenfa");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("strike", "cuixin-zhang");

        prepare_skill("claw", "jiuyin-zhao");
        prepare_skill("strike", "cuixin-zhang");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.duo" :),
                (: perform_action, "claw.sha" :),
                (: perform_action, "strike.cui" :),
                (: perform_action, "whip.julang" :),
                (: exert_function, "recover" :),
        }));

        create_family("桃花島", 2, "被逐弟子");
        set("inquiry", ([
                "銅屍" : "江湖上的人都這麼叫我的，你怕不怕？哈哈哈哈。",
                "東邪" : "那是我師父的綽號。",
                "西毒" : "那是與家師齊名的高手之一，是個老毒物，住在白駝山。",
                "南帝" : "段王爺已出家當和尚去了，法名叫一燈。",
                "北丐" : "北丐統領中原的丐幫，勢力頗為強大。",
                "黃蓉" : "她是我師父的獨女，最是刁蠻任性。",
                "洪七公" : "洪七公武功高強，而且教會郭靖那小兒降龍十八掌，可恨！",
                "梅超風" : "不就是我麼？你是白痴啊？",
                "陳玄風" : "他是我的師哥，也是我的夫君，可惜被郭靖那小兒暗算了。",
                "黃藥師" : "他是我師父。",
                "九陰真經" : "那是我師父的秘籍！你可別打注意！",
                 "九陰神爪" : (: ask_skill :),
                 "奪命連環爪" : (: ask_skill1 :),
        ]));
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();
/*
        if (clonep())
        {
                ob = find_object(YINJIAO);
                if (! ob) ob = load_object(YINJIAO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/changbian");
                        ob->move(this_object());
                        ob->wield();
                }
        }
*/
        carry_object("/clone/cloth/bupao")->wear();
        carry_object("/clone/unique/dulong-bian")->wear();
        set("startroom", "/d/yongdeng/shidong");
}

void attempt_apprentice(object ob)
{
        command("滾開！");
}

int accept_fight(object me)
{
        command("say 給我滾開！");
        return 0;
}

int accept_hit(object me)
{
        command("say 找死！");
        kill_ob(me);
        return 1;
}

void kill_ob (object ob)
{
        object me = this_object();
        object where = environment(me);
        object guard = present("chen xuanfeng", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);

        if (guard && ! guard->is_fighting())
        {
                message_vision(HIW "\n$N" HIW "大怒道：居然欺負到我們黑風雙煞"
                               "頭上來了，死吧！\n\n" NOR, guard);
                guard->kill_ob(ob);
        }
}

mixed ask_skill1()
{
        object me = this_player();

        if( query("can_perform/jiuyin-baiguzhao/duo", me) )
                return "你不是已經會了嗎？";

        if (me->query_skill("jiuyin-baiguzhao", 1) < 150)
        {
               command("shake");
               return "你九陰白骨爪火候不夠，我還不能傳你這招！";
        }

        if (me->query_skill("claw", 1) < 150)
               return "你基本爪法不夠嫻熟，我不能傳你這招！";

        if (me->query_skill("force", 1) < 150)
               return "你內功修為不夠，我不能傳你這招！";

        if (me->query_skill("martial-cognize", 1) < 200)
               return "你武學修養不夠，我不能傳你絕招！";

        if( query("max_neili", me)<2000 )
               return "你內力修為不足，我還不能傳你絕招！";

        command("heihei");
        command("say 看清楚了！");
        message_sort(HIR "梅超風桀桀怪笑，手指微微彎曲，倏的沖$N" HIR "頭頂抓下，$N" HIR
                     "急忙閃頭，然而梅超風這招來得好快，正插中$N" HIR "肩頭！\n" NOR, me);
        command("haha");

        command("say 可有看清楚？");
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 500000);
        if (me->can_improve_skill("jiuyin-baiguzhao"))
                me->improve_skill("jiuyin-baiguzhao", 500000);
        if (me->can_improve_skill("martial-cognize"))
                me->improve_skill("martial-cognize", 500000);
        set("can_perform/jiuyin-baiguzhao/duo", 1, me);
        tell_object(me, HIG "你學會了「奪命連環爪」！\n" NOR);

        return 1;
}

mixed ask_skill()
{
        object me = this_player();

        if( query("can_perform/jiuyin-baiguzhao/zhua", me) )
                return "你不是已經會了嗎？";

        if( !query("can_learn/jiuyin-baiguzhao/zhua", me) )
        {
               tell_object(me, HIG "你去將「九陰真經下冊」找來給我，我便傳你這招！\n" NOR);
               command("heihei");
               return 1;
        }

        if (me->query_skill("jiuyin-baiguzhao", 1) < 240)
        {
               command("shake");
               return "你九陰白骨爪火候不夠，我還不能傳你這招！";
        }

        if (me->query_skill("claw", 1) < 240)
               return "你基本爪法不夠嫻熟，我不能傳你這招！";

        if (me->query_skill("force", 1) < 260)
               return "你內功修為不夠，我不能傳你這招！";

        if (me->query_skill("martial-cognize", 1) < 240)
               return "你武學修養不夠，我不能傳你絕招！";

        if( query("max_neili", me)<5500 )
               return "你內力修為不足，我還不能傳你絕招！";

        command("heihei");
        command("say 小心~~！");
        message_sort(HIM "梅超風左手成爪，尖嘯一聲，猛然間抓向$N" HIM "的肩膀，$N" HIM
                     "微微一笑，隨手招架，只見梅超風左手忽然收回，右手卻猛地抓出，速度之"
                     "快，方位之準，直襲$N" HIM "檀中大穴。$N" HIM "只覺得一股陰風襲過，"
                     "早已無力招架，梅超風卻突然收招，右手卻停留在你檀中穴上，只需要稍稍"
                     "一用力，$N" HIM "便會登時斃命！\n" NOR, me);
        command("haha");

        command("say 明白了嗎？");
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 1500000);
        if (me->can_improve_skill("jiuyin-baiguzhao"))
                me->improve_skill("jiuyin-baiguzhao", 1500000);
        if (me->can_improve_skill("martial-cognize"))
                me->improve_skill("martial-cognize", 1500000);

        set("can_perform/jiuyin-baiguzhao/zhua", 1, me);
        tell_object(me, HIG "你學會了「九陰神爪」！\n" NOR);

        return 1;
}

int accept_object(object me, object ob)
{
        if (base_name(ob) != "/clone/book/jiuyin2")

        {
               command("say 你給我這種東西幹什麼？");
               return 0;
        }

        command("heihei");
        command("say 好吧，既然這樣，我就傳你絕招，你可以隨時來問我！");
        tell_object(me, HIG "梅超風決定傳你「九陰神抓」！\n" NOR);
        destruct(ob);
        set("can_learn/jiuyin-baiguzhao/zhua", 1, me);

        return 1;
}

void die()
{
        object obj, me;
        int i, flag;

        flag = 0;

        me = this_object();
        if (objectp(obj = query_last_damage_from()))
                set_temp("kill_chaofeng", 1, obj);
        else
                return;

        if( query_temp("kill_xuanfeng", obj) )
        {
                set("kill_th_traitor", 1, obj);
                flag = 1;
        }

        if (flag)
                message_vision(HIR "梅超風慘叫一聲，道：賊漢子，我陪你來了！！！\n" NOR, this_object());
        else
                message_vision(HIR "梅超風慘叫一聲，道：賊漢子，給我報仇！！！\n" NOR, this_object());

        ::die();
}
