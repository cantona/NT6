//hapagou.c 哈巴狗
#include <ansi.h>
#include <command.h>
string ask_me();
inherit NPC;

void create()
{
        set_name("哈巴狗", ({ "dog" }) );
        set("title", "博餅屋寵物");
        set("race", "家畜");
        set("gender", "雄性" );
        set("age", 15);
        set("str", 22);
        set("int", 30);
        set("dex", 30);
        set("con", 30);

        set("long",
"你看到的是博餅屋裡的小哈巴狗。\n");
        set("combat_exp", 2000000);
        set("attitude", "friendly");

        set("max_qi", 10000);
        set("max_jing", 10000);
        set("inquiry", ([
        "博餅屋" : "這兒就是，你要玩嗎？\n",
        "博餅會" :  (: ask_me :),
        "博餅"   : "你（help bobing）就知道了。\n",
        ]) );
setup();
}

string ask_me()
{
        object* ob;
        int i;
        ob = users();

        if ( !wizardp(this_player()) ) return "你無權召開博餅會！\n";

        for ( i=sizeof(ob); i>0; i-- ) {
                ob[i-1]->move("/d/city/bobing");
        }
        command("chat 博餅屋要聚會了！大家快來！\n");
        return "好，現在博餅會正式開始，全體集合！\n";
}
void init()
{
add_action("do_save","save");
add_action("do_smash","smash");
add_action("do_exert","call");
add_action("do_exert","quit");
add_action("do_exert","exert");
add_action("do_exert","exercise");
add_action("do_exert","dazuo");
add_action("do_exert","respirate");
add_action("do_exert","tuna");
add_action("do_exert","practice");
add_action("do_exert","lian");
add_action("do_exert","study");
add_action("do_exert","du");
}

int do_save(string arg)
{
        command("say"+query("name", this_player())+"，這兒不許存盤的。\n");
        return 1;
}
int do_smash(string arg)
{
        command("say"+query("name", this_player())+"，巫師在這兒也不許殺人的。\n");
        return 1;
}
int do_exert(string arg)
{
        command("say"+query("name", this_player())+"，專心博餅吧！\n");
        return 1;
}