// moye.c  莫邪
// Written by Doing Lu  1998/11/2

inherit NPC;
inherit F_NOCLONE;

#include <ansi.h>

int     ask_me();
int     no_money();

#define ITEM_TYPE       0
#define ITEM_STYPE      1
#define ITEM_UNIT       2
#define ITEM_WEIGHT     3
#define ITEM_POINT      4
#define ITEM_PROP       5

string ask_jinlan();
nosave mapping item_type = ([
//      類型        道具類別  繼承文件    單位  分量 點數 特殊變量
        "刀"   : ({ "weapon", "blade",    "把", 150, 100, 0, }),
        "劍"   : ({ "weapon", "sword",    "柄", 150, 100, 0, }),
        "棍"   : ({ "weapon", "club",     "根", 150, 100, 0, }),
        "杖"   : ({ "weapon", "staff",    "根", 150, 100, 0, }),
        "錘"   : ({ "weapon", "hammer",   "把", 350, 100, 0, }),
        "斧"   : ({ "weapon", "axe",      "把", 220, 100, 0, }),
        "鞭"   : ({ "weapon", "whip",     "根", 150, 100, 0, }),
        "短兵" : ({ "weapon", "dagger",   "支", 30,  100, 0, }),
        "暗器" : ({ "weapon", "throwing", "把", 30,  100, 0, }),
        "護甲" : ({ "armor",  "armor",    "張", 150, 80,
                     ([ "armor_prop" : ([ "parry"   : "apply_armor() / 15 + 1",
                                          "armor"   : "apply_armor()",
                                       ]),
                      ]) }),
        "戰衣" : ({ "armor",  "cloth",    "件", 200, 100, 0, }),
        "靴子" : ({ "armor",   "boots",   "雙", 60,  40,
                     ([ "armor_prop" : ([ "dodge"   : "apply_armor() / 10 + 1",
                                          "armor"   : "apply_armor()",
                                       ]),
                      ]) }),
        "頭盔" : ({ "armor",  "head",     "頂", 75,  50,  0, }),
        "腰帶" : ({ "armor",  "waist",    "條", 80,  40,  0, }),
        "護腕" : ({ "armor",  "wrists",   "對", 50,  25,
                     ([ "armor_prop" : ([ "sword"   : "apply_armor() / 6 + 1",
                                          "staff"   : "apply_armor() / 6 + 1",
                                          "blade"   : "apply_armor() / 6 + 1",
                                          "club"    : "apply_armor() / 6 + 1",
                                          "hammer"  : "apply_armor() / 6 + 1",
                                          "whip"    : "apply_armor() / 6 + 1",
                                          "dagger"  : "apply_armor() / 6 + 1",
                                          "stick"   : "apply_armor() / 6 + 1",
                                          "unarmed" : "apply_armor() / 6 + 1",
                                          "claw"    : "apply_armor() / 6 + 1",
                                          "cuff"    : "apply_armor() / 6 + 1",
                                          "hand"    : "apply_armor() / 6 + 1",
                                          "strike"  : "apply_armor() / 6 + 1",
                                          "finger"  : "apply_armor() / 6 + 1",
                                          "parry"   : "apply_armor() / 6 + 1",
                                          "whip"    : "apply_armor() / 6 + 1",
                                          "armor"   : "apply_armor()",
                                       ]),
                      ]) }),
        "簫"   : ({ "weapon", "xsword",   "支", 30,  100, 0, }),
        "鐵掌" : ({ "armor",  "hands",    "雙", 45,  100,
                    ([ "armor_prop" : ([  "hand"   : "10",
                                          "strike" : "10",
                                          "unarmed_damage" : "apply_damage()",
                                          "armor"  : "10",
                                       ]),
                     ]) }),
        "護手" : ({ "armor",  "hands",    "雙", 40,  100,
                    ([ "armor_prop" : ([  "unarmed": "10",
                                          "cuff"   : "10",
                                          "unarmed_damage" : "apply_damage()",
                                          "armor"  : "10",
                                       ]),
                     ]) }),
        "指套" : ({ "armor",  "finger",   "套", 35,  100,
                    ([ "armor_prop" : ([  "claw"   : "10",
                                          "finger" : "10",
                                          "unarmed_damage" : "apply_damage()",
                                          "armor"  : "10",
                                       ]),
                     ]) }),
]);

