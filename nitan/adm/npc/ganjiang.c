// ganjiang.c  幹將
// Written by Doing Lu  1998/11/2
// Updated by Lonely@NT

// 幹將負責煉道具的場景，但是不接受玩家的物品，玩家如果煉制
// 道具應該和莫邪打交道。如果 player 在莫邪那裡將一切手續辦
// 妥，莫邪將原料交給幹將。通過accept_object 函數啟動幹將的
// 煉制程序。

// 幹將接收到莫邪傳來的道具，則對他進行鍛煉，鍛煉完以後，設
// 設置道具的鑄造者，鑄造者的ID，不設置道具的有效點數 point，
// 因為在莫邪那裡已經設置了。並且等候 player 輸入關于道具的
// 信息，如果超時，就清除三人的標志，並解除object。如果用戶
// finish，這詢問 player 是否決定，如果是則生成道具文件，並
// 在生成道具送給 player，否則繼續修改。

inherit NPC;
inherit F_NOCLONE;

#include <ansi.h>

// 如果字符串被設置成這個值，表示輸入的字符串具有非法的格式
#define ILLEGAL_STR     "."
// 在convert時看看要不要去掉彩色
#define NOCOLOR         1
#define COLORABLE       0

int mark = 0;
protected int   ask_forging();
protected int   ask_smelting();
protected int   ask_certosina();
protected int   ask_enchanting();
protected int   ask_me();                               // 顯示定做信息
protected int   show_order();                           // 顯示規則信息
protected int   start_work(object me, object ob);       // 開始工作
protected int   prepare_make(object me, object ob);     // 開始打造
protected int   do_show(string arg);
protected int   do_notch(string arg);                   // 道具開槽
protected int   start_make(object me, object ob);       // 裝備簽名
protected void  clear_data();                           // 清除 ganjiang, moye, player 的臨時變量並去除粗坯對象
protected object  create_object(object item_temp);
protected string  create_file(object item_temp);
protected int     save_item_file(string filename, string content);
protected void    tell_rules(object me);
protected void    waiting(object me, object ob, object moye);
protected string  converts(string arg, int max_len, int nocolor);
protected string  prop_segment(mapping p, string path);
protected int     save_item_file(string filename, string content);
protected int     legal_chinese(string str);

mapping rings_sockets = ([
        "1" : ({"rune05","rune12","rune18"}),
        "2" : ({"rune06","rune13","rune19"}),
        "3" : ({"rune07","rune14","rune20"}),
]);

mapping equip_sockets = ([
        "1" : ({"rune01","rune06","rune15"}),
        "2" : ({"rune02","rune07","rune16"}),
        "3" : ({"rune03","rune08","rune17"}),
        "4" : ({"rune04","rune09","rune18"}),
        "5" : ({"rune05","rune10","rune19"}),
        "6" : ({"rune06","rune11","rune20"}),
]);

mapping qianghua_rune = ([
        "0" : "rune28",
        "1" : "rune29",
        "2" : "rune30",
        "3" : "rune31",
        "4" : "rune32",
        "5" : "rune33",
        "6" : "rune34",
        "7" : "rune35",
        "8" : "rune36",
]);

mapping suit_level = ([
        "1" : HIC"大道"NOR,
        "2" : HIB"通玄"NOR,
        "3" : HIM"鴻鈞"NOR,
        //"4" : HIM"混沌"NOR,
        "4" : HIY"造化"NOR,
]);

void create()
{
        seteuid(getuid());

        set_name("幹將", ({ "gan jiang", "ganjiang", "gan" }));
        set("long", "他長得粗壯有力，臉龐似如刀削，透出一股英氣。他是古往今來有名的鑄劍大師。\n" );

        set("nickname", HIR "劍師" NOR);
        set("gender", "男性");
        set("attitude", "friendly");

        set("age", 1535);
        set("shen_type", 0);

        set("str", 1000);

        set("inquiry", ([
                /*
                "煉制" : (: ask_me :),
                "練劍" : (: ask_me :),
                "煉劍" : (: ask_me :),
                "鑄劍" : (: ask_me :),
                "打造" : (: ask_me :),
                "鑄造" : (: ask_me :),
                "制造" : (: ask_me :),
                "打制" : (: ask_me :),
                "定制" : (: ask_me :),
                "定做" : (: ask_me :),
                "定造" : (: ask_me :),
                "兵器" : (: ask_me :),
                "道具" : (: ask_me :),
                "裝備" : (: ask_me :),
                "武器" : (: ask_me :),
                "刀劍" : (: ask_me :),
                "裝甲" : (: ask_me :),
                */
                
                "裝備簽名": "打BOSS掉落的裝備只有簽名(qianming)後才算真正自己的，開光後擁有summon和hide的能力。\n",
                "開槽" : "想要給裝備開槽(notch)，必須先了解開槽需要的符文help rune。\n",
                "強化材料": "想要知道強化裝備需要的材料，請show <裝備id>，我會告訴你所需的材料。\n",
                "開槽" : "我只給神兵利器開槽打孔(notch)，尋常刀劍防具莫提，費用一千兩黃金將從銀行扣除。\n",
                "打孔" : "我只給神兵利器開槽打孔(notch)，尋常刀劍防具莫提，費用一千兩黃金將從銀行扣除。\n",
                "原料" : "煉劍就得有原料，一分錢，一分貨，好原料就能出好東西。\n",
                "定金" : "定金少得很，才五兩黃金，要交定金請交給莫邪。\n",
                "價格" : "一分錢一分貨......",
                "銷毀" : "那就...退回(discard)來吧...",
                "退貨" : "那就...退回(discard)來吧...",

                "規則" : (: show_order :),
                "方法" : (: show_order :),
                "order": (: show_order :),

                "強化"    : "想要知道強化裝備需要的材料，請show <裝備>，我會告訴你所需的材料。\n",
                "強化裝備": "想要知道強化裝備需要的材料，請show <裝備>，我會告訴你所需的材料。\n",
                "鍛造"    : (: ask_forging :),
                "鍛造技術": (: ask_forging :),
                "鍛造技藝": (: ask_forging :),
                "forging" : (: ask_forging :),
                "冶煉"    : (: ask_smelting :),
                "冶煉技藝": (: ask_smelting :),
                "冶煉技術": (: ask_smelting :),
                "smelting": (: ask_smelting :),
                "鑲嵌"    : (: ask_certosina :),
                "鑲嵌技術": (: ask_certosina :),
                "鑲嵌技藝": (: ask_certosina :),
                "certosina": (: ask_certosina :),
                "附魔技藝": (: ask_enchanting :),
                "附魔技術": (: ask_enchanting :),
                "enchanting": (: ask_enchanting :),
                "淬煉裝備": "淬煉裝備最好的材料是無名之物，寰宇天晶次之，淬煉指令為cuilian <裝備> with <材料>",
                "改造裝備": "你要是有裝備之魂及無名之物，我就幫你改造裝備(reform <裝備> with <裝備之魂>)，歐冶子聖符可以增加成功率。",
                "套裝"    : "綠化套裝必須要有王者之心，如果給我王者之心的話，我就幫你綠化(douit <裝備>)套裝。",
                "升級套裝": "升級套裝必須要有鴻蒙靈氣，指令格式upsuit <裝備>",
        ]));

        set_skill("literate",  120);            // 讀書寫字
        set_skill("forging",   2000);            // 鍛造技巧
        set_skill("smelting",  2000);            // 冶煉技藝
        set_skill("certosina", 2000);            // 鑲嵌技藝
        set_skill("enchanting", 2000);            // 附魔技藝

        set("no_teach", ([
                "literate" : "我可不是教書先生。",
        ]));

        setup();

        set("startroom", "/d/item/xiaowu");
        check_clone();
        if (! this_object()) return;

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_name", "name");
        add_action("do_name", "命名");
        add_action("do_desc", "desc");
        add_action("do_desc", "描述");
        //add_action("do_level", "level");
        //add_action("do_level", "等級");
        add_action("do_wieldmsg", "wieldmsg");
        add_action("do_wieldmsg", "wearmsg");
        add_action("do_wieldmsg", "裝備");
        add_action("do_wieldmsg", "裝備信息");
        add_action("do_unwield", "unwieldmsg");
        add_action("do_unwield", "removemsg");
        add_action("do_unwield", "收起");
        add_action("do_unwield", "收起信息");
        add_action("do_finish", "finish");
        add_action("do_finish", "完成");

        add_action("do_increase", "qianghua"); // 強化裝備
        add_action("do_reform", "reform"); // 改造裝備
        add_action("do_suit", "dosuit"); // 套裝套化
        add_action("do_cuilian", "cuilian"); // 淬煉裝備
        add_action("do_upsuit", "upsuit"); // 套裝升級

        add_action("do_help", "help");
        add_action("do_help", "幫助");

        add_action("do_show", "show");
        add_action("do_notch", "notch"); // 開槽
        add_action("do_discard", "discard"); // 銷毀
        add_action("do_signature", "qianming"); // 裝備簽名

        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/ganjiang"); 
}

// 發出提示信息
protected int ask_me()
{
        message_vision("幹將對$N說道：這些事請問莫邪，我只管煉劍。\n", this_player());
        return 1;
}

// 認証學習
int recognize_apprentice(object me)
{
        if( !query_temp("learnd_from/幹將", me) )
        {
                message_vision("幹將對$N說：好，你既然有心學，我就"
                               "教你一點吧。\n", me);
                set_temp("learnd_from/幹將", 1, me);
        }
        return 1;
}

// 回答有關鑲嵌技藝的信息
protected int ask_certosina()
{
        message_sort("幹將對$N說道：我這裡不受理鑲嵌的活兒，"
                     "不過你有興趣的話，我可以教你一點鑲嵌的"
                     "技術。\n", this_player());
        return 1;
}

protected int ask_forging()
{
        message_sort("幹將對$N說道：我這裡不受理鍛造的活兒，"
                     "不過你有興趣的話，我可以教你一點鍛造的"
                     "技術。\n", this_player());
        return 1;
}

protected int ask_smelting()
{
        message_sort("幹將對$N說道：我這裡不受理冶煉的活兒，"
                     "不過你有興趣的話，我可以教你一點冶煉的"
                     "技術。\n", this_player());
        return 1;
}

protected int ask_enchanting()
{
        message_sort("幹將對$N說道：我這裡不受理附魔的活兒，"
                     "不過你有興趣的話，我可以教你一點附魔的"
                     "技術。\n", this_player());
        return 1;
}
        
