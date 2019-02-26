// This program is a part of NT MudLIB

#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

string ask_me();

void create()
{
        set_name("苟讀", ({ "gou du", "gou", "du" }));
        set("long", "他看上去也是幾十歲的人了，卻是純然一個\n"
                    "書呆子的模樣。\n");
        set("title", "逍遙派函谷八友");
        set("nickname", WHT "書呆" NOR);
        set("gender", "男性");
        set("age", 50);
        set("attitude", "friendly");
        set("class", "scholar");
        set("shen_type", 1);
        set("str", 25);
        set("int", 35);
        set("con", 25);
        set("dex", 25);

        set("inquiry", ([
                "論語" : (:ask_me:),
        ]) );

        set("max_qi", 1800);
        set("max_jing", 1800);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 60);
        set("level", 10);
        set("combat_exp", 300000);

        set_skill("force", 120);
        set_skill("xiaowuxiang", 120);
        set_skill("dodge", 100);
        set_skill("feiyan-zoubi", 100);
        set_skill("strike", 100);
        set_skill("liuyang-zhang", 100);
        set_skill("hand", 100);
        set_skill("qingyun-shou", 100);
        set_skill("parry", 100);
        set_skill("blade", 80);
        set_skill("ruyi-dao", 80);
        set_skill("literate", 220);
        set_skill("martial-cognize", 80);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("hand", "qingyun-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "liuyang-zhang");
        map_skill("blade", "ruyi-dao");

        prepare_skill("hand", "qingyun-shou");
        prepare_skill("strike", "liuyang-zhang");

        set("coagents", ({
                ([ "startroom" : "/d/xiaoyao/muwu1",
                   "id"        : "kang guangling" ]),
                ([ "startroom" : "/d/xiaoyao/muwu2",
                   "id"        : "xue muhua" ]),
        }));

        create_family("逍遙派", 3, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhuo" :),
                (: perform_action, "strike.pan" :),
                (: exert_function, "recover" :),
        }));

        set("book_count", 1);

        set("master_ob", 3);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 26)
        {
                command("say 這個…你的頭腦太不開竅…怎麼能夠逍遙？");
                return;
        }

        command("say 甚好，甚好！");
        command("say 有徒至遠方來，不矣樂呼。");
        command("recruit "+query("id", ob));
}

string ask_me()
{
        object me, ob, book;

        ob = this_player();
        me = this_object();

        if( query("family/family_name", ob) != "逍遙派" )
                return "幹嘛你要？";

        if( query("family/master_id", ob) == "wuyazi" || 
           query("family/master_id", ob) == "suxinghe" )
        {
                call_other("/clone/book/lbook4", "???");
                book = find_object("/clone/book/lbook4");
                if (! objectp(book) || environment(book))
                        return "你來晚了，那本《論語》我已經贈送給別入了。";

                command("say 想要這本論語麼？你只管拿去就是。");
                message_vision(HIY "$N" HIY "從懷裏掏出一本舊書，交了給$n"
                               HIY "。\n" NOR, me, ob);
                book->move(ob, 1);
                return "這本書可千萬不要借給別人啊，他們一借就不還的了。\n";
        }

        if (query("book_count") < 1)
                return "我現在手頭沒有什麼書了。";

        addn("book_count", -1);
        command("say 哈哈，論語就沒有了，這裏有我派高手從少林盜來的書。");
        command("say 既然你那麼好學，我就把它送給你吧。");
        message_vision(HIY "$N" HIY "翻箱倒櫃找了半天，找出一本舊書，交了給$n"
                       HIY "。\n" NOR, me, ob);
        if (random(2) == 1)
                book = new("/clone/book/strike_book");
        else
                book = new("/clone/book/book-paper");
        book->move(ob, 1);

        return "這本書可千萬不要借給別人啊，他們一借就不還的了。\n";
}
