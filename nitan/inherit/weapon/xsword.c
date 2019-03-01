// xsword.c
#include <ansi.h>
#include <weapon.h>
#include <music.h>

#ifdef AS_FEATURE
#include <dbase.h>
#else
inherit EQUIP;
#endif

inherit MI_XIAO;

int is_weapon() { return 1; }

varargs void init_xsword(int damage, int flag)
{
        if( clonep(this_object()) ) return;

        set("weapon_prop/damage", damage * 90 / 100);
        set("flag", (int)flag | EDGED | SECONDARY); 
        set("skill_type", "sword");
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "slash", "slice", "thrust" }) );
        }
}

void init()
{
        add_action("play_xiao", "play");
}

string extra_long()
{
        mapping need;
        string str;

        str = HIW "\n物品類型 : 兵器(簫)\n" NOR;
        if (query("bindable"))
        {
                string type;
                int t;

                t = query("bindable");
                if (t == 1) type = "裝備綁定";
                else if (t == 2) type = "拾取幫定";
                else if (t == 3) type = "直接綁定";
                str += sprintf(HIW "綁定類型 : %s\n" NOR, type);
        }
        str += sprintf(HIW "重    量 : %d\n" NOR, this_object()->query_weight());
        str += sprintf(HIW "傷 害 力 : %d\n" NOR, query("weapon_prop/damage"));
        // str += sprintf(HIW "殺    戮 : %d\n" NOR, query("combat/PKS"));
        str += sprintf(HIW "鑲嵌凹槽 : %d\n" NOR, (int)query("enchase/flute"));
        if (mapp(need = query("need")) && sizeof(need))
                foreach (string key in keys(need))
                        str += sprintf(HIW "裝備要求 : %s %d\n" NOR,
                                       to_chinese(key), need[key]);
        /*
        str += sprintf(HIW "使用方式 : 輸入指令 wield %s 裝備。\n", query("id"));
        str += sprintf(HIW "使用方式 : 輸入指令 unwield %s 卸下。\n", query("id"));
        */
        str += sprintf(HIW "下線丟失 : %s\n" NOR,
                       this_object()->query_autoload() ? "否" : "是");

        return str;
}
