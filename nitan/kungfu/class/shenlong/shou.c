// This program is a part of NT MudLIB
// shou.c

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;

void create()
{
        set_name("瘦頭陀", ({ "shou toutuo", "shou" ,"toutuo"}));
        set("title", HIY"神龍教"NOR"右護法");
        set("nickname",HIR "遼東瘦尊者" NOR);
        set("long", "這頭陀身材奇矮，而且胖得出奇，整個人就活脫脫是一個大冬瓜。\n"
                    "光溜溜的腦袋上瞪著一對銅鈴大眼，樣子非常滑稽。\n" );
        set("gender", "男性");
        set("age", 44);

        set("str", 26);
        set("int", 18);
        set("con", 31);
        set("dex", 25);

        set("max_qi", 3600);
        set("qi", 3600);
        set("max_jing", 1800);
        set("jing", 1800);
        set("neili", 4200);
        set("max_neili", 4200);
        set("jiali", 50);
        set("level", 20);
        set("combat_exp", 680000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("force", 150);
        set_skill("hand", 150);
        set_skill("strike", 150);
        set_skill("staff", 150);
        set_skill("parry", 150);
        set_skill("dodge", 150);
        set_skill("yixingbu", 150);
        set_skill("shenlong-bashi", 150);
        set_skill("huagu-mianzhang", 150);
        set_skill("shenlong-xinfa", 150);
        set_skill("shedao-qigong", 150);

        map_skill("force", "shenlong-xinfa");
        map_skill("staff", "shedao-qigong");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shenlong-bashi");
        map_skill("dodge", "yixingbu");
        prepare_skill("hand", "shenlong-bashi");
        prepare_skill("strike", "huagu-mianzhang");

        create_family("神龍教", 0, "閒散教眾");

        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/armor", 100);
        set_temp("apply/damage", 100);

        set("inquiry", ([
                "神龍教" : "一般人是入不了我神龍教的(join shenlongjiao).\n",
                "入教"   : "一般人是入不了我神龍教的(join shenlongjiao).\n",
                "洪安通" : "教主脾氣不好,要討他歡心才好。\n",
                "教主"   : "教主脾氣不好,要討他歡心才好。\n",
                "口號"   : "萬年不老！永享仙福！壽與天齊！文武仁聖！",
        ]) );
        set("master_ob", 3);
        setup();
        carry_object(CLOTH_DIR"jinduan")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
        add_money("silver", 35);
}

void attempt_apprentice(object ob)
{
        command("say 滾！少在大爺面前瞎晃。");
}
