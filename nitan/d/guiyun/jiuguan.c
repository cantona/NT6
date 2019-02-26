// Room: /d/guiyun/jiuguan.c
// Last Modified by winder on Jul. 9 2001

#define KICK_TO        __DIR__"road2"

inherit ROOM;

int do_sit(string arg);
int do_stand();
int do_order(string arg);
int do_eat(string arg);
int do_drink(string arg);
int do_pay();
int do_buy();
int do_quit();
string look_sign();
string look_table();
void quarter_pass();

mapping *food = ({
([        "name" : "油條",
        "unit" : "根",
        "short" : "youtiao",
        "value" : 10,
        "time" : "早",
        "remaining" : 1,
        "supply" : 30
]),
([        "name" : "小籠包",
        "unit" : "盤",
        "short" : "baozi",
        "value" : 20,
        "time" : "早",
        "remaining" : 2,
        "supply" : 30
]),
([        "name" : "米飯",
        "unit" : "碗",
        "short" : "mifan",
        "value" : 40,
        "time" : "午",
        "remaining" : 4,
        "supply" : 30
]),
([        "name" : "魚香肉絲",
        "unit" : "盤",
        "short" : "rousi",
        "value" : 120,
        "time" : "午",
        "remaining" : 6,
        "supply" : 50
]),
([        "name" : "清蒸鯉魚",
        "unit" : "盤",
        "short" : "liyu",
        "value" : 200,
        "time" : "午",
        "remaining" : 9,
        "supply" : 50
]),
([        "name" : "米飯",
        "unit" : "碗",
        "short" : "mifan",
        "value" : 40,
        "time" : "晚",
        "remaining" : 4,
        "supply" : 30
]),
([        "name" : "魚香肉絲",
        "unit" : "盤",
        "short" : "rousi",
        "value" : 120,
        "time" : "晚",
        "remaining" : 6,
        "supply" : 50
]),
([        "name" : "清蒸鯉魚",
        "unit" : "盤",
        "short" : "liyu",
        "value" : 200,
        "time" : "晚",
        "remaining" : 9,
        "supply" : 50
]),
([        "name" : "東坡肘子",
        "unit" : "盤",
        "short" : "zhouzi",
        "value" : 250,
        "time" : "晚",
        "remaining" : 8,
        "supply" : 60
])
});

mapping *liquid = ({
([        "name" : "麪湯",
        "unit" : "碗",
        "short" : "miantang",
        "value" : 10,
        "time" : "早",
        "remaining" : 2,
        "supply" : 12
]),
([        "name" : "稀粥",
        "unit" : "碗",
        "short" : "xizhou",
        "value" : 16,
        "time" : "早",
        "remaining" : 2,
        "supply" : 18
]),
([        "name" : "稀粥",
        "unit" : "碗",
        "short" : "xizhou",
        "value" : 16,
        "time" : "午",
        "remaining" : 2,
        "supply" : 18
]),
([        "name" : "米酒",
        "unit" : "壇",
        "short" : "mijiu",
        "value" : 130,
        "time" : "午",
        "remaining" : 9,
        "supply" : 40
]),
([        "name" : "三鮮湯",
        "unit" : "碗",
        "short" : "sanxiantang",
        "value" : 70,
        "time" : "午",
        "remaining" : 8,
        "supply" : 24
]),
([        "name" : "稀粥",
        "unit" : "碗",
        "short" : "xizhou",
        "value" : 16,
        "time" : "晚",
        "remaining" : 2,
        "supply" : 18
]),
([        "name" : "米酒",
        "unit" : "壇",
        "short" : "mijiu",
        "value" : 130,
        "time" : "晚",
        "remaining" : 9,
        "supply" : 40
]),
([        "name" : "三鮮湯",
        "unit" : "碗",
        "short" : "sanxiantang",
        "value" : 70,
        "time" : "晚",
        "remaining" : 8,
        "supply" : 24
]),
([        "name" : "冬瓜海螺湯",
        "unit" : "碗",
        "short" : "hailuotang",
        "value" : 90,
        "time" : "晚",
        "remaining" : 8,
        "supply" : 28
])
});

