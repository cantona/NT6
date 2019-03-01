#include <ansi.h>
#include <armor.h>

inherit F_OBSAVE;
inherit ARMOR;

void create()
{
        set_name(HIR "龍象袈裟" NOR, ({ "longxiang jiasha", "longxiang", "jiasha" }));
        set_weight(8000);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "件");
                set("long", HIR "這是一件陳舊的袈裟，通體血紅，印有龍象紋樣。著"
                            "手處堅韌\n無比，想必是由金剛絲混及雪蠶絲編織而成。"
                            "更有傳聞說密宗\n神功龍象般若功便是記載于這件袈裟之"
                            "上。\n" NOR);
                set("value", 100000);
                set("no_sell", "我…我的天…蒙古國師的衣服你也敢拿來賣？");
                set("material", "cloth");
                set("wear_msg", HIY "$N" HIY "展開$n" HIY "，霎時金波流轉，罡氣"
                                "籠罩全身。\n" NOR);
                set("armor_prop/armor", 200);
                set("skill", ([
                        "name" : "longxiang-gong",
                        "exp_required" : 1000000,
                        "jing_cost"    : 200,
                        "difficulty"   : 80,
                        "max_skill"    : 299,
                        "min_skill"    : 210,
                        "need"         : ([ "sanscrit" : 200 ]),
                ]));
                // 初始抵擋次數設定為十三，裝備後可以抵擋十三道任何攻擊。
                // 以後每注入一次內力可以多抵擋一次攻擊，最多可為十三次。
                set("force", 13);
                set("stable", 100);
        }
        setup();
}

void init()
{
        add_action("do_force", "force");
}

int do_force(string arg)
{
        object me = this_player();

        if (! arg || ! id(arg))
                return notify_fail("你打算往哪裡注入內力？\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，哪有時間忙這個？\n"); 

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n"); 

        if (query("equipped"))
                return notify_fail("你必須先將" + name() + "脫下。\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 280)
                return notify_fail("你龍象般若功修為不夠，難以將真氣注入袈裟。\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("你沒有激發龍象般若功，難以將真氣注入袈裟。\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("你目前的內力修為不夠，難以將真氣注入袈裟。\n");

        if( query("neili", me)<query("max_neili", me) )
                return notify_fail("你目前的內力尚不飽滿，難以將真氣注入袈裟。\n");

        if (query("force") >= 13)
                return notify_fail("現在袈裟已然膨脹，無法再容納更多的內力。\n");

        set("neili", 0, me);
        addn("max_neili", -5, me);
        me->start_busy(5);
        addn("force", 1);
        message_sort(HIY "\n$N" HIY "微一凝神，默默運聚龍象般若功勁力，雙掌緊"
                     "緊壓住" + name() + HIY "兩側。過得片刻" + name() + HIY
                     "竟然漸漸膨起，似乎已將內力盡數納入其中。$N" HIY "見狀趕"
                     "忙收回雙掌，臉色變了變，真氣有所衰竭。\n\n" NOR, me);
        return 1;
}

mixed valid_damage(object ob, object me, int damage)
{
        if (query("force") > 0)
        {
                addn("force", -1);
                return ([ "damage" : -damage,
                          "msg" : HIY "霎時只見" + name() + HIY "上一道光華閃"
                                  "過，竟然將$N" HIY "這一招化于無形。\n" NOR ]);
        }
}

// 進行保存數據的接口函數
mixed save_dbase_data()
{
        mapping data;

        data = ([ "force" : query("force") ]);

        return data;
}

// 接受存盤數據的接口函數
int receive_dbase_data(mixed data)
{
        if (! mapp(data))
                return 0;

        if (! undefinedp(data["force"]))
        {
                set("force", data["force"]);
        }
        return 1;
}

