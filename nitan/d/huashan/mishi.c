//Cracked by Kafei
// xiaolu1.c 華山密室
// qfy 10/8/1997

# include <room.h>
inherit ROOM;
inherit F_SSERVER;

void create()
{
        set("short", "密室");
        set("long",
"密室內的石牆(wall)上由大青石砌成，裡頭空空盪盪的甚麼也沒有。\n"
"周圍放著幾個數人才能合抱的大油缸，供應著燈火的燃料，把密室照得相\n"
"當明亮。\n"
);

        set ("item_desc", ([
                "wall" :
"你伸手推向剛人的石門，用盡全力，石門卻紋風不動，似乎只能由外面開\n"
"啟。你仔細的在牆上敲打搜尋許久，又發現了另一扇與石牆吻合細密的石\n"
"門(door)。\n",
        ])  ) ;

        set("cost", 0);
        setup();
}

void init()
{
        object me = this_player();

        if( query("huashan/yin-jue", me)<2){
                remove_call_out("close_door");
                call_out("close_door", 1, me);
        }

        add_action("do_biguan", "biguan");
        add_action("do_biguan", "閉關");
        add_action("do_push", "push");
}

int close_door(object me)
{
        message_vision("你身後的石門自動緩緩的關上。\n", me);
        return 1;
}

int do_biguan(string arg)
{
        object me = this_player();
        int bili, wuxing, gengu, shenfa;
        int sum, num1, num2, num3, num4;

        if ( !arg ) return notify_fail("你還是再看看紫霞遺頁吧，小心別把功法搞錯了才來遺憾！\n");

        if ( sscanf(arg, "%d %d %d %d", bili, wuxing, gengu, shenfa) != 4  )
                return notify_fail("你還是再看看紫霞遺頁吧，小心別把功法搞錯了才來遺憾！\n");

        if( query("huashan/yin-jue", me)>1 )
                return notify_fail("你任督二脈及生死玄關已通，不必再閉關了。\n");

        if ( bili < 0 ) return notify_fail("膂力值須大於零！\n");
        if ( gengu < 0 ) return notify_fail("根骨值須大於零！\n");
        if ( shenfa < 0 ) return notify_fail("身法值須大於零！\n");
        if ( wuxing < 0 ) return notify_fail("悟性值須大於零！\n");

        sum =  bili + wuxing + gengu + shenfa;

        if ( sum != 4 ) return notify_fail("所增各項天賦值的總和須為四點！\n");

        message_vision("$N盤膝坐下，凝神定意，倚著心法緩吐深納地打坐。\n", me);
        me->start_busy(12);

        remove_call_out("stage1");
        call_out("stage1", 3, me, (int)bili, (int)wuxing, (int)gengu, (int)shenfa);

        return 1;
}

int stage1(object me, int bili, int wuxing, int gengu, int shenfa)
{
        tell_object(me, "不久，你只覺得丹田中有股暖氣漸漸凝聚，越聚越強。\n");
        tell_object(me, "你驅動這股內力擴向四肢百骸，遊走於各處奇經八脈。\n");

        remove_call_out("stage2");
        call_out("stage2", 5, me, bili, wuxing, gengu, shenfa);

        return 1;
}

int stage2(object me, int bili, int wuxing, int gengu, int shenfa)
{
        tell_object(me, "良久，你全身真氣澎湃，如置火爐，但平日內力難以運轉的經脈有漸漸疏通的現向。\n");

        remove_call_out("stage3");
        call_out("stage3", 4, me, bili, wuxing, gengu, shenfa);

        return 1;
}