void create()
{
        set("short", "小酒館");
        set("long", @LONG
這是太湖邊的一家小酒館。你一走進來，就聞到一股酒菜的香味，
勾人食涎。廳內擺着幾張八仙桌(table)， 桌上整齊地擺放着碗筷，四
周放着些椅子(chair)。 一個酒保正在忙個不停。你要想打聽江湖掌故
和謠言，這裏是個好所在。櫃枱上立着一個價目表(sign)。
LONG
        );

        set("exits", ([
                "north" : KICK_TO,
        ]));

        set("item_desc", ([
                "sign" : (: look_sign :),
                "table" : (: look_table :),
                "chair" : "木製的坐椅，看起來好像很結實。\n",
        ]) );

        set("objects",([
                __DIR__"npc/zhanggui" : 1,
                __DIR__"npc/jiubao" : 1,
        ]) ); 

        set("coor/x", 290);
        set("coor/y", -870);
        set("coor/z", 0);
        setup();
        quarter_pass();
}

void init()
{
        add_action("do_quit", "quit");
        add_action("do_buy", "buy");
        add_action("do_pay", "pay");
        add_action("do_pay", "jiezhang");
        add_action("do_eat", "eat");
        add_action("do_eat", "chi");
        add_action("do_drink", "drink");
        add_action("do_drink", "he");
        add_action("do_order", "order");
        add_action("do_order", "dian");
        add_action("do_stand", "stand");
        add_action("do_stand", "zhan");
        add_action("do_sit", "sit");
        add_action("do_sit", "zuo");
}

void kick_all()
{
        object *ob;
        int i, pay;

        set_temp("serve", "無");
        tell_room(this_object(), "酒保大喊了一聲：“打烊啦！”\n", ({}));
        ob = all_inventory(this_object());
        for(i = 0; i < sizeof(ob); i++)
        {
                if (userp(ob[i]))
                {
                        if( pay=query_temp("total_pay", ob[i]) )
                        {
                                message_vision("酒保對$N喝道：“付帳走人！”\n", ob[i]);
                                if( !query_temp("to_pay", ob[i]) )
                                {
                                        message_vision("酒保把$N從座位上拽了起來，拉到櫃枱前。\n", ob[i]);
                                        message_vision("掌櫃翻出菜單，撥打了一陣算盤後告訴$N：“一共" + chinese_number(pay) + "文錢。”\n", ob[i]);
                                        delete_temp("marks/sit", ob[i]);
                                        set_temp("to_pay", 1, ob[i]);
                                }
                        }
                        else
                        {
                                if (!living(ob[i])) message_vision("酒保把$N扔出了酒店。\n", ob[i]);
                                else message_vision("酒保把$N推出了酒店。\n", ob[i]);
                                delete_temp("marks/sit", ob[i]);
                                delete_temp("cai_count", ob[i]);
                                delete_temp("cai_1", ob[i]);
                                delete_temp("cai_2", ob[i]);
                                delete_temp("cai_3", ob[i]);
                                delete_temp("cai_4", ob[i]);
                                delete_temp("cai_5", ob[i]);
                                ob[i]->move(KICK_TO);
                                if (!living(ob[i])) tell_room(KICK_TO, ob[i]->name() + "被扔出了酒店。\n", ({ob[i]}));
                                else tell_room(KICK_TO, ob[i]->name() + "被推出了酒店。\n", ({ob[i]}));
                        }
                }
        }
}