void create()
{
        set_name("莫邪", ({ "mo ye", "moye", "mo" }));
        set("long", "她長得清美秀麗，一副不食人間煙火的模樣。她就是鑄劍大師干將的妻子。\n" );

        set("nickname", HIY "劍仙" NOR);
        set("gender", "女性");
        set("attitude", "friendly");

        set("age", 1525);
        set("shen_type", 0);

        set("str", 1000);                       // 保證不會因為負荷過大而接受不了東西

        set("inquiry", ([
/*
                "煉製" : (: ask_me :),
                "鑄劍" : (: ask_me :),
                "煉劍" : (: ask_me :),
                "煉刀" : (: ask_me :),
                "煉杖" : (: ask_me :),
                "煉鞭" : (: ask_me :),
                "煉棍" : (: ask_me :),
                "煉甲" : (: ask_me :),
                "打造" : (: ask_me :),
                "鑄造" : (: ask_me :),
                "製造" : (: ask_me :),
                "打製" : (: ask_me :),
                "定製" : (: ask_me :),
                "定做" : (: ask_me :),
                "定造" : (: ask_me :),
                "兵器" : (: ask_me :),
                "道具" : (: ask_me :),
                "裝備" : (: ask_me :),
                "武器" : (: ask_me :),
                "刀劍" : (: ask_me :),
                "裝甲" : (: ask_me :),

                "沒錢" : (: no_money :),
                "錢不夠":(: no_money :),
                "等會" : (: no_money :),
*/
                "錦鑭袈裟" : (: ask_jinlan :),

/*
                "銷燬" : "那你就把東西給干將，他來做主。",
                "退貨" : "那你就把東西給干將，他來做主。",
                "原料" : "煉製道具可不能沒有原料啊，要想煉製好武器就得有"
                         "海底金母一類的東西。\n          要想煉製好防具就"
                         "得有寒絲羽竹那些東西。這些原料很難找，可遇不可求啊！\n",
                "價格" : "你把原料給我看看(show)，我就能估摸出一個價錢。",
*/
        ]));

        setup();

        set("startroom", "/d/item/xiaowu");
        check_clone();
        if (! this_object()) return;

        carry_object("/clone/misc/cloth")->wear();
}
// 製作錦鑭袈裟
string ask_jinlan()
{
        object me = this_player();
        object ob_jinzhipg, ob_yinzhipg, ob_liangzhipg, ob_xiangbianpg, ob_hongzhipg;
        object ob_lanzhipg, ob_foguangbz, ob_shenzhizs, ob_shenzhifc, ob_shenzhisj, ob_shenzhimn;
        object ob;
        
        int i;
        
        if ( query("reborn/times", me) < 3 )
                return "你好像還沒有輪迴轉世吧，看來這錦鑭袈裟並不適合你。\n";

        // 看是否有可取錦鑭袈裟標誌，並且時間超過了24小時
        if (query("badao_quest/qu_jiasha", me))
        {
                // 可以取袈裟了
                if (time() - query("badao_quest/qu_jiasha", me) > 0)
                {
                        ob = new("/clone/armor/jinlan-jiasha");
                        
                        // 如果掉在地上設置10分鐘內其他人不能揀                 
                        set("who_get", ([
                                "id"     : query("id", me),
                                "time"   : 600,
                        ]), ob);
                        ob->move(me, 1);
                        command("smile " + query("id", me));
                        command("say 閣下來得正好，你要的東西我已經做好了，請收下吧！");
                        message_vision(HIC "$N" HIC "拿出" + ob->name() + HIC "給$n" HIC "。\n", 
                                       this_object(), me); 
                        delete("badao_quest/qu_jiasha", me);
                        me->save();
                        
                        return "好了，你我從此兩不相欠，保重！\n";
                }
                else
                        return "你的錦鑭袈裟還沒有製作完成呢，請 " + HIY + 
                               chinese_number((query("badao_quest/qu_jiasha", me) - time()) / 3600) + 
                               NOR + CYN " 個小時後再來吧。\n";
                
        }

        // 需要材料
          /*
           *金質皮革 10 張
           *銀質皮革 10 張
           *亮質皮革 10 張
           *鑲邊皮革 10 張
           *紅質皮革 10 張
           *藍質皮革 10 張
           *佛光寶珠 10 粒
           *神之鑽石 1  粒
           *神之瑪瑙 1  粒
           *神之水晶 1  粒
           *神之翡翠 1  粒
           */
       
        command("nod");
        command("say 天下間，只有在下能製作錦鑭袈裟，不過需要一些特別的材料：");
        message_vision(HIM  + "\n"
                "*金質皮革 10 張\n"
                "*銀質皮革 10 張\n"
                "*亮質皮革 10 張\n"
                "*鑲邊皮革 10 張\n"
                "*紅質皮革 10 張\n"
                "*藍質皮革 10 張\n"
                "*佛光寶珠 10 粒\n"
                "*神之鑽石 5  粒\n"
                "*神之瑪瑙 5  粒\n"
                "*神之水晶 5  粒\n"
                "*神之翡翠 5  粒\n"
                "還有手工費用 黃金 10 萬兩（YSG）\n" NOR, this_object());
        command("say 如果你這些材料都備齊了的話就來找我吧！");
        
        if (! query_temp("want_make_jinlanjiasha", me))
        {
                set_temp("want_make_jinlanjiasha", 1, me);
                return "怎麼樣？如果你考慮好了，再來找我！\n";          
        }

        // 需要金質皮革 10 
        if (! objectp(ob_jinzhipg = present("jinzhi pige", me)))
                return "你好像還沒備齊金質皮革吧？\n";                  
        if (base_name(ob_jinzhipg) != "/clone/quarry/item/combine/jinzhi-pige")
                return "你好像還沒備齊金質皮革吧？\n";

        if (ob_jinzhipg->query_amount() >= 10)
        {
                //ob_jinzhipg->add_amount(-10);
                //if (ob_jinzhipg->query_amount() < 1)destruct(ob_jinzhipg);
        }
        else
        {
                return "怎麼樣，10張金質皮革備齊了嗎？\n";
        }


        // 需要銀質皮革 10 
        if (! objectp(ob_yinzhipg = present("yinzhi pige", me)))
                return "你好像還沒備齊銀質皮革吧？\n";                  
        if (base_name(ob_yinzhipg) != "/clone/quarry/item/combine/yinzhi-pige")
                return "你好像還沒備齊銀質皮革吧？\n";

        if (ob_yinzhipg->query_amount() >= 10)
        {
                //ob_yinzhipg->add_amount(-10);
                //if (ob_yinzhipg->query_amount() < 1)destruct(ob_yinzhipg);
        }
        else
        {
                return "怎麼樣，10張銀質皮革備齊了嗎？\n";
        }

        // 需要亮質皮革 10 
        if (! objectp(ob_liangzhipg = present("liangzhi pige", me)))
                return "你好像還沒備齊亮質皮革吧？\n";                  
        if (base_name(ob_liangzhipg) != "/clone/quarry/item/combine/liangzhi-pige")
                return "你好像還沒備齊亮質皮革吧？\n";

        if (ob_liangzhipg->query_amount() >= 10)
        {
                //ob_liangzhipg->add_amount(-10);
                //if (ob_liangzhipg->query_amount() < 1)destruct(ob_liangzhipg);
        }
        else
        {
                return "怎麼樣，10張亮質皮革備齊了嗎？\n";
        }

        // 需要藍質皮革 10 
        if (! objectp(ob_lanzhipg = present("lanzhi pige", me)))
                return "你好像還沒備齊藍質皮革吧？\n";                  
        if (base_name(ob_lanzhipg) != "/clone/quarry/item/combine/lanzhi-pige")
                return "你好像還沒備齊藍質皮革吧？\n";
                
        if (ob_lanzhipg->query_amount() >= 10)
        {
                //ob_lanzhipg->add_amount(-10);
                //if (ob_lanzhipg->query_amount() < 1)destruct(ob_lanzhipg);
        }
        else
        {
                return "怎麼樣，10張藍質皮革備齊了嗎？\n";
        }

        // 需要紅質皮革 10 
        if (! objectp(ob_hongzhipg = present("hongzhi pige", me)))
                return "你好像還沒備齊紅質皮革吧？\n";                  
        if (base_name(ob_hongzhipg) != "/clone/quarry/item/combine/hongzhi-pige")
                return "你好像還沒備齊紅質皮革吧？\n";

        if (ob_hongzhipg->query_amount() >= 10)
        {
                //ob_hongzhipg->add_amount(-10);
                //if (ob_hongzhipg->query_amount() < 1)destruct(ob_hongzhipg);
        }
        else
        {
                return "怎麼樣，10張紅質皮革備齊了嗎？\n";
        }               

        // 需要鑲邊皮革 10 
        if (! objectp(ob_xiangbianpg = present("xiangbian pige", me)))
                return "你好像還沒備齊鑲邊皮革吧？\n";                  
        if (base_name(ob_xiangbianpg) != "/clone/quarry/item/combine/xiangbian-pige")
                return "你好像還沒備齊鑲邊皮革吧？\n";

        if (ob_xiangbianpg->query_amount() >= 10)
        {
                //ob_xiangbianpg->add_amount(-10);
                //if (ob_xiangbianpg->query_amount() < 1)destruct(ob_xiangbianpg);
        }
        else
        {
                return "怎麼樣，10張鑲邊皮革備齊了嗎？\n";
        }
        
        // 需要佛光寶珠 10 
        if (! objectp(ob_foguangbz = present("foguang baozhu", me)))
                return "你好像還沒備齊佛光寶珠吧？\n";                  
        if (base_name(ob_foguangbz) != "/clone/quarry/item/combine/foguang-baozhu")
                return "你好像還沒備齊佛光寶珠吧？\n";

        if (ob_foguangbz->query_amount() >= 10)
        {
                //ob_foguangbz->add_amount(-10);
                //if (ob_foguangbz->query_amount() < 1)destruct(ob_foguangbz);
        }
        else
        {
                return "怎麼樣，10個佛光寶珠備齊了嗎？\n";
        }

        // 需要神之水晶 1 
        if (! objectp(ob_shenzhisj = present("magic crystal", me)))
                return "你好像還沒備齊神之水晶吧？\n";                  
        if (base_name(ob_shenzhisj) != "/clone/gift/mcrystal")
                return "你好像還沒備齊神之水晶吧？\n";                   
                        
        // 需要神之翡翠 1
        if (! objectp(ob_shenzhifc = present("magic jade", me)))
                return "你好像還沒備齊神之翡翠吧？\n";                  
        if (base_name(ob_shenzhifc) != "/clone/gift/mjade")
                return "你好像還沒備齊神之翡翠吧？\n";
        
        // 需要神之鑽石 1 
        if (! objectp(ob_shenzhizs = present("magic diamond", me)))
                return "你好像還沒備齊神之鑽石吧？\n";                  
        if (base_name(ob_shenzhizs) != "/clone/gift/mdiamond")
                return "你好像還沒備齊神之鑽石吧？\n";
        
        // 需要神之瑪瑙 1 
        if (! objectp(ob_shenzhimn = present("magic agate", me)))
                return "你好像還沒備齊神之瑪瑙吧？\n";                  
        if (base_name(ob_shenzhimn) != "/clone/gift/magate")
                return "你好像還沒備齊神之瑪瑙吧？\n";   
        
        // 需要黃金10萬兩
        if (query("balance", me) < 100000)
                return "你好像沒有備齊10萬兩黃金吧。\n";       
 
        // 消耗材料
        ob_jinzhipg = present("jinzhi pige", me);
        ob_yinzhipg = present("yinzhi pige", me);
        ob_lanzhipg = present("lanzhi pige", me);
        ob_hongzhipg = present("hongzhi pige", me);
        ob_liangzhipg = present("liangzhi pige", me);
        ob_xiangbianpg = present("xiangbian pige", me);
        ob_foguangbz = present("foguang baozhu", me);
                
        ob_jinzhipg->add_amount(-10);
        if (ob_jinzhipg->query_amount() < 1)destruct(ob_jinzhipg);
        ob_yinzhipg->add_amount(-10);
        if (ob_yinzhipg->query_amount() < 1)destruct(ob_yinzhipg);
        ob_lanzhipg->add_amount(-10);
        if (ob_lanzhipg->query_amount() < 1)destruct(ob_lanzhipg);
        ob_hongzhipg->add_amount(-10);
        if (ob_hongzhipg->query_amount() < 1)destruct(ob_hongzhipg);
        ob_liangzhipg->add_amount(-10);
        if (ob_liangzhipg->query_amount() < 1)destruct(ob_liangzhipg);
        ob_xiangbianpg->add_amount(-10);
        if (ob_xiangbianpg->query_amount() < 1)destruct(ob_xiangbianpg);
        ob_foguangbz->add_amount(-10);
        if (ob_foguangbz->query_amount() < 1)destruct(ob_foguangbz);  

        ob_shenzhifc = present("magic jade", me);
        ob_shenzhizs = present("magic diamond", me);
        ob_shenzhimn = present("magic agate", me);
        ob_shenzhisj = present("magic crystal", me);
                
        destruct(ob_shenzhifc);
        destruct(ob_shenzhizs);
        destruct(ob_shenzhimn);
        destruct(ob_shenzhisj);
        
        addn("balance", -100000, me);                
        
        //log_file("badao_quest_jiasha", query("id". me) + " 製作錦鑭袈裟成功！\n");
        
        command("say 不錯，不錯，這些材料居然你都找齊了，拿我就先收下了。");
        command("say 既然你材料和工錢我都收了，這錦鑭袈裟就由我莫邪代勞吧。");
        command("say 不過，製作錦鑭袈裟耗時很長，閣下請於24小時後再來取吧。");
        
        // 設置24小時後可取錦鑭袈裟
        set("badao_quest/qu_jiasha", time() + 24 * 3600, me);
                
        tell_object(me, HIG "恭喜你，莫邪已經答應幫你製作錦鑭袈裟，請於24小時後來取(ask mo about 錦鑭袈裟)！\n" NOR);        
        
        delete_temp("want_make_jinlanjiasha", me);
        
        me->save();
        
        return "記住，可別忘了。\n";    
}


