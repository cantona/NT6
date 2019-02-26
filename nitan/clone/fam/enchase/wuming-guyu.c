inherit ITEM;
#include <ansi.h>

#define CMD_JD   HIY + "jianding " + query("id") + HIC

void create()
{
        set_name(HIC "無名古玉" NOR, ({"wuming guyu", "wuming", "guyu"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", HIC "這是一塊不知名的古玉，看上去非常古老，不知產於哪一年代。\n" HIG
                                "需要通過鑑定，此玉的真面目才能顯現，鑑定後可隨機出現以下玉石之一：\n" HIB
                                "古玄玉（1級）、古玄玉（2級）、古玄玉（3級）\n" HIW
                                "玄冰石（1級）、玄冰石（2級）、玄冰石（3級）\n" HIR 
                                "鑑定前請確認你的揹包中的負重至少剩餘5% 。\n" HIC
                                "在揚州魯班處，輸入指令 " + CMD_JD + " 來請求魯班鑑定無名古玉。\n" NOR);
                        
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

void init()
{
        add_action("do_jianding", "jianding");
}

int do_jianding(string arg)
{
        object me, env;
        object yu;        
        int ran_point;
        
        me = this_player();
        
        
        if (! arg || arg != query("id"))
                return notify_fail("你想鑑定什麼？\n");
                
                        
        env = environment(me);
        
        if (base_name(env) != "/d/room/xiaoyuan")
                return notify_fail("這個物品好像只有魯班才能鑑定，你還是上他那去吧。\n");
                
        message_vision(HIY "$N拿出" + name() + HIY "讓魯班鑑定。\n", me);
        
        
        // 開始鑑定
        /*40%機率鑑定出1級白玉或黑玉1塊
          35%機率鑑定出2級白玉或黑玉1塊
          25%機率鑑定出3級白玉或黑玉1塊
        */
        ran_point = 1 + random(100);
        if (ran_point > 60)
        {
                if (random(2))
                {
                        yu = new("/clone/fam/enchase/guxuan-yu1");
                }
                else
                {
                        yu = new("/clone/fam/enchase/xuanbing-shi1");
                }
        }
        else if (ran_point > 0 && ran_point <= 35)
        {
                if (random(2))
                {
                        yu = new("/clone/fam/enchase/guxuan-yu2");
                }
                else
                {
                        yu = new("/clone/fam/enchase/xuanbing-shi2");
                }                
        }
        else
        {
                if (random(2))
                {
                        yu = new("/clone/fam/enchase/guxuan-yu3");
                }
                else
                {
                        yu = new("/clone/fam/enchase/xuanbing-shi3");
                }                
        }

        tell_object(me, HIG "魯班將鑑定後的玉石交給你。\n" NOR);

        yu->move(me, 1);
        
        destruct(this_object());
        
        return 1;
}

