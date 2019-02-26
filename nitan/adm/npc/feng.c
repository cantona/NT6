// 本程序用於店鋪拍賣，由WIZLELVEL權限以上的巫師來啟動
// 在啟動拍賣之前，首先請用cshshop指令初始化所有店鋪狀態
// 啟動進程有兩種方式：巫師手工操作、系統自動運行

// 如果是啟動了手工操作，在主持巫師發生如下狀況，自動進程將接管拍賣：
// 主持巫師離開拍賣場
// 主持巫師退線
// 主持巫師不進行任何拍賣操作超過規定時間
// 主持巫師斷線
// 主持巫師昏迷或者死亡

// 拍賣過程中本NPC物件的更新不會導致拍賣進程的中斷，比如update,dest & clone

#include <ansi.h>
#include <getconfig.h>

inherit NPC;
inherit F_SAVE;

#define WIZLEVEL 3 //  能夠啟動和執行拍賣的巫師等級
#define DISTANCE 8 //  拍賣中間隔的時間（秒）
#define DELAY 30   //  拍賣中主持巫師沒有進行任何動作的等待時間（秒）
                   //  超過這個時間，自動進程接管拍賣

string query_save_file();
int do_start(string arg);                // 啟動拍賣，不使用arg參數表示啟動手工進程
int do_auction(string arg);                // 指定拍賣的當前店鋪
int begin_auction();                        // 等待玩家競投的守護程序
int stop_auction();                        // 結束當前店鋪的拍賣
int do_jupai(string arg);                // 玩家競投中斷
int go_jupai();                                // 玩家競投的守護程序
int do_qiao();                                // 巫師宣價以及落棰
int do_auctionlist();                        // 查詢拍賣店鋪列表
int do_ban(string arg);                        // 取消|恢復 玩家拍賣資格
int finish_auction(string arg);                // 結束拍賣
void heart_beat();                        // 心跳線，手工拍賣守護進程
object check_operator();                // 檢查主持巫師狀態函數
int do_autoauction();                        // 將手工進程轉為自動進程
int last_time = 0;                        // 最後一次手工操作的時間
object operator;                        // 本變量記錄拍賣主持者

void create()
{
        seteuid(getuid());
        restore();

        set_name("鳳天南", ({ "feng tiannan", "feng", "tiannan" }));
        set("long", @LONG
他就是佛山五虎門掌門人鳳天南，當年憑一套
五虎棍法名震江湖。雖然為武林人士，但卻是
富甲一方。全天下各處都有他的產業。
LONG);
        set("title", "佛山五虎門掌門人");
        set("nickname", HIY "南霸天" NOR);
        set("channel_id","鳳天南");
        set("gender", "男性");
        set("age", 45);
        set("combat_exp", 800000);
        set("shen", -1);
        set("attitude", "friendly");

        set("max_qi", 3000);
        set("max_jing", 2500);
        set("neili", 3500);
        set("max_neili", 3500);

        set_skill("force", 300);
        set_skill("unarmed", 300);
        set_skill("sword", 300);
        set_skill("parry", 300);
        set_skill("dodge", 300);

        set("apply/attack", 100);
        set("apply/defense", 100);

        setup();

        if (! clonep(this_object()))
        {
                move("/d/foshan/pmc");
                message_vision(CYN "\n$N" CYN "走了過來，看了看周"
                               "圍，陰笑兩聲。\n" NOR, this_object());
                set("startroom", "/d/foshan/pmc");
        }

        carry_object("/clone/cloth/cloth")->wear();
        set_heart_beat(1);
}


void init()
{
        ::init();
        if (wiz_level(this_player()) >= WIZLEVEL)
        {
                add_action("do_auction", ({ "auction", "paimai" }));
                add_action("do_start","start");
                add_action("do_qiao", "qiao");
                add_action("do_ban", "ban");
                add_action("finish_auction", "finish");
                add_action("do_autoauction", ({ "auto", "autopaimai"}));
        }

        add_action("do_auctionlist", ({ "list", "paimailist" }));
        add_action("do_jupai", "jupai");
}

//  存盤文檔
string query_save_file()
{
        return "/data/npc/feng";
}

