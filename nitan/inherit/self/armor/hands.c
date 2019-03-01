// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// armor.c
// 自動創建防具的基準文件。                             /* COMMENT_EXIT  */

#include <armor.h>
inherit HANDS;

void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("掌套", ({ "hands", }));               /* NAME_EXIT  */

        if (clonep())
                set_default_object(__FILE__);
        else
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "這是一件普通的掌套。\n");  /* DBASE_EXIT  */
                set("unit", "件");
                set("value", 200);
                set("material", "cloth");
                set("armor_prop/armor", query("point")*2);
        }

        set_weight(500);
        setup();
}

string long() { return short() + (query("make_info")?query("make_info"):"\n") + query("long"); }

int do_touch(object me)
{
        if (this_object()->query("combine_to") != "green" &&
            this_object()->query("combine_to") != "ultimate")
                return notify_fail("你摸了半天，好像沒什麼反應。\n");

        return ITEM_D->do_touch(me, this_object());
}