void quarter_pass()
{
//        mixed *local;
        object *ob;
        int i, paytime;
        string time = NATURE_D->game_time();
/*  時間被修整
        local = localtime(time() * 60);
        if (local[2] < 6) kick_all();
        else if (local[2] < 9) set_temp("serve", "早");
        else if (local[2] < 11) set_temp("serve", "無");
        else if (local[2] < 14) set_temp("serve", "午");
        else if (local[2] < 17) set_temp("serve", "無");
        else if (local[2] < 21) set_temp("serve", "晚");
        else kick_all();
*/
        if( strsrch(time, "卯時") >= 0) set_temp("serve", "早");
        else if( strsrch(time, "辰時") >= 0) set_temp("serve", "早");
        else if( strsrch(time, "巳時") >= 0) set_temp("serve", "無");
        else if( strsrch(time, "午時") >= 0) set_temp("serve", "午");
        else if( strsrch(time, "未時") >= 0) set_temp("serve", "無");
        else if( strsrch(time, "申時") >= 0) set_temp("serve", "晚");
        else if( strsrch(time, "酉時") >= 0) set_temp("serve", "晚");
        else kick_all();

        ob = all_inventory(this_object());
        for(i = 0; i < sizeof(ob); i++)
        {
                if( paytime=query_temp("to_pay", ob[i]) )
                {
                        paytime++;
                        if( paytime == 6 && query_temp("total_pay", ob[i])){
                                message_vision("酒保對$N大喝一聲：“怎麼還不付帳？！想吃霸王餐啊！”\n", ob[i]);
                                message_vision("酒保叫來幾個大漢，指着$N説：“給我打！”\n", ob[i]);
                                message_vision("大漢們圍住$N，亂拳齊下。\n", ob[i]);
                                delete_temp("total_pay", ob[i]);
                                delete_temp("to_pay", ob[i]);
                                delete_temp("cai_count", ob[i]);
                                delete_temp("cai_1", ob[i]);
                                delete_temp("cai_2", ob[i]);
                                delete_temp("cai_3", ob[i]);
                                delete_temp("cai_4", ob[i]);
                                delete_temp("cai_5", ob[i]);
                                ob[i]->unconcious();
                                message_vision("酒保撇撇嘴，説：“丟出去！”\n", ob[i]);
                                message_vision("大漢們抬起$N，扔出了店門。\n", ob[i]);
                                ob[i]->move(KICK_TO);
                                tell_room(KICK_TO, "只見酒館大門一開，幾個大漢將一個昏迷不醒的傢伙丟了出來。\n", ({ob[i]}));
                        }
                        else set_temp("to_pay", paytime, ob[i]);
                }
        }
        call_out("quarter_pass", 30);
}

int do_sit(string arg)
{
        object me = this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢！\n");
        if (arg == "table" || arg == "zhuozi")
                return notify_fail("你要坐在桌子上？那先把你煮熟了再端上來吧。\n");        
        if ( !arg || (arg != "chair" && arg != "yizi") )
                return notify_fail("你要坐在地板上？有個性！不過這樣的話恐怕你會被轟出酒館了。\n");        
        if( query_temp("marks/sit", me) )
                return notify_fail("你已經坐在座位上了。\n");        
        if( query_temp("total_pay", me) )
                return notify_fail("先把舊帳結清了！\n");        
        remove_call_out("check_payed");
        message_vision("$N找了個空位座下，準備吃飯。\n", me);        
        if (query_temp("serve") == "無")
        {
                message_vision("酒保走過來對$N説：“對不起您哪，現在不是用餐時間。”\n", me);        
                message_vision("$N無奈地又站了起來。\n", me);        
                return 1;
        }
        set_temp("marks/sit", 1, me);
        return 1;
}

int do_stand()
{
        object me = this_player();

        if( !query_temp("marks/sit", me) )
                return notify_fail("你已經站着了，是不是站久了有點發昏啊？\n");        
        if( query_temp("total_pay", me) )
                return notify_fail("沒付錢(pay)就想走嗎？\n");        
        message_vision("$N拍拍屁股，站了起來。\n", me);        
        delete_temp("marks/sit", me);
        return 1;
}

