// aninit.h 定義殺手檢查，自己消失的時間
#include <ansi.h>
#define A_TIME 20

string *shot_msg = ({
        "驀地，街邊上一個看來毫不起眼的$N突然沖了出來！\n",
        "這是個熱鬧所在，一個$N笑嘻嘻沖著$n迎了上來，似乎要交給$n什麼東西。\n",
        "街角上一個$N本來在那裡懶洋洋地曬著太陽，突然象離弦之箭般躍進身來。\n",
        "一個$N站在街心正在吆喝著什麼，忽然轉眼看見了$n，轉身沖了過來！\n",
        "一個很平常的$N站在那裡，臉上木然地沒什麼表情。\n",
        "街面上站著一個$N，嘴裡嘟囔著什麼話，結果看見$n就大叫一聲撲了過來。\n",
});

string *name_msg = ({ "流氓", "進香客", "道士", "行者", "挑夫", "家丁", "官兵", "行人", "乞丐", "百姓", "賣花姑娘", "老船夫", "趟子手", "鐵匠", "小販", "刀客", "劍客", "遊方和尚", "江湖豪客", });

string *long_id = ({ "liu mang", "jinxiang ke", "dao shi", "xing zhe", "tiao fu", "jia ding", "guan bing", "xing ren", "qi gai", "bai xing", "flower girl", "lao chuanfu", "tangzi shou", "tie jiang", "xiao fan", "dao ke", "jian ke", "seng ren", "jianghu haoke", });

string *short_id = ({ "lm", "jk", "ds", "xz", "tf", "jd", "gb", "xr", "qg", "bx", "fg", "lc", "ts", "tj", "xf", "dk", "jk", "sr", "jh", });

string *sex_msg = ({ "男", "男", "男", "男", "男", "男", "男", "男", "男", "男", "女", "男", "男", "男", "男", "男", "男", "男", "男", });

string *weapon_msg = ({
        __DIR__"obj/anqi",
        __DIR__"obj/anqi",
        __DIR__"obj/anqi",
        __DIR__"obj/anqi",
        __DIR__"obj/anqi",
        __DIR__"obj/anqi",
        __DIR__"obj/chuidutong",
        __DIR__"obj/sheerkou",
});

void init()
{
        remove_call_out("do_check");
        call_out("do_check", 1);
        remove_call_out("do_wait");
        call_out("do_wait",A_TIME);
}

void do_check()
{
        object me = this_object();
        object ob;

        remove_call_out("do_check");
        if (! living(me) || me->fighting() )
        {

                call_out("do_check",1);
        }
        else
        {
                if( !ob = present("ren zhi",environment(me)) || ! living(me) || me->is_fighting())
                {
                        call_out("do_check",1);
                }
                else
                {
                        message_vision(HIG+shot_msg[random(sizeof(shot_msg))]+NOR,me,ob);
                        command("shot"+query("id", ob));
                        addn("combat_num", 1, ob);
                        message_vision(HIW"\n當你定過神來再找那個$N，卻已經消失得無影無蹤了。\n"NOR,me);
                        destruct(me);
                }
        }
}

void do_wait()
{
        object ob;
        object me = this_object();

        remove_call_out("do_wait");
        if (me->is_fighting() || !living(me) )
        {
                call_out("do_wait",A_TIME);
        }
        else
        {
                message_vision("$N自言自語地說道：看來那個人不會來了，我還是回去吧。\n$N悄沒聲息地向遠處走了開去。\n",this_object());
                destruct(me);
        }
}
