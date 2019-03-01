// Code of ShenZhou
#include <weapon.h>
// Jay 10/7/96

inherit STAFF;

void create()
{
        set_name("蛇杖", ({ "shezhang", "staff", "zhang" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "一根長約七尺的黑光錚亮的鋼杖，杖端有一個蛇頭，"
                "有機關可射出毒針傷人。\n");
                set("value", 450);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中，杖端的蛇頭呲呲做響。\n");
                set("unwield_msg", "$N將手中的$n放了下來。\n");
        }
        init_staff(35);
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
        if (!present("shezhang", me)) 
                return notify_fail("你身上沒有蛇杖。\n");

        if (random(me->query_skill("training",1)) <20) {
        message_vision("$N手握蛇杖手舞足蹈，好像發瘋一般。\n"
                ,me);
                me->receive_damage("jing", 95);
                return 1;
        }
        message_vision("$N手握蛇杖手舞足蹈，猛地往地上一摔，將蛇杖化為一條毒蛇。\n",
                me,);
                ob = new("/d/baituo/npc/snake");
        ob->move(environment(me));
        destruct(this_object());
        return 1;
}
