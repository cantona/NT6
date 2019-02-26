// npc: /d/city/npc/libailv.c
// Last Modified by Winder on Jul. 15 2000

#include <ansi.h>
inherit NPC;
inherit F_DEALER;

void create()
{
        set_name( YEL "李百履" NOR , ({ "li bailv","li","bailv" }) );
        set("age", 43);
        set("title", "李家絲鞋鋪老闆");
        set("long", @LONG
李百履是一條瘦小的漢子，他五短身材，但是卻很有精神。從眼睛裏就
能看出這是個精明的生意人。他就是這家鞋店的老闆。
LONG
        );
        set("chat_chance", 40);
        set("chat_msg", ({
                "李老闆道：這裏就是揚州城啦，有名的花花世界啊！\n",
                "李老闆道：説起本府的程老爺，那是天下一等一的大才子，有學問！\n",
                "李老闆道：嘿嘿，客官，您別光説話聊天啊，照顧照顧小老兒的生意啊？\n",
                "李老闆道：客官，您瞧瞧，這雙絲鞋多合適啊。您家試試，來我幫您包上，怎麼樣？\n",
        }));
        set("inquiry", ([
                "絲鞋" : "啊，您要買絲鞋是吧？沒問題，咱家的鞋是揚州城裏頭一份！\n",
                "here" : "這揚州城啊，那是大江南北頭一個繁華的去處！\n",
        ]) );
        set("vendor_goods", ({
                BOOT_DIR+"maxie",
                BOOT_DIR+"pixue",
                BOOT_DIR+"sifeng_huangxue",
                BOOT_DIR+"sifeng_kuanxue",
                BOOT_DIR+"sixie",
                BOOT_DIR+"baodi_kuaixue",
                BOOT_DIR+"xiuhua_xie2",
                BOOT_DIR+"zihua_xie",
                BOOT_DIR+"gongxie",
                BOOT_DIR+"caoxie",
                BOOT_DIR+"flower_shoe",
        }) );

        set("attitude", "friendly");
        set("rank_info/respect", "老哥");
        set("rank_info/rude","老王八蛋");
        set("combat_exp",100);
        set_skill("unarmed", 5);
        setup();
        carry_object( "/clone/cloth/male-cloth")->wear();
}

void init()
{
        object ob = this_player();
        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        message_vision( "李老闆熱情的迎上來：“客官，您買雙鞋？哎，不買不要緊，看看貨色麼。”\n",ob);
        return;
}