int do_start(string arg)
{
        object ob,me;
        int i;
        string *shop_list;
        string msg;
        mapping *all_shop;
        mapping begin_shop;
        mapping end_shop;

        me = this_player();
        ob = this_object();

        if( query("auction_start", ob) && !query("auction_end", ob) )
                return notify_fail("現在正在拍賣中，無法重新開始。\n");

        if (! SHOP_D->is_inited())
        {
                msg = "店鋪尚未全部初始化，請在進行拍賣之前將所有"
                      "店鋪初始化。\n";
                write(msg);
                return 1;
        } else
        {
                shop_list = ({});
                begin_shop = ([]);
                end_shop = ([]);

                remove_call_out("do_auction");
                remove_call_out("begin_auction");
                remove_call_out("stop_auction");
                remove_call_out("go_jupai");
                remove_call_out("finish_auction");

                all_shop = SHOP_D->query_shop();
                msg = HIC "成功初始化拍賣程序，待拍賣店鋪列表： \n" NOR;
                msg += HIC "--------------------------------------\n" NOR;
                for (i = 0;i < sizeof(all_shop);i++)
                {
                        shop_list += ({ all_shop[i]["id"] });
                        begin_shop[all_shop[i]["id"]] = all_shop[i]["price"];
                        msg += sprintf(HIY "%-20s" HIW "\t%d兩黃金\n" NOR,all_shop[i]["id"],all_shop[i]["price"]);
                }
                msg += HIC "--------------------------------------\n" NOR;
                msg += WHT "總共有" + chinese_number(sizeof(all_shop)) + "家店鋪。\n" NOR;

                delete("owner", ob);
                delete("shop_list", ob);
                delete("begin_shop", ob);
                delete("end_shop", ob);
                delete("auction_end", ob);
                delete("now_auction", ob);
                delete("temp_owner", ob);
                delete("wait_jupai", ob);
                delete("on_jupai", ob);
                delete("can_finish", ob);

                set("auction_start", 1, ob);
                set("shop_list", shop_list, ob);
                set("begin_shop", begin_shop, ob);
                set("end_shop", end_shop, ob);

                if (arg)
                {
                        CHANNEL_D->do_channel(ob, "sys", "店鋪拍賣系統由" + me->name(1) +
                                                  "成功啟動。運行模式：自動。");

                        // 拍賣設置為自動運行
                        set("operator", "fengtiannan", ob);

                        msg += HIR "您選擇了通過" HIW "自動運行" HIR "的方式來啟"
                               "動拍賣進程。\n\n" NOR;
                        write(msg);

                        message_vision(CYN "$N" CYN "哈哈大笑道：既然各位都準備好"
                                       "了，那麼咱們就開始拍賣吧。\n" NOR, ob);
                        operator = ob;
                        ob->save();
                        call_out("do_auction", 0, "automatic");
                } else
                {
                        CHANNEL_D->do_channel(ob, "sys", "店鋪拍賣系統由" + me->name(1) +
                                                  "成功啟動，運行模式：人工。");

                        // 拍賣設置為手工運行
                        set("operator",query("id",  me), ob);

                        msg += HIR "您選擇了通過" HIW "人工操作" HIR "的方式來啟"
                               "動拍賣進程。\n\n" NOR;
                        msg += WHT "拍賣的指令為(" HIY "auction <店鋪ID>" NOR +
                               WHT ")。\n" NOR;
                        msg += WHT "您可以用(" HIY "auto" NOR + WHT ")指令"
                               "來將拍賣進程轉成自動運行。\n" NOR;
                        write(msg);

                        message_vision(CYN "$N" CYN "擦了擦汗，賠笑道：這次的拍賣"
                                       "由$n" CYN "親自主持。\n" NOR, ob, me);
                        message_vision(HIC "$N" HIC "乾笑兩聲，將手中的錘子鄭重交"
                                       "給$n" HIC "。\n" NOR, ob, me);
                        operator = me;

                        // 記錄該次操作時間
                        last_time = time();

                        // 啟動手工拍賣守護進程
                        set_heart_beat(1);
                        ob->save();
                }
        }
        return 1;
}

