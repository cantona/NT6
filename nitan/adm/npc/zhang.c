// zhang.c 張天師

#include <ansi.h>

inherit KNOWER;

#define ZHOUTIAN_D      "/adm/daemons/zhoutiand"

int ask_me();
string ask_fu();
int life_warcraft();
string ask_tianjidao();

void create()
{
        set_name("張天師", ({ "zhang tianshi", "zhang" }));
        set("age", 57);
        set("gender", "男性");
        set("long", "這是一位仙風神骨，道貌岸然的法師。\n");
        set("attitude", "peaceful");

        set("str", 28);
        set("int", 35);
        set("con", 38);
        set("dex", 31);

        set("max_qi", 8000);
        set("max_jing", 8000);
        set("max_neili", 8000);

        set_skill("magic", 200);
        set_skill("taoism", 350);

        set("chat_chance_combat", 3);
        set("chat_msg_combat", ({
                "張天師搖搖鈴鐺，道：天靈靈，地零零，太上老君還不顯靈？\n",
                "張天師呼呼的吹了幾口氣。\n",
        }));

        set("inquiry", ([
                "開光" : (: ask_me :),
                "魔獸復活": (: life_warcraft :),
                "沒錢" : "沒錢就去賺，跟我説什麼。",
                "窮"   : "看你也是一副窮命。",
                "魔法" : "魔法？什麼玩藝？",
                "法術" : "法術還分很多種呢，道術、妖術、仙術不一而足。",
                "道術" : "道術？這可是本源正宗！",
                "妖術" : "妖術啊，趨於下乘，不足為提。",
                "仙術" : "仙術只好算是中乘，還是不能和道術相比。",
                "浸入" : "你要是不行我可以幫你看看(show)浸入需要用什麼物品。",
                "鑑定" : "我可以幫你看看(show)你的寶石都藴涵哪些屬性。",
                "賽神龍" : "呵呵，那是貧道的一位故友，現在也不知他生死如何了。",
                "萬年紅" : "此乃天下間最上乘的顏料，畫符首選，可用碧血石+火龍果+乾坤聖水合成。",     
                "童男童女符" : (: ask_fu :),
                "天極道" : (: ask_tianjidao :),
        ]));

        setup();
        carry_object("/clone/cloth/dao-cloth")->wear();
}

string ask_fu()
{
        object me;
        object ob_wnh,ob_zz;
        object ob_fu;
        
        me = this_player();

        command("say 童男童女符乃貧道為昔日故友所造，如果閣下需要的話貧道到是可以效勞。");
        command("say 不過，還需要以下一些材料：首先是萬年紅，此乃宮廷禁品，天下間最上乘的顏料。");
        command("say 其次，天然珍珠，用天然珍珠粉末與萬年紅調和，可使畫出的符效果最佳。");
        command("say 最後，當然，貧道也需要收取一些製作費，總共需要10萬兩黃金。");
        command("ke");
        command("say 怎麼樣，如果以上材料都找齊了可以來找我，我會製作出童男童女符給你，此符下線不丟失。");
        
        // 需要萬年紅
        if (! objectp(ob_wnh = present("wannian hong", me)))
                return "你好像還沒備齊萬年紅顏料吧？\n";        
                                
        if (base_name(ob_wnh) != "/clone/fam/item/wannian-hong")
                return "你好像還沒備齊萬年紅顏料吧？\n";
                
        // 需要天然珍珠 
        if (! objectp(ob_zz = present("tianran zhenzhu", me)))
                return "你好像還沒備齊天然珍珠吧？\n";          
                        
        if (base_name(ob_zz) != "/clone/quarry/item/zhenzhu")
                return "你好像還沒備齊天然珍珠吧？\n";          
        
        // 需要黃金一萬兩
        if (query("balance", me) < 1000000000)
                return "你好像沒有備齊10萬兩黃金吧。\n";
                
        // 物品已經備齊
        destruct(ob_wnh);
        destruct(ob_zz);
        addn("balance", -1000000000, me);
        
        ob_fu = new("/clone/fam/item/tntn_fu");
        
        command("say 不錯，既然我要的東西你都備齊了，我這就將童男童女符給你。");
        
        message_sort("\n" HIC "$N" HIC "將萬年紅和天然珍珠粉末混合在一起，拿出一張黃色的道符，然後口中"
                     "默唸符咒，一柱香的時間，一張童男童女符已經畫好。\n" NOR, this_object());

        ob_fu->move(me, 1);
        
        message_vision("$N" NOR "拿出" + ob_fu->name() + NOR "給$n" NOR "。\n" NOR, this_object(), me);

        return "這符我也做好了，錢也收了，從此我們兩不相欠。\n";                
}

