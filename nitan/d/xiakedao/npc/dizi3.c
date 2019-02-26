// dizi3.c 弟子

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("青衣弟子", ({ "di zi", "di", "zi" }));
        set("long", "這是三十多歲的壯漢，膀大腰圓，是島主從中原招募來的。\n");

        set("gender", "男性");
        set("age", 30);
        set("shen_type",1);
        set("attitude", "peaceful");

        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        set("qi", 500);
        set("max_qi", 500);
        set("jing", 200);
        set("max_jing", 200);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", 30);

        set("combat_exp", 30000);
        set("score", 10);
        set_skill("force", 70);
        set_skill("unarmed", 70);
        set_skill("dodge", 70);
        set_skill("parry", 70);
        set_skill("hand", 70);
        set_skill("staff", 50);
        create_family("俠客島", 2, "弟子");

        setup();
        carry_object(__DIR__"obj/bcloth")->wear();
}

void init()
{
        object ob= this_player();

        ::init();
        if( interactive(ob) && !ob->is_fight() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        object room;
        room = find_object("/d/xiakedao/shimen");

        if( !ob || environment(ob) != environment()
                || environment() != room)
                return;

        message_vision("
$N説道：洞內有二十四座石室，各位可請隨意來去。看得厭了，可到
洞外散心，一應飲食，石室內均有置備，各位隨意取用，不必客氣。", this_object());
        message_vision("
二十四座石室大致是這樣分佈的：

        基本掌法                 基本鈎法                 基本拳腳
           ｜                       ｜                       ｜
基本暗器—一進—基本輕功 基本棒法—二進—基本槍法 基本刀法—三進—基本招架
           ｜                       ｜                       ｜
        基本劍法                 基本腿法                 基本刺法

        基本斧法                 基本錘法                 基本指法
           ｜                       ｜                       ｜
基本爪法—四進—基本杖法 基本內功—五進—基本陣法   太玄功—六進—基本鞭法
           ｜                       ｜                       ｜
        基本拳法                 基本手法                 基本棍法\n", this_object());
}