int do_auction(string arg)
{
        object ob;
        string *shop_list;
        string now_shop, msg;
        string *shop_key;
        mapping begin_shop;
        int i, now_price;

        if (! query("auction_start") || query("auction_end"))
                return notify_fail("現在並沒有在進行拍賣。\n");

        if (! arg)
                return notify_fail("指令格式：auction <店鋪ID>\n");

        if (query("now_shop"))
                return notify_fail("現在正在進行" + query("now_shop") +
                                   "店鋪的拍賣，您彆着急。\n");

        ob = this_object();

        if (ob != operator && this_player() != operator)
                return notify_fail("現在的拍賣正在由" + operator->name(1) +
                                   "主持進行中。\n");

        remove_call_out("do_auction");
        remove_call_out("finish_auction");
        remove_call_out("begin_auction");

        shop_list = query("shop_list");
        begin_shop = query("begin_shop");

        //  非自動的
        if (ob != operator)
        {
                // 已經全部拍賣完畢了
                if (sizeof(shop_list) < 1)
                {
                        set("can_finish", 1);
                        save();
                        return notify_fail(WHT "所有店鋪都已經拍賣結束了，您現"
                                           "在可以結束(" HIY "finish" NOR + WHT
                                           ")拍賣了。\n" NOR);
                }

                //  提交的參數錯誤，重新顯示所有待拍賣店鋪列表
                if (! begin_shop[arg])
                {
                        msg = HIR "對不起，您所提交的店鋪並不存在。\n\n" NOR;
                        msg += WHT "等待拍賣的店鋪列表： \n" NOR;
                        msg += HIC "--------------------------------------\n" NOR;
                        shop_key = keys(begin_shop);

                        for (i = 0; i < sizeof(shop_key); i++)
                                msg += sprintf(HIW "%-20s" HIY "\t%d兩黃金\n" NOR,
                                               shop_key[i],
                                               begin_shop[shop_key[i]]);

                        msg += HIC "--------------------------------------\n" NOR;
                        msg += WHT "總共有" + chinese_number(sizeof(shop_key)) +
                               "家店鋪可以拍賣。\n\n";
                        write(msg);
                        return 1;
                }
                // 當前拍賣店鋪
                now_shop = arg;
        } else        // 自動拍賣
        {
                // 全部店鋪都已經拍賣完畢
                if (sizeof(shop_list) < 1)
                {
                        set("can_finish", 1, ob);
                        ob->save();
                        // 調用結束拍賣程序
                        call_out("finish_auction", 0, "automatic");
                        return 1;
                }
                // 當前拍賣店鋪
                now_shop = shop_list[random(sizeof(shop_list))];
        }

        // 從待拍店鋪中刪除當前拍賣店鋪
        shop_list -= ({ now_shop });
        now_price = query("begin_shop/" + now_shop);
        set("wait_jupai", 1, ob);
        set("shop_list", shop_list, ob);
        delete("begin_shop/"+now_shop, ob);
        set("now_shop", now_shop, ob);
        set("now_price", now_price, ob);
        ob->save();

        CHANNEL_D->do_channel(ob, "sys", "現在開始拍賣" + now_shop + "店鋪。");

        message_vision(HIW "\n$N" HIW "大聲道：現在開始拍賣『" HIC +
                       now_shop + HIC "店鋪" HIW "』底價為" +
                       chinese_number(now_price) + "兩黃金，有意者請"
                       "舉牌。\n" NOR, operator);

        // 自動拍賣
        if (ob == operator)
                call_out("begin_auction", DISTANCE);
        else
                // 記錄該次操作的時間
                last_time = time();

        return 1;
}

int begin_auction()
{
        string now_shop;
        int now_price,m;
        object ob;

        ob = this_object();

        m=query("wait_jupai", ob);

        // 已經有人開始舉牌
        if (! m)
                return 1;

        remove_call_out("begin_auction");
        remove_call_out("stop_auction");

        now_shop = query("now_shop");
        now_price = query("now_price");

        m += 1;
        set("wait_jupai", m, ob);
        ob->save();

        switch (random(3))
        {
        case 0:

                message_vision(CYN "\n$N" CYN "接着道：正在開始拍賣" HIC +
                               now_shop + NOR + CYN "店鋪。報價為" YEL +
                               chinese_number(now_price) + "兩黃金"
                               CYN "第" + chinese_number(m) + "次。\n" NOR,
                               operator);
                break;

        case 1:
                message_vision(CYN "\n$N" CYN "看了看周圍大聲道：現在"
                               YEL + chinese_number(now_price) + "兩黃金"
                               CYN "第" + chinese_number(m) + "次，"
                               YEL + chinese_number(now_price) + "兩黃金"
                               CYN "第" + chinese_number(m) + "次。拍賣" +
                               HIC + now_shop + NOR + CYN "店鋪。\n" NOR,
                               operator);
                break;

        default:
                message_vision(CYN "\n$N" CYN "乾咳兩聲，大聲道：現在為"
                               YEL + chinese_number(now_price) + "兩黃金"
                               CYN "第" + chinese_number(m) + "次，拍賣" +
                               HIC + now_shop + NOR + CYN "店鋪，欲購"
                               "者從速。\n" NOR, operator);
                break;
        }

        switch (random(4))
        {
        case 0:

                message_vision(CYN "$N" CYN "環顧了一下四周，接着説道：請有"
                               "意者舉牌(" HIY "jupai" NOR + CYN ")。\n" NOR,
                               operator);
                break;

        case 1:
                message_vision(CYN "$N" CYN "皺了皺眉頭，説道：有人願意購買"
                               "麼？請即時舉牌(" HIY "jupai" NOR + CYN ")。\n"
                               NOR, operator);
                break;

        case 2:
                message_vision(CYN "$N" CYN "微笑道：各位考慮好了麼？有人願"
                               "意購舉牌(" HIY "jupai" NOR + CYN ")出價麼？\n"
                               NOR, operator);
                break;

        default:
                message_vision(CYN "$N" CYN "清了清嗓子，繼續説道：拍賣正在"
                               "進行，請各位舉牌(" HIY "jupai" NOR + CYN ")示"
                               "意。\n" NOR, operator);
                break;
        }

        // 自動拍賣
        if (operator == ob)
        {
                if (! (m >= 3))
                        call_out("begin_auction",DISTANCE);
                else
                        call_out("stop_auction",DISTANCE);
        // 手工拍賣
        } else
                // 記錄最後一次操作的時間
                last_time = time();
}

