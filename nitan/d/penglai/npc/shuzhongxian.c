// 
//

#include <ansi.h>

inherit NPC;

string ask_nanti1();
string ask_nanti2();
string ask_nanti3();
string ask_nanti4();
string ask_nanti5();
string ask_nanti6();

void create()
{
        set_name(HIW "書中仙" NOR, ({ "shuzhong xian", "shuzhong", "xian" }));
                
        set("long", HIW "這位仙人乃大名鼎鼎的書中仙，據說天上地下之事他無所不知，神通廣大。\n" NOR);

        set("gender", "男性");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "如何不被仙氣困擾"       :   "這仙氣的困擾對于你們凡人來說是無可避免的，不過只要你能回答我的幾個難題，\n"
                                             "本仙人到是可以教你如何減少仙氣對你的困擾。\n",
                "難題"                   :   "我這裡總共有六道難題，如果你能按順序逐一解決，我便教你如何減少被仙氣困擾的方法。\n",                            
                "解決難題"               :   "你想好了就在這裡找我吧，按照順序如第一道題你就 ask xian about 難題一 。\n",
                "如何答復"               :   "每道題目都是一首詩的一部分，答案是一樣物品，你找到這個物品交給我就行了。\n",
                "蓬萊仙島"               :   "這不是你該來的地方，我看你還是快走吧。\n",
                "難題一"                 :   (: ask_nanti1 :),
                "難題二"                 :   (: ask_nanti2 :),
                "難題三"                 :   (: ask_nanti3 :),
                "難題四"                 :   (: ask_nanti4 :),
                "難題五"                 :   (: ask_nanti5 :),
                "難題六"                 :   (: ask_nanti6 :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

string ask_nanti1()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "“悠然見南山。”" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "我的六道難題你都解決了，不錯，不錯。";
                
        if (me->query("penglai/go_quest/step") > 1)
                return "這道難題你已經解答過了。";        
        
        tell_object(me, HIG "題目是：" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 1);
        me->save();
        
        return "我等你的好消息了。";
}

string ask_nanti2()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "“碧草生在幽谷中，沐日浴露姿從容。”\n“天賜神香自悠遠，引來蝴蝶弄清風。”" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "我的六道難題你都解決了，不錯，不錯。";
                
        if (me->query("penglai/go_quest/step") > 2)
                return "這道難題你已經解答過了。";        
        
        if (me->query("penglai/go_quest/step") < 2)
                return "你還是先解答前面的難題吧。";
                        
        tell_object(me, HIG "題目是：\n" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 2);
        me->save();
        
        return "我等你的好消息了。";
}

string ask_nanti3()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "“彩衣天授浮生夢，粉翅風憐浪客詩。”\n“獨步尋花花謝早，相思寄月月難知。”" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "我的六道難題你都解決了，不錯，不錯。";
                
        if (me->query("penglai/go_quest/step") > 3)
                return "這道難題你已經解答過了。";        
        
        if (me->query("penglai/go_quest/step") < 3)
                return "你還是先解答前面的難題吧。";
                        
        tell_object(me, HIG "題目是：\n" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 3);
        me->save();

        return "我等你的好消息了。";
}

string ask_nanti4()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "“若非一番寒澈骨。”\n" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "我的六道難題你都解決了，不錯，不錯。";
                
        if (me->query("penglai/go_quest/step") > 4)
                return "這道難題你已經解答過了。";        
        
        if (me->query("penglai/go_quest/step") < 4)
                return "你還是先解答前面的難題吧。";
                        
        tell_object(me, HIG "題目是：\n" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 4);
        me->save();

        return "我等你的好消息了。";
}

string ask_nanti5()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "“長晝風雷驚虎豹，半空鱗甲舞蛟龍。”" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "我的六道難題你都解決了，不錯，不錯。";
                
        if (me->query("penglai/go_quest/step") > 5)
                return "這道難題你已經解答過了。";        
        
        if (me->query("penglai/go_quest/step") < 5)
                return "你還是先解答前面的難題吧。";
                        
        tell_object(me, HIG "題目是：\n" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 5);
        me->save();

        return "我等你的好消息了。";
}

