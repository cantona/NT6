// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// armor.c
// 自動創建防具的基準文件。                             /* COMMENT_EXIT  */

#include <armor.h>
inherit CHARM;

#include <template/armor.h>
void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("護身符", ({ "charm", }));                /* NAME_EXIT  */ 

        if (clonep())
                set_default_object(__FILE__);
        else
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "這是一個普通的護身符。\n");  /* DBASE_EXIT  */
                set("unit", "個");
                set("value", 200);
                set("material", "stone");
                set("armor_prop/armor", 1);
        }

        set_weight(200);
        setup();
}