int stop_auction()
{
        string now_shop, temp_owner, *owner, *shop_list, msg, *shop_key;
        mapping begin_shop, end_shop, *shop_record, record;
        object ob, the_owner;
        int i, now_price;

        remove_call_out("stop_auction");
        remove_call_out("go_jupai");
        remove_call_out("begin_auction");
        remove_call_out("finish_auction");
        remove_call_out("do_auction");

        msg = "";
        ob = this_object();
        owner = query("owner");
        temp_owner = query("temp_owner");
        shop_list = query("shop_list");
        begin_shop = query("begin_shop");
        end_shop = query("end_shop");
        now_shop = query("now_shop");
        now_price = query("now_price");

        if (! mapp(end_shop) || sizeof(end_shop) < 1)
                end_shop = ([]);

        if (! arrayp(owner) || sizeof(end_shop) < 1)
                owner = ({});

        if (query("wait_jupai"))
        {
                message_vision(BEEP + HIY "\n$N" HIY "舉起手中的小木棰用"
                               "力的一敲，只聽得『當』的一聲巨響。\n" NOR,
                               operator);
                message_vision(HIY "$N" HIY "大聲宣佈道：現在" HIC + now_shop +
                               HIY "店鋪的所有權拍賣流標了。\n" NOR,
                               operator);

                end_shop[now_shop] = 0;
                delete("wait_jupai", ob);
                delete("now_shop", ob);
                set("end_shop", end_shop, ob);
                ob->save();

                // 自動拍賣
                if (operator == ob)
                {
                        // 所有店鋪拍賣結束
                        if (sizeof(shop_list) < 1)
                        {
                                set("can_finish", 1);
                                save();
                                call_out("finish_auction", 0, "automatic");
                                return 1;
                        }
                        call_out("do_auction", 1, "automatic");
                } else
                {
                        // 所有店鋪拍賣結束
                        if (sizeof(shop_list) < 1)
                        {
                                set("can_finish", 1);
                                save();
                                tell_object(operator, WHT "所有店鋪都已經拍賣結"
                                            "束，您現在可以結束(" HIY "finish"
                                            NOR + WHT ")拍賣。\n"NOR);
                                return 1;
                        }

                        msg += HIC "等待拍賣的店鋪列表： \n" NOR;
                        msg += HIC "≡" HIY "──────────────" HIC "≡\n" NOR;
                        shop_key = keys(begin_shop);

                        for (i = 0; i < sizeof(shop_key); i++)
                                msg += sprintf(CYN "%-20s" WHT "\t%d兩黃金\n" NOR,
                                               shop_key[i],
                                               begin_shop[shop_key[i]]);

                        msg += HIC "≡" HIY "──────────────" HIC "≡\n" NOR;
                        msg += HIC "總共有" HIY + chinese_number(sizeof(shop_key)) + HIC
                               "家店鋪可以拍賣。\n\n";

                        tell_object(operator, msg);
                        // 記錄該次操作時間
                        last_time = time();
                }
                return 1;
        } else
        {
                //  首先檢查當前競投店鋪的玩家是否在線，或者是否在投標後趕回
                //  錢莊取走了存款如果該玩家數據異常，則該店鋪重新歸入待拍店
                //  鋪數組，並且取消該玩家的拍賣資格。

                the_owner = find_player(temp_owner);

                if (! objectp(the_owner)
                    || query("balance", the_owner)<(now_price*10000) )
                {
                        // 取消該玩家的拍賣資格
                        do_ban(temp_owner + " 1");
                        begin_shop[now_shop] = 2000;
                        set("begin_shop", begin_shop, ob);

                        message_vision(HIY "$N" HIY "冷笑一聲道：居然敢跟我玩？" +
                                       temp_owner + HIY "數據異常，取消拍賣資格"
                                       "。\n\n" NOR, operator);

                        CHANNEL_D->do_channel(ob, "sys", "由於" + temp_owner +
                                                  "數據異常，取消該玩家的拍賣資"
                                                  "格！" + now_shop + "店鋪"
                                                  "重新歸入待拍賣列表！");
                } else
                {
                        // 記錄店鋪歷史數據
                        record = ([]);
                        shop_record = query(now_shop);

                        if (! sizeof(shop_record))
                                shop_record = ({});

                        record["time"] = time();
                        record["id"]=query("id", the_owner);
                        record["name"] = the_owner->name(1);
                        record["pms"] = operator->name(1);
                        record["value"] = now_price;
                        shop_record += ({ record });
                        set(now_shop, shop_record, ob);

                        addn("balance", -now_price*10000, the_owner);
                        the_owner->save();
                        owner += ({ temp_owner });
                        set("owner", owner, ob);
                        end_shop[now_shop] = now_price;
                        set("end_shop", end_shop, ob);
                        SHOP_D->change_owner(operator, now_shop, temp_owner);

                        message_vision(BEEP + HIY "\n$N" HIY "舉起手中的小木棰用"
                                       "力的一敲，只聽得『當』的一聲巨響。\n" NOR,
                                       operator);
                        message_vision(HIY "$N" HIY "大聲宣佈道：成交！恭喜" +
                                       the_owner->name() + HIY "以" NOR + YEL +
                                       chinese_number(now_price) +"兩黃金" HIY
                                       "的價格獲得了" HIC + now_shop + HIY
                                       "店鋪的所有權。\n" NOR, operator);

                        shout(HIY "【商界傳聞】" NOR + WHT + operator->name() +
                              WHT"["+query("id", operator)+WHT"]：恭喜"+
                              the_owner->name() + NOR + WHT "獲得了" + now_shop +
                              NOR + WHT "店鋪的所有權。\n" NOR);

                        CHANNEL_D->do_channel(ob, "sys", temp_owner + "獲得了" +
                                                  now_shop + "店鋪的所有權。"
                                                  "最終出價" + chinese_number(now_price) +
                                                  "兩黃金！");

                        tell_object(the_owner, HIC + BLINK "\n恭喜您以" +
                                               chinese_number(now_price) +
                                               "兩黃金的價格獲得店鋪的所有權。\n" NOR);
                }
                delete("on_jupai", ob);
                delete("now_shop", ob);
                delete("now_price", ob);
                delete("temp_owner", ob);
                ob->save();

                // 自動拍賣
                if (operator == ob)
                {
                        // 所有店鋪拍賣結束
                        if (sizeof(shop_list) < 1)
                        {
                                set("can_finish", 1);
                                save();
                                call_out("finish_auction", 0, "automatic");
                        } else
                                call_out("do_auction", 1, "automatic");
                } else
                {
                        // 所有店鋪拍賣結束
                        if (sizeof(shop_list) < 1)
                        {
                                set("can_finish", 1);
                                save();
                                tell_object(operator, WHT "所有店鋪都已經拍賣結束了，您現"
                                                      "在可以結束(" HIY "finish" NOR + WHT
                                                      ")拍賣了。\n"NOR);
                                return 1;
                        }

                        msg += WHT "等待拍賣的店鋪列表： \n" NOR;
                        msg += HIC "--------------------------------------\n" NOR;
                        shop_key = keys(begin_shop);

                        for (i = 0; i < sizeof(shop_key); i++)
                                msg += sprintf(HIW "%-20s" HIY "\t%d兩黃金\n" NOR,
                                               shop_key[i],
                                               begin_shop[shop_key[i]]);

                        msg += HIC "--------------------------------------\n" NOR;
                        msg += WHT "總共有" + chinese_number(sizeof(shop_key)) +
                               "家店鋪可以拍賣。\n\n";

                        tell_object(operator,msg);

                        // 記錄該次操作時間
                        last_time = time();
                }
                return 1;
        }
}

