// Feb. 6, 1999 by Winder
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("阿鳳", ({ "a feng","a","feng"}) );
        set("gender", "女性" );
        set("age", 16);
        set("long", "這是一個活潑可愛的女僕人。\n");
        set("shen_type", 1);
        set("combat_exp", 500);
        set("str", 16);
        set("dex", 17);
        set("con", 17);
        set("int", 18);
        set("attitude", "friendly");
        set("chat_chance",1);
        set("chat_msg",({
            "阿鳳一邊微笑著，一邊不知道在想什麼心事。\n",
            "阿鳳自言自語地說：阿土那個死人，連人家的心意都不知道。\n",
            "阿鳳嘆了口氣道：女大思春啊！\n",
            "阿鳳突然說道：我家小姐好慘啊，被關在這個島上不許出去。\n"
           }) );
       set("inquiry",([
           "阿土" : "他是我的心上人啊，但我不知道他的心意如何，這種事情叫我一個女孩子家怎麼說得出口嘛。\n"
           ]) );
       setup();
       carry_object("/clone/misc/cloth")->wear();
}
int accept_object(object me, object ob)
{
        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0; 
        if ( !present(ob, me) ) return notify_fail("你沒有這件東西。");
        if( query("id", ob) == "qingshu" )
        {
         write(HIC "阿鳳一把搶過你送來的情書，高興地跳了起來，說道: \n" NOR);
         write(HIC "既然你對我這麼好，我就告訴你一個秘密。這裡是可以\n" NOR);         
         write(HIC "出去的。你只需在《蘭亭集序》下磕九個頭就可以了！\n" NOR);
        }               
        return 1;
}