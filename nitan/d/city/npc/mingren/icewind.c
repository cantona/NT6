// gzf 鬼丈夫

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name(HIW "雪魂" NOR, ({ "icewind" }));
        set("title", HIR "忙碌之神" NOR);
        set("gender", "男性");
        set("age", 35);
        set("no_get", 1);
        set("long", sort_msg(HIY"雪魂，2005年8月重返泥潭，始於泥潭（二），終於泥潭（二），以雪淺凝（滅淺）闖蕩江湖"
"，一生無為，交友甚多。與友千王之王，發呆蟲，狐一劍，楚風，司馬天籟共建幫派“雪域蒼狼”,闖蕩江湖時，處事雖無大善，"
"亦無大惡，以勤奮修練為專長，以團結兄弟為己任，終因私務而離開泥潭。\n" NOR));
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
