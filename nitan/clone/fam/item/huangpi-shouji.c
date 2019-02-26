
#include <ansi.h>

inherit ITEM;

mixed check_title(string arg)
{
    arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);

        if (strlen(filter_color(arg)) > 30 || strlen(arg) > 100)
                return notify_fail("這個外號太長了，為了節約資源，請你重新設定。\n");

    return arg + NOR;
}

void create()
{
        set_name(NOR + YEL "《黃皮手記》" NOR, ({ "huangpi shouji" }) );
        set_weight(100);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "這是一本泛黃的皮冊子，裏面記載着如何修改您的頭銜的祕訣。\n"
                                                "使用後可修改您的頭銜（TITLE），指令：retitle 頭銜 即可。\n" 
                                                                "下線丟失:否\n" 
                                                        "顏色定義，您可以在您的頭銜中加入指定顏色：\n"
                                                                "$BLK$ - 黑色      $NOR$ - 恢復正常顏色\n"
                                                                "$RED$ - 紅色      $HIR$ - 亮紅色\n"
                                                                "$GRN$ - 綠色      $HIG$ - 亮綠色\n"
                                                                "$YEL$ - 土黃色    $HIY$ - 黃色\n"
                                                                "$BLU$ - 深藍色    $HIB$ - 藍色\n"
                                                                "$MAG$ - 淺紫色    $HIM$ - 粉紅色\n"
                                                                "$CYN$ - 藍綠色    $HIC$ - 天青色\n"
                                                                "$WHT$ - 淺灰色    $HIW$ - 白色（或淡紫色）\n\n"
                                                                "根據系統的不同，以上顏色定義有一定偏差。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                        set("unit", "本");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_retitle", "retitle");
        }
}

int do_retitle(string arg)
{
                object me;

                me = this_player();

                if (! arg)return notify_fail("指令格式: retitle 頭銜\n");

        if (! stringp(arg = check_title(arg)))return 1;

                me->set("title", arg);

                me->save();

                write(HIG "修改頭銜成功！您現在的江湖稱號是：" + arg + "。\n" NOR);

                destruct(this_object());

                return 1;
}

int query_autoload()
{
         return 1;
}
