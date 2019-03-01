inherit __DIR__"bhd_npc.c";
#include <ansi.h>

void create()
{
        set_name(HIG "九頭飛龍" NOR, ({ "jiutou long", "jiutou", "long" }));
        set("long", HIG "巨大的飛龍，居然長有九個頭顱，渾身泛出恐怖的綠芒，似乎想要吞噬一切。\n" NOR);

        set("age", 99999);
        set("str",500);
        set("dex", 500);
        set("int", 500);
        set("con", 500);
        set("max_qi", 200000000);
        set("max_jing", 100000000);
        set("max_jingli", 100000000);
        set("max_neili", 2500000);
        set("neili", 2500000);
        set("combat_exp", 1000000000);
        set("no_nuoyi", 1);
        set("gift/exp", 3000);
        set("gift/pot", 800);
        set("gift/mar", 40);
        set("oblist", ([
                "/clone/fam/gift/str3" :1,
                "/clone/fam/gift/con3" :1,
                "/clone/fam/gift/dex3" :1,
                "/clone/fam/gift/int3" :1,
        ]));


        set_skill("force", 1500);
        set_skill("dodge", 1500);
        set_skill("unarmed", 1500);
        set_skill("sword", 1500);
        set_skill("parry", 1500);
        set_skill("claw", 1500);

        setup();
        add_money("gold", 3 + random(3));
}

void init()
{
        // 隨機攻擊玩家
        if (userp(this_player()))
        {
                kill_ob(this_player());
        }
}
