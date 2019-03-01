#include <weapon.h>
#include <ansi.h>
inherit TASK;
void create()
{
        set_name(WHT"魯班尺"NOR, ({ "lubanchi" }) );
        set_weight(4000);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "柄");
                set("jungle",1);
                set("material", "iron");
                set("long", @LONG
木匠名師魯班有兩個徒弟，一個笨，一個驕傲自滿和不自量力，他們就是
阿毛和阿發。他們每天跟在魯班身邊，紮實地學不少手藝。但阿發因為驕
傲自滿，所以他一個人離開了師傅，只剩下阿毛跟在師傅身邊。阿毛是阿
發的弟弟，他雖然笨，但勤力向上用心學習，每天手持魯班尺在大小佛塔
上量尺寸。因此阿毛量尺寸非常準確。每當阿毛手持魯班尺時，他便想起
他的師傅如何用心地教他。阿毛手上的魯班尺就像他身體的一部份，寸步
不離。阿毛死後，這把魯班尺就不知所蹤了。
LONG);
                set("wield_msg", "$N抽出一把黑油油的$n握在手中。\n");
                set("unequip_msg", "$N將手中的$n插入腰間。\n");
        }
        set("owner", "魯班");
        setup();
}      
