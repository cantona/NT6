#include <ansi.h>;
#include "etc.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed ask_me();
mixed ask_skill();

void create()
{
        set_name("桑土公", ({ "sang tugong", "sang", "tugong"}));
        set("gender", "男性");
        set("title", "川西碧磷洞洞主");
        set("age", 58);
        set("long", @LONG
這便是川西碧磷洞洞主端桑土公，只見他身材
矮小，須發皆白。手持一個大銅鼎，鼎足上鑄
著一個“桑”字，乃是幾條小蛇、蜈蚣之形盤
成，銅綠斑斕，宛是一件古物。
LONG );
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
    
        set("qi", 4200);
        set("max_qi", 4200);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 3800);
        set("max_neili", 3800);
        set("jiali", 100);
        set("combat_exp", 2000000);

        set_skill("force", 180);
        set_skill("shennong-xinjing", 180);
        set_skill("dodge", 200);
        set_skill("xuefu-mizong", 200);
        set_skill("strike", 180);
        set_skill("dusha-zhang", 180);
        set_skill("hand", 180);
        set_skill("lansha-shou", 180);
        set_skill("parry", 180);
        set_skill("staff", 180);
        set_skill("shennong-zhang", 180);
        set_skill("throwing", 220);
        set_skill("pidi-shenzhen", 220);
        set_skill("literate", 160);
        set_skill("poison", 200);
        set_skill("martial-cognize", 180);

        map_skill("force", "shennong-xinjing");
        map_skill("dodge", "xuefu-mizong");
        map_skill("strike", "dusha-zhang");
        map_skill("hand", "lansha-shou");
        map_skill("throwing", "pidi-shenzhen");
        map_skill("parry", "jiuqu-zhegufa");
        map_skill("staff", "shennong-zhang");

        prepare_skill("hand", "lansha-shou");
        prepare_skill("strike", "dusha-zhang");

        set("inquiry", ([
                "斕蜈金針"   : (: ask_me :),
                "幻遁寒星"   : (: ask_skill :),
                "虛竹"       : "他是我們靈鷲宮新的主公，我們全部聽他號令。",
                "虛竹子"     : "他是我們靈鷲宮新的主公，我們全部聽他號令。",
        ]));

        create_family("碧磷洞", 8, "洞主");

        set("zhen_count", 3);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.lun" :),
                (: perform_action, "throwing.huan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob",3);
        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        set_temp("handing", carry_object("/d/lingjiu/npc/obj/jinzhen"));
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "靈鷲宮" )
        {
                command("bite");
                command("say 快滾，快滾！我可沒時間和你耗。");
                return -1;
        }

        if( query("family/master_id", ob) != "xuzhu zi" )
        {
                command("heng");
                command("say 你算什麼東西？就是你師父我也不放在眼裡。");
                return -1; 

        }

        if (skill != "pidi-shenzhen" && skill != "throwing")
        {
                command("say 我能只教你一些暗器手法，不學就算了。");
                return -1;
        }

        if (skill == "throwing" && ob->query_skill("throwing", 1) > 179)
        {
                command("say 你暗器的造詣已經很高了，剩下的就自己去研究吧。");
                return -1;
        }

        if( !query_temp("can_learn/sangtugong", ob) )
        {
                command("bored");
                command("say 唉……看在主公的份上，我教你好了。");
                set_temp("can_learn/sangtugong", 1, ob);
        }
        return 1;
}

mixed ask_skill()
{
        object me;

        me = this_player();
        if( query("can_perform/pidi-shenzhen/huan", me) )
                return "我不是已經教會你了嗎？";

        if( query("family/family_name", me) != "靈鷲宮" && 
           query("family/family_name", me) != "碧磷洞" )
                return "快給我滾開！我可沒時間和你耗。";

        if (me->query_skill("pidi-shenzhen", 1) < 1)
                return "你辟地神針都沒學，還談什麼絕招。";

        if( query("family/family_name", me) == "靈鷲宮" && 
           query("family/gongji", me)<600 )
                return "嗯，主公說過了，不得傳功給無功勞的弟子。";

        if (me->query_skill("force") < 200)
                return "你的內功差成這樣，怎麼學絕技？";

        if (me->query_skill("pidi-shenzhen", 1) < 140)
                return "你的辟地神針火候還差得遠，再回去練練！";

        message_vision(HIY "$n" HIY "陰陰一笑，將$N" HIY "招至跟前，輕"
                       "聲在耳旁秘密說了些什麼。隨後又伸出右\n手，十指"
                       "箕張，一伸一縮，看樣子是一種很特別的暗器法門。\n"
                       NOR, me, this_object());

        command("grin");
        command("say 這招在打架的時候很管用，如果抹上了毒……嘿嘿。");
        tell_object(me, HIC "你學會了「幻遁寒星」。\n" NOR);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("pidi-shenzhen"))
                me->improve_skill("pidi-shenzhen", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/pidi-shenzhen/huan", 1, me);
        if( query("family/family_name", me) == "靈鷲宮" )
                addn("family/gongji", -600, me);
        return 1;
}

mixed ask_me()
{
        object me;
        object ob;

        me = this_player();

        if( query("family/family_name", me) != "靈鷲宮" && 
           query("family/family_name", me) != "碧磷洞" )
                return "滾開！我可沒時間和你耗。";

        if( query("family/master_id", me) != "xuzhu zi" )
                return "讓你師父來拿，這寶貝可不能亂送人。";

        if (me->query_skill("pidi-shenzhen", 1) < 100)
                return "你辟地神針的手法還不到家，拿了這針也沒什麼用。";

        if (query("zhen_count") < 1)
                return "沒了，沒了！我老底都被你掀幹凈了。";

        addn("zhen_count", -1);
        ob = new("/d/lingjiu/npc/obj/jinzhen");
        message_vision("$N拿出五十根" HIR "斕蜈金針" NOR "(Lanwu jinzhen)給$n。\n",
                       this_object(), me);
        ob->move(me, 1);
        return "我這兒的斕蜈金針你先拿去用吧。";
}

/*
void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("sigh2");
        command("say 這個世道真是什麼人都有，擺著那麼多門派不拜，卻跑來拜我。");
        command("say 虧你也想得出來，既然來了，我就收下你吧。");
        command("recruit "+query("id", ob));
} 
*/
