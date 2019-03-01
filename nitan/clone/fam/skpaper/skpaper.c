#include <ansi.h>
inherit ITEM;

string long();

void create()
{
        set_name(NOR + WHT "劍典殘篇" NOR, ({ "jiandian canpian", "jiandian", "canpian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "這是一張殘缺不全的書頁。\n" NOR);
                set("value", 30);
                set("no_sell", "什麼世道，就一張破紙頭也拿來賣錢？");
                set("material", "paper");
                set("skill_name", "基本劍法");      // 研究技能的名稱
                set("skill_type", "sword");         // 研究技能的種類
                set("power_point", 30000);          // 增加技能的點數
                set("need_exp", 300000);            // 研究所需的最低經驗
                set("min_lvl", 100);                // 研究所需的最低等級
                set("max_lvl", 300);                // 能夠研究的最高等級
        }
        setup();
}

void init()
{
        add_action("do_read", "read");
}

string long()
{
        string msg;

        if (query("power_point"))
        {
                msg = WHT "這是一張" + name() + NOR + WHT "，看樣子"
                      "已經頗有年時了。頁片上用隸體密密麻麻寫滿了蠅"
                      "頭小字，似乎都和" + query("skill_name") +
                      "有關，你可以試著讀讀(read)看，也許對武學能夠"
                      "有所幫助。";
        } else
                msg = "這是一張殘缺不全的書頁，可字跡已無法辨清了。";

        return sort_string(msg, 54);
}

int do_read(string arg)
{
        object me = this_player();
        mapping my = me->query_entire_dbase();

        int na = this_object()->name();
        string booksk=query("skill_type", this_object());

        if (me->is_busy())
                return notify_fail("你現在正在忙。\n");

        if (me->is_fighting())
                return notify_fail("戰鬥中無法研讀新知。\n");

        if (arg && id(arg))
        {
                if( query("combat_exp", me)<query("need_exp") )
                        return notify_fail("你覺得殘頁上記載的東西太過深奧，憑自"
                                           "己的武學似乎難以參詳。\n");

                if (me->query_skill(booksk, 1) < query("min_lvl"))
                        return notify_fail("你覺得自己對這項技能的了解尚過淺薄，"
                                           "一時無法參詳透徹。\n");

                if (me->query_skill(booksk, 1) >= query("max_lvl"))
                        return notify_fail("你覺得殘頁上記載的東西太過淺顯，無法"
                                           "從中獲得任何幫助。\n");

                if (! me->can_improve_skill(booksk))
                        return notify_fail("你參詳了半天，發覺似乎是由于自身經驗"
                                           "不足的緣故，很多東西無法理解。\n");

                message_vision(HIW "$N" HIW "聚精會神地閱讀「" NOR + na + HIW
                               "」上所記載的東西，似乎有所收獲。\n" NOR, me);

                if (me->can_improve_skill(booksk))
                        me->improve_skill(booksk, query("power_point"));

                tell_object(me, HIY "你只覺以前存在的諸多疑問豁然開朗，對「" +
                                query("skill_name") + "」有了新的感悟。\n" NOR);

                me->start_busy(random(20) + 20);
                destruct(this_object());
                return 1;
        }
}

int query_autoload()
{
        return 1;
}
