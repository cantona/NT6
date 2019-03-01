// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// armor.c
// 自動創建防具的基準文件。                             /* COMMENT_EXIT  */

#include <armor.h>
inherit NECK;

#include <template/armor.h>
void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("項鏈", ({ "neck", }));                /* NAME_EXIT  */ 

        if (clonep())
                set_default_object(__FILE__);
        else
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "這是一個普通的項鏈。\n");  /* DBASE_EXIT  */
                set("unit", "個");
                set("value", 200);
                set("material", "gold");
                set("armor_prop/armor", 1);
        }

        set_weight(200);
        setup();
}
