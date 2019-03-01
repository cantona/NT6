// huoji. 花店伙計
#include <ansi.h>
#include <dbase.h>

inherit BUNCHER; 
int ask_me();
int ask_send();
int do_send(string arg);
string makeup_space(string s);
mixed ask_back();
void create()
{
       set_name("紫茵", ({ "zi yin", "zi", "yin" }));
        set("shen_type", 1);
        set("gender", "女性");
        set("age", 15);
        set("long","她是這裡的賣花女，只見其含笑如春桃，玉唇含香，纖纖細腰，婀娜多姿，雖粗布花衣，但不掩其清秀，實乃人間絕色。\n");
        set("attitude", "friendly");
        set("inquiry", ([
                "送花" : (: ask_send :),
                "song" : (: ask_send :),
                "send" : (: ask_send :),
                "桃花盛開" : (: ask_back :),
        ]));
        set("vendor_goods", ([
                "/clone/flower/red_rose":99,
                "/clone/flower/white_rose":99,
                "/clone/flower/qingren_cao":99,
                "/clone/flower/ding_xiang":99,
                "/clone/flower/mu_dan":99,
                "/clone/flower/yu_jinxiang":99,
                "/clone/flower/bai_he":99,
                "/clone/flower/kang_naixin":99,
                "/clone/flower/ma_tilian":99,
                "/clone/flower/jin_yucao":99,
                "/clone/flower/huo_he":99,
                "/clone/flower/hu_dielan":99,
                "/clone/flower/qiu_haitang":99,
                "/clone/flower/shi_hulan":99,
                __DIR__"obj/zhongzhi": 20,
        ]));
        setup();
        carry_object(CLOTH_DIR"pink_cloth")->wear();
        carry_object(CLOTH_DIR"boot/flower_shoe")->wear();
        //remove_call_out("do_check_flower");
        //call_out("do_check_flower", 10+random(10) );
        remove_call_out("do_full_flower");
        call_out("do_full_flower", 1800 );
}
int do_full_flower()
{
        tell_room(environment(), "\n幾個花匠走了進來。\n");
        tell_room(environment(), "“嗨！紫茵姑娘，給你送鮮花來了。”帶頭的那個花匠對紫茵打招呼。\n");
        tell_room(environment(), "紫茵喜聲道：“謝謝花匠叔叔，放在後面的花室裡吧。”\n");
        tell_room(environment(), "花匠們走過去將花放置好。\n");
        tell_room(environment(), "花匠們走了出來對紫茵說道：“花放好了，我們下次再來。”\n");
        tell_room(environment(), "花匠們走了出去。\n");
        set("vendor_goods", ([
                "/clone/flower/red_rose":99,
                "/clone/flower/white_rose":99,
                "/clone/flower/qingren_cao":99,
                "/clone/flower/ding_xiang":99,
                "/clone/flower/mu_dan":99,
                "/clone/flower/yu_jinxiang":99,
                "/clone/flower/bai_he":99,
                "/clone/flower/kang_naixin":99,
                "/clone/flower/ma_tilian":99,
                "/clone/flower/jin_yucao":99,
                "/clone/flower/huo_he":99,
                "/clone/flower/hu_dielan":99,
                "/clone/flower/qiu_haitang":99,
                "/clone/flower/shi_hulan":99,
        ]));
        remove_call_out("do_full_flower");
        call_out("do_full_flower",1800);
        return 1;
}
private void go_home()
{
        if( !living(this_object()) ) return;
        message_vision("$N神色慌張地離開了。\n", this_object());
        this_object()->move("/d/city/huadian");
        message_vision("$N快步走了過來。\n", this_object());
}
void init()
{
        if( environment() != load_object("/d/city/huadian") )
        {
                remove_call_out("go_home");
                call_out("go_home", 1);
        }
        add_action("do_check", "list");
        add_action("do_buy", "buy");
        //add_action("do_send", "send");
        //add_action("do_check_flower", "check_test");

}
string inventory_desc(object ob)
{
        return sprintf("%s%s",
                query("equipped", ob)?HIC"□"NOR:"",
                ob->short()
        );
}
string price_string(int v)
{
        if( v%10000 == 0 )
                return chinese_number(v/10000) + "兩黃金";
        if( v%100 == 0 )
                return chinese_number(v/100) + "兩白銀";
        return chinese_number(v) + "文銅板";
}
int do_buy(string what)
{
        int i, amount, value, val_factor;
        string ob_file;
        object ob, me = this_player();
        mapping goods;
        string *name, last = "";
        amount=1;
        val_factor=10;
        if( !what ) return notify_fail("紫茵說：你想買什麼？\n");
        if( sscanf(what, "%d %s", amount, what)!=2 )
        {
                amount = 1;
        }
        if( amount < 1 ) return notify_fail("紫茵說：您想買多少？\n");
        if( amount > 10 ) return notify_fail("紫茵說：我這一次最多買十朵。\n");
        if( !mapp(goods = query("vendor_goods")) )
                return notify_fail("紫茵說：這兒的東西全賣光了。\n");
        if(this_player()->is_busy())
                return notify_fail("你現在正忙著呢。\n");
        name = keys(goods);
        for(i=0; i<sizeof(name); i++)
        {
                if(what == name[i]->name() || name[i]->id(what))
                {
                        if( stringp(ob_file = name[i]) )
                        {
                                if(goods[name[i]]<amount)
                                        return notify_fail("紫茵說：我這裡沒有這麼多你要買的這種花了。\n");
                                ob = new(ob_file);
                                if(goods[name[i]]<10)
                                {
                                        val_factor=30;
                                        tell_object(this_player(), "紫茵說：現在這"+query("name",ob)+"只剩下很少了，價格上漲兩倍，合"+MONEY_D->price_str(query("value",ob)*val_factor/10)+"一"+query("unit",get_object(name[i]))+"。\n");
                                }
                                else if(goods[name[i]]<20)
                                {
                                        val_factor=20;
                                       tell_object(this_player(), "紫茵說：現在這"+query("name",ob)+"太走俏了，價格上漲一倍，合"+MONEY_D->price_str(query("value",ob)*val_factor/10)+"一"+query("unit",get_object(name[i]))+"。\n");
                                }
                                else if(goods[name[i]]<50)
                                {
                                        val_factor=15;
                                       tell_object(this_player(), "紫茵說：現在這"+query("name",ob)+"喜歡的人很多，價格上漲一半，合"+MONEY_D->price_str(query("value",ob)*val_factor/10)+"一"+query("unit", get_object(name[i]))+"。\n"); 
                                }
                                switch(MONEY_D->player_pay(me,query("value", ob)*amount*val_factor/10) )
                                {
                                        case 0: destruct(ob);
                                                return notify_fail("紫茵說：窮光蛋，一邊呆著去！\n");
                                        case 2: destruct(ob);
                                                return notify_fail("紫茵說：您的零錢不夠了，銀票又沒人找得開。\n");
                                }
                                ob->set_amount(amount);
                                if (ob->move(me))
                                {
                                        goods[name[i]]=goods[name[i]]-amount;
                                        if(goods[name[i]] <= 0)
                                        {
                                                map_delete(goods,name[i]);
                                                last = "最後";
                                        }
                                        message_vision(sprintf("$N向$n買下%s"+chinese_number(amount)+"%s%s。\n",last,query("unit", ob),ob->name()),me,this_object());
                                } else destruct(ob);
                                this_player()->start_busy(1);
                                return 1;
                        }
                }
        }
        return notify_fail("您想買什麼？\n");
}
int do_check(string arg)
{
        mapping goods;
        string list, *name;

        int i;
        if( arg && !this_object()->id(arg) ) return 0;
        if( !mapp(goods = query("vendor_goods")) ) return 0;
        name = keys(goods);
        if(!sizeof(name)) return 0;
        list = "你可以購買下列這些東西：\n";
        for(i=0; i<sizeof(name); i++)
                list += sprintf("%-30s：\t%s\t還剩%s%s\n",
                        makeup_space(query("name",get_object(name[i]))+"("+ 
                        query("id", get_object(name[i]))+")"),
                        MONEY_D->price_str(query("value", get_object(name[i]))),
                        CHINESE_D->chinese_number(goods[name[i]]),
                        query("unit", get_object(name[i])));
        write(list);
        return 1;
}
string query_flower_file( string arg)
{
        return sprintf( DATA_DIR "flower/%c/%s", arg[0], arg );
}
int do_check_flower()
{
        object *ob,ob_letter;
        string file ;
        int i;
        ob = users();
        i = sizeof(ob);
        while (i--)
        {
                if (userp(ob[i]))
                {
                        file=query_flower_file(query("id", ob[i])+".o");
                        assure_file( file );
                        if(file_size(file)!=-1)
                        {
                                if( (interactive(ob[i])) && (living(ob[i])) &&
                                        (!ob[i]->is_busy()) &&
                                        (!ob[i]->is_fighting()) )
                                {
                                        ob_letter=new("/clone/misc/flower");
                                        ob_letter->set_owner(query("id", ob[i]));
                                        ob_letter->check(ob[i],this_object());
                                        destruct(ob_letter);
                                }
                        }
                }
        }
        remove_call_out("do_check_flower");
        call_out("do_check_flower", 10+random(10) );
        return 1;
}
int ask_send()
{
        write( "紫茵欠身說道：“感謝客官光臨小店，您先在這裡將花買好，\n然後告訴小女要送給誰，小女一定為您送到。\n(send flower_name to playername)”\n我們花店收費規則是：送花費用最低十兩紋銀。\n每一朵花收取一兩紋銀的送花費。\n");
        return 1;
}
int do_send(string arg)
{
        object tar, ob_flower, send_flower, me=this_player();
        int i, k, money_amount;
        mapping flower, *flowers;
        string flower_name, who;

        if( !arg || sscanf(arg, "%s to %s", flower_name, who)!=2 )
                return notify_fail("紫茵說道：你要送什麼花給誰？\n");
        if(!FINGER_D->acquire_login_ob(who))
                return notify_fail("紫茵說道：這裡有這個人嗎？\n");
        ob_flower=present(flower_name,me);
        if(!ob_flower) return notify_fail("紫茵道：你身上好像並沒有這種花？\n");
        if( !query("flower", ob_flower) )
                return notify_fail("紫茵道：對不起！我們這裡不負責送這個。\n");
        if(me->is_busy())
                return notify_fail("你現在正忙著呢。\n");
        if(!send_flower=new("/clone/misc/flower"))
                return notify_fail("/clone/misc/flower初始化錯誤。\n");
        send_flower->set_owner(who);
        if( query("flowername", send_flower) == flower_name )
        {
                command("hmm ");
                return notify_fail("紫茵道：對不起，我還沒將您上次的花送到呢，請您稍後再來吧。\n");
        }
        if( query("from", send_flower) == (me->name(1)+"("+query("id", me)+")") )
        {
                command("hmm ");
                return notify_fail("紫茵道：對不起，我還沒將您上次的花送到呢，請您稍後再來吧。\n");
        }
        //******************************收費*******************************************//
        if(ob_flower->query_amount()<10) money_amount=10;
        else money_amount=ob_flower->query_amount();
        if(ob_flower->query_amount()>1000) money_amount=1000;
        else money_amount=ob_flower->query_amount();
        switch (MONEY_D->player_pay(me, money_amount*100) )
        {
                case 0: destruct(send_flower);
                        return notify_fail("紫茵道：您好像沒有足夠的銀兩來支付送花費用。\n");
                case 2: destruct(send_flower);
                        return notify_fail("紫茵道：您的零錢不夠了，銀票又沒人找得開。\n");
        }
        message_vision("$N對$n說道：“送花共收您"+price_string(money_amount*100)+"”。\n",this_object(), me);

        set("flowername",query("name",  ob_flower), send_flower);
        set("flower_id",query("id",  ob_flower), send_flower);
        set("to", who, send_flower);
        set("from", me->name(1)+"("+query("id", me)+")", send_flower);
        set("amount", ob_flower->query_amount(), send_flower);

        flower = ([
                "flowername":query("name", ob_flower),
                "flower_id":query("id", ob_flower),
                "to": who,
                "from":me->name(1)+"("+query("id", me)+")",
                "amount": ob_flower->query_amount(),
        ]);
        send_flower->send_flower(flower);
        send_flower->save();
        destruct(send_flower);
        destruct(ob_flower);
        me->start_busy(1);

        message_vision("$n將身上的"+flower["flowername"]+"拿出交給$N。\n",this_object(), me);
        message_vision("$N對$n說道：“好吧，小女子定會將花送到。”\n",this_object(), me);

        remove_call_out("do_check_flower");
        call_out("do_check_flower", 10+random(10) );
        return 1;
}
string makeup_space(string s)
{
        string *ansi_char = ({
                BLK,   RED,   GRN,   YEL,   BLU,   MAG,   CYN,   WHT,
                BBLK,  BRED,  BGRN,  BYEL,  BBLU,  BMAG,  BCYN,
                       HIR,   HIG,   HIY,   HIB,   HIM,   HIC,   HIW,
                       HBRED, HBGRN, HBYEL, HBBLU, HBMAG, HBCYN, HBWHT,
                NOR
        });

        string space = s;
        int i, space_count;

        for (i = 0; i < sizeof(ansi_char); i ++)
                space = replace_string(space, ansi_char[i], "", 0);

        space_count = sizeof(s) - sizeof(space);
        if (sizeof(s) >= 15)
                space_count = 15 - sizeof(space);

        space = s;

        for (i = 0; i < space_count; i ++) space += " ";
        return space;
}