int do_order(string arg)
{
        object me = this_player();
        string serve;
        int i, count;

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢！\n");
        if( !query_temp("marks/sit", me) )
                return notify_fail("酒保用好像瞧見一個怪物一樣的眼神打量着你：“站着吃喝？有位子不坐，您不嫌累呀？”\n");
        if (!arg)
                return notify_fail("酒保不耐煩地説：“你究竟要什麼啊？”\n");
                        
        serve = query_temp("serve");
        if (serve == "無")
                return notify_fail("酒保賠笑道：“客官見諒，廚房已經停火了！”\n");
        if( !query_temp("total_pay", me))set_temp("total_pay", 0, me);
        if( !(count=query_temp("cai_count", me)) )
                set_temp("cai_count", 0, me);
        for (i = 0; i < sizeof(food); i++)
                if ((arg == food[i]["name"] || arg == food[i]["short"]) &&
                        serve == food[i]["time"])
                {
                        message_vision("$N衝酒保喊道：“來" + food[i]["unit"] + food[i]["name"] +"。”\n", me);
                        if( query_temp("cai_count", me) >= 5 )
                        {
                                message_vision("酒保奇怪地問$N：“您打算開宴呀？！先把桌上的吃完了再説！”\n", me);
                                return notify_fail("");
                        }
                        message_vision("酒保喊着：“來～啦～”，給$N端來了" + food[i]["unit"] + food[i]["name"] +"。\n", me);
                        addn_temp("total_pay", food[i]["value"], me);
                        addn_temp("cai_count", 1, me);
                        set_temp("cai_"+count+"/name", food[i]["name"], me);
                        set_temp("cai_"+count+"/short", food[i]["short"], me);
                        set_temp("cai_"+count+"/unit", food[i]["unit"], me);
                        set_temp("cai_"+count+"/remaining", food[i]["remaining"], me);
                        set_temp("cai_"+count+"/supply", food[i]["supply"], me);
                        set_temp("cai_"+count+"/type", "food", me);
                        return 1;
                }
        for (i = 0; i < sizeof(liquid); i++)
                if ((arg == liquid[i]["name"] ||
                        arg == liquid[i]["short"]) &&
                        serve == liquid[i]["time"])
                {
                        message_vision("$N衝酒保喊道：“來" + liquid[i]["unit"] + liquid[i]["name"] +"。”\n", me);
                        if( query_temp("cai_count", me) >= 5 )
                        {
                                message_vision("酒保奇怪地問$N：“您打算開宴呀？！先把桌上的吃完了再説！”\n", me);
                                return notify_fail("");
                        }
                        message_vision("酒保喊着：“來～啦～”，給$N端來了" + liquid[i]["unit"] + liquid[i]["name"] +"。\n", me);
                        addn_temp("total_pay", liquid[i]["value"], me);
                        addn_temp("cai_count", 1, me);
                        set_temp("cai_"+count+"/name", liquid[i]["name"], me);
                        set_temp("cai_"+count+"/short", liquid[i]["short"], me);
                        set_temp("cai_"+count+"/unit", liquid[i]["unit"], me);
                        set_temp("cai_"+count+"/remaining", liquid[i]["remaining"], me);
                        set_temp("cai_"+count+"/supply", liquid[i]["supply"], me);
                        set_temp("cai_"+count+"/type", "liquid", me);
                        return 1;
                }
        return notify_fail("酒保不耐煩地説：“沒這樣菜！”\n");
}

