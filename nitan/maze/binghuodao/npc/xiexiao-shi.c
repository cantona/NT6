#include <ansi.h>

inherit NPC;

int move_bhd();
int join_battle();

void create()
{
        set_name(HIM "謝曉詩" NOR, ({ "xiexiao shi", "xiexiao", "shi" }));
        set("title", HIW "冰" HIR "火" HIC "使者");
        set("long", "她是負責護送玩家到冰火島的秘密使者。\n");
        set("gender", "女性");
        set("age", 20);
        set("max_qi", 99999);
        set("qi", 99999);
        set("max_jingli", 99999);
        set("max_jing", 99999);
        set("max_neili", 99999);
        set("jing", 99999);
        set("jingli", 99999);
        set("neili", 99999);

        set("per", 25);
        set("con", 88);
        set("int", 88);
        set("dex", 88);
        set("str", 88);

        set("inquiry", ([
                "冰火島" : (: move_bhd :),
                "幫派爭奪戰" : (: join_battle :),
        ]));
        set("combat_exp", 10000000);
        set("shen_type", 1);
        setup();
        carry_object("/d/city/npc/cloth/feature")->wear();      
}

int move_bhd()
{
        object me = this_player();
        
        // 身上錢不足
        if( query("balance", me)<100 )
        {
                command("say 你的銀庫中似乎缺錢吧，我護送你到冰火島至少得一百兩黃金！");
                return 1;
        }
        addn("balance", -100, me);
        
        command("say 既然如此，我就護送你到冰火島吧！");

        me->move("/maze/binghuodao/haitan"); 
        return 1;
}

int join_battle()
{
        object me = this_player();
        BUNCH_D->join_battle(me);
        return 1;
}

