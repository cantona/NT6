#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
        set_name(HIW "神虎戰甲" NOR, ({ "shenhu zhanjia", "shenhu", "zhanjia" }));
        set_weight(6000);
        if (clonep())set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", HIW "\n一張投射着奇異光芒的戰甲，乃天地間的極品。\n" NOR
                            HIG "有效招架修正：+ 70        有效輕功修正：+ 10\n" NOR
                            HIG "抗毒效果修正：+ 20%       防禦效果等級： 220\n" NOR
                            HIG "抗毒迴避修正：+ 20%\n" NOR);
                set("value", 2000000);
                set("material", "tiger");

                set("material_name", "白虎骨、白虎筋、白虎皮、如意通天钁");
                set("can_summon", 1);
                set("summon_id", "shenhujia");
                set("ctype", "護甲");
                set("summon_wear_msg", HIW "剎那間，風聲驟起，山洪咆哮，天際處一道白光\n"
                                       "劃過，漸漸地與$N" HIW "合為一體。\n" NOR);
                set("summon_remove_msg", HIW "風雨漸息，一隻白虎騰空而起，消失在天際。\n" NOR);
                set("armor_prop/armor", 350);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 70);
                set("armor_prop/reduce_poison", 20); // 提高30%抗毒效果
                set("armor_prop/avoid_poison", 20); // 提高20%迴避效果

        }
        setup();
}

int query_autoload()
{
        return 1;
}