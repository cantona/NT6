// This program is a part of NT MudLIB

#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_me();

void create()
{
        set_name("康廣陵", ({ "kang guangling", "kang", "guangling" }));
        set("long", "只見他高額凸顙，容貌奇古，笑眯眯的臉\n"
                    "色極為和謨，手中抱著一具瑤琴。\n");
        set("gender", "男性");
        set("title", "逍遙派函谷八友");
        set("nickname", YEL "琴顛" NOR);
        set("age", 58);
        set("attitude", "friendly");
        set("class", "scholar");
        set("shen_type", 1);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 38);

        set("max_qi", 3500);
        set("max_jing", 3000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 120);
        set("level", 10);
        set("combat_exp", 1500000);
        set("book_count", 1);

        set_skill("force", 180);
        set_skill("xiaowuxiang", 180);
        set_skill("dodge", 160);
        set_skill("feiyan-zoubi", 160);
        set_skill("strike", 160);
        set_skill("liuyang-zhang", 160);
        set_skill("hand", 160);
        set_skill("qingyun-shou", 160);
        set_skill("parry", 160);
        set_skill("blade", 180);
        set_skill("ruyi-dao", 180);
        set_skill("literate", 140);
        set_skill("tanqin-jifa", 220);
        set_skill("qiuyue-lai", 220);
        set_skill("martial-cognize", 160);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("hand", "qingyun-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "ruyi-dao");
        map_skill("blade", "ruyi-dao");
        map_skill("tanqin-jifa", "qiuyue-lai");

        prepare_skill("hand", "qingyun-shou");
        prepare_skill("strike", "liuyang-zhang");

        create_family("逍遙派", 3, "弟子");

        //set("inquiry", ([
        //        "棋譜" : (: ask_me :),
        //]) );
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhuo" :),
                (: perform_action, "strike.pan" :),
                (: perform_action, "blade.ruyi" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/blade")->wield();
        set_temp("handing", carry_object("/d/changan/npc/obj/muqin"));
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 28)
        {
                command("hmm");
                command("say 你的悟性太差，怎麼學我的琴技？");
                return;
        }

        if (ob->query_skill("xiaowuxiang", 1) < 30)
        {
                command("sigh");
                command("say 你連本門的入門心法都沒有學好，教我如何收你？");
                return;
        }

        command("say 好吧，我收你為徒，多學些東西，別整天就想著練武。");
        command("recruit "+query("id", ob));
}

mixed ask_me()
{
        object me, ob;

        ob = this_player();
        if (query("book_count") < 1)
                return "你來晚了，棋譜我已經贈送給別入了。";

        addn("book_count", -1);
        command("say 好吧，那我就把它送給你了。\n");
        message_vision(HIY "康廣陵微笑著從懷中拿出了一本書，交了給$N\n\n" NOR, ob);
        me = new("/clone/book/hand_book");
        me->move(ob);
        return "這本棋譜可千萬不要隨便給別人。\n";
}