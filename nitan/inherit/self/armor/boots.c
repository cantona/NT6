// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// armor.c
// 自動創建防具的基準文件。                             /* COMMENT_EXIT  */

#include <armor.h>
inherit BOOTS;

#include <template/armor.h> 
void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("靴", ({ "boots", }));                 /* NAME_EXIT  */

        if (clonep())
                set_default_object(__FILE__);
        else
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "這是一件普通的鞋子。\n");  /* DBASE_EXIT  */
                set("unit", "件");
                set("value", 200);
                set("material", "cloth");
                set("armor_prop/armor", query("point")*2);
        }

        set_weight(500);
        setup();
}