/*
void init()
{
        object me;

        // 清除詢問標誌
        if (! objectp(me = this_player()) || ! interactive(me))
                return;

        add_action("do_show", "show");
        add_action("do_answer", "answer");
        if( query_temp("item/status", me) == "item_gived" )
        {
                remove_call_out("greeting2");
                call_out("greeting2", 1, me);
        } else
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}
*/

void greeting(object me)
{
        if (objectp(me) && environment(me) == environment())
        {
                message_vision("$N笑着對$n説：你好，你是想打造道具"
                               "嗎？\n", this_object(), me);
        }
}

void greeting2(object me)
{
        if (objectp(me) && environment(me) == environment())
        {
                message_vision("$N對$n説：交錢就可以打造了哦。\n",
                               this_object(), me);
        }
}

int do_show(string arg)
{
        object  me;
        object  ob;
        string  msg;
        string  mat;
        int     power_point;
        int     value;
        int     n;

        me = this_player();
        if (! arg)
                return notify_fail("你想幹什麼，是要跳個舞麼？\n");

        mat = arg;
        power_point = 0;

        if (! objectp(ob = present(mat, me)))
                return notify_fail("算了吧，你身上沒有 " + mat + " 這種東西。\n");

        if( !query("material_attrib", ob) )
        {
                message_vision("$N一愣，對$n説道：這種東西也能用來煉"
                               "制，我沒聽説過。\n", this_object(), me);
        }

        power_point=query("power_point", ob);
        if (! power_point)
        {
                message_vision("$N仔細的看了看$n拿出的原料，歎道："
                               "這樣原料看來已經是鍛造不了了。\n",
                               this_object(), me);
                return 1;
        }
        value = power_point * 2 + 10;
        msg = sprintf("$N仔細看了看$n拿出的原料，説道：這種原料打造道具，\n" +
                      "只需要%s兩黃金，怎麼樣，我們價格很合理吧。要是沒問題"
                      "，請給我原料並付錢。\n", chinese_number(value));
        message_vision(msg, this_object(), me);

        return 1;
}

