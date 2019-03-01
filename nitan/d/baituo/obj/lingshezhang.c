// Code of ShenZhou
#include <weapon.h>
// kane, 2/9/98

#include <ansi.h>
inherit STAFF;

void create()
{
        set_name(HIW"靈蛇杖"NOR, ({ "lingshe zhang", "staff", "shezhang" }));
        set_weight(4000);  //***** ADDED BY SCATTER *****                 set("wposition", "/d/baituo/obj/lingshezhang.c");
//***** END OF ADDING ***** 
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "一根彎彎曲曲的黑色粗杖，似是鋼鐵所制，\n"+
                "杖頭鑄著個裂口而笑的人頭，人頭口中露出尖利雪白的牙齒，\n"+
                "模樣甚是猙獰詭異，更奇的是杖上盤著兩條銀鱗閃閃的小蛇，不住的蜿蜒上下。\n");
                set("value", 1);
                set("material", "steel");
                set("snake_type","靈蛇");
                set("wield_msg", "$N抽出一根$n握在手中，杖端的銀蛇呲呲做響。\n");
                set("unwield_msg", "$N將手中的$n放了下來。\n");
                set("poison_applied", 100);
        }
        init_staff(550);
        setup();
}

void init()
{
        add_action("convert","bian");
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="shezhang" && arg!="staff" && arg!="zhang") return 0;
        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你不能化杖為蛇。\n");
        if( query("jing", me)<100 )
                return notify_fail("你的精力不夠。\n");
        if (!present("lingshe zhang", me)) 
                return notify_fail("你身上沒有靈蛇杖。\n");

        if (me->query_skill("training",1) < 70+random(70)) {
        message_vision("$N手握靈蛇杖手舞足蹈，好像發瘋一般。\n"
                ,me);
                me->receive_damage("jing", 95);
                return 1;
        }
        message_vision("$N手握靈蛇杖手舞足蹈，猛地往地上一摔，將蛇杖化為一條靈蛇。\n",
                me,);
        ob = new("/d/baituo/npc/lingshe");
        ob->move(environment(me));
        destruct(this_object());
        return 1;
}