void init()
{
        add_action("do_show", "show");
        add_action("do_summon", "summon");
}

int life_warcraft()
{
        object me, ob;
        
        me = this_player();
        
        if( !query("warcraft/file", me) ) 
        {
                command("say 你目前沒有魔獸，請到揚州找狂風購買，詳情見 help warcraft。");
                return 1;
        }

        if( query("warcraft/status", me) != "died" )
        {
                command("shake");
                command("say 你的魔獸目前並沒有死亡啊。");
                return 1;
        }
        if( !query_temp("want_life_warcraft", me) )
        {
                command("hehe");
                command("say 既然如此，那你就交五千兩黃金吧，貧道變給你作一次法。");
                command("say 如果你確認銀行中有足夠黃金，那麼請再輸入一次該指令。");
                
                set_temp("want_life_warcraft", 1, me);
                
                return 1;
        }
        
        if( query("balance", me) < 50000000)
        {
                command("heng");
                command("say 説好五千兩黃金，難道你想戲耍貧道！！！");
                return 1;
        }
        
        addn("balance", -50000000, me);
        
        message_vision(HIM "$N" HIM "拿出一張符，點燃了拋向空中，然後念着：#￥%……·￥·…·#￥...\n" NOR, this_object());
        
        set("warcraft/status", "living", me);

        command("say 好了，你的魔獸復活了，使用 whistle <id> 就可以召喚出來了。");
        
        delete_temp("want_life_warcraft", me);
        me->save();

        return 1;
        
}
int ask_me()
{
        command("heihei");
        command("say 我只給神兵利器開光，尋常刀劍莫提！要"
                "你本人的，我可不能幫你做壞事！");
        tell_object(this_player(), GRN "張天師在你耳邊悄悄説："
                    "你把要開光的拿出來給我看看(show)！\n" NOR);
        return 1;
}

int do_summon(string arg)
{
        if (! wizardp(this_player()))
        {
                command("say 你在我面前瞎抓個什麼勁？別地試去！");
                return 1;
        }

        return 0;
}

