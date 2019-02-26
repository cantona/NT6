#include <ansi.h>
inherit ITEM;

int generate_taoist;
void set_generate_taoist(int i)
{
        generate_taoist = i;
}

int query_generate_taoist()
{
        return generate_taoist;
}

void create()
{
        set_name("棺材", ({"coffin"}) );
        set_weight(3000);
        set("no_get", 1);
        set("unit", "具");
        set("long", "一具漢白玉做的石棺，上面還有一個奇形怪狀的輪盤，也許是什麼古怪機關。");
        set("value", 2000);
        setup();
}

void init()
{
        add_action("do_push","push");
        add_action("do_turn","turn");
}

int do_push(string arg)
{
        if( !arg || (arg!="coffin" &&  arg!="棺材") )
                return notify_fail("你要推什麼？\n");

        tell_object(this_player(), "棺材似乎只有撥轉(turn)輪盤才能開啟機關打開。\n");
        return 1;
}

int do_turn(string arg)
{
        object taoist;
        object me, mazeobj;
        int answer,puzzle;

        me = this_player();
        if( !arg )
                return notify_fail("你要把輪盤轉到哪一個數字上？\n");
        if( query("neili", me) < 5000 )
                return notify_fail("你的內力不夠，撥不動輪盤。\n");
        mazeobj = FUBEN_D->query_maze_mainobj(this_object());
        if( !(answer = (int)arg) || sizeof(query("quest/password", mazeobj)) < 9 )
                return notify_fail("你瞎轉什麼？\n");
        puzzle  = query("quest/password/1", mazeobj);
        puzzle += query("quest/password/2", mazeobj) * 10;
        puzzle += query("quest/password/3", mazeobj) * 100;
        puzzle += query("quest/password/4", mazeobj) * 1000;
        puzzle += query("quest/password/5", mazeobj) * 10000;
        puzzle += query("quest/password/6", mazeobj) * 100000;
        puzzle += query("quest/password/7", mazeobj) * 1000000;
        puzzle += query("quest/password/8", mazeobj) * 10000000;
        puzzle += query("quest/password/9", mazeobj) * 100000000;
        me->add("neili",-1500);
        message_vision("$N把輪盤撥到了"+arg+"的位置\n",me);
        if( ("X"+puzzle+"X") == ("X"+answer+"X") ) {
                if( query_generate_taoist() ) {
                        tell_room(this_object(), "一陣機關之聲響過之後棺材打開了，但是裏面什麼都沒有。\n");
                        return 1;
                }
                tell_room(this_object(), "一陣機關之聲響過之後，石棺開始慢慢開啟。\n");
                message_vision(@LONG
棺中躺了一個頭戴珍珠玄冠，身着黑色龍袍的俊秀王者，面如冠玉，神態安詳平和，
宛然若生，似乎只是在沉睡之中。左手橫於胸前，託着一個三寸來長、形如猛虎的五
色石印，絢光閃耀。右手垂膝，緊握着一根六尺來長的盤龍青銅旗杆，黑色幡布橫鋪
在他的腹部，赫然是河圖紋案。棺蓋打開之後，屍體緊閉的雙眼突然睜開，雙目之中
精光暴射，隨即從棺中一躍而出，可能是在棺中躺了千年的緣故，他的手臂腿腳都不
十分靈便，但他力大無窮，直上直下，手腳揮舞着向你攻來。躍出石棺之後，他的皮
肉急速萎縮焦枯，剎那之間便化為一具白骨骷髏！
LONG, me);
                taoist = new("/maze/mausoleum/npc/king");
                taoist->move(environment(me));
                set_generate_taoist(1);
        } else
                message_vision("可是什麼都沒有發生。\n",me);
        return 1;
}

