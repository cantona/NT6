// Room: /d/guiyun/zhongting.c
// Last Modified by winder on Jul. 9 2001

#include <ansi.h>
inherit ROOM;

string look_xiao();
string look_zishi();

void create()
{
        set("short","中廳");
        set("long",@LONG
這是歸雲莊的中廳。莊中的大事以及召集弟子訓話都是在這裡進行
的。由于修建年代久遠，看起來已頗為陳舊，但打掃得十分幹凈，光線
也較為充足，完全沒有陳年舊宅的陰晦之氣。四壁掛著一些古人書畫精
品，皆為上乘之作，顯得主人眼光不凡，胸中大有丘壑。
    靠裡面是一張太師椅，椅後的牆上掛著一幅畫(hua)。
LONG );
        set("objects",([
                __DIR__"npc/kezhene" : 1,
                __DIR__"npc/zhucong" : 1,
                __DIR__"npc/hanbaoju" : 1,
                __DIR__"npc/nanxiren" : 1,
                __DIR__"npc/zhangasheng" : 1,
                __DIR__"npc/quanjinfa" : 1,
                __DIR__"npc/hanxiaoying" : 1,
                __DIR__"npc/guanjia" :     1,
                __DIR__"npc/zhuangding3" : 1,
        ]));
        set("exits",([
                "east"  : __DIR__"qianting",
                "north" : __DIR__"zoulang1",
                "south" : __DIR__"zoulang4",
        ]) );
        set("item_desc", ([
                "hua" :  "畫中是一位形貌清矍的青衫老者，正在吹簫(xiao)，但是他的姿勢(zishi)卻有點奇怪。\n",
                "xiao" : (: look_xiao :),
                "zishi" : (: look_zishi :),
        ]) );

        set("no_clean_up",0);
        set("coor/x", 260);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
}

string look_xiao()
{
        object me = this_player();

        if( !query_temp("guiyun_hua", me))return "畫中老人拿簫的姿勢甚是怪異！\n";
        set_temp("guiyun_hua", 2, me);
        return "原來畫中老人竟是把手中握著的簫當作了劍來舞。\n";
}

string look_zishi()
{
        object me = this_player();
        int level, exp;

        level = me->query_skill("sword", 1);
        exp=query("combat_exp", me);
        if( query_temp("guiyun_hua", me)<2 )
        {
                set_temp("guiyun_hua", 1, me);
                return "你仔細地端詳著畫中老人的身姿，恍惚間仿佛看見老人正在緩緩舞動著什麼。\n";
        }
        else
        {
                write("原來畫中老人舞簫的姿勢裡竟然暗藏著高深的劍法！\n");
                if (me->is_busy())
                {
                        write("可惜你現在正忙著做別的事，無法專心研究這幅畫。\n");
                        return "";
                }
                if( me->is_fighting() ) {
                        write("可惜你現在正在戰鬥中，無法專心研究這幅畫。\n");
                        return "";
                }
                if( query("jing", me)<30 )
                        return "可惜你太累了，無法集中精神來研究這幅畫。\n";
                if (me->query_skill("sword", 1) > 100)
                        return "這幅在以前的你看來很艱深的畫對現在的你而言已經沒有什麼可值得研究的了。\n";
                if ((int)me->query_skill("sword", 1) < 30 )
                        return "你努力試圖從畫中老人的身姿裡看出些什麼，卻發現一切都是徒勞的。\n";

                me->receive_damage("jing", 25);
                if( level * level * level /10 < exp)
                        me->improve_skill("sword",query("int", me));

                write("你仔細端詳著畫中老人舞簫的身姿。\n");
                if (!random(8))
                        tell_room(this_object(), me->name() + "仔細端詳著畫中老人舞簫的身姿。\n", ({me}));
                return "你對劍法運用的微妙之處有了進一步的認識。\n";
        }
}

void init()
{
        object me = this_player();
        int score, skill, age;

        if( query("age", me) >= 30 || random(query("kar", me))<15 )
                return;

        if( query("family/master_id", me) != "lu chengfeng" && 
            query("family/master_id", me) != "qu lingfeng" )
                return;


        age=query("age", me)-10;
        skill = (me->query_skill("force") + me->query_skill("dodge") +
                me->query_skill("strike") + me->query_skill("qimen-wuxing")) / 4;
        skill*=query("combat_exp", me)/1000;
        score = skill / age;

        if (score < 1000)
                return;

        remove_call_out("recruit_ob");
        call_out("recruit_ob", 1, me);

        tell_object(me, CYN "你覺得身後有點古怪，似乎有人跟隨？\n" NOR);
}

void recruit_ob(object me)
{
        object ob, *obj;
        int i, j = 0;

        if (! me) return;

        obj = all_inventory(environment(me));

        for(i = 0; i < sizeof(obj); i++)
        {
                if (playerp(obj[i]))
                j++;
        }

        if (j > 1) return;

        ob = new(CLASS_D("taohua/huang"));
        if (! me->is_busy())
                me->start_busy(1);
        ob->move(environment(me));

        message_sort("$N前面突然出現了一人，身材高瘦，身穿青色布袍，臉色古怪之極，兩顆眼珠似乎尚能"
                       "微微轉動，除此之外，肌肉口鼻，盡皆僵硬如木石，直是一個死人頭裝在活人的軀體上。\n\n", me);

        message_sort("$N一見之下，登時一陣涼氣從背脊上直冷下來，目光與這張臉孔相觸，便都不敢再看，立時將"
                       "頭轉開，心中怦然而動：莫非這就是祖師爺爺，江湖中傳聞的桃花島主？ 忙上前恭恭敬敬的"
                       "磕了四個頭，說道：“孫兒叩見師祖。”黃藥師道：“罷了！”並不俯身相扶，卻伸左手抓住$N後"
                       "心一提，右掌便向$N肩頭拍下。。。\n", me);
        message_sort("$N一見不妙，來不及細想，趕緊身形疾閃，使出一招“海燕騰空”，身體如同為海風所激，向後飄開一丈有余。\n\n", me);
        message_sort("黃藥師微一愣，哼了一聲道：" + RANK_D->query_rude(me) + "卻有幾分資質，我就成全你吧。\n\n", me);

        message_sort("$N想要收$n為弟子。\n", ob, me);
        tell_object(me, YEL "如果你願意拜" + ob->name() + "為師父，用 apprentice 指令。\n" NOR);
        set_temp("huang_recr", 1, me);

        //remove_call_out("finish_recr");
        call_out("finish_recr", 30, me, ob);
}

void finish_recr(object me, object ob)
{
        if (! objectp(me) || ! objectp(ob))
                return;

        if( query("family/master_id", me) != "huang yaoshi" )
        {
                message_vision("$N冷笑一聲：" + RANK_D->query_rude(me) + "居然有幾分臭架子。說完飄然而去。\n", ob);
                delete_temp("huang_recr", me);
                destruct(ob);
        }
        return;
}
