inherit __DIR__"pld_npc.c";
#include <ansi.h>

int is_pld_npc(){return 1;}

void create()
{
        set_name(HIW "飛龍" NOR, ({ "fei long", "fei", "long" }));
        set("long", HIW "這是一隻長着翅膀的惡龍，看起來令人毛骨悚然。\n" NOR);

        set("age", 190);
        set("str", 40);
        set("dex", 30);
        set("max_qi", 2100000);
        set("max_jing", 150000);
        set("max_jingli", 1500000);
        set("max_neili", 200000);
        set("neili", 200000);                
        set("combat_exp", 20000000);
        set("no_nuoyi", 1);
        set("gift/exp", 600);
        set("gift/pot", 350);
        set("oblist", ([
                "/clone/fam/gift/str4" :1,
                "/clone/fam/gift/con4" :1,                        
                "/clone/armor/moling-zhiyi3" : 3,                        
                "/clone/armor/zhanhun-xue3":20,
                "/clone/armor/xingyue-erhuan3":20,
                "/clone/fam/item/wannian-hong":30,
                "/clone/fam/max/naobaijin":20,        
        ]));

        set_skill("force", 460);
        set_skill("dodge", 460);
        set_skill("unarmed", 400);
        set_skill("sword", 460);
        set_skill("parry", 460);
        set_skill("claw", 460);
        
        setup();
        add_money("silver", 22 + random(30));
}
void init()
{
        // 隨機攻擊玩家
        if (userp(this_player()))
        {
                kill_ob(this_player());
        }
}

void die()
{
        if (query("qi") > 100000)
        {
                revive();
                return;
        }
        ::die();
}