#include <ansi.h>
inherit NPC;

int ask_me();

void create()
{
        set_name("毒道人", ({ "du daoren", "daoren" }));
        set("gender", "男性" );
        set("age", 35);
        set("per", 20);
        set("long", "一位身穿道服，幹癟黑瘦的中年道人．\n");
        set("combat_exp", 200000);
        set("attitude", "friendly");
        set("book_count", 1);

        set_skill("blade", 50);
        set_skill("ruyi-dao", 50);
        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("unarmed", 50);
        set_skill("parry", 50);
        set_skill("feiyan-zoubi", 50);
        set_skill("beiming-shengong",50);
        set_skill("changquan", 50);

        map_skill("unarmed", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("force", "beiming-shengong");
        map_skill("blade", "ruyi-dao");

        set("title", "五毒教小頭目");

        set("chat_chance", 2);
        set("chat_msg",({
                CYN "毒道人冷笑道：江湖中人誰敢和我們五毒教作對，管叫"
                "他死的不明不白。\n" NOR,
                CYN "毒道人幹笑一聲道：貧道專管練制各種毒藥，保証藥到"
                "命除。\n" NOR,
        }));

        setup();
        add_money("silver", 20);
        set("inquiry", ([
                "here"     : "此乃煉丹房，可以在這裡練制(lianzhi)各種毒藥。",
                "毒藥"     : "閣下可以在這裡練制(lianzhi)各種毒藥。",
                "原料"     : (: ask_me :),
                "練毒"     : (: ask_me :),
                "毒經"     : "你打算煉毒麼？可惜我這裡只有毒經上篇。",
                "上篇"     : (: ask_me :),
                "毒經上篇" : (: ask_me :),
                "配方"     : (: ask_me :),
                "毒藥配方" : (: ask_me :),
        ]) );
        carry_object("/d/wudang/obj/greenrobe")->wear();
}

int ask_me()
{
        object ob, me;
        me = this_player();

        if( query("family/family_name", me) != "五毒教" )
        {
                command("say 閣下與本派並無淵源，這話是從何而來？");
                return 1;
        }

        if (query("book_count") < 1)
        {
                command("say 你來晚了，毒經我已經給別人了。");
                return 1;
        }
        addn("book_count", -1);
        ob = new("/d/wudu/obj/dujing1");
        ob->move(this_object());

        command("say 此毒經上記載了各種密藥的練制方法，千萬不可遺失了。");
        command("givedujing1to"+query("id", me));
        return 1;
}