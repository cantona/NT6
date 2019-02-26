#include <ansi.h>
inherit NPC;
inherit F_DEALER;

string ask_eguidao();

void create()
{
        set_name("杜鳳鄂", ({ "du fenge", "du", "fenge" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long", "杜鳳鄂一臉惆悵，不知道他心中所煩為何事。\n");
        set("combat_exp", 400000);
        set("attitude", "friendly");
        set("no_get", "1");
        set_skill("unarmed", 200);
        set_skill("dodge", 200);
        set_temp("apply/damage", 25);

        set("inquiry", ([
                "狐仙"   : "聽説狐能化成狐仙，我倒是遇見過一回。\n",
                "緋胭"   : "緋胭姑娘好久沒有來買我的畫了，不知道她現在怎麼樣了？\n",
                "餓鬼道" : (: ask_eguidao :),
                
        ]));
        set("vendor_goods", ({
                "/clone/tattoo/face1",
                "/clone/tattoo/face2",
                "/clone/tattoo/face3",
                "/clone/tattoo/face4",
                "/clone/tattoo/face5",
                "/clone/tattoo/face6",
                "/clone/tattoo/face7",
                "/clone/tattoo/face8",
                "/clone/tattoo/face9",
                "/clone/tattoo/face10",
                "/clone/tattoo/face11",
                "/clone/tattoo/face12",
                "/clone/tattoo/face13",
                "/clone/tattoo/face14",
                "/clone/tattoo/face15",
                "/clone/tattoo/face16",
                "/clone/tattoo/face17",
                "/clone/tattoo/face18",
                "/clone/tattoo/face19",
                "/clone/tattoo/face20",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

// 餓鬼道
// 需要100張狐狸皮
string ask_eguidao()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "你的先天屬性還不足以修煉餓鬼道，我看你還是先回去吧。\n";

        if( query("reborn/times", me)<3 )
                return "哼，我看你才像個什麼餓鬼，沒事別來煩我，走開！\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                return "閣下武功已經獨步天下，恭喜恭喜！\n";

        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此貪心！\n";
                                
        // 是否閲讀過狐仙書
        if( !query("lunhui-sword_quest/read_huxian_book", me) )
        {
                    
                command("tan");
                return "你聽過" HIM "狐仙" NOR "的故事嗎？\n";
        }
        
        // 已經完成任務
        if( query("lunhui-sword_quest/eguidao/finish", me) )
                return "呵呵，你上次找的那些狐狸皮質地不錯，緋胭她很是喜歡。\n";

        // 分配任務
        if( !query("lunhui-sword_quest/eguidao/give_quest", me) )
        {
                command("tan");
                command("say 我現在急需五十張白狐皮來縫製狐皮大衣，緋胭應該會很高興的！");
                command("ke");
                command("say 能幫我完成這個心願嗎？");
                tell_object(me, this_object()->name() + HIG "讓你幫他蒐集50張白狐皮，趕快去吧！\n" NOR);
                set("lunhui-sword_quest/eguidao/give_quest", 1, me);
                me->save();
                return "事成之後，我會告訴你一個天大的祕密！";
        }
        
        // 完成任務
        
        if (! objectp(ob_hlp = present("baihu pi", me)))
                return "怎麼樣，50張白狐皮蒐集夠了嗎？\n";
                
        if (base_name(ob_hlp) != "/clone/quarry/item/lipi2")
                return "怎麼樣，50張白狐皮蒐集夠了嗎？\n";
 
        if (ob_hlp->query_amount() >= 50)
        {
                ob_hlp->add_amount(-50);
                if (ob_hlp->query_amount() < 1)destruct(ob_hlp);
        }
        else
        {
                return "怎麼樣，50張白狐皮蒐集夠了嗎？\n";
        }
        
        command("hehe");
        command("nod");
        command("say 既然你幫我了這個忙，我就告訴你一個祕密 ...");
        
        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳邊悄悄説了幾句，然後又拿出一本書，指指點點，"
                     "$n" HIC "不住地點頭，忽而眉頭深鎖，忽而低頭沉思 ……\n良久，$n" HIC "大笑一聲，似乎"
                     "對剛才的疑慮有所頓悟。\n", this_object(), me);
                     
        
        tell_object(me, HIG "恭喜你領悟了「餓鬼道」劍法，目前等級為10級。\n");
        me->set_skill("egui-dao", 10);
        set("lunhui-sword_quest/eguidao/finish", 1, me);
        
        return "明白了？";
        
                
}

void init()
{       
        object ob; 

        ob = this_player();

        ::init();
        if (interactive(ob) && ! is_fighting()) 
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;

        say(CYN "杜鳳鄂搖了搖頭道：這位" + RANK_D->query_respect(ob) +
            "你相信狐能化成狐仙嗎？\n" NOR);

        return;
}
