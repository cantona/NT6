inherit __DIR__"bhd_npc.c";
#include <ansi.h>

void create()
{
        set_name(HIY "金色鳳凰" NOR, ({ "jinse fenghuang", "jinse", "fenghuang" }));
        set("long", HIY "一隻巨大鳳凰，鱗片閃爍着金光，張開雙翅，遮天蔽日。\n" NOR);

        set("age", 99999);
        set("str",500);
        set("dex", 121);
        set("int", 121);
        set("con", 121);
        set("max_qi", 45000000);
        set("max_jing", 8500000);
        set("max_jingli", 8500000);
        set("max_neili", 2500000);
        set("neili", 2500000);
        set("combat_exp", 100000000);
        set("no_nuoyi", 1);
        set("gift/exp", 2000);
        set("gift/pot", 650);
        set("gift/mar", 35);
        set("oblist", ([
                "/clone/fam/gift/str3" :1,
                "/clone/fam/gift/con3" :1,
                "/clone/fam/gift/dex3" :1,
                "/clone/fam/gift/int3" :1,
        ]));


        set_skill("force", 1200);
        set_skill("dodge", 1200);
        set_skill("unarmed", 1200);
        set_skill("sword", 1200);
        set_skill("parry", 1200);
        set_skill("claw", 1200);

        setup();
        add_money("gold", 2 + random(2));
}

void init()
{
        // 隨機攻擊玩家
        if (userp(this_player()) && random(2) == 1)
        {
                kill_ob(this_player());
        }
}
