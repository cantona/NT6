#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "紅包" NOR, ({ "hongbao"}) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "這一是個新年紅包，上面用金色的字體寫着" HIY "「豬年吉祥 萬事如意」" HIR " ！\n"
                                "拆開(chai)紅包可以獲得新年壓歲錢及小小的經驗潛能獎勵。\n"
                                "*請於2007年4月28日前使用紅包，過期則使用無效！！！\n\n" NOR);
                set("value", 1);
                set("unit", "個"); 
        }
}

void init()
{
        //add_action("do_chai", "chai");
}

int do_chai(string arg)
{
        object me = this_player();
        string msg;
        int i, exp, pot;
        
        // 新手村的拿不到
        
        if (! objectp(me))return 0;
        
        if (! arg || arg != "hongbao")
                return notify_fail("你要拆開什麼？\n");
                
        if (environment(this_object()) != me)
                return notify_fail("你身上沒有這樣東西呀。\n");
                
        i = 8000 + random(2000);
        exp = 80000 + random(20001);
        pot = 80000 + random(20001);

        message_vision(HIR "$N一陣興奮，趕緊將紅包拆開，用無比期待地眼神朝紅包內一望，剎那間，一陣光環"
                       "將$N籠罩 ……\n" NOR, me);
        
        tell_object(me, HIG "恭喜你，獲得了" HIY + chinese_number(exp) + HIG "點實戰經驗、" HIY + chinese_number(pot) + 
                        HIG "點潛能及" HIY + chinese_number(i) + HIG "兩黃金（YSG）。\n炎黃祝您「豬年吉祥 萬事如意」！\n" NOR);
        
        me->add("stocks/balance", i);
        me->add("combat_exp", exp);
        me->add("potential", pot);
        
        me->save();
        
        log_file("hongbao", me->query("id") + " 於 " + ctime(time()) + " 打開紅包。(/clone/misc/hongbao) \n");

        destruct(this_object());
        return 1;
}
/*
int query_autoload()
{
        return 1;
}
*/