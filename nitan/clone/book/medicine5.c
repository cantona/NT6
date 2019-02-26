// medicine5.c
// Last Modified by Winder on May. 29 2001

#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_kan", "watch");
        add_action("do_kan", "kan");
}

void create()
{
        set_name(HIY"孫思邈千金方"NOR,({"qianjin fang","qianjingfang","fang"}));
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
"\n這是一本『孫思邈千金方』，你可以好好看看(watch)。\n");
                set("value", 50);
                set("material", "paper");
        }
        setup();
}
int do_kan(string arg)
{
        object me = this_player();
        int lvl = me->query_skill("medicine", 1);

        if(!id(arg))
                return notify_fail("你要看什麼？\n");
        if (!present(this_object(), this_player()))
                return 0;

        if (me->is_busy()) {
                write("你現在正忙着呢。\n");
                return 1;
        }
        if ( !me->query_skill("medicine", 1) )
        {
                write("這是醫書。你一竅不通，有啥好看的？\n");
                return 1;
        }
        if( !me->query_skill("literate", 1) )
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }
        write(HIR"                   【黃帝內經】\n");
        write(YEL" 〖江湖珍藥祕方〗\n\n");
                write(HIG"金創藥           川貝、生地、血竭\n");
        if (lvl >= 10)
                write("養精丹           川貝，枸枳子，菊梗\n");
        if (lvl >= 20)
                write("清心散           巴豆，荷葉，菊梗\n");
        if (lvl >= 30)
                write("白虎奪命丹       虎骨、天山雪蓮、茯苓、白芷\n");
        if (lvl >= 40)
                write("白雲熊膽丸       熊膽、白芷、柴胡、沒藥\n");
        if (lvl >= 50)
                write("天香斷續膏       白薇、沒藥、靈芝、靈脂\n");
        if (lvl >= 60)
                write("小還丹           桑葉、當歸、天山雪蓮、藿香\n");
        if (lvl >= 70)
                write("百草丹           穿山甲、甘草、藏紅花\n");
        if (lvl >= 80)
                write("延年聚精丹       天山雪蓮，藏紅花，荷葉\n");
        if (lvl >= 90)
                write("回陽五龍散       何首烏、穿山甲、茯苓、防風、菊梗\n");
        if (lvl >= 100)
                write("黑石玉洞丹       豹胎、防風、熊膽、天山雪蓮\n");
        if (lvl >= 110)
                write("九轉結氣丸       牛黃、蟬蜕、枸枳子、荷葉\n");
        if (lvl >= 120)
                write("九花玉露丸       天山雪蓮、甘草、桃花瓣、荷葉\n");
        if (lvl >= 130)
                write("玉露清新散       荷葉、當歸、白薇、金銀花\n");
        if (lvl >= 140)
                write("三黃寶蠟丸       麻黃、藤黃、雄黃、靈脂\n");
        if (lvl >= 150)
                write("大還丹           荷葉、當歸、天山雪蓮、藿香\n");
        if (lvl >= 160)
                write("續命八丸         人蔘、茯苓、靈芝、鹿茸、何首烏、靈脂、熊膽、三七、麝香\n");
                write("\n"NOR);
        return 1;
}