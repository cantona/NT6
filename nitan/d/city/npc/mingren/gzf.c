// gzf 鬼丈夫

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name(HIW "鬼丈夫" NOR, ({ "gzf" }));
        set("title", HIR "衝動之神" NOR);
        set("gender", "男性");
        set("age", 35);
        set("no_get", 1);
        set("long", sort_msg(HIY"這是一位仙風道骨的中年道人，早年雲遊四方，中年"
                "長居泥潭，性好任俠，公正無私。鬼丈夫是泥潭的最忠實玩家之一，可"
                "惜的是他在泥潭天神調整門派任務獎勵時以自殺來表示不滿而離開泥潭。\n" NOR));
        set("combat_exp", 60000);
        set("shen_type", 1);
        set("attitude", "friendly");

        set("apply/attack", 50);
        set("apply/defense", 50);

        set("max_qi", 800);
        set("max_jing", 800);
        set("max_neili", 800);

        setup();

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}