int accept_object(object me, object ob)
{
        if( query_temp("item") ) return notify_fail("幹將正忙著呢，稍等會。\n");
        
        if (me->name(1) == "莫邪")
        {
                if( query("id", me) != "mo ye" )
                {
                        command("kick "+query("id", me));
                        message_vision("$N嘿嘿的姦笑了兩聲，對$n說道："
                                       "你以為取了我妻子的名字就能蒙蔽"
                                       "我？我還沒瞎呢！\n",
                                       this_object(), me);
                        return 1;
                }
                start_work(query("item/owner", ob),ob);
                return 1;
        }
        
        if (ob->is_item_make())
        {
                if( ob->item_owner() != query("id", me) )
                {
                        command("heng");
                        command("say 這是你的東西嗎？沒收了！");
                        destruct(ob);
                        return 1;
                }
                message_vision("$N疑惑的望著$n道：“你是嫌它"
                               "不好麼？那就退掉(discard)吧！”\n",
                               this_object(), me);
                return 0;
        }
        else if( query("id", ob) == "wangzhe zhixin" )
        {
                message_vision("幹將對$N說：有了王者之心，自造裝備就可以綠化套裝了(dosuit)，你想"
                               "綠化套裝什麼道具？\n", me);
                set_temp("paid/dosuit", 1, me);
                destruct(ob);
                return 1;
        }

        message_vision("幹將冷冷的對$N說道：你給我這些東西幹什"
                       "麼？我煉劍，不用這些東西。\n", me);
        return 0;
}

protected int start_work(object me, object ob)
{
        remove_call_out("prepare_make");
        call_out("prepare_make", 1, me, ob);
        set_temp("item/making", ob);
        set_temp("item/player", me);
        set_temp("item/status", "waiting", me);
        return 1;
}

protected int prepare_make(object me, object ob)
{
        message_vision(HIC "\n$N說道：好，開爐鍛煉！\n\n" NOR, this_object());
        message_vision(HIM "$N接過莫邪手中的" + ob->name() +
                       HIM "，隨手把它拋入爐內，霎時間，那" + ob->name() +
                       HIM "已被火爐中的熊熊" HIR "烈燄" HIM "吞沒。\n" +
                       "$N凝視著爐火，喃喃說道：天地之精華為其血脈，日"
                       "月之光輝是其靈氣......\n\n" NOR , this_object());
        remove_call_out("work_step_1");
        call_out("work_step_1", 5, me, ob);
        return 1;
}

protected int work_step_1(object me, object ob)
{
        message_vision(HIG "爐火漸漸的轉成了綠色，火苗不斷跳躍，你覺得屋"
                       "內十分燥熱，可是幹將莫邪若無其事。\n\n" NOR, this_object());

        if (objectp(me) && environment(me) == environment())
        {
                set_temp("item/can_help", 1, me);
                message_vision(HIW "$N對$n說道：如果你想煉得更好，需"
                               "要注入自己的精氣血脈，如是你有此意，請"
                               "助(help)我一臂之力！\n\n", this_object(), me);
        }
        remove_call_out("work_step_2");
        call_out("work_step_2", 6, me, ob);
        return 1;
}

protected int work_step_2(object me, object ob)
{
        message_vision(RED "爐火淡淡的暗了下來，呈現出一片紅色......\n\n" NOR, this_object());
        remove_call_out("work_step_3");
        if (objectp(me))
                delete_temp("item/can_help", me);
        call_out("work_step_3", 3, me, ob);
        return 1;
}

protected int work_step_3(object me, object ob)
{
        message_vision(HIW "$N左手持蛟龍剪，一揚手已經取出了" + ob->name() +
                       HIW "，右手持金剛錘聚精會神地用力錘打，\n漸漸的，" + ob->name() +
                       HIW"在幹將手下的成了"+query("item/ctype", ob)+
                       HIW "的形狀。\n\n" NOR, this_object());
        remove_call_out("work_step_4");
        call_out("work_step_4", 5, me, ob);
        return 1;
}

protected int work_step_4(object me, object ob)
{
        message_vision(HIC"$N錘打完畢，大喝一聲，將"+query("item/ctype", ob)+
                       HIC "拋入水池，只聽絲絲作響，從水池騰起一股霧氣，"
                       "彌漫四周。\n\n" NOR, this_object());
        remove_call_out("work_step_5");
        call_out("work_step_5", 3, me, ob);
        return 1;
}

protected int work_step_5(object me, object ob)
{
        message_vision(HIW"$N緩緩的從水池抽出了煉好的"+query("item/ctype", ob)+
                       HIW "看了看，滿意地說，很好，很好。\n\n" NOR,
                       this_object());
        remove_call_out("work_step_6");
        call_out("work_step_6", 2, me, ob);
}

protected int work_step_6(object me, object ob)
{
        object moye;

        if (! objectp(moye = present("mo ye")))
        {
                message_vision(HIW "幹將看了看四周，說道：咦，莫邪呢？"
                               "算了算了，不做了，去吧！\n"
                               "幹將把煉好的道具拋進火爐，就此不見。\n\n" NOR,
                               this_object());
                if (objectp(me))
                        delete_temp("item", me);

                if (objectp(ob) && present(ob, this_object()))
                        destruct(ob);

                delete_temp("item");
                return 1;
        }

        if (! objectp(me))
                me = find_player(query("item/owner_id", ob));

        if (! objectp(me) || environment(me) != environment())
        {
                message_vision(HIW "$N嘆了口氣，說道：客人為何這就去"
                               "了！？罷了罷了，不做了，去吧！\n"
                               "$N把煉好的道具拋進火爐，就此不見。\n\n" NOR,
                               this_object());
                if (objectp(me))
                        delete_temp("item", me);

                if (objectp(ob) && present(ob, this_object()))
                        destruct(ob);

                delete_temp("item");
                delete_temp("item", moye);
                return 1;
        }
        set_temp("item/status", "waiting", moye); 
        set_temp("item/status", "inputing", me); 
        message_vision("$N對$n說道：一"+query("item/unit", ob)+"好"+
                       query("item/ctype", ob)+NOR"不能沒有名字，你給它起個名字吧！\n",
                       this_object(), me);

        tell_rules(me);

        // 清除道具的名字，ID，和其它屬性，並且設置道具的價值和制造者
        set("item/long", "", ob);
        set("item/wield_msg", "", ob);
        set("item/wear_msg", "", ob);
        set("item/unwield_msg", "", ob);
        set("item/remove_msg", "", ob);
        set("item/owner_name",query("name",  me), ob);
        set("item/owner_id",query("id",  me), ob);

        // 設置等待時間，最多3次
        set_temp("item/waited", 4);

        // 如果超時，提醒輸入
        remove_call_out("waiting");
        call_out("waiting", 300, me, ob, moye);
        return 1;
}

// 以內力哺育爐火，提高道具等級
// 要求：精 >= 180  氣 >= 300  內力有效等級 >= 100  內力 >= 800 最大內力 >= 1000
// 結果：耗費 200 點內力，可以提高 10%
int do_help(string arg)
{
        object me;
        object ob;

        me = this_player();
        if( query_temp("item/status", me) != "waiting" )
        {
                return notify_fail("沒你什麼業務。\n");
        }
        if( !query_temp("item/can_help", me) )
        {
                if (arg) return 0;
                write("現在不是你幫忙的時候！\n", me);
                return 1;
        }
        if( query("jing", me)<180 )
        {
                message_vision(HIR "$N" HIR "長嘯一聲，雙手搭上爐邊，正待以內"
                               "力哺育爐火，突然眼前一黑...\n" NOR, me);
                tell_object(me, RED "你感到精力衰竭。\n" NOR);
                set("jing", 0, me);
                return 1;
        }
        me->receive_damage("jing", 180);
        if( query("qi", me)<300 )
        {
                message_vision(HIR "$N" HIR "長嘯一聲，雙手搭上爐邊，正待以內"
                               "力哺育爐火，突然眼前一黑...\n" NOR, me);
                tell_object(me, RED "你感到心虛氣短。\n" NOR);
                set("qi", 0, me);
                return 1;
        }
        me->receive_damage("qi", 300);
        if( query("neili", me)<800 || query("max_neili", me)<1000 )
        {
                message_vision(HIR "$N" HIR "長嘯一聲，雙手搭上爐邊，正待以內"
                               "力哺育爐火，突然眼前一黑...\n" NOR, me);
                tell_object(me, RED "你感到內力枯竭。\n" NOR);
                set("neili", 0, me);
                return 1;
        }
        message_vision(HIR "$N" HIR "長嘯一聲，雙手搭上爐邊，剎那間，爐火沸騰，"
                       "一道" HIW "白光" HIR "，直沖霄漢。\n\n" NOR, me);

        ob = query_temp("item/making");
        // 這裡處理特殊材料的效果
        addn("item/point",query("item/point",  ob)*me->query_skill("force")/500, ob);
        addn("item/point",query("item/power",  ob), ob);
        delete_temp("item/can_help", me);
        addn("max_neili", -200, me);
        addn("neili", -200, me);
        return 1;
}

protected int show_order()
{
        object me;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
        {
                message_vision("$N冷冷的坐在那裡，理都不理$n。\n",
                               this_object(), me);
                return 1;
        }

        tell_rules(me);
        return 1;
}

void tell_rules(object me)
{
        tell_object(me, CYN @RULES
幹將在你耳邊悄聲說道：
名字需要你來定，其它信息系統有缺省的描述，當然也可以由你自己為它自定描述。
當然了，最好不用讓別人誤會的詞語字句噢。具體的方法如下。
    命名: name 中文名字 英文代號。   (必須有)
    描述: desc 武器的描述文字。      (可  選)
    裝備: wieldmsg   裝備時的描述。  (可  選)
    收起: unwieldmsg 收起時的描述。  (可  選)
描述時分行請用\n，除了英文代號以外所有的文字都可以用顏色，使用顏色的方法可以參照nick 。
如果你覺得可以了，就請告訴我(finish)，要是沒看清楚，可以再問問我 < 規則 >

RULES NOR);
}

void waiting(object me, object ob, object moye)
{
        if (! objectp(me))
                me=find_player(query("item/owner_id", ob));

        if (! objectp(me))
        {
                message_vision("$N嘆了口氣說道：怎麼這走了，算了算"
                               "了，去吧！\n", this_object());
                if (objectp(moye))
                        delete_temp("item", moye);

                delete_temp("item");
                destruct(ob);
                return;
        }

        if (addn_temp("item/waited", -1) <= 0)
        {
                // 等待超時
                if (objectp(moye))
                        delete_temp("item", moye);

                log_file("static/item", sprintf("%s %s do timeout when make item of %s\n",
                                 log_time(), log_id(me),
                                 (ob ? filter_color(ob->name(1)) : "???")));
                if (objectp(ob) && present(ob, this_object()))
                        destruct(ob);

                delete_temp("item", me);
                delete_temp("item");
                if (in_input(me)) return;
                if (environment(me) == environment())
                {
                        message_vision("$N皺了皺眉頭說道：這人怎麼這麼"
                                       "磨蹭，算了，不要就不要吧！\n",
                                       this_object());
                        return;
                }
                message_vision("$N皺了皺眉頭對$n說道：你這人怎麼這麼"
                               "磨蹭，不要就算了，恕不退款！\n",
                               this_object(), me);
                return;
        }

        if (environment(me) != environment())
        {
                message_vision("$N疑惑地說道：人怎麼跑掉了？算了，再等"
                               "他一會吧。\n", this_object());
        } else
        if (! in_input(me))
        {
                message_vision(HIR "$N" HIR "催$n" HIR
                               "道：快點，快點，別磨蹭，否則我可就不做了。\n" NOR,
                               this_object(), me);
        }

        remove_call_out("waiting");
        call_out("waiting", 300, me, ob, moye);
}

