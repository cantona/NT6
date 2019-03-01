#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "虎虎生威新年紅包" NOR, ({ "hongbao2010"}) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "這一是個新年紅包，上面用金色的字體寫著" HIY "「虎年快樂，虎虎生威」" HIR " ！\n"
                                "拆開(chai)紅包可以獲得新年壓歲錢及小小的經驗潛能獎勵。並有機會獲得隨機物品一件。\n"
                                "*請于2010年3月15日前使用紅包，過期則使用無效！！！\n\n" NOR);
                set("value", 0);
                set("no_give", 1);
                set("no_sell", 1);
                set("no_store", 1);
                set("no_drop", 1);
                set("unit", "個"); 
        }
}

void init()
{
        add_action("do_chai", "chai");
}

int do_chai(string arg)
{
        object me = this_player();
        string msg;
        int i, exp, pot;
        object obgift;
        
        string *oblist = 
        ({
                "/clone/fam/gift/dex3",
                "/clone/fam/gift/con3",
                "/clone/fam/gift/int3",
                "/clone/fam/gift/str3",
                "/clone/fam/gift/dex2",
                "/clone/fam/gift/con2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/str2",                
                "/clone/fam/max/naobaijin",
                "/clone/fam/item/jintiao",
                "/clone/fam/item/moye-shengfu",
                "/clone/armor/fusang/shenxing-xue",
                "/clone/armor/qilin/jixing",
                "/clone/armor/fudai",
                "/clone/armor/shuixian-erhuan",
                "/clone/armor/dugu/jianmo-zhiyu",
                "/clone/armor/daojian/lengyue",
                "/clone/fam/item/xiling-hu",
                "/clone/fam/item/yuanshenjingyan-guo",
        });

        // 新手村的拿不到
        if (! objectp(me))return 0;

        if (! arg || arg != "hongbao2010")
                return notify_fail("你要拆開什麼？\n");

        if (environment(this_object()) != me)
                return notify_fail("你身上沒有這樣東西呀。\n");

        i = 12010;
        exp = 102010;
        pot = 102010;

        message_vision(HIR "$N一陣興奮，趕緊將紅包拆開，用無比期待地眼神朝紅包內一望，剎那間，一陣光環"
                       "將$N籠罩 ……\n" NOR, me);

        tell_object(me, HIG "恭喜你，獲得了" HIY + chinese_number(exp) + HIG "點實戰經驗、" HIY + chinese_number(pot) + 
                        HIG "點潛能及" HIY + chinese_number(i) + HIG "兩黃金（YSG）。\n炎黃祝您「虎年快樂，虎虎生威」！\n" NOR);

        me->add("stocks/balance", i);
        me->add("combat_exp", exp);
        me->add("potential", pot);

        // 10%機率獲取隨機物品一件
        if (random(10) == 1)
        {
                obgift = new(oblist[random(sizeof(oblist))]);
                if (obgift)
                {
                        tell_object(HIY "恭喜你，從紅包中獲得" + obgift->name() + HIY "，恭喜恭喜！。\n" NOR);
                        CHANNEL_D->do_channel(this_object(), "rumor", "聽說" + me->name() + "開啟新年紅包獲得隨"
                                                                    "機物品" + obgift->name() + HIM "獎勵！\n");  
                        obgift->move(me, 1);
                        log_file("hongbao2010", HIY + me->query("id") + "從紅包中獲得 " + obgift->name() + "。\n" NOR);
                }
        }

        me->save();

        log_file("hongbao2010", me->query("id") + " 于 " + ctime(time()) + " 打開紅包。(/clone/misc/hongbao2010) \n");

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
