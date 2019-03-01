inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
        set_name("柳大洪", ({ "liu dahong", "liu" }));
        set("nickname", HIY"鐵背蒼龍"NOR);
        set("title", "沐王府家將");
        set("long", 
"一個頭發蒼白的老者，紅潤臉色，身材魁梧。\n"
"他便是江湖上人稱鐵背蒼龍的柳大洪，也是雲\n"
"南沐王少主沐劍聲的師父\n");
        set("gender", "男性");
        set("age", 62);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 40);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 20);        
        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);

        set("combat_exp", 1000000);
        set("score", 20000);

        set_skill("force", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("strike", 150);
        set_skill("hunyuan-yiqi", 150);
        set_skill("qianye-shou", 150);
       set_skill("shaolin-shenfa",150);

        map_skill("force", "hunyuan-yiqi");
       map_skill("dodge", "shaolin-shenfa");
       map_skill("parry", "qianye-shou");
        map_skill("strike", "qianye-shou");

        prepare_skill("strike", "qianye-shou");

        setup();
        carry_object("/d/beijing/npc/obj/cloth1")->wear();
}
