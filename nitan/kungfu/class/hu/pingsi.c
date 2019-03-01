#include <ansi.h>

inherit NPC;
inherit F_GUARDER;

int ask_job();
int ask_fail();
mixed ask_me();

void create()
{
        set_name("平四", ({ "ping si", "ping", "si" }));
        set("gender", "男性");
        set("age", 65);
        set("title", "胡家僕傭");
        set("long", "他是胡家忠心耿耿的僕役。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("int", 20);
        set("con", 24);
        set("dex", 20);

        set("max_qi", 4000);
        set("max_jing", 1000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("combat_exp", 150000);

        set_skill("force", 40);
        set_skill("blade", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("unarmed", 40);

        create_family("關外胡家", 0, "僕傭");

        set("inquiry",([
                "閻基"   : "閻基…哼…這個狗賊。",
                "胡一刀" : "那……那是老主人，唉。",
                "苗人鳳" : "苗大俠可不是壞人。",
                "趙半山" : "他對我家主人的交情那是沒得說的。",
                "出關"   : (: ask_me :),
                "辦事"   : (: ask_me :),
                "出去"   : (: ask_me :),
                "job" : (: ask_job() :),
                "失敗" : (: ask_fail() :),
        ]));
        set("coagents", ({
                ([ "startroom" : "/d/guanwai/xiaowu",
                   "id"        : "hu fei" ]),
        }));

        setup();
        set("startroom", "/d/guanwai/xiaoyuan");
        carry_object("/clone/cloth/cloth")->wear();
}

mixed ask_me()
{
        object ob, me;
        me = this_player();

        if( query("family/family_name", me) != "關外胡家" )
                return "你自己沒長腿麼？";

        if (find_object(query("startroom")) != environment())
                return "我這裡還有事，你就自己走回去吧。";

        command("nod");
        command("say 要出去辦事麼？那我叫幾個朋友送你一程吧。");

        message_sort(HIC "\n平四朝遠方一招手，頓時幾個參客趕著馬車駛了"
                     "過來。平四笑道「我家小主人要出關辦點事，今趟就勞"
                     "駕你們送送。」參客聽後連忙陪笑著答應，$N" HIC "見"
                     "狀急忙鑽進車中，只聽一陣清脆的鞭響，馬車絕塵而去"
                     "。\n\n" NOR, me);

        ob = load_object("/d/beijing/majiu");
        ob = find_object("/d/beijing/majiu");
        me->move("/d/beijing/majiu");

        message("vision", HIC "\n遠處一輛馬車急駛而來，車門一開" +
                          query("name", me)+HIC"從裡面鑽了出"
                          "來。\n\n" NOR, environment(me), ({me}));

        tell_object(me, CYN "\n參客笑道：這位" + RANK_D->query_respect(me) +
                        CYN "已經到了，請下車吧。\n參客說道：我要"
                        "在這裡辦些事情，如果打算" HIC "入關" NOR +
                        CYN "的話，我還可以找人送你。\n\n" NOR);
        return 1;

}

int ask_job()
{

        object me = this_player();
        object ob;
        mapping quest;
        mapping skl;
        string *sname, place;
        int i, skill = 0;
        quest = ("/d/guanwai/npc/lagjob")->query_quest();

        skl = me->query_skills();
        if ( !skl ) {
                tell_object(me, "你去學一些本事先吧！\n");
                return 1;
                }
        sname  = sort_array( keys(skl), (: strcmp :) );
        for(i=0; i<sizeof(skl); i++)
                if (skl[sname[i]] >= skill && sname[i] != "literate" && sname[i] != "taoism")

                        skill = skl[sname[i]];

        if (skill < 80) skill = 80;

        if( query("family/family_name", me) != "關外胡家" )
        {
                message_vision("$N對著$n說道。你是哪裡來的姦細？\n", this_object(), me);
                return 1;
        }

        if( query("combat_exp", me)<100000){
                command("say " + RANK_D->query_respect(me) + "救反清義士的事沒那麼容易，你還是練高經驗再來吧");
                return 1;
        }
        if( query("potential", me)<200){
                command("say 你的潛能太少了!!");
                return 1;
        }

        if (sizeof(children("/d/guanwai/npc/shangdui")) > 10 ||
              !get_object(quest["place"])) {
                command("say 暫時沒有任務給你，請稍後再來!!");
                return 1;
        }
        if( query("kill_yunlong", me) == 1){

                command("kick"+query("id", me));
                command("say 我不是給了你任務了嗎？");
                return 1;
                }
        else {
                command("nod"+query("id", me));
                command("say " + RANK_D->query_respect(me) + "反清復明，就要堅貞志士，你去吧!");
                command("say"+query("id", me)+"有一個反清義士被抓了，要送往京城，要在『"+quest["short"]+"』路過，快去救人吧！\n"NOR);
                set("kill_yunlong", 1, me);
                set("task_time", time()+300, me);
                ob = new("/d/guanwai/npc/shangdui",1);
                ob->move(quest["place"]);
                set_temp("owner/id",query("id",  me), ob);
                set("combat_exp",query("combat_exp",  me), ob);
                set("max_force",query("max_force",  me), ob);

                ob->set_skill("dodge", skill);
                ob->set_skill("force", skill);
                ob->set_skill("parry", skill);

                set("force_factor", random(10), ob);
                return 1;
        }
}

int ask_fail()
{
        object me = this_player();

        if( query("kill_yunlong", me) == 1){
                command("pk1");
                command("say 我看錯你了，我只能派別人去救反清義士。");

                delete("kill_yunlong", me);
                addn("potential", -50, me);
                tell_object(me, "扣除你的潛能50點。\n");
                return 1;
        }
}