int do_eat(string arg)
{
        object me = this_player();
        int i, count, remaining;

        if (!arg) return 0;
                        
        if( !(count=query_temp("cai_count", me)))return 0;
        for (i = 0; i < count; i++)
                if( query_temp("cai_"+i+"/type", me) == "food" && 
                        (arg == query_temp("cai_"+i+"/name", me) || 
                        arg == query_temp("cai_"+i+"/short", me)) )
                        break;
        if (i == count) return 0;
        if( !query_temp("marks/sit", me) )
        {
                write( "酒保用好像瞧見一個怪物一樣的眼神打量着你：“站着吃喝？有位子不坐，您不嫌累呀？”\n");
                return 1;
        }
        if (me->is_busy()) {
                write("你上一個動作還沒有完成。\n");
                return 1;
        }
        if( query("food", me) >= me->max_food_capacity() )
        {
                write("你已經吃太飽了，再也塞不下任何東西了。\n");
                return 1;
        }

        addn("food",query_temp("cai_"+i+"/supply",  me), me);
        if (me->is_fighting()) me->start_busy(2);

        message_vision("$N端起一"+query_temp("cai_"+i+"/unit", me)+query_temp("cai_"+i+"/name", me)+"，吃了兩口。\n",me);
        remaining=query_temp("cai_"+i+"/remaining", me);
        remaining--;
        if (remaining == 0)
        {
                message_vision("$N將一"+query_temp("cai_"+i+"/unit", me)+query_temp("cai_"+i+"/name", me)+"吃得一乾二淨。\n",me);
                for (; i < count - 1; i++)
                {
                        set_temp("cai_"+i+"/name",query_temp("cai_"+(i+1,  me)+"/name"), me);
                        set_temp("cai_"+i+"/short",query_temp("cai_"+(i+1,  me)+"/short"), me);
                        set_temp("cai_"+i+"/unit",query_temp("cai_"+(i+1,  me)+"/unit"), me);
                        set_temp("cai_"+i+"/remaining",query_temp("cai_"+(i+1,  me)+"/remaining"), me);
                        set_temp("cai_"+i+"/supply",query_temp("cai_"+(i+1,  me)+"/supply"), me);
                        set_temp("cai_"+i+"/type",query_temp("cai_"+(i+1,  me)+"/type"), me);
                }
                addn_temp("cai_count", -1, me);
        }
        else
                set_temp("cai_"+i+"/remaining", remaining, me);
        return 1;
}

int do_drink(string arg)
{
        object me = this_player();
        int i, count, remaining;

        if (!arg) return 0;
                        
        if( !(count=query_temp("cai_count", me)))return 0;
        for (i = 0; i < count; i++)
                if( query_temp("cai_"+i+"/type", me) == "liquid" && 
                        (arg == query_temp("cai_"+i+"/name", me) || 
                        arg == query_temp("cai_"+i+"/short", me)) )
                        break;
        if (i == count) return 0;
        if( !query_temp("marks/sit", me) )
        {
                write( "酒保用好像瞧見一個怪物一樣的眼神打量着你：“站着吃喝？有位子不坐，您不嫌累呀？”\n");
                return 1;
        }
        if (me->is_busy())
        {
                write("你上一個動作還沒有完成。\n");
                return 1;
        }
        if( query("water", me) >= me->max_water_capacity() )
        {
                write("你已經喝太飽了，再也灌不下任何東西了。\n");
                return 1;
        }

        addn("water",query_temp("cai_"+i+"/supply",  me), me);
        if (me->is_fighting()) me->start_busy(2);

        message_vision("$N端起一"+query_temp("cai_"+i+"/unit", me)+query_temp("cai_"+i+"/name", me)+"，喝了兩口。\n",me);
        remaining=query_temp("cai_"+i+"/remaining", me);
        remaining--;
        if (remaining == 0)
        {
                message_vision("$N將一"+query_temp("cai_"+i+"/unit", me)+query_temp("cai_"+i+"/name", me)+"喝得一乾二淨。\n",me);
                for (; i < count - 1; i++)
                {
                        set_temp("cai_"+i+"/name",query_temp("cai_"+(i+1,  me)+"/name"), me);
                        set_temp("cai_"+i+"/short",query_temp("cai_"+(i+1,  me)+"/short"), me);
                        set_temp("cai_"+i+"/unit",query_temp("cai_"+(i+1,  me)+"/unit"), me);
                        set_temp("cai_"+i+"/remaining",query_temp("cai_"+(i+1,  me)+"/remaining"), me);
                        set_temp("cai_"+i+"/supply",query_temp("cai_"+(i+1,  me)+"/supply"), me);
                        set_temp("cai_"+i+"/type",query_temp("cai_"+(i+1,  me)+"/type"), me);
                }
                addn_temp("cai_count", -1, me);
        }
        else set_temp("cai_"+i+"/remaining", remaining, me);
        return 1;
}