string ask_nanti6()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "“勸君莫嗟嘆，精神可勝兵；”\n“充塞天和地，懷抱浪與星。”" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "我的六道難題你都解決了，不錯，不錯。";
                
        if (me->query("penglai/go_quest/step") > 6)
                return "這道難題你已經解答過了。";        
        
        if (me->query("penglai/go_quest/step") < 6)
                return "你還是先解答前面的難題吧。";
                        
        tell_object(me, HIG "題目是：\n" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 6);
        me->save();

        return "我等你的好消息了。";
}
int accept_object(object me, object obj)
{                        
        
        if (me->query("penglai/go_quest/ok"))
        {
                command("say 閣下智慧超群，佩服佩服。");
                return 0;
        }
        
        switch(me->query("penglai/go_quest/step"))
        {
                // 菊花
                case 1:
                        if (obj->query("id") == "penglai juhua" &&
                                base_name(obj) == "/d/penglai/obj/juhua")
                            {
                                    command("nod");
                                    command("say 很好，很好，你可以開始解答下一道難題了。");
                                    destruct(obj);
                                    me->set("penglai/go_quest/step", 2);
                                    me->save();
                                    return 1;
                            }
                            command("say 本仙人從不亂收別人東西。");
                            return 0;
                        break;
                // 蘭草        
                case 2:
                        if (obj->query("id") == "penglai lancao" &&
                                base_name(obj) == "/d/penglai/obj/lancao")
                            {
                                    command("nod");
                                    command("say 很好，很好，你可以開始解答下一道難題了。");
                                    destruct(obj);
                                    me->set("penglai/go_quest/step", 3);
                                    me->save();
                                    return 1;
                            }
                            command("say 本仙人從不亂收別人東西。");
                            return 0;                
                        break;                
                // 蝴蝶標本
                case 3:
                        if (obj->query("id") == "hudie biaoben" &&
                                base_name(obj) == "/d/penglai/obj/biaoben")
                            {
                                    command("nod");
                                    command("say 很好，很好，你可以開始解答下一道難題了。");
                                    destruct(obj);
                                    me->set("penglai/go_quest/step", 4);
                                    me->save();
                                    return 1;
                            }
                            command("say 本仙人從不亂收別人東西。");
                            return 0;                
                        break;                
                // 梅花
                case 4:
                        if (obj->query("id") == "penglai meihua" &&
                                base_name(obj) == "/d/penglai/obj/meihua")
                            {
                                    command("nod");
                                    command("say 很好，很好，你可以開始解答下一道難題了。");
                                    destruct(obj);
                                    me->set("penglai/go_quest/step", 5);
                                    me->save();
                                    return 1;
                            }
                            command("say 本仙人從不亂收別人東西。");
                            return 0;                
                        break;                
                // 鬆葉
                case 5:
                        if (obj->query("id") == "penglai songye" &&
                                base_name(obj) == "/d/penglai/obj/songye")
                            {
                                    command("nod");
                                    command("say 很好，很好，你可以開始解答下一道難題了。");
                                    destruct(obj);
                                    me->set("penglai/go_quest/step", 6);
                                    me->save();
                                    return 1;
                            }
                            command("say 本仙人從不亂收別人東西。");
                            return 0;                
                        break;                
                // 竹葉
                case 6:
                        if (obj->query("id") == "penglai zhuye" &&
                                base_name(obj) == "/d/penglai/obj/zhuye")
                            {
                                    command("nod");
                                    command("say 很好，很好，閣下智慧超群，將老仙難題逐一解答。");
                                    destruct(obj);
                                    command("say 本仙人便教你如何減少仙氣的困擾，你可記好了 ……");
                                    tell_object(me, HIG "恭喜你，已經學會了如何減少島上仙氣對你的困擾。\n" NOR);
                                    me->set("penglai/go_quest/ok", 1);
                                    me->save();
                                    return 1;
                            }
                            command("say 本仙人從不亂收別人東西。");
                            return 0;                
                        break;        
                default :
                        command("say 本仙人從不亂收別人東西。");
                        return 0;
                        break;                        
        }
        
        return 0;

}
void unconcious()
{
        die();
}