// 發出提示信息
int ask_me()
{
        message_vision("$N對$n説道："
                "你是要打造自己的道具嗎？\n"
                "我們這裏可以為你打造各種武器包括刀、劍、鞭、杖和護甲，都是第一流的。\n"
                "你先把原料給我看看(show)，我先估算一下價錢。如果你滿意"
                "咱們就一手交錢，一手交貨！\n", this_object(), this_player());
        return 1;
}

int no_money()
{
        object me;
        object ob;

        me = this_player();
        if( query_temp("item/status", me) == "item_gived" )
        {
                message_vision("$N打量了一下$n道：沒錢那就下次吧！\n",
                               this_object(), me);
                if (objectp(ob = query_temp("item/accept")))
                {
                        message_vision("$N把" + ob->name() +
                                       "交還給$n。\n", this_object(), me);
                        if (! ob->move(me))
                                ob->move(environment());
                }
                delete_temp("item");
                delete_temp("item", me);
                return 1;
        }

        message_vision("$N眼睛一瞪，對$n説道：沒錢？你沒錢關我啥事，"
                       "我又不是財神爺。\n", this_object(), me);
        return 1;
}

/*
// 接受定金
int accept_object(object me, object ob)
{
        string status;
        int    val;

        if( query("level", me)<10 )
        {
                message_vision("$N遺憾的對$n説：打造神兵利器必須人物等級達到10級方可。\n",
                               this_object(), me);
                return 0;
        }

        status = query_temp("item/status");
        if (status == "look_working")
        {
                message_vision("$N緊張的對$n説：別吵，干將正在幹活呢。\n",
                               this_object(), me);
                return 0;
        }

        if (status == "waiting")
        {
                if( query_temp("item/player_id") == query("id", me) )
                {
                        command("say 你好好和干將談，少打岔！");
                        return 0;
                }

                message_vision("$N對$n説：別吵，干將正在和顧客談話呢。\n",
                               this_object(), me);
                return 0;
        }

        if (status == "accept")
        {
                if( query_temp("item/player_id") != query("id", me) )
                {
                        command("say 我正在和別的客人商量呢，你先別添亂！");
                        return 0;
                }

                if( !query("money_id", ob) )
                {
                        command("say 你還是快點交錢吧，要是沒錢就明説！");
                        return 0;
                }
        }

        if( query("material_attrib", ob) && 
            query("power_point", ob) )
        {
                // 計算價值
                val=query("power_point", ob)*2+10;
                message_vision("$N對$n説道：很好，用這塊原料打造道具需要" +
                               chinese_number(val) + "兩黃金，交錢吧。\n",
                               this_object(), me);
                val *= 10000;
                if (wizardp(me))
                {
                        message_vision("$N仔細看了看$n，笑着説道：原"
                                       "來是巫師，那麼你隨便給點好了。\n",
                                       this_object(), me);
                        val = 1;
                }
                set("item/value", val, ob);
                set_temp("item/status", "item_gived", me);
                set_temp("item/value", val, me);
                set_temp("item/status", "accept");
                set_temp("item/player_id",query("id", me));
                set_temp("item/accept", ob);

                // 如果過一段時間沒有交款，還道具粗坯
                remove_call_out("time_out");
                call_out("time_out", 30, me, ob);
                return 1;
        }

        if( query("money_id", ob) )
        {
                object origin;
                mixed p;
                string *types;

                if( query_temp("item/status", me) == "answer_type" )
                {
                        message_vision("$N搖搖頭，對$n説：快説你要做什麼東西！\n",
                                       this_object(), me);
                        return 0;
                }

                if( query_temp("item/status", me) != "item_gived" )
                {
                        message_vision("$N把$n遞過去的" + ob->name() +
                                       "推了回來，道：無功不受祿！\n",
                                       this_object(), me);
                        return 0;
                }

                if( ob->value()<query_temp("item/value", me) )
                {
                        message_vision("$N對$n説：對不起，本店開張一"
                                       "千多年來，還沒有打過折扣。\n",
                                       this_object(), me);
                        return 0;
                }

                origin = query_temp("item/accept");
                if( (p=query("can_make", origin)) == "all" )
                {
                        types = keys(item_type);
                } else
                if (arrayp(p))
                        types = p;
                else
                if (stringp(p))
                        types = ({ p });

                p=query("not_make", origin);
                if (arrayp(p))
                        types -= p;
                else
                if (stringp(p))
                        types -= ({ p });

                set_temp("item/types", types);
                set_temp("item/money", ob);
                ob->move(this_object());

                message_vision("$N對$n説道：好，這就給你煉！你打算打"
                               "造什麼東西，請告訴我(answer 類型)！\n"
                               "（" + implode(types, "、") + "）\n",
                               this_object(), me);

                set_temp("item/status", "answer_type", me);
                return -1;
        }

        message_vision("莫邪眼睛一瞪，對$N説道：你給我這些東西幹什麼？我不要！\n", me);
        return 0;
}
*/

