#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "喳悃肣﹞栠欂闕﹞懈鏀悃" NOR, ({ "tongren b4", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "跺");
                set("long", NOR + YEL "涴岆珨跺喳悃肣ㄛ奻醱餅秶賸珨虳冪釐悃弇芞偶ㄛ眕摯喳悃妏蚚源楊﹝\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "栠欂闕");
        set("xuewei_name", "懈鏀悃");
        set("chongxue_xiaoguo", "QI:800:AMR:10");
        set("neili_cost", "900");
        setup();
}