int do_show(string arg)
{
        object money;
        object ob;
        mixed  obj;
        object me;
        string fn, filename;
        int    n, d;

        if (! arg)
                return notify_fail("你要亮出什麼東西？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上沒有這種東西。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的裝備再説！\n");

        message_vision("$n拿出一"+query("unit", ob)+ob->name()+
                       "對$N説：“拜託拜託...”\n",
                       this_object(), me);

        if( query("money_id", ob) )
        {
                command("say 你亮出錢幹什麼？想獻給觀裏？那就給我好了。");
                return 1;
        }

        if( !wizardp(me) && !query_temp("zhangpaid/張天師", me) )
        {
                command("heihei");
                command("say 這...怎麼也的有點意思意思吧？你"
                        "説十兩黃金怎麼樣？當然多些我也不反對。");
                return 1;
        }

        if( ob->query_tongren() && query("no_identify", ob) )
        {
                if (! objectp(obj = ZHOUTIAN_D->identify_tongren(me, ob)))
                {
                        command("say 你的物品乃我所從未見過，叫巫師來處理吧。");
                        return 1;
                }
                obj->move(me, 1);
                command("say 行了，你的衝穴銅人我給鑑定完了，拿去吧。");
                delete_temp("zhangpaid/張天師", me);
                return 1;
        }

        if( ob->is_tessera() && query("no_identify", ob) )
        {
                if (! objectp(obj = IDENTIFY_D->identify_ob(me, ob)))
                {
                        command("say 你的物品乃我所從未見過，叫巫師來處理吧。");
                        return 1;
                }
                message("vision", sort_string(HIM + name() + "從口袋中摸出一張黃色"
                                "的符紙，抽出背後的桃木劍，將那符紙點燃了，蓋在" +
                                ob->name() + HIM "上，然後口中唸唸有詞：“太上老君"
                                "急急如律賜令！”説罷一抖掌中劍，喝道：“疾”！\n" NOR, 64),
                                environment());
                tell_object(me, HIC "你感受" + ob->name() + HIC"發生了不可言喻的變化。\n" NOR);

                destruct(ob);
                obj->move(me, 1);
                delete("no_identify", obj);
                command("say 行了，你的寶物我給鑑定完了，拿去吧。");
                delete_temp("zhangpaid/張天師", me);
                return 1;
        }

        if( stringp(query("magic/imbue_ob", ob)) )
        {
                command("say 嗯...我看看，應該用" +
                        query("magic/imbue_ob", ob)->name()+
                        CYN "浸入它才能進一步激發它的潛力。" NOR);
                delete_temp("zhangpaid/張天師", me);
                return 1;
        }

        if( mapp(query("magic/imbue_ok", ob)) )
        {
                command("say 哦！我看它現在已經不需要在浸入了，"
                        "要發揮潛力得用別的法子了。\n");
                return 1;
        }

        if (! ob->is_item_make())
        {
                command("heng");
                command("say 這...這...我看還是算了吧！");
                return 1;
        }

        if( ob->item_owner() != query("id", me) )
        {
                command("kick"+query("id", me));
                command("say 你以為本山人的仙術是矇事的啊，這分明不是你的！");
                return 1;
        }

        if( query("can_summon/"+query("id", ob), me) )
        {
                if (ob->weapon_level() > 1)
                {
                        command("poor"+query("id", me));
                        command("say 它現在還不到浸入的時候..."
                                "你要先聖化它才行啊！");
                } else
                {
                        command("kok"+query("id", me));
                        command("say 你和它已經有緣了！我説你的"
                                "記性怎麼這麼差？");
                }
                return 1;
        }

        message("vision", sort_string(HIM + name() + "從口袋中摸出一張黃色"
                                "的符紙，抽出背後的桃木劍，"
                                "將那符紙點燃了，掃過" + ob->name() + HIM "，然"
                                "後用桃木劍穿了，手舞足蹈，口中唸唸有詞："
                                "“太上老君急急如律賜令！”説罷一抖掌中劍，"
                                "喝道：“疾”！\n" NOR, 64), environment());
        message_vision("焰光劃出一道光華，$N發了發呆，也不知道算是怎麼回事。\n",
                       me);
        command("say 行了，行了！你可以走了。");
        delete_temp("zhangpaid/張天師", me);
        set("can_summon/"+query("id", ob), base_name(ob), me);
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/kaiguang");
        log_file("static/item", sprintf("%s %s sancitfy %s(%s)\n",
                        log_time(), log_id(me),
                        filter_color(ob->name(1)),query("id", ob)));
        return 1;
}

