// Npc: /d/guiyun/npc/qianzhang.c
// Last Modified by winder on Jul. 9 2001

inherit NPC;
int ask_me();

void create()
{
        set_name("老者", ({ "old man", "old" }));
        set("gender", "男性");
        set("age", 70);
        set("long","他身高八尺有余，白發白須，滿面紅光，太陽穴高高隆起。看起來身負絕技。\n");
        set("attitude", "friendly");
        set_skill("unarmed", 70);
        set_skill("dodge", 70);
        set_skill("parry", 70);
        set("combat_exp", 90000);
        set("shen_type", -1);
        set("shen", -300);
        set("str", 20);
        set("dex", 24);
        set("con", 19);
        set("int", 21);
        set("inquiry",([
                "name" : "我就是江湖上人稱“鐵掌水上飄”的裘千仞！",
                "裘千丈" : (: ask_me :),       
        ]));
        setup();
        set("chat_chance",10);
        set("chat_msg",({
                "老者將一口大鐵缸頂在頭上，走出數步，身子微擺，缸中忽然潑出些水來。\n",
                "老者足不停步地從河面上走了過去，身形凝穩，河水只浸及小腿。\n",
                "老者盤膝而坐，雙目微閉，嘴裡正噴出一縷縷的煙霧，連續不斷。\n",
        }));
        carry_object("/clone/misc/cloth")->wear();
}

int ask_me()
{
        say( "老者臉色大變：這麼說你都知道了？我求你千萬別告訴別人。我告訴你怎麼過河。\n");
        write("老者說道：水下有暗樁，jump river即可過河。\n");
        say("老者急急忙忙地離開了。\n");
        set_temp("guiyun_river", 1, this_player());
        destruct(this_object());
        return 1;
}

void unconcious()
{
        say("老者叫道：我裘千仞年紀老了，武功已大不如前，不過輕身功夫卻還沒丟荒。\n");
        say("老者叫道：今天暫且放過你，來日再算帳！\n");
        say("老者低頭疾趨而去。\n");
        destruct(this_object());
}
