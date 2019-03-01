// Npc: /d/guiyun/npc/zhanggui.c
// Last Modified by winder on Jul. 9 2001

inherit NPC;

void create()
{
        set_name("掌櫃", ({ "zhang gui", "zhanggui", "zhang" }) );
        set("gender", "男性" );
        set("age", 52);
        set("long",
                "這位老掌櫃正在忙著敲打算盤。\n");
        set("combat_exp", 2000);
        set("attitude", "friendly");
        set("inquiry", ([
                "name" : "不瞞客官說，小老兒的小名實在難聽，叫做趙阿狗。",
                "rumors" : "歸雲莊的弟子們總來這裡，有時候談到桃花島，都流露出向往的神情。",
                "here" : "這裡是太湖邊，往北走就可以看到歸雲莊了。",
                "桃花島": "聽說是東海上的小島，往杭州的東南走，到海邊看能不能雇船吧？",
                "生意" : "因為歸雲莊的弟子們總來照顧小店的生意，所以還算不錯。",
                "歸雲莊" : "向北走就能看到。那裡的莊主姓陸，平時難得見到。",
        ]) );
        setup();
}

void init()
{        
}

int accept_object(object who, object ob)
{
        int pay, value;

        if( query("money_id", ob)){
                if( !(pay=query_temp("total_pay", who))){
                        tell_object(who, "掌櫃忙不迭地笑道：“客官您又不欠小店的錢，就別拿老頭兒尋開心了。”\n");
                        return 0;
                }
                if( !query_temp("to_pay", who)){
                        tell_object(who, "掌櫃說道：“客官您先結帳(pay)再付款。”\n");
                        return 0;
                }
                value = ob->value();
                if (value >= pay) {
                        delete_temp("to_pay", who);
                        delete_temp("total_pay", who);
                        if (value == pay) message_vision("掌櫃滿臉堆著笑，沖$N哈腰道：“謝客官您啦，走好。”\n", who);
                        else message_vision("掌櫃滿臉堆著笑，沖$N哈腰道：“謝客官您的小費，老兒不客氣就收下了，您走好。”\n", who);
                        return 1;
                }
                else {
                        pay -= value;        
                        message_vision("掌櫃對著$N說道：“不夠！還差" + chinese_number(pay) + "文。”\n", who);
                        set_temp("total_pay", pay, who);
                        return 1;
                }
        }
        return 0;
}

void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        message_vision("$N沮喪地發現掌櫃站在高高的櫃台後面，夠不到。\n", ob);
}

void unconcious()
{
        say( "掌櫃大喊一聲：“我不行了，快來接班！”\n");
        say( "結果從櫃台後面又鑽出一個掌櫃來，說：“沒問題，交給我吧。”\n");
        say( "前一個掌櫃呲牙咧嘴地離開了。\n");
        reincarnate();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
}

void die()
{
        unconcious();
}
