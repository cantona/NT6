#include <ansi.h>
inherit NPC;

void create()
{
        set_name("都大錦", ({ "du dajin", "du", "dajin"}) );
        set("nickname", YEL "多臂熊" NOR );
        set("title", "龍門鏢局總鏢頭");
        set("long", "這便是龍門鏢局的總鏢頭都大錦，乃是少林寺俗家弟子。\n");
        set("shen_type", 1);
        set("gender", "男性" );
        set("attitude", "friendly");
        set("age", 36);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 1000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 100000);
        set("score", 5000);

        set_skill("force", 120);
        set_skill("hunyuan-yiqi", 120);
        set_skill("shaolin-xinfa", 120);
        set_skill("dodge", 120);
        set_skill("shaolin-shenfa", 120);
        set_skill("hand", 130);
        set_skill("fengyun-shou", 130);
        set_skill("parry", 120);
        set_skill("buddhism", 120);
        set_skill("literate", 120);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("hand", "fengyun-shou");
        map_skill("parry", "fengyun-shou");

        prepare_skill("hand", "fengyun-shou");

        setup();
        carry_object("clone/misc/cloth")->wear();
}