/*
inherit NPC;
inherit F_DEALER;
#include <ansi.h>;
int do_send(string arg);
void create()
{
        set_name("花店伙計", ({ "huadian huoji", "huoji" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 18);
        set("long", "他十分強壯，看上去會幾分武功，對花店生意也很是精通。\n");
        set("combat_exp", 2500);
        set("attitude", "friendly");

        set("vendor_goods", ({
                __DIR__"obj/red_rose",
                __DIR__"obj/yellow_rose",
                __DIR__"obj/yujinxiang",
                __DIR__"obj/kangnaixin",
                __DIR__"obj/dog_grass",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_send", "send");
}
int do_send(string arg)
{
        object obj, flower, me = this_player();
        string target, item;

        if(!arg) return notify_fail("花店伙計說：你要給誰什麼東西？\n");
        if( me->is_busy() )
                return notify_fail("你上一個動作還沒有完成！\n");
        if( sscanf(arg, "%s to %s", item, target) !=2)
                return notify_fail("花店伙計說：你要給誰什麼東西？\n");
        obj = find_player(target);
                if(!obj || !me->visible(obj))
                        return notify_fail("花店伙計說：此人現在不在。沒法幫你送花。\n");

        if( !living(obj))
                return notify_fail("花店伙計說：抱歉，現在沒法幫你送花。\n");
        if( !objectp(flower = present(item, me)) )
                return notify_fail("花店伙計說：你身上沒有這種花。\n");
        if( !query("flower", flower) )
                return notify_fail("花店伙計說：你只能讓我幫你送花。\n");
        if( query("no_drop", flower) )
                return notify_fail("這樣東西不能隨便給人。\n");

        flower->move(obj);
        me->save();
        obj->save();
        tell_object(me,HIC"花店伙計笑了笑道：“這位"+RANK_D->query_respect(me)+"稍候，這就給你送到"+query("name", obj)+"手上。”轉身出門去了。\n"NOR);
        tell_object(obj,HIC"花店伙計走過來遞給你一"+query("unit", flower)+query("name", flower)+HIC"，輕輕說道：“這是"+query("name", me)+"送給你的。”轉身笑了笑就走了。\n"NOR);
        tell_object(me, HIC"花店伙計片刻後回來笑道：“放心吧，送到了。”\n" NOR );
        return 1;
}
*/


mixed ask_back()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "桃花島" )
        {
                message_vision("$N自顧自的幹活，好象沒有聽見$n在說什麼。\n",
                               this_object(), me);
                return -1;
        }

        message_sort("$N猛然抬起頭來，上上下下打量了一會"
                     "兒$n，眼角微微一動，立刻放下手中的"
                     "活計，從內室領出一只白雕，說道：你"
                     "乘坐這只白雕回桃花島吧。\n", 
                     this_object(), me);

        tell_object(me, HIW "你坐上白雕飛了很久，越過大海，忽然眼前一亮，"
                    "你已經來到了桃花島。\n" NOR);
        me->move("/d/taohua/jingshe");
        return -1;
}