int do_jupai(string arg)
{
        object ob, buyer;
        string now_shop, temp_owner;
        int money, now_price;

        ob = this_object();
        buyer = this_player();

        if (! query("auction_start"))
                return notify_fail("現在拍賣還沒有開始，不必心急。\n");

        //  手工拍賣，檢查執行巫師是否還在，如果不在則進程轉為自動
        if (operator != ob)
                operator = check_operator();

        if (! query("now_shop"))
               return notify_fail(operator->name(1) + "還沒有宣佈"
                                  "要拍賣哪家店鋪，你急個啥？\n");

        if (arrayp(query("owner"))
            && member_array(query("id", buyer),query("owner")) != -1 )
                return notify_fail("你已經購買到了店鋪，就別太心黑了。\n");

        if (arrayp(query("ban"))
            && member_array(query("id", buyer),query("ban")) != -1 )
                return notify_fail("你已經給取消了拍賣資格，老實點吧。\n");

        if( query("id", buyer) == query("temp_owner") )
                return notify_fail("當前的價格本來就是你所競投的。\n");

        now_shop = query("now_shop");
        now_price = query("now_price");
        temp_owner=query("id", buyer);

        if (! arg)
                money = 30;
        else
                if (! (sscanf(arg, "%d", money) == 1)
                   || money < 30
                   || money > 10000)
                        return notify_fail("你打算加價多少兩(30-10000)黃金？\n");

        if( query("balance", buyer)<(money+now_price)*10000 )
                return notify_fail("你帳户裏的錢並不足" +
                                   chinese_number(money+now_price) + "兩黃金。\n");

        remove_call_out("begin_auction");
        remove_call_out("go_jupai");
        remove_call_out("stop_auction");

        now_price += money;

        set("temp_owner", temp_owner, ob);
        set("on_jupai", 1, ob);
        set("now_price", now_price, ob);
        delete("wait_jupai", ob);
        ob->save();

        tell_object(buyer, HIC "你舉了舉手中的牌子，示意加價" +
                           chinese_number(money) + "兩黃金。\n" NOR);

        message_vision(HIW "\n$N" HIW "大笑道：好！現在" + buyer->name() +
                       HIW "出價" NOR + YEL + chinese_number(now_price) +
                       "兩黃金" HIW "，各位請繼續出價。\n" NOR, operator);

        switch (random(3))
        {
        case 0:

                message_vision(CYN "$N" CYN "環顧了一下四周，接着説"
                               "道：有意者可繼續舉牌(" HIY "jupai" NOR +
                               CYN ")認購。\n" NOR, operator);
                break;

        case 1:
                message_vision(CYN "$N" CYN "微笑道：有人願繼續拼價"
                               "麼？請有意者繼續舉牌(" HIY "jupai" NOR +
                               CYN ")出價。\n" NOR, operator);
                break;

        default:
                message_vision(CYN "$N" CYN "清了清嗓子，接着道：拍"
                               "賣正在進行，請各位繼續舉牌(" HIY "jupai"
                               NOR + CYN ")示意。\n" NOR, operator);
                break;
        }

        // 自動拍賣
        if (operator == ob)
                call_out("go_jupai", DISTANCE);
        else
                // 記錄當前操作時間
                last_time = time();

        return 1;
}