protected void clear_data()
{
        object me;
        object ob;
        object moye;

        if (objectp(moye = present("mo ye")))
                delete_temp("item", moye);

        if (objectp(ob = query_temp("item/making")))
                destruct(ob);

        if (objectp(me = query_temp("item/player")))
                delete_temp("item", me);

        delete_temp("item");
        remove_call_out("waiting");
}

int do_level(string arg)
{
        object me, ob;
        int level;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        if (! arg || sscanf(arg, "%d", level) != 1)
        {
                write("格式不對！應該是：level 等級\n例如：level 30\n");
                return 1;
        }

        if( level<10 || level>query("level", me) )
        {
                write("裝備的等級最低不能小于10級，最高也不能高于你現在的人物等級。\n");
                return 1;
        }

        if (level%10 != 0)
        {
                write("裝備的等級必須是10的倍數。\n");
                return 1;
        }

        ob = query_temp("item/making");
        set("item/level", level, ob);
        write(CYN "你決定打造" + level + "級的道具。\n" NOR);
        return 1;
}

int do_name(string arg)
{
        object me;
        object ob;
        string pname;
        string sname, sid;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        if (! arg || sscanf(arg, "%s %s", sname, sid) != 2)
        {
                write("格式不對！應該是：命名 中文名字 英文名字\n例如：命名 長劍 sword\n");
                return 1;
        }

        // ILLEGAL_STR = "." 表示非法的輸入
        if ((sname = converts(sname, 14, COLORABLE)) == ILLEGAL_STR)
                return 1;

        if ((sid = converts(sid, 8, NOCOLOR)) == ILLEGAL_STR)
                return 1;

        if (! sname || ! sid)
        {
                message_vision("$N搖搖頭，對$n道：不行不行，你好好個定個名字！\n",
                               this_object(), me);
                return 1;
        }

        if( file_size(ITEM_DIR+query("id", me)[0..0]+"/"+
                      query("id", me)+"-"+sid+".c") != -1 )
        {
                message_vision("$N搖搖頭，對$n道：不好，你不要再用(" + sid +
                               ")這個英文代號了，換一個吧！\n",
                               this_object(), me);
                return 1;
        }

        if (! is_chinese(filter_color(sname)))
        {
                command("kick "+query("id", me));
                command("say 不會寫中文字怎麼的？");
                return 1;
        }

        if (! is_legal_id(sid))
        {
                command("say 英文代號必須全部用小寫英文才可以！");
                return 1;
        }

        if (strlen(filter_color(sname)) < 4)
        {
                command("say 我說你這名字起得也太短了吧，至少兩個漢字！");
                return 1;
        }

        if (strlen(sid) < 3)
        {
                command("say 我說你這代號起得也太短了吧，至少三個字符！");
                return 1;
        }

        if (sid == "cruise")
        {
                command("say 這代號是漫遊包專用代號，請重新選擇代號！");
                return 1;
        }

        if (sname[0] == 27 &&
            sname[4] == 'm')
        {
                // Add color prefix
                sname = NOR + sname;
        }

        ob = query_temp("item/making");
        set("item/name", sname, ob);
        set("item/id", sid, ob);

        write("名字：" CYN + sname + "    代號：" CYN + sid + NOR "\n");
        return 1;
}