int do_answer(string arg)
{
        object money;
        object ob;
        object me;
        object ganjiang;

        me = this_player();
        if( query_temp("item/status", me) != "answer_type" )
                return 0;

        if (! arg)
                return notify_fail("你要回答什麼？\n");

        message_vision("$n對$N道：就打造" + arg + "吧！\n",
                       this_object(), me);

        if (member_array(arg, query_temp("item/types")) == -1 ||
            undefinedp(item_type[arg]))
        {
                message_vision("$N“啊秋”一下打了個噴嚏，一臉無辜的看着$n。\n",
                               this_object(), me);
                return 1;
        }

        // 如果幹將不在
        if (! objectp(ganjiang = present("gan jiang")))
        {
                message_vision("$N看了看四周，不禁一呆，説道：干將呢"
                               "？他不在，沒辦法做了...你改天再來吧。\n",
                               this_object());
                if (ob = query_temp("item/accept"))
                {
                        message_vision("$N把" + ob->name() + "交還給$n。\n",
                                       this_object(), me);
                        if (! ob->move(me))
                                ob->move(environment());
                }
                delete_temp("item");
                delete_temp("item", me);
                return 0;
        }

        if (objectp(money = query_temp("item/money")))
                destruct(money);
        delete_temp("item/money");
        set_temp("item/status", "look_working");
        set_temp("item/status", "waiting", me);
        ob = query_temp("item/accept");
        set("item/ctype", arg, ob);
        set("item/type", item_type[arg][ITEM_TYPE], ob);
        set("item/stype", item_type[arg][ITEM_STYPE], ob);
        set("item/unit", item_type[arg][ITEM_UNIT], ob);
        set("item/point",query("power_point",  ob)*item_type[arg][ITEM_POINT]/100, ob);
        set("item/power",query("power_special",  ob), ob);
        set("item/owner", me, ob);
        set("item/owner_id",query("id",  me), ob);
        set("item/owner_name", me->name(1), ob);
        set("item/wscale", item_type[arg][ITEM_WEIGHT], ob);
        set("item/prop", item_type[arg][ITEM_PROP], ob);
        message_vision("$N把" + ob->name() + "交給了$n。\n",
                       this_object(), ganjiang);
        if (! ob->move(ganjiang))
                error("Can move the object to ganjiang.");
        remove_call_out("time_out");
        ganjiang->accept_object(this_object(), ob);
        return 1;
}

void time_out(object me, object ob)
{
        object money;
        int at_present;

        money = query_temp("item/money");

        if (! objectp(me))
                me = find_player(query_temp("item/player_id"));

        if (! objectp(me) || environment(me) != environment())
        {
                command("say 奇怪，剛才那位客人呢？怎麼這就走了？\n");
                at_present = 0;
        } else
        {
                command("say 你慢慢猶豫吧，我可不能跟你耗着！想好再來吧！");
                at_present = 1;
        }

        delete_temp("item");
        if (objectp(me))
                delete_temp("item", me);

        if (money)
        {
                if (at_present)
                          command("give "+query("id", money)+
                                  " to "+query("id", me));

                if (environment(money) == this_object())
                        command("drop"+query("id", money));
        }

        if (ob)
        {
                if (at_present)
                          command("give "+query("id", ob)+
                                  " to "+query("id", me));

                if (environment(ob) == this_object())
                        command("drop"+query("id", ob));
        }
}