int go_jupai()
{
        object ob;
        int m, now_price;
        string now_shop, temp_owner;

        remove_call_out("go_jupai");
        remove_call_out("stop_auction");

        ob = this_object();
        m = query("on_jupai");
        now_shop = query("now_shop");
        now_price = query("now_price");
        temp_owner = query("temp_owner");

        m += 1;
        set("on_jupai", m, ob);
        ob->save();

        switch (random(3))
        {
        case 0:

                message_vision(CYN "\n$N" CYN "接着道：現在正在拍賣" HIC +
                               now_shop + NOR + CYN "店鋪。報價為" + YEL +
                               chinese_number(now_price) + "兩黃金" CYN "第" +
                               chinese_number(m) + "次。\n" NOR, operator);
                break;

        case 1:
                message_vision(CYN "\n$N" CYN "環顧四周大聲道：現在報價為"
                               YEL + chinese_number(now_price) + "兩黃金"
                               CYN "第" + chinese_number(m) + "次，拍賣" +
                               HIC + now_shop + NOR + CYN "店鋪。\n" NOR,
                               operator);
                break;

        default:
                message_vision(CYN "\n$N" CYN "乾咳兩聲，大聲道：現在為"
                               YEL + chinese_number(now_price) + "兩黃金"
                               CYN "第" + chinese_number(m) + "次，拍賣" +
                               HIC + now_shop + NOR + CYN "店鋪，欲購"
                               "者從速。\n" NOR, operator);
                break;
        }

        switch (random(3))
        {
        case 0:

                message_vision(CYN "$N" CYN "環顧了一下四周，接着説"
                               "道：有意者可繼續舉牌(" HIY "jupai" NOR +
                               CYN ")認購。\n" NOR, operator);
                break;

        case 1:
                message_vision(CYN "$N" CYN "微笑道：有人願繼續拼價"
                               "麼？請有意者繼續舉牌(" HIY "jupai" NOR +
                               CYN ")出價。\n" NOR, operator);
                break;

        default:
                message_vision(CYN "$N" CYN "清了清嗓子，接着道：拍"
                               "賣正在進行，請各位繼續舉牌(" HIY "jupai"
                               NOR + CYN ")示意。\n" NOR, operator);
                break;
        }

        // 自動拍賣
        if (operator == ob)
        {
                if (! (m >= 3))
                        call_out("go_jupai", DISTANCE);
                else
                        call_out("stop_auction", DISTANCE);
        // 手工拍賣
        } else
                // 記錄最後一次操作的時間
                last_time = time();

        return 1;
}