int do_desc(string arg)
{
        object ob;
        object me;
        string chk;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        ob = query_temp("item/making");
        if( !query("item/name", ob) )
        {
                message_vision("$N瞪了$n一眼道：你還是先給它取好名字再考慮描述吧！\n",
                               this_object(), me);
                return 1;
        }

        if (! arg)
        {
                write("參照格式：應該是 desc 描述的文字。\n例如：一把"
                      "鋒利的$n\\n它在陽光下閃閃發光 -- 其中\\n表示換行，$n代表道具。\n");
                return 1;
        }

        if ((arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR)
                return 1;

        arg = replace_string(arg, "$N", me->name(1));

        chk = filter_color(arg);
        if (strlen(chk) >= 2 && chk[0..1] == "你" || strsrch(chk, "\\n你") != -1)
                return notify_fail("對不起，描述不能以“你”字打頭。\n");

        chk = replace_string(chk, " ", "");
        chk = replace_string(chk, "\\n", "");
        chk = replace_string(chk, "$n", "");
        if (! legal_chinese(chk))
                return notify_fail("對不起，描述必須使用漢字和系統規定可以使用的代表符號。\n");

        arg=replace_string(arg,"$n",query("item/name", ob));
        arg = replace_string(arg, "\\n", "\n");
        arg = replace_string(arg, "\"", "");
        arg = replace_string(arg, "\\", "");
        arg = chinese_desc(arg);
        set("item/long", arg, ob);
        write(CYN "當你觀察它的時候將會出現下列描述：\n" NOR + arg + "\n");
        return 1;
}

int do_wieldmsg(string arg)
{
        object ob;
        object me;
        string chk;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        ob = query_temp("item/making");
        if( !objectp(ob) ) return 0;
        if( !query("item/name", ob) )
        {
                message_vision("$N瞪了$n一眼道：你還是先給它取好名字再考慮描述吧！\n",
                               this_object(), me);
                return 1;
        }

        if (! arg)
        {
                write("參照格式：應該是 wieldmsg 描述的文字。\n例如："
                      "$N伸手一抖，抽出一把鋒利長劍。 -- 其中$N表示你自"
                       "己，$n代表道具。\n");
                return 1;
        }

        if ((arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR)
                return 1;

        chk = filter_color(arg);
        if (strlen(chk) >= 2 && chk[0..1] == "你" || strsrch(chk, "\\n你") != -1)
                return notify_fail("對不起，描述不能以“你”字打頭。\n");

        chk = replace_string(chk, " ", "");
        chk = replace_string(chk, "\\n", "");
        chk = replace_string(chk, "$N", "");
        chk = replace_string(chk, "$n", "");
        if (! legal_chinese(chk))
                return notify_fail("對不起，描述必須使用漢字和系統規定可以使用的代表符號。\n");

        // 這裡不區分武器還是裝備，在生成文件時自動選擇一條信息
        /*
        arg = "☆" + arg;
        arg = chinese_desc(arg);
        arg = replace_string(arg, me->name(1), "$N");
        arg = replace_string(arg, "\\n", "\n☆");
        set("item/wear_msg", arg, ob);
        set("item/wield_msg", arg, ob);
        */
        arg = chinese_desc(arg);
        arg = replace_string(arg, me->name(1), "$N");
        set("item/wear_msg", arg, ob);
        set("item/wield_msg", arg, ob);
        arg = replace_string(arg, "\\n", "\n");
        arg = replace_string(arg, "$N", me->name(1));
        arg=replace_string(arg,"$n",query("item/name", ob));
        write(CYN "當你裝備它的時候將會出現下列描述：\n" NOR + arg + "\n");
        return 1;
}

int do_unwield(string arg)
{
        object ob;
        object me;
        string chk;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        ob = query_temp("item/making");
        if( !query("item/name", ob) )
        {
                message_vision("$N瞪了$n一眼道：你還是先給它取好名字再考慮描述吧！\n",
                               this_object(), me);
                return 1;
        }

        if (! arg)
        {
                write("格式不對！應該是：unwield 描述的文字。\n例如："
                       "$N隨手一揮，$n已入鞘內。 -- 其中$N表示你自己，$n代表道具。\n");
                return 1;
        }

        if ((arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR)
                return 1;

        chk = filter_color(arg);
        if (strlen(chk) >= 2 && chk[0..1] == "你" || strsrch(chk, "\\n你") != -1)
                return notify_fail("對不起，描述不能以“你”字打頭。\n");

        chk = replace_string(chk, " ", "");
        chk = replace_string(chk, "\\n", "");
        chk = replace_string(chk, "$N", "");
        chk = replace_string(chk, "$n", "");
        if (! legal_chinese(chk))
                return notify_fail("對不起，描述必須使用漢字和系統規定可以使用的代表符號。\n");

        // 這裡不區分武器還是裝備，在生成文件時自動選擇一條信息
        /*
        arg = "☆" + arg;
        arg = chinese_desc(arg);
        arg = replace_string(arg, me->name(1), "$N");
        arg = replace_string(arg, "\\n", "\n☆");
        set("item/unwield_msg", arg, ob);
        set("item/remove_msg", arg, ob);
        */
        arg = chinese_desc(arg);
        arg = replace_string(arg, me->name(1), "$N");
        set("item/unwield_msg", arg, ob);
        set("item/remove_msg", arg, ob);
        arg = replace_string(arg, "\\n", "\n");
        arg=replace_string(arg,"$N",query("name", me));
        arg=replace_string(arg,"$n",query("item/name", ob));
        write(CYN "當你收回它的時候將會出現下列描述：\n" NOR + arg + "\n");
        return 1;
}

// 判斷是否是合法的漢字
protected int legal_chinese(string str)
{
        int i;

        if (strlen(str) < 2) return 0;

        for (i = 0; i < strlen(str); i++)
        {
                if (str[i] < 161 || str[i] == 255) return 0;
                if ((! (i % 2)) && str[i] >= 248) return 0;
        }

        return 1;
}

// 轉換字符串中的顏色標志
protected string converts(string arg, int max_len, int no_color)
{
        int i;

        // 去除字符串中的空格，引號，避免被別人利用做破壞
        arg = replace_string(arg, " ", "");
        arg = replace_string(arg, "\"", "'");

        for (i = 0; i < strlen(arg) - 1; i++)
        {
                if (arg[i] == '\\' && arg[i + 1] != 'n')
                {
                        write("字符'\\'後面只能跟隨n字符表示回車！\n");
                        return ILLEGAL_STR;
                }
        }

        arg = replace_string(arg, ",", "，");
        arg = replace_string(arg, ":", "：");
        arg = replace_string(arg, "?", "？");

        if (no_color)
        {
                arg = filter_color(arg, 1);
        } else
        {
                arg = trans_color(arg, 3);
                if (strlen(arg) < strlen(NOR) ||
                    arg[strlen(arg) - strlen(NOR)..<1] != NOR)
                {
                        // append NOR at tail
                        arg += NOR;
                }
        }
        if (strlen(arg) > max_len + 30 ||
            strlen(filter_color(arg)) > max_len)
        {
                write("對不起，這個字符串太長了，請不要輸入超過" + chinese_number(max_len) +
                      "個字符長的字符串。\n");
                // 表示非法的輸入
                return ILLEGAL_STR;
        }
        return arg;
}

int do_finish()
{
        object me;
        object ob;
        object moye;
        string msg;
        int    level;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        if (! objectp(ob = query_temp("item/making")))
        {
                // 數據不對，可能是由于BUG造成，也可能是因為幹將被update過
                write("系統故障：數據不一致，你無法完成煉制道具！\n");
                delete_temp("item", me);
                delete_temp("item");
                if (objectp(moye = present("mo ye")))
                        delete_temp("item", moye);

                // 返回失敗，停止進行
                return 0;
        }

        if( !query("item/name", ob) )
        {
                message_vision("$N瞪了$n一眼，說道：你怎麼能不給它起個"
                               "名字？你要是不想要了就算了！\n",
                               this_object(), me);
                return 1;
        }

        if( !query("item/id", ob) )
        {
                message_vision("$N瞪了$n一眼，說道：你怎麼能不給它起個"
                               "代號？你要是不想要了就算了！\n",
                               this_object(), me);
                return 1;
        }
        
        /*
        level = query("item/level", ob);
        if (! level)
        {
                level=(query("level", me)/10)*10;
                set("item/level", level, ob);
        }
        */
        
        // 顯示 player 輸入的信息
        msg = sprintf("幹將對$N說：你的道具描述如下，請看看有沒有錯。\n");
        message_vision(msg, me);
        // 私有信息
        msg = sprintf("道具名字：%s   道具英文代號：%s\n\n",
                      query("item/name", ob),query("item/id", ob));

        //msg += sprintf("道具等級：%d\n\n",query("item/level", ob));

        if( query("item/long", ob) != "" )
                msg += sprintf(CYN"外觀描述如下："NOR"\n%s\n\n",query("item/long", ob));
        else
                msg += "採用缺省的外觀描述。\n";

        if( query("item/wield_msg", ob) != "" )
                msg += sprintf(CYN "裝備時描述如下：" NOR "\n%s\n\n",
                               replace_string(query("item/wield_msg", ob),"\\n","\n"));
        else
                msg += "裝備時採用缺省的描述。\n";

        if( query("item/unwield_msg", ob) != "" )
                msg += sprintf(CYN "收回時描述如下：" NOR "\n%s\n\n",
                               replace_string(query("item/unwield_msg", ob),"\\n","\n"));
        else
                msg += "收回時採用缺省的描述。\n";
                msg += CYN "如果沒有問題，就可以繼續進行了(y/n):" NOR;
        msg=replace_string(msg,"$N",query("name", me));
        msg=replace_string(msg,"$n",query("item/name", ob));

        tell_object(me, msg);

        // 判定 player 是否決定生成道具
        input_to("confirm_make", ob);
        return 1;
}

void confirm_make(string arg, object ob)
{
        mapping enchase, insert, require;
        mapping temp = ([]);
        object me;
        object moye;
        object item;
        string item_filename;
        int rate, level, quality_level;

        me = this_player();

        if (!objectp(query_temp("item/making")))
        {
                command("kick "+query("id", me));
                command("say 你太磨蹭了，這生意我不做了，恕不退貨！");
                return;
        }

        if (arg != "y" && arg != "Y")
        {
                message_vision("$N對道：那你還是再看看吧！\n", this_object());
                return;
        }

        message_vision("$N對$n說道：好，馬上就好！\n",
                       this_object(), me);

        if (item_filename = create_file(ob))
        {
                // clear the old item's data
                //level = query("item/level", ob);
                enchase = query("item/enchase", ob);
                insert  = query("item/insert", ob);
                require = query("item/require", ob);
                quality_level = query("item/quality_level", ob);
                
                DBASE_D->set_object_data(ob, 0);
                destruct(ob);
                
                /*
                temp["level"] = level;
                rate = random(100);
                if( rate < 40 ) temp["str"] = level*2 + random(level);
                else if( rate < 60 ) temp["con"] = level*2 + random(level);
                else if( rate < 80 ) temp["dex"] = level*2 + random(level);
                else temp["int"] = level*2 + random(level);
                */
                catch(call_other(item_filename, "???"));
                ob = find_object(item_filename);
                if (! ob)
                {
                        message_vision("$N一呆，對$n道：抱歉抱歉！出了一些問題！\n",
                                       this_object(), me);
                } else
                {
                        //set("require", temp, ob);
                        set("require", require, ob);
                        set("enchase", enchase, ob);
                        set("insert", insert, ob);
                        set("quality_level", quality_level, ob);
                        set("status", 1, ob);
                        set("consistence", query("max_consistence", ob), ob);
#ifdef DB_SAVE
                        if (! DATABASE_D->query_db_status())
                                DATABASE_D->connect_to_database();
                        DATABASE_D->db_create_item(ob, ob->query_entire_dbase());
#endif
                        ob->move(me, 1);
                        ob->save();             // Create the record in dbase
                        message_vision("$N把"+query("name", ob)+"交給了$n。\n",
                                       this_object(), me);
                        
                        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/makeweapon");
                        log_file("static/item", sprintf("%s %s created  %s(%s)\n",
                                 log_time(), log_id(me),
                                 filter_color(ob->name(1)),query("id", ob)));
                }
        }
        if (objectp(moye = present("mo ye", environment())))
                delete_temp("item", moye);

        delete_temp("item", me);
        delete_temp("item");
        remove_call_out("waiting");
}

// 生成道具文檔, 需要一個的道具原料對象
// 生成以後建立 ITEM_DIR/???.c 然後刪除舊的原料對象, 生成一件新的道具，返回文件名

// 關于原料對象各個屬性的說明(item/)
// ------ 用戶可以描述的屬性
// name                 道具的名稱， 必須要
// id                   道具的ID，   必須要
// long                 道具的描述，系統會在生成道具時自動添加關于煉制原料的描述
// wield_msg            裝備武器的描述，如果沒有系統會自動生成
// unwield_msg          收回武器時的描述
// wear_msg             穿上護甲時的描述
// unwear_msg           脫掉護甲時的描述

// ------ 不是用戶描述的屬性
// owner_id             制造者的ID
// owner_name           制造者的名字
// unit                 單位
// type                 道具的類型 weapon 或 armor
// stype                道具的子類別 weapon 為 sword, blade, whip, stick ； armor 為 armor
// ctype                道具的類別的中文名 weapon 為 劍、刀、鞭、杖 ； armor 為 護甲
// value                道具的價值
// point                傷害力

// ------ 說明是用戶自練的道具的屬性
// item_make            1

protected object create_object(object item_temp)
{
        string  filename;
        string  desc;
        mapping info;
        string  id;
        object ob;

        info=query("item", item_temp);
        id = info["id"];
        if (info["type"] == "weapon")
        {
                desc="這是由"+query("material_name", item_temp)+"煉制而成的一"+
                       info["unit"] + info["ctype"] + "。\n";

                desc += info["long"];
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

                info["long"] = desc;

                info["makeinfo"] = info["ctype"] + "柄上刻著一行小字：" +
                        info["owner_name"] + "(" + info["owner_id"] + ")\n";

                if (info["wield_msg"] == "")
                {
                        info["wield_msg"] = HIC "$N" HIC "一聲清嘯，" +
                                            (info["stype"] == "throwing" ? "握著一" : "抖出一") +
                                            info["unit"] + HIC "$n" HIC "。" NOR;
                }

                if (info["unwield_msg"] == "")
                {
                        info["unwield_msg"] = "$N隨手一抹，收起了$n。";
                }
                info["wield_msg"] += "\n";
                info["unwield_msg"] += "\n";
                info["max_consistence"] = info["point"];
                info["material"]=query("material_attrib", item_temp);
                info["material_file"] = base_name(item_temp);

                filename = sprintf("/inherit/self/weapon/%s.c", info["stype"]);
                //ob = TEMPLATE_D->create_object(filename, id, info, 0, (["init_damage" : info["point"]*2]));
                ob = TEMPLATE_D->create_object(filename, id, info, 0);
                if( !objectp(ob) )
                        return 0;
                //ob->init_damage(info["point"]*2);
        }
        else
        {
                desc="這是由"+query("material_name", item_temp)+"煉制而成的一"+
                       info["unit"] + info["ctype"] + "。\n";

                desc += info["long"];
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

                info["long"] = desc;

                info["makeinfo"] = info["ctype"] + "緣上刻著一行小字：" +
                        info["owner_name"] + "(" + info["owner_id"] + ")\n";

                if (info["wear_msg"] == "")
                {
                        info["wear_msg"] = YEL "$N" YEL "裝備" +
                                           YEL "$n" YEL "。" NOR;
                }
                if (info["remove_msg"] == "")
                {
                        info["remove_msg"] = YEL "$N" YEL "脫下了" +
                                             YEL "$n" YEL "。" NOR;
                }
                info["wear_msg"] += "\n";
                info["remove_msg"] += "\n";
                info["max_consistence"] = info["point"];
                info["material"]=query("material_attrib", item_temp);
                info["material_file"] = base_name(item_temp);

                filename = sprintf("/inherit/self/armor/%s.c", info["stype"]);
                //ob = TEMPLATE_D->create_object(filename, id, info, 0, (["init_armor" : info["point"]*2]));
                ob = TEMPLATE_D->create_object(filename, id, info, 0);
                if( !objectp(ob) )
                        return 0;
                //ob->init_armor(info["point"]*2);
        }

        return ob;
}

protected string create_file(object item_temp)
{
        string  buf;                    // 生成文件的緩沖區
        string  filename;
        string  desc;
        int     i;
        mapping info;
        string  ih;
        string  id;

        // 生成文件名
        id = query("item/owner_id", item_temp);
        filename = ITEM_DIR + id[0..0] + "/" + id +
                   "-"+query("item/id", item_temp)+".c";
        if( file_size(filename) != -1 )
        {
                write("無法生成檔案，請通知巫師處理。\n");
                return 0;
        }
        assure_file(filename);
        buf="//ITEMMadebyplayer("+query("item/owner_name", item_temp)+
              ":"+query("item/owner_id", item_temp)+")"+filename+
              "\n// Written by GAN JIANG(Doing Lu 1998/11/2)\t" + ctime(time()) + "\n";
        info = query("item", item_temp);
        ih = up_case(info["stype"]);
        if( info["type"] == "weapon" )
        {
                // 生成武器道具文件
                desc = "這是由"+info["material_name"]+"煉制而成的一"+
                       info["unit"] + info["ctype"] + "。\n";

                desc += info["long"];
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

                //info["makeinfo"] = info["ctype"] + "柄上刻著一行小字：" +
                //        info["owner_name"] + "(" + info["owner_id"] + ")\n";
                info["makeinfo"] = HIR "\n" + info["owner_name"] + "(" + info["owner_id"] + ")" + HIR " 出品\n" NOR;

                // 自動補充空信息
                if( info["wield_msg"] == "" )
                {
                        info["wield_msg"] = HIC "$N" HIC "一聲清嘯，" +
                                            (info["stype"] == "throwing" ? "握著一" : "抖出一") +
                                            info["unit"] + HIC "$n" HIC "。" NOR;
                }

                if( info["unwield_msg"] == "" )
                {
                        info["unwield_msg"] = "$N隨手一抹，收起了$n。";
                }

                buf += "#include <ansi.h>\n";
                buf += "#include <weapon.h>\n\n";
                buf += "inherit " + ih + ";\n";
                buf += "inherit F_ITEMMAKE;\n\n";
                buf += "void create()\n{\n";
                buf += sprintf("\tset_name(\"%s\", ({ \"%s\" }));\n",
                                info["name"], info["id"]);
                buf += sprintf("\tset_weight(%d);\n",
                                item_temp->query_weight()*query("item/wscale", item_temp)/100);
                buf += sprintf("\tset(\"item_make\", 1);\n");
                buf += sprintf("\tset(\"unit\", \"%s\");\n", info["unit"]);
                buf += sprintf("\tset(\"long\", \"%s\");\n", desc);
                buf += sprintf("\tset(\"makeinfo\", \"%s\");\n", info["makeinfo"]);
                buf += sprintf("\tset(\"value\", %d);\n", info["value"]);
                if( info["stype"] == "throwing" )
                {
                       buf += sprintf("\tset(\"base_weight\", %d);\n",
                                       item_temp->query_weight()*query("item/wscale", item_temp)/10000);
                       buf += sprintf("\tset(\"base_unit\", \"枚\");\n");
                       // buf += sprintf("\tset(\"base_value\", %d);\n", info["value"] / 100);
                       buf += sprintf("\tset(\"base_value\", 1);\n");
                }
                buf += sprintf("\tset(\"point\", %d);\n", info["prop"]["weapon_prop"]["damage"]);
                //buf += sprintf("\tset(\"consistence\", %d);\n", info["point"]);
                buf += sprintf("\tset(\"max_consistence\", %d);\n", 100);
                buf += sprintf("\tset(\"material\",\"%s\");\n",info["material_attrib"]);
                buf += sprintf("\tset(\"material_file\", \"%s\");\n", info["material_file"]);
                if( info["stype"] == "throwing" )
                {
                        buf += sprintf("\tset(\"hand_msg\", \"%s\\n\");\n", info["wield_msg"]);
                        buf += sprintf("\tset(\"unhand_msg\", \"%s\\n\");\n", info["unwield_msg"]);
                } else
                {
                        buf += sprintf("\tset(\"wield_msg\", \"%s\\n\");\n", info["wield_msg"]);
                        buf += sprintf("\tset(\"unwield_msg\", \"%s\\n\");\n", info["unwield_msg"]);
                }
                buf += sprintf("\tif (! check_clone()) return;\n\trestore();\n");
                if (info["stype"] == "throwing")
                        buf += sprintf("\tset_amount(100);\n");   
                buf += sprintf("\tinit_%s(apply_damage());\n", info["stype"]);    
                buf += prop_segment(info["prop"], "");    
                buf += sprintf("\n\tsetup();\n}\n\n");
                // 生成武器道具文件完畢
        }
        else
        {
                // 生成防護道具文件
                desc="這是由"+info["material_name"]+"煉制而成的一"+
                       info["unit"] + info["ctype"] + "。\n";

                desc += info["long"];
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

                //info["makeinfo"] = info["ctype"] + "柄上刻著一行小字：" +
                //        info["owner_name"] + "(" + info["owner_id"] + ")\n";
                info["makeinfo"] = HIR "\n" + info["owner_name"] + "(" + info["owner_id"] + ")" + HIR " 出品\n" NOR;

                // 自動補充空信息
                if (info["wear_msg"] == "")
                {
                        info["wear_msg"] = YEL "$N" YEL "裝備" +
                                           YEL "$n" YEL "。" NOR;
                }
                if (info["remove_msg"] == "")
                {
                        info["remove_msg"] = YEL "$N" YEL "脫下了" +
                                             YEL "$n" YEL "。" NOR;
                }
                buf += "#include <ansi.h>\n";
                buf += "#include <armor.h>\n\n";
                buf += "inherit " + ih + ";\n";
                buf += "inherit F_ITEMMAKE;\n\n";
                buf += "void create()\n{\n";
                buf += sprintf("\tset_name(\"%s\", ({ \"%s\" }));\n",
                                info["name"], info["id"]);
                buf += sprintf("\tset_weight(%d);\n",
                                item_temp->query_weight()*query("item/wscale", item_temp)/100);
                buf += sprintf("\tset(\"item_make\", 1);\n");
                buf += sprintf("\tset(\"unit\", \"%s\");\n", info["unit"]);
                buf += sprintf("\tset(\"long\", \"%s\");\n", desc);
                buf += sprintf("\tset(\"makeinfo\", \"%s\");\n", info["makeinfo"]);
                buf += sprintf("\tset(\"value\", %d);\n", info["value"]);
                buf += sprintf("\tset(\"point\", %d);\n", info["prop"]["armor_prop"]["armor"]);
                //buf += sprintf("\tset(\"consistence\", %d);\n", info["point"]);
                buf += sprintf("\tset(\"max_consistence\", %d);\n", 100);
                buf += sprintf("\tset(\"material\",\"%s\");\n",info["material_attrib"]);
                buf += sprintf("\tset(\"material_file\", \"%s\");\n", info["material_file"]);
                buf += sprintf("\tset(\"wear_msg\", \"%s\\n\");\n", info["wear_msg"]);
                buf += sprintf("\tset(\"remove_msg\", \"%s\\n\");\n", info["remove_msg"]);
                buf += sprintf("\tif (! check_clone()) return;\n\trestore();\n");
                if( info["stype"] == "hands" || info["stype"] == "finger" )
                {
                        buf += sprintf("\tset(\"armor_prop/armor\", 10);\n");
                        buf += sprintf("\tset(\"armor_prop/unarmed_damage\", apply_damage());\n");
                } else  
                if( info["stype"] == "rings" || info["stype"] == "neck" || info["stype"] == "charm" )
                        buf += sprintf("\tset(\"armor_prop/armor\", 10);\n");     
                else    buf += sprintf("\tset(\"armor_prop/armor\", apply_armor());\n");
                buf += prop_segment(info["prop"], "");
                buf += sprintf("\n\tsetup();\n}\n\n");
                // 生成防護道具文件完畢
        }
        buf += sprintf("string long() { return short() + query(\"makeinfo\") + query(\"long\") + item_long(); }\n");

        if (save_item_file(filename, buf) == 1)
                return filename;
        
        return 0;
}

// add mapping
protected string prop_segment(mapping p, string path)
{
        string path2;
        string buf;
        string *ks;
        int i;

        buf = "";
        if (! p) return buf;

        ks = keys(p);
        for (i = 0; i < sizeof(ks); i++)
        {
                // check the paramter's type
                if (mapp(p[ks[i]]))
                {
                        path2 = path + ks[i] + "/";
                        buf += prop_segment(p[ks[i]], path2);
                } else
                {
                        if( intp(p[ks[i]]) )
                                buf += sprintf("\tset(\"%s\", %d);\n",
                                       path + (string)ks[i], p[ks[i]]);
                        else if( stringp(p[ks[i]]) )
                                buf += sprintf("\tset(\"%s\", \"%s\");\n",
                                       path + (string)ks[i], p[ks[i]]);
                }
        }

        return buf;
}

// filename 是寫入文檔的名稱，已經包含有路徑
// content 是寫入文檔的內容
protected int save_item_file(string filename, string content)
{
        rm(filename);
        if (write_file(filename, content))
        {
                VERSION_D->append_sn(filename);
                return 1;
        } else
        {
                write("寫入檔案(" + filename + ")時出錯，請通知巫師處理。\n");
                return 0;
        }
}

int do_discard(string arg)
{
        string desc, file;
        object money;
        object ob, item;
        object me;
        int n;

        if (! arg)
                return notify_fail("你去退回什麼東西？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上沒有這種東西。\n");

        message_vision("$n拿出一"+query("unit", ob)+ob->name()+
                       "對$N說：“這個東西我想退掉了...”\n",
                       this_object(), me);

        //if (! ob->is_item_make())
        if( !query("material_file", ob) )
        {
                command("heng");
                command("say 這不是我這裡出來的東西，我可不能負責。");
                return 1;
        }

        if( query("equipped", ob) ) 
                return notify_fail("你先解除" + ob->name() + "的裝備再說！\n"); 

        if( ob->item_owner() != query("id", me) )
        {
                command("kick "+query("id", me));
                command("say 你拿了別人的東西還敢來我這裡？以為我是傻子？");
                return 1;
        }

        command("sigh");
        command("say 一千多年來還沒有什麼人嫌我的貨色不好的，算了！算了！");
        message_vision("$N接過$n遞過來的" + ob->name() + "，隨手"
                       "扔進了火爐，呆呆的望了半晌。\n",
                       this_object(), me);

        item=new(query("material_file", ob));
        item->move(me, 1);

        message_vision("不一會兒" + ob->name() + "就熔化成一塊" + item->name() + "。\n",
                       this_object(), me);

        command("say 你既然不滿意我的東西，我也不能收你的錢，"
                "這些算是我退回給你的！");
        n=(query("value", ob)*8/10+9999)/10000;
        if (! n)
        {
                money = new("/clone/money/silver");
                money->set_amount(1);
        } else
        {
                money = new("/clone/money/gold");
                money->set_amount(n);
        }
        message_vision("$N拿出一"+query("unit", item)+item->name()+"交給"
                       "$n。\n", this_object(), me);
        message_vision("$N拿出一些" + money->name() + "交給"
                       "$n。\n", this_object(), me);
        log_file("static/item", sprintf("%s %s discard  %s(%s)\n",
                                log_time(), log_id(me),
                                filter_color(ob->name(1)),query("id", ob)));
        delete("can_summon/"+query("id", ob), me);
        file = base_name(ob) + ".c";
        DBASE_D->clear_object(ob);
        if (sscanf(file, "/data/item/%*s"))
                rm(file);
        money->move(me, 1);
        return 1;
}

int do_notch(string arg)
{
        object me, ob, ob1;
        string *runes;
        int i, n;

        if (! arg)
                return notify_fail("你要將什麼東西開槽？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上沒有這種東西。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的裝備再說！\n");

        if( query("balance", me)<10000000 )
                return notify_fail("你在錢莊裡的存款不夠支付道具開槽費用。\n");

        message_vision(CYN"$n拿出一"+query("unit", ob)+ob->name()+
                       CYN "對$N說：我想請您給" + ob->name() + CYN "開些鑲嵌用的凹槽。\n",
                       this_object(), me);

        if (!ob->is_item_make())
        {
                command("heng");
                command("say 我且能給這如此平凡之物開槽鑽孔？！");
                return 1;
        }

        if( !query("armor_type", ob) &&
            !query("skill_type", ob) )
        {
                command("say 我只給兵器或防具類型的道具開槽打孔。");
                return 1;
        }

        n = query("enchase/flute", ob);
        n++;
        
        if( n > 6 )
                return notify_fail(ob->name() + "已經再開槽到極限了！\n");
                        
        if( !query("armor_type", ob) || (query("armor_type", ob) != "rings" && 
             query("armor_type", ob) != "neck" && query("armor_type", ob) != "charm") )
        {
                if( !ob->is_weapon() && !ob->is_unarmed_weapon() && n > 4 )
                        return notify_fail(ob->name() + "已經再開槽到極限了！\n");
                runes = equip_sockets[to_string(n)];
        }
        else
        {
                if( n > 3 )
                        return notify_fail(ob->name() + "已經再開槽到極限了！\n");
                        
                runes = rings_sockets[to_string(n)];
        }
        
        for( i=0; i< sizeof(runes); i++ )
        {  
                // 需要材料
                if( !objectp(present(runes[i], me)) )
                        return notify_fail("你好象還沒備齊開槽符文"+runes[i]+"吧？\n");
        }

        for( i=0; i< sizeof(runes); i++ )
        {  
                if( objectp(ob1 = present(runes[i], me)) )
                        destruct(ob1);
        }

        message_vision(HIM "$N接過$n" HIM "手中的" + ob->name() + HIM "及符文......\n" NOR,
                     this_object(), me);

        addn("enchase/flute", 1, ob);

        switch(query("material", ob) )
        {
        case "tian jing":
                set("enchase/SN", 8, ob);
                break;
        case "no name":
                set("enchase/SN", 16, ob);
                break;
        default         :
                break;
        }

        ob->save();

        addn("balance", -10000000, me);
        me->save();

        message_vision(HIW "只見一束眩光閃過，" + ob->name() + HIW"上面豁然多了一個圓形的小孔。\n\n" NOR, this_object(), me);

        message_vision(HIC "$N把" + ob->name() + HIC "交還給了$n。\n" NOR, this_object(), me);
        command("say 行了，行了！你可以走了。");
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/notch");
        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;

        i = strlen(name);
        if ((strlen(name) < 2) || (strlen(name) > max_len ))
        {
                write(sprintf("對不起，中文字必須是 1 到 %d 個中文字。\n",
                      max_len / 2));
                return 0;
        }

        if (max_len < 9 && ! is_chinese(name))
        {
                write("對不起，請您用「中文」為套裝取名字。\n");
                return 0;
        }
        return 1;
}

void get_modname(string arg, object me, object ob)
{
        mapping prop;
        string arg_old;
        string type;

        if( arg == "q" || arg == "Q" ) {
                write("你取消了綠化套裝，將裝備取回。\n");
                return;
        }
        if( query_temp("big5", me) )
                arg = LANGUAGE_D->Big52GB(arg);

        arg_old = arg;
        arg = trans_color(arg, 3);
        arg = filter_color(arg, 1);

        if (! check_legal_name(arg, 8))
        {
                write("請給你的綠化裝備起個套裝名稱(不要超過4個字，可加顏色)：\n");
                input_to( (: get_modname :), me, ob);
                return;
        }
        
        if( !(type = query("skill_type", ob)) )
                type = query("armor_type", ob);
                
        arg = arg_old;
        arg = trans_color(arg, 3);
        //arg = HIG "※" NOR+arg+NOR+HIG "※" NOR;

        prop = EQUIPMENT_D->apply_ultimate_prop(ob, type, 3);
        set("enchase/mod_prop", prop, ob);
        set("mod_name", arg, ob);
        //mark++;
        //set("mod_mark", "M"+(10000+mark), ob);
        set("mod_mark", base_name(ob), ob);
        set("mod_level", "1", ob);
        ob->save();
        delete_temp("paid/dosuit", me);

        message_sort(HIY "\n幹將小心翼翼地接過" + ob->name() + HIY "，輕輕地來回撫摩，但見" + ob->name() +
                     HIY "表面微微泛起紫色光芒，若隱若現，猶如遙遠夜空中的一點星光。隨即，幹將將" + ob->name() +
                     HIY "交予旁邊的莫邪，莫邪微微一笑，雙手托起" + ob->name() + HIY "，口中默默地念著奇怪的咒語 ……" +
                         "一柱香後" + ob->name() + HIY "表面的紫芒消失不見，但旋即被數道青芒包裹著，並伴隨著" +
                         "一道金色的電光，異常閃耀，似乎要將一切吞噬……莫邪輕噓一聲，又小心翼翼地將" + ob->name() + HIY "交還到" +
                         "幹將手中，幹將再次輕撫" + ob->name() + HIY "，奇怪的是，" + ob->name() + HIY "周圍的光芒" +
                         "突然間消失，回復了平靜！\n\n" NOR, me);

        CHANNEL_D->do_channel(this_object(), "chat", HIY "恭喜" + query("name", me) + HIY "的" + ob->name() + HIY "升級為" + 
                                                          suit_level[query("mod_level", ob)] + HIY "品質！\n" NOR);
                                                          
        tell_object(me, HIG "幹將把 " + ob->name() + HIG + "交給了你。\n" NOR);
        MYGIFT_D->check_mygift(me, "newbie_mygift/dosuit");
        return;
}

int do_suit(string arg)
{
        object me, obj;

        string *type_list = ({
                "head",
                "waist",
                "boots",
                "surcoat",
                "armor",
                "cloth",
                "wrists",
                "neck",
                "rings",
                "charm",
        });

        me = this_player();

        if (! query_temp("paid/dosuit", me)) 
                return notify_fail("幹將說道：”你想幹什麼，別打攪我思考！“\n");

        if (! arg) return notify_fail("你要為什麼物品綠化套裝屬性 dosuit <物品ID> \n");

        if (! objectp(obj = present(arg, me)))
                return notify_fail("你身上沒有這樣道具。\n");
        
        if( query("equipped", obj) )
                return notify_fail("你先解除" + obj->name() + "的裝備再說！\n");
                
        if (! obj->is_item_make())
                return notify_fail("這樣物品不能升級套裝屬性。\n");
        
        /*
        if (obj->item_owner() != query("id", me))
                return notify_fail("這個，好象不屬于你吧，這樣不大合適。\n");
        */
        
        // 判斷目標是否屬于可以升級的套裝部件
        if (! obj->is_weapon() && !obj->is_unarmed_weapon() )
                if (member_array(query("armor_type", obj), type_list) == -1)
                        return notify_fail("該裝備種類不能進行綠化套裝，詳情見 help suit 說明。\n");

        if (query("status", obj) < 6)
                return notify_fail(obj->name() + NOR "的品質還不完美，無法綠化套裝！\n");

        if (query("balance", me) < 10000000)
                return notify_fail("你銀行裡的錢不夠吧，為" + obj->name() + NOR "綠化套裝需要" +
                                   HIY "一千兩黃金，" NOR "還是湊夠再來吧！\n");

        // 判斷目標部件是否已經綠化套裝
        if (query("mod_name", obj))
        {
                if (!query_temp("pending/dosuit", me))
                {
                        set_temp("pending/dosuit", 1, me);
                        return notify_fail(obj->name() + NOR "已經被綠化成套裝的一個部件了，想要重新綠化請再輸入一次dosuit！\n");
                }

                delete("mod_level", obj);
                delete("mod_name", obj);
                delete("enchase/mod_prop", obj);
        }

        delete_temp("pending/dosuit", me);
        addn("balance", -10000000, me);

        write("請給你的綠化套裝起個套裝名稱(不要超過4個字，可加顏色)：\n");
        input_to( (: get_modname :), me, obj);
        return 1;
}

int do_upsuit(string arg)
{
        object me, ob, item;
        mixed level;

        me = this_player();
        
        if( !arg ) return notify_fail("你要提升哪個套裝部件品級 upsuit <物品ID> \n");

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上沒有這樣道具。\n");
        
        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的裝備再說！\n");
                
        if( !ob->is_item_make() )
                return notify_fail("這樣物品不能升級套裝品級。\n");
        
        if( !query("mod_name", ob) )
                return notify_fail("你先綠化套裝後，才能升級套裝品級。\n");
        
        if( (level = query("mod_level", ob)) == "4" )
                return notify_fail(ob->name() + NOR "已達到最高級別─造化神器！\n");
        
        /*       
        if( ob->item_owner() != query("id", me) )
                return notify_fail("這個，好象不屬于你吧，這樣不大合適。\n");
        */
        
        if( !objectp(item = present("hongmeng lingqi", me)) )
                return notify_fail("你好象還沒備齊鴻蒙靈氣吧？\n");

        if (query("balance", me) < 100000000)
                return notify_fail("你銀行裡的錢不夠吧，為" + ob->name() + NOR "提升套裝品級需要" +
                                   HIY "一萬兩黃金，" NOR "還是湊夠再來吧！\n");
        
        level = to_int(level);
        level++;
        level = to_string(level);
        set("mod_level", level, ob);
        ob->save();
        message_sort(HIY "\n幹將小心翼翼地接過" + ob->name() + HIY "，輕輕地來回撫摩，但見" + ob->name() + 
	             HIY "表面微微泛起紫色光芒，若隱若現，猶如遙遠夜空中的一點星光。隨即，幹將將" + ob->name() + 
	             HIY "交予旁邊的莫邪，莫邪微微一笑，雙手托起" + ob->name() + HIY "，口中默默地念著奇怪的咒語 ……" + 
	                 "一柱香後" + ob->name() + HIY "表面的紫芒消失不見，但旋即被數道青芒包裹著，並伴隨著" + 
	                 "一道金色的電光，異常閃耀，將"+item->name()+HIY"吞噬……莫邪輕噓一聲，又小心翼翼地將" + ob->name() + HIY "交還到" + 
	                 "幹將手中，幹將再次輕撫" + ob->name() + HIY "，奇怪的是，" + ob->name() + HIY "周圍的光芒" + 
	                 "突然間消失，回復了平靜！\n\n" NOR, me);
        
        destruct(item);
        addn("balance", -100000000, me);

        CHANNEL_D->do_channel(this_object(), "chat", HIY "恭喜" + query("name", me) + HIY "的" + ob->name() + HIY "升級為" + 
                                                          suit_level[query("mod_level", ob)] + HIY "品質！\n" NOR);

        if( query("mod_level", ob) == "4" )                                           
                CHANNEL_D->do_channel(get_object(__DIR__"moye"), "chat", HIC "不想千年之後，能再次見到傳說中的造化神器，實在是死而無憾也！\n" NOR);                                                    

        tell_object(me, HIG "幹將把 " + ob->name() + HIG + "交給了你。恭喜你" + 
                       ob->name() + HIG "升級為" + suit_level[query("mod_level", ob)] + HIG "品質！\n" NOR);
        return 1;
}

int do_reform(string arg)
{
        mapping props;
        object me;
        object ob, ob1, ob2, ob3;
        string item, what, soul, type;
        string *apply;
        int i, status, qlvl, success, value;
        
        me = this_player();
        
        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || sscanf(arg, "%s with %s & %s", item, soul, what ) != 3 )
                return notify_fail("改造裝備指令格式：reform <裝備> with <裝備之魂> & <無名或天晶>\n");

        if( !objectp(ob = present(item, me)) )
                return notify_fail("你身上沒有這樣裝備用來改造。\n");
        
        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的裝備再說！\n");
                
        if( !ob->is_item_make() )
                return notify_fail("這樣物品不能改造品質。\n");
        
        /*
        if( ob->item_owner() != query("id", me) )
                return notify_fail("這個，好象不屬于你吧，這樣不大合適。\n");
        */
        
        if( query("status", ob) == 6 )
                return notify_fail(ob->name()+"已經達到完美品級了，不需要繼續改造了。\n");
                
        // 需要無名之物
        if( !objectp(ob1 = present(what, me)) || !ob1->is_reform_ob())
                return notify_fail("你好象還沒備齊無名之物或寰宇天晶吧？\n");

        // 需要裝備之魂
        if( !objectp(ob2 = present(soul, me))|| !ob2->is_equip_soul() )
                return notify_fail("你好象還沒備齊改造需要的裝備之魂吧？\n");
        
        type = query("type", ob2); // 裝備之魂部位

        if( ob->is_weapon() )
        {
                if( type != "weapon" )
                        return notify_fail("改造"+ob->name()+NOR"需要武器之魂！\n");
        }
        else
        {
                if( type != query("armor_type", ob) )
                        return notify_fail("改造"+ob->name()+NOR"需要"+query("armor_type", ob)+"之魂！\n");
        }
        
        status = query("status", ob2); // 裝備之魂等級
        qlvl = query("status", ob);
        if( !qlvl ) 
        {
                set("status", 1, ob);
                qlvl = 1;
        }
        if( status <= qlvl )
                return notify_fail("你的裝備之魂等級不夠，無法改造！\n");
        
        if( query("balance", me) < 100000000 )
                return notify_fail("你的銀行存款不足，改造費用需要一萬兩黃金。\n");
                
        if( qlvl == 1 ) success = 80;
        else if( qlvl == 2 ) success = 70;
        else if( qlvl == 3 ) success = 40;
        else if( qlvl == 4 ) success = 20;
        else if( qlvl == 5 ) success = 10;
        
        success += (status - qlvl) * 10;
        
        if( success < 70 )
        {
                if( query("id", ob1) == "tian jing" )
                {
                        if( objectp(ob3 = present("ouyezi symbol", me)) )
                                success = 70;
                }
        }
        if( success < 90 )
        {
                if( query("id", ob1) == "no name" )
                {        
                        if( objectp(ob3 = present("ouyezi symbol", me)) )
                                success = 90;
                }
        }
        
        if( random(100) < success || query("id", me) == "lonely" )
        {
                addn("reform/apply_prop/max_jing", 1000*(qlvl+1), ob);     // 增加精
                addn("reform/apply_prop/max_qi", 2000*(qlvl+1), ob);       // 增加氣
                addn("status", 1, ob);

                if( type == "rings" || type == "neck" || type == "charm" )
                {
                        addn("reform/apply_prop/research_effect", 1, ob);
                        addn("reform/apply_prop/derive_effect", 1, ob);
                        addn("reform/apply_prop/practice_effect", 1, ob);
                }

                tell_object(me, HIC "你感受" + ob->name() + HIC "發生了不可言喻的變化。\n" NOR); 
                if( query("status", ob) == 6 )
                {
                        if( type == "rings" || type == "neck" || type == "charm" )
                        {
                                addn("reform/apply_prop/research_effect", 3, ob);
                                addn("reform/apply_prop/derive_effect", 3, ob);
                                addn("reform/apply_prop/practice_effect", 3, ob);
                                tell_object(me, HIC "完美的品質使得" + ob->name() + HIC "的研究、汲取、練習的效果提高了3%。\n" NOR); 
                        }
                        else
                        {
                                addn("enchase/flute", 1, ob);
                                tell_object(me, HIC "完美的品質使得" + ob->name() + HIC "多了一個凹槽。\n" NOR); 
                        }
                        if( ob->is_weapon() )
                        {
                                props = copy(query("weapon_prop", ob));
                                map_delete(props, "damage");
                        }
                        else 
                        {
                                props = copy(query("armor_prop", ob));
                                map_delete(props, "unarmed_damage");
                                map_delete(props, "armor");
                        }
                        if( sizeof(props) > 0 )
                        {
                                apply = keys(props);
                                for( i=0;i<sizeof(apply);i++ )
                                {
                                        value = EQUIPMENT_D->query_prop_value(apply[i], 3, 1); // 強化值
                                        if( query("quality_level", ob) == 4 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        value = value * 3;
                                        } else
                                        if( query("quality_level", ob) == 5 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        value = value * 4;
                                                else if( sizeof(apply) == 2 )
                                                        value = value * 2;
                                        } else
                                        if( query("quality_level", ob) == 6 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        value = value * 16;
                                                else if( sizeof(apply) == 2 )
                                                        value = value * 8;
                                                else if( sizeof(apply) == 3 )
                                                        value = value * 4;
                                                else
                                                        value = value * 2;
                                        }
                                        addn("reform/apply_prop/"+apply[i], value, ob); 
                                        tell_object(me, HIC "完美的品質使得" + ob->name() + HIC "的" + EQUIPMENT_D->chinese(apply[i]) + "提高了"+value +"。\n" NOR); 
                                }
                        }
                }
                
                MYGIFT_D->check_mygift(me, "newbie_mygift/reform");      
        }
        else
                tell_object(me, HIW "很遺憾，改造失敗。\n" NOR);
        
        addn("balance", -100000000, me);
        if( objectp(ob3) ) destruct(ob3);       
        destruct(ob1);
        destruct(ob2);
        ob->save();
        return 1;
}

int do_show(string arg)
{
        mapping props;
        string str, what, element;
        string *apply;
        object me, ob;
        int i, n, level;
       
        if( !arg )
                return notify_fail("你要亮出什麼東西？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上沒有這種東西。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的裝備再說！\n");
                
        message_vision("$n拿出一"+query("unit", ob)+ob->name()+
                       "對$N說：“拜托拜托...”\n",
                       this_object(), me);

        if( !ob->is_item_make() )
        {
                command("heng");
                command("say 這...這...我看還是算了吧！");
                return 1;
        }
        
        if( !mapp(props = query("enchase/apply_prop", ob)) || !mapp(query("insert", ob)) )
                return notify_fail(ob->name() + NOR "連寶石都沒有鑲嵌，如何能強化。\n");
        
        level = query("qianghua/level", ob);
        what = qianghua_rune[to_string(level)];
        
        str = CYN"幹將說道：強化"+ob->name()+CYN"到"+(level+1)+"星需要材料有：乾坤聖水、";
        str += "符文"+what + " 3個以及下列的屬性元素\n";
          
        props = query("enchase/apply_prop", ob);
        apply = keys(props);
        n = sizeof(apply);
        for( i=0;i<n;i++ )
        {
                element = apply[i];
                str += EQUIPMENT_D->chinese(element)+"元素3個"; 
                if( i+1 == n ) str += "，\n";
                else if( (i+1) % 6 == 0 ) str += "、\n"; 
                else str += "、";      
        }
        
        str += "如果你備齊了以上材料，請輸入qianghua <裝備>進行強化。\n" NOR;
        tell_object(me, str);

        return 1;
}

int do_increase(string arg)
{
        mapping props;
        string what, item, element;
        object me, ob, crystal;
        object ob_water, ob_zz1, ob_zz2, ob_zz3;
        object ob_rune1, ob_rune2, ob_rune3;
        object *obs;
        int level, value, success;
        string *apply;
        int i, n;
        int wash;
        int rate, rate2;

        me = this_player();
        
        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg )
                return notify_fail("強化裝備指令格式：qianghua <裝備> 或 qianghua <裝備> with <強化水晶>\n");
        
        if( sscanf(arg, "%s with %s", arg, item ) == 2 )
        {
                if( !objectp(ob = present(arg, me)) )
                        return notify_fail("你身上沒有這樣裝備用來強化。\n");
                
                if( !objectp(crystal = present(item, me)) )
                        return notify_fail("你身上沒有這樣道具用來輔助強化。\n");
        } 
        else     
        {
                if( !objectp(ob = present(arg, me)) )
                        return notify_fail("你身上沒有這樣裝備用來強化。\n");
        }
        
        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的裝備再說！\n");
                
        if( !ob->is_item_make() )
                return notify_fail("這樣物品不能強化屬性。\n");
        
        /*
        if( ob->item_owner() != query("id", me) )
                return notify_fail("這個，好象不屬于你吧，這樣不大合適。\n");
        */
        
        if( !mapp(props = query("enchase/apply_prop", ob)) || !mapp(query("insert", ob)) )
                return notify_fail(ob->name() + NOR "必須鑲嵌寶石後才能強化。\n");
                
        if( query("status", ob) < 6 )
               return notify_fail(ob->name() + NOR "沒有達到完美品級，無法強化！\n");
            
        // 需要乾坤聖水
        if( !objectp(ob_water = present("bless water", me)) )
                return notify_fail("你好象還沒備齊乾坤聖水吧？\n");    
       
        level = query("qianghua/level", ob); 
        // 需要符文
        what = qianghua_rune[to_string(level)];  
        if( !objectp(ob_rune1 = present(what + " 1", me)) || !ob_rune1->is_rune() )
                return notify_fail("你好象還沒備齊3個"+what+"吧？\n");

        if( !objectp(ob_rune2 = present(what + " 2", me)) || !ob_rune2->is_rune() )
                return notify_fail("你好象還沒備齊3個"+what+"吧？\n");

        if( !objectp(ob_rune3 = present(what + " 3", me)) || !ob_rune3->is_rune() )
                return notify_fail("你好象還沒備齊3個"+what+"吧？\n");

        // 需要黃金一萬兩
        if( query("balance", me) < 100000000 )
                return notify_fail("你的銀行裡好象沒有備齊1萬兩黃金吧。\n");
         
        apply = keys(props);
        n = sizeof(apply);
        for( i=0;i<n;i++ )
        {
                if( query("id", me) == "lonely" ) break;
                // 需要強化材料
                element = apply[i];
                if( !objectp(ob_zz1 = present(element + " 1", me)) )
                        return notify_fail("你好象還沒備齊強化需要的3個"+element+"元素吧？\n");

                if( base_name(ob_zz1) != "/inherit/template/element/element" )
                        return notify_fail("你好象還沒備齊強化需要的3個"+element+"元素吧？\n");

                if( !objectp(ob_zz2 = present(element + " 2", me)) )
                        return notify_fail("你好象還沒備齊強化需要的3個"+element+"元素吧？\n");

                if( base_name(ob_zz2) != "/inherit/template/element/element" )
                        return notify_fail("你好象還沒備齊強化需要的3個"+element+"元素吧？\n");

                if( !objectp(ob_zz3 = present(element + " 3", me)) )
                        return notify_fail("你好象還沒備齊強化需要的3個"+element+"元素吧？\n");

                if( base_name(ob_zz3) != "/inherit/template/element/element" )
                        return notify_fail("你好象還沒備齊強化需要的3個"+element+"元素吧？\n");
        }
        for( i=0;i<n;i++ )
        {
                if( query("id", me) == "lonely" ) break;
                element = apply[i];
                if( !objectp(ob_zz1 = present(element + " 1", me)) )
                        return notify_fail("你好象還沒備齊強化需要的3個"+element+"元素吧？\n");
                if( !objectp(ob_zz2 = present(element + " 2", me)) )
                        return notify_fail("你好象還沒備齊強化需要的3個"+element+"元素吧？\n");
                if( !objectp(ob_zz3 = present(element + " 3", me)) )
                        return notify_fail("你好象還沒備齊強化需要的3個"+element+"元素吧？\n");
                
                destruct(ob_zz1);
                destruct(ob_zz2);
                destruct(ob_zz3);
        }        
        
        destruct(ob_water);
        destruct(ob_rune1);
        destruct(ob_rune2);
        destruct(ob_rune3);
        addn("balance", -100000000, me);
               
        command("say 不錯，既然我要的東西你都備齊了，我這就開始強化"+ob->name()+NOR+CYN"。\n"NOR);
        
        if( level == 0 ) success = 70;
        else if( level == 1 ) success = 70;
        else if( level == 2 ) success = 70;
        else if( level == 3 ) success = 50;
        else if( level == 4 ) success = 35;
        else if( level == 5 ) success = 20;
        else if( level == 6 ) success = 15;
        else if( level == 7 ) success = 10;
        else if( level == 8 ) success = 5;
        
        if( query("material", ob) == "no name" )
                success += 5;
        
        message_vision(HIW "\n$N將乾坤聖水、符文和元素粉末混合在一起融合，然後將融合後的乾坤聖水緩緩洒在" + ob->name() + HIW "上，\n頃刻間"
                       + ob->name() + HIW "猶如烈火中重生一般，散發出絢目的光彩！\n\n", this_object(), me);
        
        rate = random(100);
/*
        rate2 = random(100);
        rate = (rate + rate2)/2;
*/
        if( rate < success || (level < 6 && objectp(crystal)) || query("id", me) == "lonely" )
        {      
                level++;
                for(  i=0;i<n;i++ )
                {               
                        what = apply[i];
                        value = EQUIPMENT_D->query_prop_value(what, level, 1); // 強化值
                        // set("enchase/pink_prop/"+what, value, ob); 
                        set("qianghua/apply_prop/"+what, value, ob); 
                }
                addn("qianghua/level", 1, ob);
                ob->save();
                tell_object(me, HIG "強化成功！" + ob->name() + HIG "強化等升至 " + 
                                sprintf(HIY "%d" HIG, query("qianghua/level", ob)) + " 星。\n" NOR); 
                if( query("qianghua/level", ob) >= 4 ) 
                { 
                        if( !wizardp(me) )
                        CHANNEL_D->channel_broadcast("news",  
                                                      YEL "聽說" + ob->name() +  
                                                      YEL "強化至 " HIR + sprintf("%d", query("qianghua/level", ob)) +  
                                                      YEL " 星。\n" NOR); 
                } 
                if( query("qianghua/level", ob) >= 9 )
                {
                        if( !wizardp(me) )
                        CHANNEL_D->channel_broadcast("news",
                                                      YEL "恭喜" + ob->name() +  
                                                      YEL "強化為曠世神兵！\n" NOR); 
                }
                tell_object(me, HIC "你感受" + ob->name() + HIC "發生了不可言喻的變化。\n" NOR); 
                if( objectp(crystal) )
                        destruct(crystal);
                        
                MYGIFT_D->check_mygift(me, "newbie_mygift/qianghua");     
        }        
        else
        {
                if( query("qianghua/level", ob) > 4 )
                {
                        if( objectp(crystal=present("shengling crystal", me)) )
                        {
                                destruct(crystal);
                                tell_object(me, HIR "很遺憾，強化失敗。\n" NOR);
                        }
                        else
                        {
                                set("qianghua/level", 4, ob);
                                ob->save();
                                tell_object(me, HIR "很遺憾，強化失敗了(強化等級降為4級）！\n" NOR); 
                        }
                }
                else
                        tell_object(me, HIR "很遺憾，強化失敗。\n" NOR);
        }
        message_vision("$N" NOR "拿出" + ob->name() + NOR "還給$n" NOR "。\n" NOR, this_object(), me);
        return 1;
}

// 裝備簽名
int do_signature(string arg)
{
        object me, ob;
        mapping data, enchase, insert, require;
        mapping prop, armor_prop, weapon_prop;
        int value, quality_level;
        string type, ctype, stype, unit;
        string material_attrib, material_name, material_file;
        
        if( query_temp("item") ) return notify_fail("幹將正忙著呢，稍等會。\n");

        if (! arg)
                return notify_fail("你要將什麼裝備簽名？\n");
        
        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上沒有這種東西。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的裝備再說！\n");

        if( ob->is_item_make() )
                return notify_fail(ob->name() + "不是已經簽名過了嗎。\n");
                
        if( !query("can_sign", ob) )
                return notify_fail(ob->name() + "無法簽名！\n");

        if( query("require/level", ob) < 20 )
                return notify_fail("我只給20級以上的裝備簽名！\n");

        if( query("balance", me) < 10000000 )
                return notify_fail("你在錢莊裡的存款不夠支付裝備簽名費用。\n");

        message_vision(CYN"$n拿出一"+query("unit", ob)+ob->name()+
                       CYN "對$N說：我想給" + ob->name() + CYN "簽名。\n",
                       this_object(), me);

        if( !(stype = query("armor_type", ob)) &&
            !(stype = query("skill_type", ob)) )
        {
                command("say 我只給兵器或防具類型的裝備簽名。");
                return 1;
        }
        
        set_temp("item/status", "makeing");
        message_vision(HIM "$N接過$n" HIM "手中的" + ob->name() + HIM "，仔細端詳了半天，嘆道：明珠蒙塵，可惜啊可惜！！！\n"
                        "也罷，既然此物與你有緣，那我就幫你銘刻簽名。說完，隨手將" + ob->name() + HIM "拋入爐中，\n" +
                        ob->name() + HIM "轉眼間就被爐火吞沒。\n" NOR,
                        this_object(), me);
        
        if( query("skill_type", ob) )
        {
                type = "weapon";
                material_name = "百煉精鐵";
                material_attrib = "iron";
                material_file = "/d/item/obj/jingtie";            
                if( query("skill_type", ob) == "throwing" )
                        ctype = filter_color(query("name", ob), 1)[<4..<1];
                else
                        ctype = filter_color(query("name", ob), 1)[<2..<1];
        }
        else 
        {
                type = "armor";
                material_name = "冰蠶絲";
                material_attrib = "silk";
                material_file = "/d/item/obj/tiancs";
                if( query("armor_type", ob) == "charm" )
                        ctype = filter_color(query("name", ob), 1)[<6..<1]; 
                else   
                        ctype = filter_color(query("name", ob), 1)[<4..<1];
        }
        unit = query("unit", ob);
        
        data = ob->query_entire_dbase();
        
        enchase = data["enchase"];
        insert  = data["insert"];
        require = data["require"];
        quality_level = data["quality_level"];
        value = pow(quality_level,3) * 100000;
        if( query("skill_type", ob) )
        {
                weapon_prop = data["weapon_prop"];
                map_delete(weapon_prop, "damage");
                prop = ([ "weapon_prop" : weapon_prop ]);
        }
        else
        {
                armor_prop = data["armor_prop"];
                map_delete(armor_prop, "unarmed_damage");
                map_delete(armor_prop, "armor");
                prop = ([ "armor_prop" : armor_prop ]);        
        }       
        set("item/value", value, ob);
        set("item/type", type, ob);
        set("item/ctype", ctype, ob);
        set("item/stype", stype, ob);
        set("item/unit", unit, ob);
        set("item/material_attrib", material_attrib, ob); 
        set("item/material_name", material_name, ob); 
        set("item/material_file", material_file, ob); 
        set("item/enchase", enchase, ob);
        set("item/insert", insert, ob);
        set("item/require", require, ob);
        set("item/quality_level", quality_level, ob);
        set("item/wscale", 100, ob);
        set("item/prop", prop, ob);
        set("item/owner", me, ob);
        set("item/owner_id", query("id", me), ob);
        set("item/owner_name", query("name", me), ob);
       
        addn("balance", -10000000, me);
        me->save();
        
        set_temp("item/making", ob);
        set_temp("item/player", me);
        set_temp("item/status", "waiting", me);
        ob->move(this_object());
        work_step_6(me, ob);
        return 1;
}

int do_cuilian(string arg)
{
        object me, ob, obj, item;
        string target, what;
        string filename, content_str;
        string *content;
        string type;
        int i, n, a, b;
        
        me = this_player();
        
        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || sscanf(arg, "%s with %s", target, what ) != 2 )
                return notify_fail("淬煉裝備指令格式：cuilian <裝備> with <物品>\n");

        if( !objectp(item = present(target, me)) )
                return notify_fail("你身上沒有這樣裝備用來淬煉。\n");
        
        if( query("equipped", item) )
                return notify_fail("你先解除" + item->name() + "的裝備再說！\n");
                
        if( !item->is_item_make() )
                return notify_fail("這樣物品不可通過淬煉提升。\n");

        if( item->item_owner() != query("id", me) )
                return notify_fail("這個，好象不屬于你吧，這樣不大合適。\n");
        
        if( !objectp(ob = present(what, me)) )
                return notify_fail("你身上沒有這樣道具用來淬煉裝備。\n");
                
        if( !query("item_origin", ob) || !(type=query("can_make", ob)) )
                return notify_fail(ob->name()+"不是淬煉裝備的材料。\n");
        
        if( type != "all" && type != query("skill_type", item) && type != query("armor_type", item) )
                return notify_fail(ob->name()+"無法用來淬煉該類型裝備。\n");
                
        if( query("balance", me) < 10000000 )
                return notify_fail("你銀行裡的錢不夠吧，為" + item->name() + NOR "淬煉需要" +
                                   HIY "一千兩黃金，" NOR "還是湊夠再來吧！\n");

        addn("balance", -10000000, me);

        message_vision(HIM "$N接過$n" HIM "手中的" + item->name() + HIM "，仔細端詳了半天，嘆道：明珠蒙塵，可惜啊可惜！！！\n"
                     "也罷，既然你找到好的材料，那我就幫你淬煉一番。說完，隨手將" + item->name()+HIM"和"+ob->name() + HIM "拋入爐\n" +
                     "內，霎時間，那" + item->name()+HIM"和"+ob->name() + HIM "已被火爐中的熊" HIR "烈燄" HIM "吞沒。\n"
                     "$N凝視著爐火，仰天嘆道：天地之精華為其血脈，日月之光輝是其靈氣......\n" NOR,
                     this_object(), me);
        
        filename = base_name(item) + ".c";    
        destruct(item);          
        content_str = read_file(filename); 
        rm(filename); 
        content = explode(content_str, "\n"); 
        n = sizeof(content); 
        for (i = 0; i < n; i++) 
        {
                /*
                if( (a = strsrch(content[i], "是由")) > 0 && (b = strsrch(content[i], "煉制而成的一")) > 0 ) 
                        content[i] = content[i][0..a]) + "是由" + query("material_name", ob) + content[i][b..]);
                */
                if( (a = strsrch(content[i], "這是由")) > 0 && (b = strsrch(content[i], "煉制而成的一")) > 0 ) 
                        content[i] = sprintf("\tset(\"long\", \"這是由%s%s", query("material_name", ob), content[i][b..]);
                else        
                if( strsrch(content[i], "material_file") != -1 ) 
                        content[i] = sprintf("\tset(\"material_file\",\"%s\");", base_name(ob));
                else        
                if( strsrch(content[i], "material") != -1 ) 
                        content[i] = sprintf("\tset(\"material\",\"%s\");", query("material_attrib", ob)); 
                
                write_file(filename, content[i] + "\n"); 
        }
        
        catch(call_other(filename, "???")); 
        obj = find_object(filename); 
        if( !obj ) 
        {
                write(HIR "裝備淬煉出現問題，請匯報給巫師！\n" NOR); 
        }
        else 
        {
                destruct(ob);
                obj->move(me, 1); 
                message_vision("$N" NOR "拿出已經淬煉好的" + obj->name() + NOR "給$n" NOR "。\n" NOR, this_object(), me);
        }
        
        return 1;
}
