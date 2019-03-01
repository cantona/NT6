// Npc: /d/kunlun/npc/bigmonkey.c
// Last Modified by winder on Jun. 29 2001

inherit NPC;

void create()
{
        set_name("大白猿", ({ "yuan", "dabai yuan", "big monkey" }) );
        set("gender", "雄性");
        set("race", "走獸");
        set("age", 65);
        set("long","這是一只大白猿，奇怪的是從它身上聞得到一陣腐臭之氣，\n原來白猿肚上膿血模糊，生著一個大瘡。\n");
        set("combat_exp", 50000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set("water", 200);
        set("food", 200);
        set("apply/attack", 100);
        set("apply/defense", 100);

        set_skill("unarmed", 25);
        set_skill("parry", 20);
        set_skill("dodge", 20);
        set("bag_count",1);

        setup();
}
void init()
{
        add_action("do_lifeheal", "lifeheal");
}
int do_lifeheal(string arg)
{
        object weapon, bag, me = this_player();
        if (query("bag_count")<1)
        {
                write("白猿一把跳開，不想讓你醫治！\n");
                return 1;
        }
        if( !arg || arg != "yuan")
        {
                write("你想幹什麼呀？\n");
                return 1;
        }
        if (!present("fish bone", me))
        {
                write("怎麼，管開刀不管縫肚皮啊！\n");
                return 1;
        }
        if( !objectp(weapon=query_temp("weapon", me)) || 
                (query("skill_type", weapon) != "sword" && 
                query("skill_type", weapon) != "blade") )
                return notify_fail("你沒有工具怎麼給它做手術！\n");

        message_vision(
"$N割開右邊及上端的縫線，再斜角切開早已聯結的腹皮，只見它肚子
裡藏著一個油布包裹。$N將油布包放在一邊，以魚骨做針，在它腹皮
上刺下一個個小孔，再將樹皮撕成細絲，穿過小孔打結，勉強將白猿
的腹肌縫好，在創口敷上草藥。\n", me);
        bag = new(__DIR__"obj/bag");
        bag -> move (environment(me));
        addn("bag_count",-1);
        return 1;
}