int do_qiao()
{
        object ob,me;
        int m;

        ob = this_object();
        me = this_player();

        if (! query("auction_start"))
                return notify_fail(WHT "現在拍賣進程還沒有啟動，您可用("
                                   HIY "start" NOR + WHT ")指令來啟動拍"
                                   "賣進程。\n" NOR);

        if (operator != me)
                return notify_fail("現在拍賣進程正由" + operator->name(1) +
                                   "主持中，您就看看吧。\n");

        remove_call_out("do_auction");
        remove_call_out("begin_auction");
        remove_call_out("stop_auction");
        remove_call_out("go_jupai");

        // 已經宣佈所拍店鋪，等待舉牌中
        if (m = query("wait_jupai"))
        {
                if (! (m >= 3))
                        call_out("begin_auction", 0);
                else
                        call_out("stop_auction", 0);
        } else
        if (m = query("on_jupai"))
        {
                if (! (m >= 3))
                        call_out("go_jupai", 0);
                else
                        call_out("stop_auction", 0);
        } else
                return notify_fail("您準備繼續宣佈拍賣哪個店鋪？\n");

        return 1;
}

int do_auctionlist()
{
        int i,now_price;
        object me;
        string msg, now_shop, *shop_list, *shop_key;
        mapping begin_shop, end_shop;

        msg = "";
        me = this_player();
        now_shop = query("now_shop");
        now_price = query("now_price");
        begin_shop = query("begin_shop");
        end_shop = query("end_shop");

        if (query("auction_start"))
                msg += HIC "現在正在拍賣之中。\n" NOR;
        else
                msg += HIC "現在並沒有在拍賣店鋪。\n" NOR;

        msg += HIC "--------------------------------------\n" NOR;

        if (now_shop)
        {
                msg += sprintf(HIY "當前拍賣店鋪：\n" HIW "%-20s"
                               HIY "\t%d兩黃金\n" NOR,
                               now_shop, now_price);
                msg += HIC "--------------------------------------\n" NOR;
        }

        if (mapp(begin_shop) && sizeof(begin_shop) > 0)
        {
                msg += WHT "待拍賣店鋪列表： \n" NOR;
                shop_key = keys(begin_shop);

                for (i = 0; i < sizeof(shop_key); i++)
                        msg += sprintf(HIW "%-20s" HIY "\t%d兩黃金\n" NOR,
                                       shop_key[i],
                                       begin_shop[shop_key[i]]);

                msg += HIC "--------------------------------------\n" NOR;
        }

        if (mapp(end_shop) && sizeof(end_shop) > 0)
        {
                msg += HIR "已被拍賣店鋪列表： \n" NOR;
                shop_key = keys(end_shop);

                for (i = 0; i < sizeof(shop_key); i++)
                        msg += sprintf(HIW "%-20s" HIY "\t%d兩黃金\n" NOR,
                                       shop_key[i],
                                       end_shop[shop_key[i]]);

                msg += HIC "--------------------------------------\n" NOR;
        }

        tell_object(me,msg);
        return 1;
}

int do_ban(string arg)
{
        int i, m;
        string *ban;
        string msg;
        ban = query("ban");

        if (! ban || sizeof(ban) < 1)
                ban = ({ });

        if (! arg)
        {
                if (sizeof(ban) < 1)
                        return notify_fail("現在沒有玩家給取消拍賣資格。\n");

                msg = HIC "取消拍賣資格的玩家列表：\n" NOR;
                msg += HIC "------------------------------------\n" NOR;

                for (i = 0; i < sizeof(ban); i++)
                        msg += HIY + ban[i] + "\n" + NOR;

                msg += HIC "------------------------------------\n" NOR;
                msg += WHT "總共" + sizeof(ban) + "位玩家給取消拍賣資格。\n" NOR;

                msg += HIC "\n指令格式：ban [id] [1|0]\n"
                       "其中參數id缺省表示查詢，如果參數為1或是"
                       "缺省表示添加，為0表示刪除。\n" NOR;

                tell_object(this_player(), msg);
                return 1;
        }

        if (sscanf(arg, "%s %d", arg, m) != 2)
                m = 1;

        if (m)
        {
                if (member_array(arg, ban) == -1)
                {
                        ban += ({ arg });
                        set("ban", ban);
                }
        } else
        {
                if (member_array(arg, ban) != -1)
                {
                        ban -= ({ arg });
                        set("ban", ban);
                }
        }
        save();
        return 1;
}