int accept_object(object who, object ob)
{
        if( !query("money_id", ob) )
        {
                command("say 這玩藝我可沒啥興趣！");
                return 0;
        }

        if (ob->value() < 50000)
        {
                command("say 算是給觀裏的香火麼？那我就收下了！");
                return 1;
        }

        if (ob->value() < 100000)
        {
                command("say 唉！看你也算有點心意，我就替你開一次光吧！");
                set_temp("zhangpaid/張天師", 1, who);
                destruct(ob);
                return 1;
        }

        command("say 好...好...這麼照顧本觀，我能幫你點什麼？");
        set_temp("zhangpaid/張天師", 1, who);
        destruct(ob);
        return 1;
}

void fight_ob(object ob)
{
        ::fight_ob(ob);
        message_vision("$N冷笑一聲，道：“這年頭，什麼人都有。”説完伸手一指$n。\n",
                       this_object(), ob);
        ob->unconcious();
}

int accept_fight(object who)
{
        command("say 沒興趣。");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是眼前一花，看不太清楚。\n");
}

void receive_damage(string type, int n)
{
        return;
}

void receive_wound(string type, int n)
{
        return;
}

string ask_tianjidao()
{
        object *obs;
        object ob;
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "你的先天屬性還不足以修煉天極道，我看你還是先回去吧。\n";


        if( query("reborn/times", me)<3 )
                return "走開，走開，沒看我正忙嗎？\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                return "閣下武功已經獨步天下，何必如此貪心?\n";

        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此貪心！\n";
                                        
        // 已經完成任務
        if( query("lunhui-sword_quest/tianjidao/finish", me) )
                return "呵呵，不錯不錯，上次那些天蠶絲解了老夫燃眉之急啊。\n";

        // 分配任務
        if( !query("lunhui-sword_quest/tianjidao/give_quest", me) )
        {
                command("shake");
                command("say 不久前，老夫將借來的一件天蠶寶甲給弄丟了，不知如何是好？");
                command("say 如果能蒐集到30根天蠶絲，老夫倒是有辦法重新制作一。");
                command("不過……");
                command("tan");
                command("say 那天蠶絲並非凡物，只有天山頂峯的天蠶身才有，看來這次真是闖大禍了！");
                command("look"+query("id", me));
                command("say 閣下如果能蒐集到30根天蠶絲給老夫，老夫這裏倒是有一些厲害的武功可以傳授給你。");
                tell_object(me, this_object()->name() + HIG "讓你幫他蒐集30根天蠶絲，趕快去吧！\n" NOR);
                set("lunhui-sword_quest/tianjidao/give_quest", 1, me);
                me->save();
                return "怎麼樣，考慮考慮？";
        }
        
        // 完成任務
        
        if (! objectp(ob_hlp = present("tiancan si", me)))
                return "怎麼樣，30根天蠶絲蒐集夠了嗎？\n";
                
        if (base_name(ob_hlp) != "/clone/quarry/item/cansi2")
                return "怎麼樣，30根天蠶絲蒐集夠了嗎？\n";
                
        obs = all_inventory(me);
        obs = filter_array(obs, (: base_name($1) == "/clone/quarry/item/cansi2" :));
        if( sizeof(obs) < 30 )
                return "怎麼樣，30根天蠶絲蒐集夠了嗎？\n";
                
        for (i = 0; i < 30; i++)
        {
                ob = obs[i];
                obs[i] = 0;
                destruct(ob);
        }
        
        command("hehe");
        command("nod");
        command("say 既然你幫我了這個忙，好！老夫也遵守諾言，傳你「天極道」……");
        
        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳邊悄悄説了幾句，然後又拿出一本書，指指點點，"
                     "$n" HIC "不住地點頭，忽而眉頭深鎖，忽而低頭沉思 ……\n良久，$n" HIC "大笑一聲，似乎"
                     "對剛才的疑慮有所頓悟。\n", this_object(), me);
                        
        tell_object(me, HIG "恭喜你領悟了「天極道」劍法，目前等級為10級。\n");
        me->set_skill("tianji-dao", 10);
        set("lunhui-sword_quest/tianjidao/finish", 1, me);
        
        return "多謝了！";
        
                
}
