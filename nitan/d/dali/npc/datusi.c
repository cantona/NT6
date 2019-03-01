// datusi.c

inherit NPC;

void create()
{
        set_name("大土司", ({ "da tusi", "tusi" }));
        set("age", 42);
        set("gender", "男性");
        set("long", "大土司是擺夷族人氏，是蒼山納蘇系的。他倒是長的肥頭大耳的，
每說一句話，每有一點表情，滿臉的肉紋便象是洱海裡的波浪一樣。
他身著彩綢，頭帶鳳羽，腳踩籐鞋，滿身掛著不同色彩的貝殼。只見
他傲氣凜然地高居上座，不把來人看在眼裡。\n");
        set("attitude", "peaceful");

        set("str", 30);
        set("per", 18);
        set("dex", 36);
        set("combat_exp", 150000);
        set("shen_type", 1);

        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("blade", 50);
        set_skill("force", 50);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/armor", 100);

        setup();
        carry_object("/d/dali/npc/obj/lace")->wear();
}