int stage3(object me, int bili, int wuxing, int gengu, int shenfa)
{
        object env, link_ob, obj, place;

        if ( !me->query_skill("ziyin-yin") || !me->query_skill("zhengqi-jue") || !me->query_skill("zixia-gong") ) {
                tell_object(me, "突然一股真氣沖抵心口，似乎砰上了阻擾，你連連加力，卻三番四次都沖不過去。\n");
                tell_object(me, "你覺得胸口逐漸麻木，而且麻處不斷向周圍擴散，四周也似乎癒來癒冷！\n");
                tell_object(me, "你張口欲呼卻啞然無聲，但耳邊可聞陣陣焦雷在頭頂上炸開！全身血氣似乎湧在喉頭！\n");
                message_vision("$N突然噴出一口紫紅的鮮血！驚慌萬狀，不由得揮動雙手，在地下激烈翻滾！\n", me);
                addn("max_neili", -300, me);
                addn("max_jingli", -300, me);
                addn("str", -1, me);
                addn("dex", -1, me);
                addn("con", -1, me);
                me->receive_wound("qi",query("max_qi", me)+100,"打坐走火入魔死了");
        }
        else if ( me->query_skill("ziyin-yin", 1) < 80 || me->query_skill("zhengqi-jue", 1) < 80
        || me->query_skill("zixia-gong", 1) < 100 ) {
                tell_object(me, "突然一股真氣沖抵心口，似乎砰上了阻擾，你連連加力，卻三番四次都沖不過去。\n");
                tell_object(me, "你覺得胸口逐漸麻木，而且麻處不斷向周圍擴散，四周也似乎癒來癒冷！\n");
                tell_object(me, "你張口欲呼卻啞然無聲，但耳邊可聞陣陣焦雷在頭頂上炸開！全身血氣似乎湧在喉頭！\n");
                message_vision("$N噴出一口紫紅的鮮血！無奈之下，只好倒在地下照紫氤正氣心法緩緩收斂真氣。\n", me);
                addn("max_neili", -150, me);
                addn("max_jingli", -150, me);
                me->receive_wound("qi",query("max_qi", me)/2,"打坐走火入魔死了");
                tell_object(me, "過了良久，你覺得麻痹漸止，慢慢能動了。\n");
                message_vision("$N雙手撐地，緩緩坐了起來，顯得功力大損，體虛力弱，神情極之萎靡！\n", me);
        }
        else if ( me->query_skill("ziyin-yin", 1) < 120 || me->query_skill("zhengqi-jue", 1) < 120
        || me->query_skill("zixia-gong", 1) < 150 ) {
                tell_object(me, "突然一股真氣沖抵心口，似乎砰上了阻擾，你連連加力，卻三番四次都沖不過去。\n");
                tell_object(me, "你覺得胸口逐漸麻木，而且麻處不斷向周圍擴散，四周也似乎癒來癒冷！\n");
                tell_object(me, "你連忙依照紫氤氤和正氣訣的心法凝神思定，緩緩收斂散亂了的內力將其導入內腑。\n");
        }
        else {
                place = environment(me);

                tell_object(me, "你覺得真氣颶盛，各處穴道彷如萬針穿刺，難受之極！\n");
                tell_object(me, "突然似乎有個焦雷在你天庭穴上炸開，那往各處穴道穿刺的萬針亦同時將穴道打通。\n");
                tell_object(me, "你只覺全身上下有十多條水柱在經脈間流竄，暢通無比，十分舒泰。\n");
                addn("str", bili, me);
                addn("dex", shenfa, me);
                addn("int", wuxing, me);
                addn("con", gengu, me);
                addn("huashan/yin-jue", 1, me);
                addn("max_neili", 200, me);

                link_ob=query_temp("link_ob", me);
                obj = LOGIN_D->make_body(link_ob);
                if (!obj) return 0;

                me->save();
                exec(link_ob, me);
                destruct(me);

                obj->restore();
                LOGIN_D->enter_world(link_ob, obj, 1);

                write("你天賦及功力大增了！\n\n");
                obj->move(place);
                obj->write_prompt();

                set("neili",query("max_neili",  me), obj);
                set("jingli",query("max_jingli",  me), obj);
                set("eff_qi",query("max_qi",  me), obj);
                set("qi",query("max_qi",  me), obj);
                set("eff_jing",query("max_jing",  me), obj);
                set("jing",query("max_jing",  me), obj);
                obj->save();
        }

        return 1;
}

int do_push(string arg)
{
        object me = this_player();

        if ( !arg ) return notify_fail("你想推甚麼？\n");

        if ( arg != "door" ) return notify_fail("你不能推動這樣東西！\n");

        message_vision("$N雙掌平伸，運起內力推向石門。\n", me);

        if( query("huashan/yin-jue", me)<2){
                if( query("neili", me)<300){
                        set("neili", 0, me);
                        message_vision("$N用盡全力，累得渾身大汗淋漓，石門卻依然分毫不動。\n", me);
                        return 1;
                }

                addn("neili", -300, me);
        }

        message_vision("石門在$N的推動下發出一陣轟響，緩緩往後移，一寸一寸的開啟了。\n", me);

        set("exits/out", __DIR__"outmishi");
        remove_call_out("auto_close");
        call_out("auto_close", 5, this_object());

        return 1;
}

void auto_close(object room)
{
        message("vision","石門突然發出一陣轟響，自動關閉起來。\n", room);
        delete("exits/out", room);
}