int finish_auction(string arg)
{
        object me,ob;
        ob = this_object();

        if (!arg || arg != "automatic")
        {
                me = this_player();

                if (! query("auction_start"))
                        return notify_fail("拍賣進程並沒有啟動。\n");

                if (! query("can_finish"))
                        return notify_fail("現在拍賣正在進行之中，無法中止。\n");

                if (operator != me)
                        return notify_fail("現在是" + operator->name(1) + "主持"
                                           "店鋪拍賣，您就別操心了。\n");
        }

        remove_call_out("finish_auction");

        delete("can_finish", ob);
        delete("shop_list", ob);
        delete("begin_shop", ob);
        delete("auction_start", ob);
        set("auction_end", 1, ob);
        delete("wait_jupai", ob);
        delete("on_jupai", ob);
        delete("now_shop", ob);
        delete("now_price", ob);
        delete("temp_owner", ob);
        delete("owner", ob);
        ob->save();

        message_vision(CYN "\n$N" CYN "滿意的點了點頭，道：本次店鋪拍賣圓"
                       "滿結束。\n" NOR, operator);

        CHANNEL_D->do_channel(ob, "sys", "店鋪拍賣完畢。" + operator->name(1) +
                                  "結束了拍賣進程！");

        if (operator == ob)
        {
                SHOP_D->open_all(operator);
                message_vision(CYN "$N" CYN "笑道：現在所有拍出店鋪全部"
                               "開放，大家忙去吧。\n" NOR, operator);
        } else
                tell_object(operator, WHT "您現在可以用(" HIY "shop open"
                                      NOR + WHT ")指令開放店鋪。\n" NOR);

        shout(HIY "【商界傳聞】" NOR + WHT + operator->name() + WHT "[" +
              query("id", operator)+WHT"]：拍賣大會到此結束，各位可用"
              "(" HIY "shop" NOR + WHT ")查看各家店鋪詳情。\n" NOR);

        return 1;
}

// 心跳線 -- 用於檢查啟動拍賣進程的巫師是否狀態正常
// 如果狀態不正常，則轉為自動運行模式，並且關閉心跳線
void heart_beat()
{
        int m;
        object ob,obj;
        string the_operator;

        ob = this_object();

        if (! query("auction_start") || operator == this_object())
        {
                set_heart_beat(0);
                return;
        }

        the_operator = query("operator");

        if (! the_operator)
        {
                set_heart_beat(0);
                return;
        }

        if (! operator
           || ! (obj = find_player(the_operator))
           || ! living(obj)
           || environment(obj) != environment(ob)
           || (time() - last_time) > 30)
        {
                set_heart_beat(0);
                operator = this_object();

                command("say 這個…嗯…看來他有點別的事情要忙，接下來"
                        "就我來代替吧。");

                CHANNEL_D->do_channel(ob, "sys", "由於" + the_operator +
                                          "狀態異常，現在拍賣進程轉入自動模式！");
                set("operator", "feng tiannan");
                save();

                if (m = query("wait_jupai"))
                {
                        if (!(m >= 3))
                               call_out("begin_auction",DISTANCE);
                        else
                               call_out("stop_auction",DISTANCE);
                } else
                if (m = query("on_jupai"))
                {
                        if (!(m >= 3))
                                call_out("go_jupai",DISTANCE);
                        else
                                call_out("stop_auction",DISTANCE);
                } else
                        call_out("do_auction", 0, "automatic");
        }

        return;
}

object check_operator()
{
        object obj;
        string the_operator;

        the_operator = query("operator");

        if (! (obj = find_player(the_operator))
           || ! living(obj)
           || environment(obj) != environment())
        {
                set("operator", "feng tiannan");
                save();
                return this_object();
        }
        return obj;
}

int do_autoauction()
{
        object ob,me;
        int m;

        ob = this_object();
        me = this_player();

        if (! query("auction_start"))
                return notify_fail("拍賣進程並沒有啟動，怎麼自動化？\n");

        if (operator != me)
                return notify_fail("現在拍賣並不是你在主持。\n");

        operator = this_object();
        set_heart_beat(0);

        message_vision(CYN "$N" CYN "招手將$n" CYN "叫上來，説道：我"
                       "有點其它事，這裏就你來處理吧。\n" NOR, me, ob);
        message_vision(CYN "$N" CYN "連忙朝$n" CYN "賠笑道：您老人家"
                       "忙您的，這裏就交給我吧。\n" NOR, ob, me);

        CHANNEL_D->do_channel(ob,"sys",query("id", me)+"將拍賣進"
                                  "程轉入自動模式！");
        set("operator", "feng tiannan");
        save();

        if (m = query("wait_jupai"))
        {
                if (! (m >= 3))
                        call_out("begin_auction", DISTANCE);
                else
                        call_out("stop_auction", DISTANCE);
        } else
        if (m = query("on_jupai"))
        {
                if (! (m >= 3))
                        call_out("go_jupai", DISTANCE);
                else
                        call_out("stop_auction", DISTANCE);
        } else
                call_out("do_auction", 0, "automatic");

        return 1;
}