int do_pay()
{
        object me = this_player();
        int pay;

        if( !(pay=query_temp("total_pay", me)) )
                return notify_fail("掌櫃賠笑道：“您是來做善事是嗎？不吃也付帳？”\n");
        if( query_temp("marks/sit", me) )
        {
                message_vision("$N站起身來，走到櫃枱前結帳。\n", me);
                message_vision("掌櫃翻出菜單，撥打了一陣算盤後告訴$N：“一共" + MONEY_D->price_str(pay) + "。”\n", me);
                message_vision("掌櫃衝着酒保嚷道：把這位客官桌子上的剩菜收拾乾淨。\n", me);
        }
        else
        {
                message_vision("$N向掌櫃問道：“還差多少？”\n", me);
                message_vision("掌櫃翻了翻白眼，説道：“還差" + MONEY_D->price_str(pay) + "。”\n", me);
        }
        delete_temp("marks/sit", me);
        delete_temp("cai_count", me);
        set_temp("to_pay", 1, me);
        return 1;
}

int do_buy()
{
        write("酒保説道：“本店不外賣，請坐下來(sit)點菜(order)。”\n");
        return 1;
}

int do_quit()
{
        if( query_temp("total_pay", this_player()) )
        {
                write("吃飽喝足了不付錢就想退出？！\n");
                return 1;
        }
        return 0;
}

string look_sign()
{
        string serve;
        int i;

        write("牌子上寫着：\n");
        serve = query_temp("serve");
        if (serve == "無")
        {
                write("    非用餐時間。\n");
                return "";
        }
        write("    " + serve + "餐供應以下飯食，隨便您點(order)：\n");
        for (i = 0; i < sizeof(food); i++)
                if (serve == food[i]["time"]) 
                        printf("    %30s    每%s文。\n", food[i]["name"] + "(" + food[i]["short"] + ")", food[i]["unit"] + chinese_number(food[i]["value"]));
        for (i = 0; i < sizeof(liquid); i++)
                if (serve == liquid[i]["time"]) 
                        printf("    %30s    每%s文。\n", liquid[i]["name"] + "(" + liquid[i]["short"] + ")", liquid[i]["unit"] + chinese_number(liquid[i]["value"]));
        return "";
}

string look_table()
{
        object me = this_player();
        int i, j, num, count;
        string name;

        if( !(count=query_temp("cai_count", me)) )
        {
                write("桌子上是空的。\n");
                return "";
        }
        write("你面前的桌子上放着：\n");
        for (i = 0; i < count; i++)
        {
                name=query_temp("cai_"+i+"/name", me);
                num = 1;
                for (j = 0; j < count; j++)
                {
                        if (j == i) continue;
                        if( name == query_temp("cai_"+j+"/name", me) )
                        {
                                if (j < i)
                                {
                                        num = 0;
                                        break;
                                }
                                num++;
                        }
                }
                if (!num) continue;
                write(""+chinese_number(num)+query_temp("cai_"+i+"/unit", me)+name+"("+query_temp("cai_"+i+"/short", me)+")。\n");
        }
        return "";
}

int valid_leave(object me, string dir)
{
        if( query_temp("marks/sit", me) )
                return notify_fail("你打算連椅子也搬出去？\n");        
        if( query_temp("total_pay", me) )
                return notify_fail("酒保攔住你説：“不付錢就想溜？找扁啊！”\n");        
        delete_temp("cai_count", me);
        delete_temp("cai_1", me);
        delete_temp("cai_2", me);
        delete_temp("cai_3", me);
        delete_temp("cai_4", me);
        delete_temp("cai_5", me);
        return ::valid_leave(me, dir);
}