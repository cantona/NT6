// qiao.c 樵夫

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("樵夫", ({ "qiao fu", "qiao" }));
        set("title",  "大理國大將軍" );
        set("long", 
"他就是大理國的原大將軍，一燈大師的四大弟子之一。
左手提着一捆鬆柴，右手握着一柄斧頭，但見他容色豪
壯，神態虎虎，舉手邁足間似是大將軍有八面威風。若
非身穿粗布衣裳而在這山林間樵柴，必當他是個叱吒風
雲的統兵將帥。\n");
        set("gender", "男性");
        set("age", 45);
        set("class", "officer");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 20);
        set("str", 30);
        set("int", 30);
        set("con", 35);
        set("dex", 30);

        set("max_qi", 1500);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);
        set("combat_exp", 500000);
        set("score", 10000);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("cuff", 100);
        set_skill("strike", 100);
        set_skill("axe", 100);
        set_skill("finger", 100);
        set_skill("kurong-changong", 100);
        set_skill("tiannan-bu", 150);
        set_skill("jinyu-quan", 150);
        set_skill("wuluo-zhang", 150);
        set_skill("duanyun-fu", 150);
        set_skill("sun-finger", 150);
        set_skill("literate", 100);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "sun-finger");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "sun-finger");
        map_skill("axe", "duanyun-fu");
        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.jingtian" :),        
                (: perform_action, "finger.qiankun" :),                        
                (: exert_function, "powerup" :),                
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
        }) );

        set("inquiry", ([
                "一燈大師"   : "師父他老人家在上面。\n",
                "段智興"     : "那是我師父俗世的名諱。\n",
                "劉瑛姑"     : "她是我師父俗世的妃子。\n",
        ]) );

        set("chat_chance", 3);
        set("chat_msg", ({
"那樵子唱道：
    “城池俱壞，英雄安在？雲龍幾度相交代？想興衰，苦為懷。唐家才起隋家敗，世態
有如雲變改。疾，也是天地差！遲，也是天地差！”\n",
"那樵子唱道：
    “天津橋上，憑欄遙望，舂陵王氣都凋喪。樹蒼蒼，水茫茫，雲台不見中興將，千古
轉頭歸滅亡。功，也不久長！名，也不久長！”\n",
"那樵子唱道：
    “城池俱壞，英雄安在？雲龍幾度相交代？想興衰，苦為懷。唐家才起隋家敗，世態
    “峯巒如聚，波濤如怒，山河表裏潼關路。望西都，意踟躕。傷心秦漢經行處，宮闕
萬間都做了土。興，百姓苦！亡，百姓苦！”\n",
"那樵子唱道：
    “青山相待，白雲相愛。夢不到紫羅袍共黃金帶。一茅齋，野花開，管甚誰家興廢誰
成敗？陋巷單瓢亦樂哉。貧，氣不改！達，志不改！”\n",
"隱隱聽得那樵子又在唱曲，甚麼
    “……當時紛爭今何處？贏，都變作土！輸，都變作土！”\n",
        }) );
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/kungfu/class/dali/obj/axe")->wield();
        add_money("silver", 50);

        create_family("大理段家",25,"弟子");
}
